#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct cell
{
    int x;
    int y;
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
        printf("2");
    for ( current=list;current!=NULL;current=current->next)
        if(current->x==xi && current->y==yi){
            return 1;
        }
        return 0;
}
CELL * make_new_nod_rand(void)
{
    CELL * new_nod = (CELL *)malloc(sizeof(CELL));
    new_nod->next=NULL;
    new_nod->x=-5;
    return new_nod;
}

CELL* make_list(int count_cells)
{
    CELL* list = make_new_nod_rand();
    for (int i=0;i<count_cells-1;i++){
            CELL* current;
            for(current=list;current->next!=NULL;current=current->next);
    current->next=make_new_nod_rand();
    }
    return list;
}

void naming(char name[8])
{
    int oper;
    printf("1-make the name randomly     2-make it yourself\n ");
    scanf("%d",&oper);
    if (oper==1)
    strcpy(name,"aaaaa");
}


CELL* make_add_random(int count_cell,int n,PLACE visual_map[3+4*n][1+8*n],int enerjyi)
{


   CELL* list=make_list(count_cell);
   CELL* current;
   int tempx,tempy;
   for(current=list;current!=NULL;current=current->next){
    do
   {
       int temp_rand;
       temp_rand= rand()%n;
       tempx=(temp_rand)*8+4;
       if (temp_rand%2==1){
       temp_rand= rand()%n;
       tempy=temp_rand*4+2;
       }
       else{
       temp_rand= rand()%n;
       tempy=temp_rand*4+4;
       }
   // printf("%d %d",tempx,tempy);
    //visual_map[tempy][tempx].type=Forbidden;
   // printing_map(n,visual_map);
   }while(visual_map[tempy][tempx].type==Forbidden || check_repeat(list,tempx,tempy));
   current->x=tempx;
   current->y=tempy;
   naming(current->name);
   current->enerjy=enerjyi;
   }
   return list;
}


