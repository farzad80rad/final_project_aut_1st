#include <stdio.h>
#include <windows.h>
#include "visual_map.h"


enum chars_map { frame=' ', Energy='1',Mitosis='2',Forbidden='3',Normal='4'};

int permision_move(CELL * cell_move,int n,PLACE visual_map[3+4*n][1+8*n],int oper)
{
    switch(oper)
    {
    case 1:
        if(visual_map[cell_move->y-4][cell_move->x].fullnes==1 || cell_move->y-4<=0)
            return 1;
        break;
    case 2:
        if(visual_map[cell_move->y+4][cell_move->x].fullnes==1 || cell_move->y+4>=3+4*n)
            return 1;
        break;
    case 3:
        if(visual_map[cell_move->y-2][cell_move->x+8].fullnes==1  || cell_move->y-2<=0 || cell_move->x+8>=1+8*n )
            return 1;
        break;
    case 4:
        if(visual_map[cell_move->y-2][cell_move->x-8].fullnes==1  ||  cell_move->y-2<=0 || cell_move->x-8<=0 )
            return 1;
        break;
    case 5:
        if(visual_map[cell_move->y+2][cell_move->x+8].fullnes==1 ||  cell_move->y+2>=3+4*n || cell_move->x+8>=1+8*n )
            return 1;
        break;
    case 6:
        if(visual_map[cell_move->y+2][cell_move->x-8].fullnes==1  || cell_move->y+2>=3+4*n || cell_move->x-8<=0)
            return 1;
        break;
    }
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
