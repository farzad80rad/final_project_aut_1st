
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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

 int search_cells_print(int xi, int yi,CELL *list)
 {

         HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo);
    int originalAttrs = ConsoleInfo.wAttributes;


     CELL * current;
     for (current =list ;current!=NULL;current=current->next)
        if(current->x==xi && current->y==yi)
            {
                SetConsoleTextAttribute(hConsole, 6);
                printf("%d",current->number);
                return 1;
            }
    return 0;
 }

char *read_binary (char * file_name,int n)
{

    FILE *fpin = fopen(file_name,"rb");

    fseek(fpin,sizeof(unsigned int),SEEK_SET);
    char *str;
    str = (char*)malloc(sizeof(char)*n*n);
        fread(str,sizeof(char),n*n,fpin);
    fclose(fpin);
    //for (int i=0;i<n*n;i++)
      //  printf("%c ",str[i]);
    return str;

}


int find_elements_count(char * file_name)
{
    FILE *fpin = fopen(file_name,"rb");
    if (fpin==NULL){
        printf("not such a file\n");
        return NULL;
    }
    unsigned int count;
    fread(&count,4,1,fpin);
    //printf("%d\n",count);
    fclose(fpin);
        //printf("1");
    return count;
}


void printing_map(int n,PLACE visual_map[3+4*n][1+8*n],CELL *list){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo);
    int originalAttrs = ConsoleInfo.wAttributes;

    int n_y=3+4*n;
    int n_x = 1+8*n;

    for (int y=0; y<n_y; y++)
    {
        for(int x=0; x<n_x; x++)
        {

                if(search_cells_print(x,y,list)){
                    continue;
                }

                if(visual_map[y][x].type==Energy)
                {
                SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
                    if(strcmp(visual_map[y+1][x+3].score,"0"))
                printf("%c",visual_map[y+1][x+3].score[0]);
                else if(strcmp(visual_map[y+1][x+2].score,"0"))
                printf("%c",visual_map[y+1][x+2].score[1]);
                else if(strcmp(visual_map[y+1][x+1].score,"0"))
                printf("%c",visual_map[y+1][x+1].score[2]);
                else
                    printf(" ");
                SetConsoleTextAttribute(hConsole, originalAttrs);
                continue;
                }
                if(visual_map[y][x].type==Mitosis)
                {
                SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
                printf(" ");
                  SetConsoleTextAttribute(hConsole, originalAttrs);
                continue;
                }
                if(visual_map[y][x].type==Normal)
                {
                SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY);
                printf(" ");
                  SetConsoleTextAttribute(hConsole, originalAttrs);
                continue;
                }
                 if(visual_map[y][x].type==Forbidden)
                {
                printf(" ");
                continue;
                }



              printf("%c",visual_map[y][x].type);
        }
        printf("\n");
    }
}


int init_table(int n, char file_name[50] , char str[n*n] ,PLACE visual_map[3+4*n][1+8*n] )
{

    int n_x=1+8*n;
    int n_y = 3+4*n;

    for (int i=0; i<n_y; i++)
        for(int j=0; j<n_x; j++){
            visual_map[i][j].type=' ';
            strcpy(visual_map[i][j].score,"0");

        }

    for (int y=0; y<n_y; y++)
        for(int x=0; x<n_x; x++)
        {
            if (y%4==0 && x%16<10 && x%2==0)
                visual_map[y][x].type=frame;
            if (y%4==2 && x%16>8 && x%2==0)
                visual_map[y][x].type=frame;
            if(x%8==0)
                visual_map[y][x].type=frame;
        }


    int element_str=0;
    int yy=4*n-2;
    for(int i=0;i<4*n;i+=4)
        for(int j=0;j<n;j++)
    {

      if (str[element_str]==Energy)
            sprintf(visual_map[yy-i+2*(j%2)][8*j+4].score,"%d",100);
           // printf("%s\n",visual_map[yy-i+2*(j%2)][8*j+4].score);

      for (int k=-1;k<=1;k++)
      for (int g=1;g<8;g++)
         visual_map[yy-i+2*(j%2)+k][8*j+g].type=str[element_str];
        element_str++;
    }

}

int printing_enrjes(int n,PLACE visual_map[3+4*n][1+8*n])
{
    for (int i=0;i<3+4*n;i++)
        for (int j=0;j<1+8*n;j++)
        if (strcmp(visual_map[i][j].score,"0"))
        printf("(%d,%d)   enerjy = %s\n",n-(i-2)/4-1,(j-4)/8,visual_map[i][j].score);

}
