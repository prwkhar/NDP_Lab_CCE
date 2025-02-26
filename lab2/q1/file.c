#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE* fptr;
    char ch;
    fptr = fopen("file1.txt","r");

    if(fptr==NULL)
    {
        printf("unable to open file\n");
        exit(EXIT_FAILURE);
    }
    printf("file opened and reading\n");
    printf("enter teh word to be serached for\n");
    char str[50];
    fgets(str,50,stdin);

    int linenumber=0;
    char line[1024];
    int maxline=strlen(str);
    printf("character --> %c\n",str[maxline-2]);
    str[maxline-1]='\0';
    maxline=strlen(str);
    int found=0;
    while(fgets(line,1024,fptr)!=NULL){
        linenumber++;
        if(strstr(line,str)!=NULL){
            printf("Found %s at line %d: %s", str,linenumber,line );
            found=1;
        }
    }
    if (!found) {
        printf("Word '%s' not found in file file1\n", str);
    }

    fclose(fptr);  // Close the file
    return 0;
}