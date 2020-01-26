#include <stdio.h>
#include "visual_map.h"
#include <windows.h>


enum chars_map { frame=' ', Energy='1',Mitosis='2',Forbidden='3',Normal='4'};


void save_map_edit(int n,char str[n*n])
{
    char name[50];
    printf("enter the file name to be saved.\n");
    scanf("%s",name);
    FILE  *map_write = fopen(name,"wb");
    fwrite(&n,4,1,map_write);
    fwrite(str,1,n*n,map_write);
    fclose(map_write);
}


void make_map(void)
{
    int n,oper=1;
    printf("enter n\n");
    scanf("%d",&n);
    char str[n*n];
    for(int i=0; i<n*n; i++)
        str[i]=Normal;
    PLACE visual_map[3+4*n][1+8*n];
    while(1)
    {
        system("cls");
        init_table(n,"alaki hast",str,visual_map);
        printing_map(n,visual_map,NULL,NULL);
        printf("1- change place\n2- save\n3- exit\n");
        scanf("%d",&oper);
        if(oper==3)
            break;
        if(oper==1)
        {
            int x,y;
            char kind;
            printf("enter y _ is measured from down,starts from 0.\n");
            scanf(" %d",&y);
            printf("enter x _ is measured from left,starts from 0.\n");
            scanf(" %d",&x);
            printf("enter kind of place. 1-Energy , 2-Mitosis, 3-Forbidden, 4-Normal\n");
            scanf(" %c",&kind);
            str[y*n+x]=kind;
        }
        if(oper==2)
        {
            save_map_edit(n,str);
        }

    }
}
