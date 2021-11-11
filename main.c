#include <stdio.h>
#include <stdlib.h>
#include "at.h"
AT_STATUS_DATA at_RESULT;
void printData(){
    int realSizeOfArray=0;
    if(at_RESULT.line_counter>MAX_STRING_COUNTER){
        realSizeOfArray=MAX_STRING_COUNTER;
    }else{
        realSizeOfArray=at_RESULT.line_counter;
    }
    printf("%d\n",realSizeOfArray);
    for(int i=0;i<realSizeOfArray;i++){
        char str[at_RESULT.currentLineLength[i]+1];
        printf("LINE %d: ",i);
          for(int j=0;j<at_RESULT.currentLineLength[i];j++){
            int charsHex[MAX_STRING_LENGTH+1];
            charsHex[j]=(int)at_RESULT.lines[i][j];
            sprintf(str,"%c",charsHex[j]);
            printf("%s",str);
          }
          printf("\n");
        }
}
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
    while (feof(file)!=1)
    {
        character = fgetc(file);
        if(at_RESULT.ok!=1){
            at_RESULT.ok = validator(character);
        }else{
            break;
        }
    }
    if (at_RESULT.ok == 0)
    {
        printf("\nMESSAGE OK!!\n");
        printf("\nNUMBER OF LINES: %d\n",at_RESULT.line_counter);
        printData();
    }
    else if (at_RESULT.ok == 1)
    {
        printf("SYNTAX ERROR!");
    }
    fclose(file);
    return 0;
}