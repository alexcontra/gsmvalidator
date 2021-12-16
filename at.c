#include <stdint.h>
#include <stdio.h>
#include<string.h>
#include "at.h"
uint32_t state = 0; // we will store this var in heap because we need everytime to know the last state
int checkIfError = 0;
int isOKorERROR = 0; // checks if the next CRLF will end the message
int is_message = 0;  //will check if there exists some messages like +something ,because we want to know how much CR LF we expect
int is_exception =0; //will mark the exception message
int it_was_error= 0;
int printed_syntax_error=0;
int count_CR=0;
int is_sms=0;//dezactivated 0, activated 1
int count_plus_state=1;
int iserror=0;
void printData(){
    int realSizeOfArray=0;
    if(at_RESULT.line_counter>MAX_STRING_COUNTER){
        realSizeOfArray=MAX_STRING_COUNTER;
    }else{
        realSizeOfArray=at_RESULT.line_counter;
    }
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
void resetValuesFromArrays(){
    for(int i=0;i<MAX_STRING_COUNTER;i++){
        at_RESULT.currentLineLength[i]=0;
    }
    for(int i=0;i<at_RESULT.line_counter;i++){
        for(int j=0;j<MAX_STRING_LENGTH+1;j++){
                    at_RESULT.lines[i][j]=0;
        }
    }
}
void processData(){
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
    at_RESULT.line_counter=0; 
    resetValuesFromArrays();
}
void writeData(uint8_t character){
    at_RESULT.lines[(int)at_RESULT.line_counter][(int)at_RESULT.currentLineLength[(int)at_RESULT.line_counter]] = character;
    at_RESULT.currentLineLength[(int)at_RESULT.line_counter]++;
}

int32_t validator(uint8_t character)
{
    int32_t result = 2; //sustain the state to be in process
    //RULES:
    /*
        var result will contain everytime a value which will be returned in our main call
        0- correct message 
        1- incorrect message 
        2- it started but it's not done
    */

    switch (state)
    {
    case 0:
    {
        //printf("\nIS SMS IN STATE 1 %d",is_sms);
        if (character == CR)
        {
            state = 1;
        }
        else if (character == PLUS)
        {
            //if there will be another +something message
            is_message = 0;
            state = 9;
        }
        else if(character!=CR && character!=PLUS && is_sms==1)
        {
            writeData(character);
            state=3;
        }
        else
        {
            state = 12;
        }
        break;
    }
    case 1:
    {
        if (is_message == 1)
        {
            if (character == LF)
            {
                //to manage the case <CR><LF>message<CR><LF><CR><LF>OK && ERROR <CR><LF>
                is_message = 0;
                state = 0;
            }
            
            else if (character != LF && character != PLUS)
            {
                state = 12;
            }
        }
        else if (isOKorERROR == 1)
        {
            //end of message
            if (character == LF)
            {
                state = 8;
            }
            else if (character != LF)
            {
                state = 12;
            }
        }
        else if(is_exception == 1){
            if(character==LF){
                is_exception=0;
                state=0;
            }
            else if(character!=LF){
                state = 12;
            }
        }
        else
        {
            if (character == LF)
            {
                state = 2;
            }
            else if (character != LF)
            {
                state = 12;
            }
        }
        break;
    }
    case 2:
    {
       // printf("is_SMS in STATE 2  %d\n",is_sms);
        if (character == E )
        {            
            state = 13;
        }
        else if (character == O )
        {           
            state = 17;
        }
        else if (character == PLUS && is_sms==0)
        {
            state = 9;
        }
       
        else if(character==CR && is_sms==1){
            is_sms=0;
            count_plus_state=1;
            state=1;
        }
        else if(character==CR && is_sms==0){
            state=12;
        }
        else if(character!=CR && is_sms==1){
            state=12;
        }
        else
        {
            writeData(character);
            state = 3;
        }
        break;
    }
    case 3:{
          //printf("%x CHAR : \n" ,character);
         
            if(character!=CR){
                    if(is_sms!=1){
                        is_exception = 1;
                    }         
                        if(at_RESULT.line_counter<MAX_STRING_COUNTER){
                            //add the content in at_RESULT - lines;
                            if(at_RESULT.currentLineLength[(int)at_RESULT.line_counter]<MAX_STRING_LENGTH+1){
                                writeData(character);
                            }
                        }
                        state=3;
                    }
            else if(character == CR){
                at_RESULT.line_counter++;
                state = 1;
            }
        
        
        break;
    }
    case 8:
    {

        if (checkIfError == 0)
        {
            //correct answer
            result = 0;
        }
        else
        {
            //wrong answer
            it_was_error=1;
            result = 1;
        }

        state=0;
        isOKorERROR=0;
        checkIfError=0;        
        break;
    }
    case 9:
    {
        if (character != CR)
        {
            if(at_RESULT.line_counter<MAX_STRING_COUNTER){
                //add the content in at_RESULT - lines;
                if(at_RESULT.currentLineLength[(int)at_RESULT.line_counter]<MAX_STRING_LENGTH+1){
                    writeData(character);
                }
            }
            is_message = 1;
            state = 9;
            if(character==PLUS){
                count_plus_state++;
            }
            
        }
        else if (character == CR)
        {
            //count the at_RESULT lines
            at_RESULT.line_counter++;
            //reset the line length
            state = 1;
            //To check if is a sms
            if(count_plus_state>=2){
                is_sms=1;
            }
        }
        break;
    }
    case 10:
    {
        isOKorERROR = 1;
        if (character == CR)
        {
            state = 1;
        }
        else
        {
            state = 12;
        }
        break;
    }
    case 12:
    {
        iserror=1;
        state = 8;
        checkIfError = 1;
        break;
    }
    case 13:
    {
        if (character == R)
        {
            state = 14;
        }
        else
        {
            state = 12;
        }
        break;
    }
    case 14:
    {
        if (character == R)
        {
            state = 15;
        }
        else
        {
            state = 12;
        }
        break;
    }
    case 15:
    {
        if (character == O)
        {
            state = 16;
        }
        else
        {
            state = 12;
        }
    }
    case 16:
    {
        if (character == R)
        {
            state = 10;
        }
        break;
    }
    case 17:
    {
        if (character == K)
        {
            state = 10;
        }
        else
        {
            state = 12;
        }
        break;
    }
    }

    if(at_RESULT.ok!=2){
        if(printed_syntax_error==0){
            processData();
        }
        if(it_was_error==1){
            printed_syntax_error=1;
        }
    }
    return result;
}

/*
    Daca intra pe starea 9 de mesaj merge inregistreaza mesajul bla bla bla dupa il incheie cu CRLF 
    Si daca urmatoarea chestie e ceva fara plus teoretic ar trebui sa intre pe starea 3 ceea ce inseamna
    ca e o exceptie, dar noi nu vrem sa il tratam ca si pe o exceptie deoarece ar putea avea oricate randuri
    ceea ce inseamna ca setam flag-ul de is_sms pe 1 la intrarea in starea 3 si asta inseamna ca avem daca dupa 
    urmatorul CRLF primeste orice altceva decat CRLF, +, O sau E inseamna ca mai este un mesaj deci flag-ul 
    nostru e inca activ ceea ce repeta procesul. 
*/