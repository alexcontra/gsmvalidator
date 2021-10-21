#include <stdio.h>
#include<stdlib.h>
int main(int argc , char **agrv){
    if(argc<2){
        printf("NOT ENOUGH ARGUMNETS\nSOMETHING IS MISSING");
    }
    FILE *file;
    if((file=fopen(agrv[1],"rb"))==NULL){
        printf("FILE CANNOT BE OPEN");
        exit(-1);
    }
    int character;
    while(!feof(file)){
        character= fgetc(file);
        //call function to itterate through F
    }
    fclose(file);
    return 0;
}