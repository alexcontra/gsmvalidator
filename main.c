#include <stdio.h>
#include <stdlib.h>
#include "at.h"
AT_STATUS_DATA at_RESULT;
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
    at_RESULT.line_counter=0;
    at_RESULT.ok=2;
    while (feof(file)!=1)
    {
                character = fgetc(file);
                if(at_RESULT.ok!=1){
                at_RESULT.ok = validator(character);
                if (at_RESULT.ok!=2)
                {
                    at_RESULT.ok = validator(character);
                }
            }else{
                break;
            }
    }
    fclose(file);
    return 0;
}