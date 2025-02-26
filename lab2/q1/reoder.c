#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void sort(char* line)
{
    int l=strlen(line);
    for(int i=0;i<l-1;i++)
    {
        for(int j=i+1;j<l;j++)
        {
            if(line[j]>line[i])
            {
                char temp=line[j];
                line[j]=line[i];
                line[i]=temp;
            }
        }
    }
}
int main()
{
    FILE* fptr= fopen("file1.txt","r");
    FILE* tptr= fopen("tempfile.txt","w");
    char line[1024];

    int linenumber=0;
    while(fgets(line,1024,fptr)!=NULL){
        linenumber++;
        //sort line array
        sort(line);
        fputs(line,tptr);
    }
    fclose(fptr);
    fclose(tptr);
    remove("file1.txt");
    rename("tempfile.txt","file1.txt");
    return 0;
}