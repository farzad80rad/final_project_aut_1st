
#include <stdio.h>
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

#include "cells.h"



void save_map(int n,PLACE visual_map[3+4*n][1+8*n])
{
    FILE  *map_write = fopen("map_save_me.bin","wb");
    fwrite(&n,4,1,map_write);
    fwrite(visual_map,sizeof(PLACE),(n*4+3)*(1+8*n),map_write);
    fclose(map_write);
}

int scan_n(void)
{
    int n;
    FILE  *map_read = fopen("map_save_me.bin","rb");
    fread(&n,4,1,map_read);
    fclose(map_read);
    //printf("%d\n",n);
    return n;
}


CELL * make_nod(void)
{
    CELL * new_nod = (CELL *)malloc(sizeof(CELL));
    new_nod->next=NULL;
    return new_nod;
}

void add_end(CELL * list,CELL *new_nod)
{
    CELL * current;
    for( current = list ; current->next != NULL ; current =  current->next);
    current->next = new_nod;
}


void load_player(CELL ** list,int player)
{
    FILE * player_save ;
    CELL * temp ;
    if(player==1)
        player_save=fopen("player1_save_me.bin","rb");
    else
        player_save=fopen("player2_save_me.bin","rb");
        int count_cells;
        fread(&count_cells,4,1,player_save);
        *list = make_nod();
        fread(*list,sizeof(CELL),1,player_save);
        (*list)->next=NULL;

        for (int i=0;i<count_cells-1;i++)
        {
            temp = make_nod();
            fread(temp,sizeof(CELL),1,player_save);
            temp->next=NULL;
            add_end(*list,temp);
        }

    fclose(player_save);
}

void save_mood(int mood,int turn)
{
    FILE * mood_file = fopen("mood_me.bin","wb");
    fwrite(&mood,4,1,mood_file);
    fwrite(&turn,4,1,mood_file);
    fclose(mood_file);
}

int  load_mood(void)
{
    int mood;
    FILE * mood_file = fopen("mood_me.bin","rb");
    fread(&mood,4,1,mood_file);
    fclose(mood_file);
    return mood;
}

int load_turn(void)
{
        int mood;
    FILE * mood_file = fopen("mood_me.bin","rb");
    fread(&mood,4,1,mood_file);
    fread(&mood,4,1,mood_file);
    fclose(mood_file);
    return mood;
}


void save_player(CELL *list,int count_cells,int player)
{
    FILE * player_save ;
    if(player==1)
        player_save=fopen("player1_save_me.bin","wb");
    else
        player_save=fopen("player2_save_me.bin","wb");

        CELL *current;
        fwrite(&count_cells,4,1,player_save);
    for(current = list;current != NULL; current=current->next)
        fwrite(current,sizeof(CELL),1,player_save);

    fclose(player_save);
}

void load_map(int *n,PLACE visual_map[3+4*(*n)][1+8*(*n)])
{
        FILE  *map_read = fopen("map_save_me.bin","rb");
        fread(n,4,1,map_read);
        fread(visual_map,sizeof(PLACE),((*n)*4+3)*(1+8*(*n)),map_read);


    fclose(map_read);
}





