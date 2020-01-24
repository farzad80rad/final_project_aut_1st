#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "visual_map.h"
#include "cells.h"
#include <time.h>
#include "move.h"



enum chars_map {frame=' ', Energy='1',Mitosis='2',Forbidden='3',Normal='4'};


void multiplay_game(void)
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
    do{
    printf("enter count of cells_the limitation is 10 \n");
    scanf("%d",&count_cells);
    }while(count_cells>9);


    list = make_add_random(count_cells,n,visual_map,40);
    list2 = make_add_random(count_cells,n,visual_map,40);
    system("cls");

    printing_map(n,visual_map,list,list2);
    for (CELL * current=list;current!=NULL;current=current->next){
         SetConsoleTextAttribute(hConsole, 6);
        printf("%d- coordinate(%d,%d)  name:%7s      energy=%d \n",current->number,n-(current->y-2)/4 - 1,(current->x-4)/8,current->name,current->enerjy);
         SetConsoleTextAttribute(hConsole, originalAttrs);
    }

    printf("\n");
     for (CELL * current=list2;current!=NULL;current=current->next){
            SetConsoleTextAttribute(hConsole, 9);
        printf("%d- coordinate(%d,%d)  name:%7s      energy=%d \n",current->number,n-(current->y-2)/4 - 1,(current->x-4)/8,current->name,current->enerjy);
        SetConsoleTextAttribute(hConsole, originalAttrs);

     }
}


void single_game(void)
{
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
    do{
    printf("enter count of cells_the limitation is 10 \n");
    scanf("%d",&count_cells);
    }while(count_cells>9);


    list = make_add_random(count_cells,n,visual_map,40);
    int oper=1;
    int cell_choosed;

            system("cls");
    printing_map(n,visual_map,list,list2);
    while(oper!=4){
            printf(" [1]Move\n[2]Split a cell\n[3]Boost energy\n[4]Save\n[5]Exit\n");
    //printf("enter oper\n");
    scanf("%d",&oper);
    system("cls");
    printing_map(n,visual_map,list,list2);
    CELL * current;

    for ( current=list;current!=NULL;current=current->next)
        printf("%d- coordinate(%d,%d)  name:%7s      energy=%d \n",current->number,n-(current->y-2)/4 - 1,(current->x-4)/8,current->name,current->enerjy);
    printf("choose a cell\n");
    scanf("%d",&cell_choosed);

    for ( current=list;current->number!=cell_choosed;current=current->next);

    move(current,n,visual_map,list,list2);
    system("cls");
    printing_map(n,visual_map,list,list2);
    }
}


int main()
{
    srand(time(0));
    int a;
    printf("1- load\n2- new single game\n3- new multi player game\n4- exit\n");
    scanf("%d",&a);
    if (a==2)
    {
       single_game();
    }

    if (a==1)
    {

    }

    if(a==3)
    {
      multiplay_game();
    }

    if(a==4)
    {

    }


}
