#include <stdio.h>
#include <string.h>

int main()
{
    char name_bin[50];
    char name_text[50];
    printf("enter the file to be converted to text.\n");
    scanf("%s",name_bin);
    printf("enter the name of text file to make.\n");
    scanf("%s",name_text);
    FILE * map_bin = fopen(name_bin,"rb");
    FILE * map_text = fopen (name_text,"w");

    int n;
    char kind;
    char kind_str[10];
    fread(&n,4,1,map_bin);
    fprintf(map_text,"the mas is %d * %d map.\n",n,n);
    for(int i=0; i<n*n; i++)
    {

        fread(&kind,1,1,map_bin);
        if(kind=='1')
            strcpy(kind_str,"ENERGY");
        if(kind=='2')
            strcpy(kind_str,"MITOSIS");
        if(kind=='3')
            strcpy(kind_str,"FORBIDDEN");
        if(kind=='4')
            strcpy(kind_str,"NORMAL");


        fprintf (map_text,"[%d][%d] : '%c' = %s\n",i/n,i%n,kind,kind_str);
    }
    fclose(map_bin);
    fclose(map_text);

}
