#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "visual_map.h"
#include "cells.h"
#include <time.h>


enum chars_map {frame=' ', Energy='1',Mitosis='2',Forbidden='3',Normal='4'};

int main()
{

    srand(time(0));

    printf("enter file name\n");
    char file_name[50];
    int n;
    scanf("%s",file_name);
    n=find_elements_count(file_name);

    char *str;
    str = read_binary(file_name,n);

    PLACE visual_map[3+4*n][1+8*n];
    init_table(n,file_name,str,visual_map);

    printing_map(n,visual_map);


    int count_cellsX,count_cellsY;
    char map_player[3+4*n][1+8*n];

    CELL* list;
    list = make_add_random(3,n,visual_map,40);
    for (CELL * current=list;current!=NULL;current=current->next)
        printf("(%d,%d)  %s  %d\n",n-(current->y-2)/4 - 1,(current->x-4)/8,current->name,current->enerjy);


}
