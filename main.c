#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "visual_map.h"


int main()
{
    printf("enter file name\n");
    char file_name[50];
    int n;
    scanf("%s",file_name);
    n=find_elements_count(file_name);

    char *str;
    str = read_binary(file_name,n);

    char visual_map[3+4*n][1+8*n];
    init_table(n,file_name,str,visual_map);
    printing_map(n,visual_map);

}
