#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct cell
{
    int x;
    int y;
    int number;
    char name[8];
    int enerjy;
    struct cell *next;
};
typedef struct cell CELL;


typedef struct
{
    char type;
    char  score[4];
} PLACE;

enum chars_map { frame=' ', Energy='1',Mitosis='2',Forbidden='3',Normal='4'};

int check_repeat(CELL* list,int xi,int yi)
{
    CELL* current;
    // printf("2");
    for ( current=list; current!=NULL; current=current->next)
        if(current->x==xi && current->y==yi)
        {
            return 1;
        }
    return 0;
}
CELL * make_new_nod_rand(void)
{
    CELL * new_nod = (CELL *)malloc(sizeof(CELL));
    new_nod->next=NULL;
    new_nod->x=-5;
    new_nod->number=1;
    return new_nod;
}

CELL* make_list(int count_cells)
{
    CELL* list = make_new_nod_rand();
    for (int i=0; i<count_cells-1; i++)
    {
        CELL* current;
        for(current=list; current->next!=NULL; current=current->next);
        current->next=make_new_nod_rand();
        current->number=i+2;
    }
    return list;
}

void naming(char name[8])
{
    char names[18][8]= {"sam","bili","bob","ali","jany","warior","jacky","mom","wow","jizz","dany","popy","nazy","iran","danis","venom","batman","halk"};
    static int used[18]={-1},element=0;
    int oper;
    printf("1-make the name randomly     2-make it yourself\n ");
    scanf("%d",&oper);
    if (oper==1)
    {
        while(1)
        {
            int temp;
            temp=rand()%18;
            for(int i=0;i<18;i++)
                if(temp==used[i])
                    continue;
            used[element]=temp;
            strcpy(name,names[temp]);
            element++;
            break;
        }

    }
    else
    {
        printf("enter the name\n");
        char name_in[8];
        scanf("%s",name_in);
        strcpy(name,name_in);
    }
}


CELL* make_add_random(int count_cell,int n,PLACE visual_map[3+4*n][1+8*n],int enerjyi)
{


    CELL* list=make_list(count_cell);
    CELL* current;
    int tempx,tempy;
    for(current=list; current!=NULL; current=current->next)
    {
        do
        {
            int temp_rand;
            temp_rand= rand()%n;
            tempx=(temp_rand)*8+4;
            if (temp_rand%2==1)
            {
                temp_rand= rand()%n;
                tempy=temp_rand*4+4;
            }
            else
            {
                temp_rand= rand()%n;
                tempy=temp_rand*4+2;
            }

        }
        while(visual_map[tempy][tempx].type==Forbidden || check_repeat(list,tempx,tempy));
        current->x=tempx;
        current->y=tempy;
        naming(current->name);
        current->enerjy=enerjyi;
    }
    return list;
}






