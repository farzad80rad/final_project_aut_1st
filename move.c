#include <stdio.h>
#include <windows.h>
#include "visual_map.h"
#include <string.h>


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


int boost_enerjy(int  cell_choosed,int n,PLACE  visual_map[3+4*n][1+8*n],CELL * list)
{
    CELL * cell_gain;
                for ( cell_gain=list; cell_gain->number!=cell_choosed; cell_gain=cell_gain->next);
    if(cell_gain->enerjy==100)
        return -1;


        int temp_enerj;
        sscanf(visual_map[cell_gain->y][cell_gain->x].score,"%d",&temp_enerj);

        if(temp_enerj==0)
            return -1;

    if(temp_enerj > 15)
    {

        if(cell_gain->enerjy<=85){
        temp_enerj-= 15;
        cell_gain->enerjy+=15;
        }
        if(cell_gain->enerjy>85)
        {
            temp_enerj -= 100-cell_gain->enerjy;
            cell_gain->enerjy=100;
        }
    }

      else
    {

        if(cell_gain->enerjy<=85){
        temp_enerj-= 15;
        cell_gain->enerjy+=15;
        }
        if(cell_gain->enerjy>85)
        {
            temp_enerj -= 100-cell_gain->enerjy;
            cell_gain->enerjy=100;
        }
    }

        if(temp_enerj < 15)
        {
         if(cell_gain->enerjy<=85){
        cell_gain->enerjy+=temp_enerj;
        temp_enerj=0;
        }
//        if(cell_gain->enerjy>85)
//        {
//            if(temp_enerj)
//        }

        }
        char temp_str[4];
        sprintf(temp_str,"%d",temp_enerj);
        strcpy(visual_map[cell_gain->y][cell_gain->x].score,temp_str);
        return 0;

}



void move(CELL * cell_move,int n,PLACE visual_map[3+4*n][1+8*n],CELL *list,CELL *list2)
{
    int oper;
    do{
    system("cls");
    printing_map(n,visual_map,list,list2);
    printf(" [1]North\n[2]South\n[3]Northeast\n[4]Northwest\n[5]Southeast\n[6]Southwest\n");
    scanf("%d",&oper);
    }while(permision_move(cell_move,n,visual_map,oper));

    visual_map[cell_move->y][cell_move->x].fullnes=0;

    switch(oper){
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
