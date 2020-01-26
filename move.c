#include <stdio.h>
#include <windows.h>
#include "visual_map.h"
#include <string.h>
#include <stdlib.h>
#include "cells.h"
#include <time.h>


enum chars_map { frame=' ', Energy='1',Mitosis='2',Forbidden='3',Normal='4'};

int permision_move(CELL * cell_move,int n,PLACE visual_map[3+4*n][1+8*n],int oper)
{
    switch(oper)
    {
    case 1:
        if(visual_map[cell_move->y-4][cell_move->x].fullnes==1 || cell_move->y-4<=1)
            return 1;
        break;
    case 2:
        if(visual_map[cell_move->y+4][cell_move->x].fullnes==1 || cell_move->y+4 >= 2+4*n)
            return 1;
        break;
    case 3:
        if(visual_map[cell_move->y-2][cell_move->x+8].fullnes==1  || cell_move->y-2<=1 || cell_move->x+8>=8*n )
            return 1;
        break;
    case 4:
        if(visual_map[cell_move->y-2][cell_move->x-8].fullnes==1  ||  cell_move->y-2<=1 || cell_move->x-8<=0 )
            return 1;
        break;
    case 5:
        if(visual_map[cell_move->y+2][cell_move->x+8].fullnes==1 ||  cell_move->y+2>=2+4*n || cell_move->x+8>=8*n )
            return 1;
        break;
    case 6:
        if(visual_map[cell_move->y+2][cell_move->x-8].fullnes==1  || cell_move->y+2>=2+4*n || cell_move->x-8<=1)
            return 1;
        break;
    }
    return 0;

}


int boost_enerjy(int  cell_choosed,int n,PLACE  visual_map[3+4*n][1+8*n],CELL * list,CELL *list2,int turn)
{
    CELL * cell_gain;
    if(turn%2==1)
        for ( cell_gain=list; cell_gain->number!=cell_choosed; cell_gain=cell_gain->next);
    else
        for ( cell_gain=list2; cell_gain->number!=cell_choosed; cell_gain=cell_gain->next);
    if(cell_gain->enerjy==100)
        return -1;


    int temp_enerj;
    sscanf(visual_map[cell_gain->y][cell_gain->x].score,"%d",&temp_enerj);

    if(temp_enerj==0)
        return -1;

    if(temp_enerj > 15)
    {

        if(cell_gain->enerjy<=85)
        {
            temp_enerj-= 15;
            cell_gain->enerjy+=15;
        }
        else
        {
            temp_enerj -= 100-cell_gain->enerjy;
            cell_gain->enerjy=100;
        }
    }

    else
    {
        cell_gain->enerjy+=temp_enerj;
        temp_enerj  = 0;
    }
    char temp_str[4];
    sprintf(temp_str,"%d",temp_enerj);
    strcpy(visual_map[cell_gain->y][cell_gain->x].score,temp_str);
    return 0;

    system("cls");
    printing_map(n,visual_map,list,list2);

}

CELL * make_add_nod(int xi,int yi,CELL * list,int count_cells)
{
    CELL * new_nod;
    new_nod = (CELL *) malloc(sizeof(CELL));
    new_nod->next=NULL;
    new_nod->enerjy=40;
    new_nod->x=xi;
    new_nod->y=yi;
    new_nod->number=count_cells+1;
    naming(new_nod->name,count_cells);

    CELL * current;
    for( current= list; current->next!=NULL; current=current->next);
    current->next=new_nod;
    return new_nod;

}

int find_empty(int x, int y,int n,PLACE visual_map[3+4*n][1+8*n])
{
    if((visual_map[y-4][x].fullnes==0 ) || visual_map[y+4][x].fullnes==0 )
        return 0;
    if(visual_map[y-2][x+8].fullnes==0 || visual_map[y+2][x+8].fullnes==0 )
        return 0;
    if(visual_map[y-2][x-8].fullnes==0 || visual_map[y+2][x-8].fullnes==0 )
        return 0;
    return 1;
}


CELL * move_mitos(CELL * cell_move,int n,PLACE visual_map[3+4*n][1+8*n],int oper)
{
    switch(oper)
    {
    case 1:
        cell_move->y-=4;
        break;
    case 2:
        cell_move->y+=4;
        break;
    case 3:
        cell_move->y-=2;
        cell_move->x+=8;
        break;
    case 4:
        cell_move->y-=2;
        cell_move->x-=8;
        break;
    case 5:
        cell_move->y+=2;
        cell_move->x+=8;
        break;
    case 6:
        cell_move->y+=2;
        cell_move->x-=8;
        break;

    }
    visual_map[cell_move->y][cell_move->x].fullnes=1;
    return cell_move;
}


int mitosis_action(int n,PLACE visual_map[3+4*n][1+8*n],CELL *list,CELL *list2,int turn, int cell_choosed,int count_cells1,int count_cells2)
{

    CELL * cell_mitosis,* current;
    if(turn%2==1)
        for ( cell_mitosis=list; cell_mitosis->number!=cell_choosed; cell_mitosis=cell_mitosis->next);
    else
        for ( cell_mitosis=list2; cell_mitosis->number!=cell_choosed; cell_mitosis=cell_mitosis->next);

    if(visual_map[cell_mitosis->y][cell_mitosis->x].type!=Mitosis){
        system("cls");
        printing_map(n,visual_map,list,list2);
    printf("not a mitosis place.\n");
        return 0;
    }
    if(cell_mitosis->enerjy<80){
        system("cls");
        printing_map(n,visual_map,list,list2);
        printf("not enough energy.\n");
        return 0;
    }

    if(turn%2==1)
    {
        if(count_cells1==9){
            system("cls");
            printing_map(n,visual_map,list,list2);
            printf("you reach the limitation.\n");
            return 0;
        }
    }
    else if(count_cells2==9){
        system("cls");
        printing_map(n,visual_map,list,list2);
        printf("you reach the limitation.\n");
        return 0;
    }

    int noooooooooob=0;
    int resx,resy,temp;
    do
    {
        temp = rand()%6+1;
        noooooooooob++;
        if(noooooooooob ==100)
        {
            system("cls");
            printing_map(n,visual_map,list,list2);
            printf("there is no empty place near you\n");
            return 0;
        }
    }
    while(permision_move(cell_mitosis,n,visual_map,temp));

    if (turn%2 ==1){
        current =  make_add_nod(cell_mitosis->x,cell_mitosis->y,list,count_cells1)  ;
        naming(cell_mitosis->name,count_cells1);
    }
    else{
        current = make_add_nod(cell_mitosis->x,cell_mitosis->y,list2,count_cells2);
                naming(cell_mitosis->name,count_cells2);

    }

    move_mitos(current,n,visual_map,temp);
    cell_mitosis->enerjy=40;


    return 1;
}



int move(CELL * cell_move,int n,PLACE visual_map[3+4*n][1+8*n],CELL *list,CELL *list2)
{
    int oper;
    do
    {
        system("cls");
        printing_map(n,visual_map,list,list2);
        printf("[1]North\n[2]South\n[3]Northeast\n[4]Northwest\n[5]Southeast\n[6]Southwest\n[7]EXIT\n");
        scanf("%d",&oper);
        if(oper==7)
            return 1;
    }
    while(permision_move(cell_move,n,visual_map,oper));

    visual_map[cell_move->y][cell_move->x].fullnes=0;

    switch(oper)
    {
    case 1:
        cell_move->y-=4;
        break;
    case 2:
        cell_move->y+=4;
        break;
    case 3:
        cell_move->y-=2;
        cell_move->x+=8;
        break;
    case 4:
        cell_move->y-=2;
        cell_move->x-=8;
        break;
    case 5:
        cell_move->y+=2;
        cell_move->x+=8;
        break;
    case 6:
        cell_move->y+=2;
        cell_move->x-=8;
        break;

    }
    visual_map[cell_move->y][cell_move->x].fullnes=1;

}
