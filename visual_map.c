
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


enum chars_map { frame=' ', Energy='1',Mitosis='2',Forbidden='3',Normal='4'};

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


void printing_map(int n,char visual_map[3+4*n][1+8*n]){

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
                if(visual_map[y][x]==Energy)
                {
                SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
                printf(" ");
                SetConsoleTextAttribute(hConsole, originalAttrs);
                continue;
                }
                if(visual_map[y][x]==Mitosis)
                {
                SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
                printf(" ");
                  SetConsoleTextAttribute(hConsole, originalAttrs);
                continue;
                }
                if(visual_map[y][x]==Normal)
                {
                SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY);
                printf(" ");
                  SetConsoleTextAttribute(hConsole, originalAttrs);
                continue;
                }
                 if(visual_map[y][x]==Forbidden)
                {
                printf(" ");
                continue;
                }


              printf("%c",visual_map[y][x]);
        }
        printf("\n");
    }
}


int init_table(int n, char file_name[50] , char str[n*n] ,char visual_map[3+4*n][1+8*n] )
{

    int n_x=1+8*n;
    int n_y = 3+4*n;

    for (int i=0; i<n_y; i++)
        for(int j=0; j<n_x; j++)
            visual_map[i][j]=' ';

    for (int y=0; y<n_y; y++)
        for(int x=0; x<n_x; x++)
        {
            if (y%4==0 && x%16<10 && x%2==0)
                visual_map[y][x]=frame;
            if (y%4==2 && x%16>8 && x%2==0)
                visual_map[y][x]=frame;
            if(x%8==0)
                visual_map[y][x]=frame;
        }


    int element_str=0;
    int yy=4*n-2;
    for(int i=0;i<4*n;i+=4)
        for(int j=0;j<n;j++)
    {
        visual_map[yy-i+2*(j%2)][8*j+4]=visual_map[yy-i+2*(j%2)][8*j+3]=visual_map[yy-i+2*(j%2)][8*j+5]=visual_map[yy-i+2*(j%2)][8*j+2]=visual_map[yy-i+2*(j%2)][8*j+1]=visual_map[yy-i+2*(j%2)][8*j+6]=visual_map[yy-i+2*(j%2)][8*j+7]=str[element_str];
        visual_map[yy-i+2*(j%2)-1][8*j+4]=visual_map[yy-i+2*(j%2)-1][8*j+3]=visual_map[yy-i+2*(j%2)-1][8*j+5]=visual_map[yy-i+2*(j%2)-1][8*j+2]=visual_map[yy-i+2*(j%2)-1][8*j+1]=visual_map[yy-i+2*(j%2)-1][8*j+6]=visual_map[yy-i+2*(j%2)-1][8*j+7]=str[element_str];
        visual_map[yy-i+2*(j%2)+1][8*j+4]=visual_map[yy-i+2*(j%2)+1][8*j+3]=visual_map[yy-i+2*(j%2)+1][8*j+5]=visual_map[yy-i+2*(j%2)+1][8*j+2]=visual_map[yy-i+2*(j%2)+1][8*j+1]=visual_map[yy-i+2*(j%2)+1][8*j+6]=visual_map[yy-i+2*(j%2)+1][8*j+7]=str[element_str];
        element_str++;
    }


}
