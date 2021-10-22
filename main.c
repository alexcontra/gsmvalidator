#include <stdio.h>
#include <stdlib.h>
#include "at.h"
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("NOT ENOUGH ARGUMNETS\nSOMETHING IS MISSING");
    }
    FILE *file;
    if ((file = fopen(argv[1], "rb")) == NULL)
    {
        printf("FILE CANNOT BE OPEN");
        exit(-1);
    }
    
    int character;
    int messageCheck ;
    while (feof(file)!=1)
    {
        character = fgetc(file);
        // char str[2];
        // sprintf(str,"%c",character);
        // printf("%s",str);
        if(messageCheck!=1){
            messageCheck = validator(character);
        }else{
            break;
        }
    }
    if (messageCheck == 0)
    {
        printf("MESSAGE OK!!");
    }
    else if (messageCheck == 1)
    {
        printf("SYNTAX ERROR !");
    }
    fclose(file);
    return 0;
}