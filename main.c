#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "visual_map.h"


enum chars_map { frame=' ', Energy='1',Mitosis='2',Forbidden='3',Normal='4'};

int main()
{
    printf("enter file name\n");
    char file_name[50];
    int n;
    scanf("%s",file_name);
    n=find_elements_count(file_name);

    char *str;
    str = read_binary(file_name,n);

    PLACE visual_map[3+4*n][1+8*n];
    init_table(n,file_name,str,visual_map);

  //  int count_enj = find_count_enj(n,str);
    //ENERJY_CELL arr_cell_enj[count_enj];
    printing_map(n,visual_map);

   printing_enrjes(n,visual_map);

}
