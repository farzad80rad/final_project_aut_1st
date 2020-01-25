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
    int fullnes;
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

void naming(char name[8],int count_cells)
{
    static int counter=-1;
    counter++;
    char names[][8]= {"sam","bili","bob","ali","jany","warior","jacky","mom","wow","jizz","dany","popy","nazy","iran","danis","venom","batman","halk","boy","farzad","hadi","A.H","armin","sina","killer","nooo","yeees","fish","cat","you","me","they","aahhh"
                        "freind","BIJ","love","fire","water","ground","wind","book","CEIT","master","origin","dog","moon","sun","tree","~_~","-_-","+_+","=_=","hii","howwm","ice","github","int","float"};
    static int used[58]={-1},element=0;
    int oper;
    printf("%d  1-make the name randomly     2-make it yourself\n ",counter%count_cells +1);
    scanf("%d",&oper);
    if (oper==1)
    {
        while(1)
        {
            int temp,flag=1;
            temp=rand()%58;
            for(int i=0;i<58;i++)
                if(temp==used[i])
                    flag=0;
                    if(flag){
            used[element]=temp;
            strcpy(name,names[temp]);
            element++;
            break;
                    }
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

printf("\n\n");

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
        while(visual_map[tempy][tempx].fullnes==1);
        visual_map[tempy][tempx].fullnes=1;
        current->x=tempx;
        current->y=tempy;
        naming(current->name,count_cell);
        current->enerjy=enerjyi;
    }
    return list;
}
