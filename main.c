#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "visual_map.h"
#include "cells.h"
#include <time.h>
#include "move.h"
#include "load_save.h"
#include "map_editor.h"



enum chars_map {frame=' ', Energy='1',Mitosis='2',Forbidden='3',Normal='4'};

// for single mode : move the specific cell by searching for its number in list.
void movment_1(int n, PLACE visual_map[3+4*n][1+8*n], CELL *list,CELL *list2,int  cell_choosed)
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo);
    int originalAttrs = ConsoleInfo.wAttributes;
    CELL * current;

    for ( current=list; current->number!=cell_choosed; current=current->next);

    move(current,n,visual_map,list,list2);
    system("cls");
    printing_map(n,visual_map,list,list2);
}

/*for multi player mode. works like the above function . this illustrates the player by "turn".
 turn is send as pointer for the time the movement action fails so the turn should not change.therefore we
 add 1 to the turn if the action fails.*/
void movment_2(int n, PLACE visual_map[3+4*n][1+8*n], CELL *list,CELL *list2,int * turn,int cell_choosed)
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo);
    int originalAttrs = ConsoleInfo.wAttributes;

    CELL * current;

    if(*turn %2==1)
    {
        for ( current=list; current->number!=cell_choosed; current=current->next);

        *turn+=move(current,n,visual_map,list,list2);
        system("cls");
        printing_map(n,visual_map,list,list2);
    }

    else
    {
        for ( current=list2; current->number!=cell_choosed; current=current->next);

        *turn+= move(current,n,visual_map,list,list2);
        system("cls");
        printing_map(n,visual_map,list,list2);
    }
}



void  load_mood_game_1(int n,CELL* list,PLACE visual_map[3+4*n][1+8*n] )
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo);

    int originalAttrs = ConsoleInfo.wAttributes;
    int oper=1 , flag =1 , cell_choosed , count_cells=0;
    CELL *list2=NULL;

    for(CELL * current = list; current != NULL; current=current->next)
        count_cells++;

    system("cls");
    printing_map(n,visual_map,list,list2);

    while(flag)
    {
        for (CELL * current=list; current!= NULL; current=current->next)
        {
            SetConsoleTextAttribute(hConsole, 6);
            printf("%d- coordinate(%d,%d)  name:%7s      energy=%d \n",current->number,n-(current->y-2)/4 - 1,(current->x-4)/8,current->name,current->enerjy);
            SetConsoleTextAttribute(hConsole, originalAttrs);
        }

        int temp_count;
        int cell_choosed;
        printf("choose a cell\n");
        scanf("%d",&cell_choosed);

        printf("[1]Move\n[2]Split a cell\n[3]Boost energy\n[4]Save\n[5]Exit\n");
        scanf("%d",&oper);

        switch (oper)
        {
        case 1:

            movment_1(n,visual_map,list,list2,cell_choosed);
            break;

        case 2:

            temp_count = mitosis_action(n,visual_map,list,list2,1,cell_choosed,count_cells,count_cells);
            count_cells+=temp_count;
            if(temp_count==0)
                continue;
            system("cls");
            printing_map(n,visual_map,list,list2);
            break;

        case 3:

            if( boost_enerjy(cell_choosed,n,visual_map,list,list2,1) )
            {
                system("cls");
                printing_map(n,visual_map,list,list2);
                printf("not allowed\n");
                continue;
            }
            system("cls");
            printing_map(n,visual_map,list,list2);
            break;

        case 4:

            save_map(n,visual_map);
            save_player(list,count_cells,1);
            save_mood(1,1);
            system("cls");
            printing_map(n,visual_map,list,list2);
            break;

        case 5:

            flag=0;
            break;

        default:
            printf("not valid operand.\n");
        }
    }
    system("cls");
}


void load_mood_game_2(int n,CELL * list,CELL * list2,PLACE visual_map[3+4*n][1+8*n],int turn)
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo);
    int originalAttrs = ConsoleInfo.wAttributes;
    int cell_choosed,oper=1,flag =1;

    system("cls");
    printing_map(n,visual_map,list,list2);

    int count_cell1=0,count_cell2=0;

    for(CELL * current = list; current != NULL; current=current->next)
        count_cell1++;

    for(CELL * current = list2; current != NULL; current=current->next)
        count_cell2++;

    system("cls");
    printing_map(n,visual_map,list,list2);

    while(flag)
    {
        if(turn%2 == 0)
        {
            SetConsoleTextAttribute(hConsole, 9);
            printf("turn of player 2 \n");

            for (CELL * current=list2; current!=NULL; current=current->next)
                printf("%d- coordinate(%d,%d)  name:%8s      energy=%d \n",current->number,n-(current->y-2)/4 - 1,(current->x-4)/8,current->name,current->enerjy);

            printf("\n");
            SetConsoleTextAttribute(hConsole, originalAttrs);
        }
        else
        {

            SetConsoleTextAttribute(hConsole, 6);
            printf("tern of player 1\n");

            for (CELL * current=list; current!=NULL; current=current->next)
                printf("%d- coordinate(%d,%d)  name:%8s      energy=%d \n",current->number,n-(current->y-2)/4 - 1,(current->x-4)/8,current->name,current->enerjy);

            SetConsoleTextAttribute(hConsole, originalAttrs);
        }

        printf("choose a cell\n");
        scanf("%d",&cell_choosed);

        printf("[1]Move\n[2]Split a cell\n[3]Boost energy\n[4]Save\n[5]Exit\n");
        scanf("%d",&oper);

        // this is for the time of mitosis action in which we need to add the cells.
        int temp_count;

        switch (oper)
        {
        case 1:

            movment_2(n,visual_map,list,list2,&turn,cell_choosed);
            break;

        case 2:

            temp_count = mitosis_action(n,visual_map,list,list2,turn,cell_choosed,count_cell1,count_cell2);
            if(turn%2==1)
                count_cell1 += temp_count;
            else
                count_cell2 += temp_count;

            if(temp_count==0)
                continue;

            system("cls");
            printing_map(n,visual_map,list,list2);
            break;

        case 3:

            if( boost_enerjy(cell_choosed,n,visual_map,list,list2,turn) )
            {
                system("cls");
                printing_map(n,visual_map,list,list2);
                printf("not allowed\n");
                continue;
            }
            system("cls");
            printing_map(n,visual_map,list,list2);
            break;

        case 4:

            save_map(n,visual_map);
            save_player(list,count_cell1,1);
            save_player(list2,count_cell2,2);
            save_mood(2,turn);

            turn++;
            system("cls");
            printing_map(n,visual_map,list,list2);
            break;

        case 5:

            flag=0;
            break;
        }
        // this would be ignored if the function above face the "continue" .
        turn++;
    }
    system("cls");
}



void multiplay_game(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo);
    int originalAttrs = ConsoleInfo.wAttributes;


    system("cls");
    int n, count_cells;
    char file_name[50];
    char *str;

    printf("enter map file name\n");
    scanf("%s",file_name);

    // this scans the int 'n' from the file.
    n = find_elements_count(file_name);

    str = read_binary(file_name,n);

    PLACE visual_map[3+4*n][1+8*n];
    init_table(n,file_name,str,visual_map);
    CELL* list=NULL;
    CELL* list2=NULL;

    printing_map(n,visual_map,list,list2);

    do
    {
        printf("enter count of cells _ the limitation is 10 \n");
        scanf("%d",&count_cells);
    }
    while(count_cells>9);

    list  = make_add_random(count_cells,n,visual_map,40);
    list2 = make_add_random(count_cells,n,visual_map,40);

    int count_cell1,count_cell2;
    count_cell1=count_cell2=count_cells;

    int cell_choosed, oper=1, turn=1, flag=1;

    system("cls");
    printing_map(n,visual_map,list,list2);
    while(flag)
    {
        if(turn%2==0)
        {
            SetConsoleTextAttribute(hConsole, 9);
            printf("tern of player 2\n");

            for (CELL * current=list2; current!=NULL; current=current->next)
                printf("%d- coordinate(%d,%d)  name:%7s      energy=%d \n",current->number,n-(current->y-2)/4 - 1,(current->x-4)/8,current->name,current->enerjy);

            printf("\n");
            SetConsoleTextAttribute(hConsole, originalAttrs);
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 6);
            printf("tern of player 1\n");

            for (CELL * current=list; current!=NULL; current=current->next)
                printf("%d- coordinate(%d,%d)  name:%7s      energy=%d \n",current->number,n-(current->y-2)/4 - 1,(current->x-4)/8,current->name,current->enerjy);

            SetConsoleTextAttribute(hConsole, originalAttrs);
        }

        printf("choose a cell\n");
        scanf("%d",&cell_choosed);

        printf("[1]Move\n[2]Split a cell\n[3]Boost energy\n[4]Save\n[5]Exit\n");
        scanf("%d",&oper);

        int temp_count;
        switch (oper)
        {
        case 1:

            movment_2(n,visual_map,list,list2,&turn,cell_choosed);
            break;

        case 2:

            temp_count = mitosis_action(n,visual_map,list,list2,turn,cell_choosed,count_cell1,count_cell2);

            if(turn%2==1)
                count_cell1+=temp_count;
            else
                count_cell2+=temp_count;

            if(temp_count==0)
                continue;

            system("cls");
            printing_map(n,visual_map,list,list2);
            break;

        case 3:

            if( boost_enerjy(cell_choosed,n,visual_map,list,list2,turn) )
            {
                system("cls");
                printing_map(n,visual_map,list,list2);
                printf("not allowed\n");
                continue;
            }
            system("cls");
            printing_map(n,visual_map,list,list2);
            break;

        case 4:
            save_map(n,visual_map);
            save_player(list,count_cell1,1);
            save_player(list2,count_cell2,2);
            save_mood(2,turn);
            turn++;
            system("cls");
            printing_map(n,visual_map,list,list2);
            break;

        case 5:

            flag=0;
            break;
        }
        turn++;
    }
    system("cls");
}


void single_game(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo);
    int originalAttrs = ConsoleInfo.wAttributes;

    system("cls");
    int n;
    printf("enter map file name\n");
    char file_name[50];
    scanf("%s",file_name);
    n=find_elements_count(file_name);

    char *str;
    str = read_binary(file_name,n);

    PLACE visual_map[3+4*n][1+8*n];
    init_table(n,file_name,str,visual_map);
    CELL* list=NULL;
    CELL* list2=NULL;


    printing_map(n,visual_map,list,list2);


    int count_cells;
    do
    {
        printf("enter count of cells_the limitation is 10 \n");
        scanf("%d",&count_cells);
    }
    while(count_cells>9);


    list = make_add_random(count_cells,n,visual_map,40);
    int oper=1,flag =1;
    int cell_choosed;

    system("cls");
    printing_map(n,visual_map,list,list2);
    while(flag)
    {

        for (CELL * current=list; current!=NULL; current=current->next)
        {
            SetConsoleTextAttribute(hConsole, 6);
            printf("%d- coordinate(%d,%d)  name:%7s      energy=%d \n",current->number,n-(current->y-2)/4 - 1,(current->x-4)/8,current->name,current->enerjy);
            SetConsoleTextAttribute(hConsole, originalAttrs);
        }

        int temp_count;
        int cell_choosed;
        printf("choose a cell\n");
        scanf("%d",&cell_choosed);


        printf("[1]Move\n[2]Split a cell\n[3]Boost energy\n[4]Save\n[5]Exit\n");
        scanf("%d",&oper);
        switch (oper)
        {
        case 1:

            movment_1(n,visual_map,list,list2,cell_choosed);
            break;

        case 2:

            temp_count = mitosis_action(n,visual_map,list,list2,1,cell_choosed,count_cells,count_cells);
            count_cells+=temp_count;
            if(temp_count==0)
                continue;
            system("cls");
            printing_map(n,visual_map,list,list2);
            break;

        case 3:

            if(boost_enerjy(cell_choosed,n,visual_map,list,list2,1))
            {
                system("cls");
                printing_map(n,visual_map,list,list2);
                printf("not allowed\n");
                continue;
            }
            system("cls");
            printing_map(n,visual_map,list,list2);
            break;

        case 4:

            save_map(n,visual_map);
            save_player(list,count_cells,1);
            save_mood(1,1);
            break;

        case 5:

            flag=0;
            break;
        }
    }
    system("cls");
}


int main()
{
    srand(time(0));
    int a;
    while(1)
    {
        system("cls");
        printf("1- load\n2- new single game\n3- new multi player game\n4- map_editor\n5- exit\n");
        scanf("%d",&a);
        if (a==2)
            single_game();

        if (a==1)
        {
            int turn;
            CELL *list=NULL,*list2=NULL;
            int n,mood;
            n=scan_n();
            PLACE visual_map[3+4*n][1+8*n];

            load_map(&n,visual_map);
            mood = load_mood();

            load_player(&list,1);
            if(mood==2)
            {
                load_player(&list2,2);
                turn = load_turn();

            }

            if(mood==1)
                load_mood_game_1(n,list,visual_map);
            if (mood ==2)
                load_mood_game_2(n,list,list2,visual_map,turn);


        }

        if(a==3)
            multiplay_game();
        if(a==4){
            system("cls");
        make_map();
        }
        if(a==5)
            break;
    }

}
