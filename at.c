#include<stdint.h>
#include<stdio.h>
#define CR 0x0D
#define LF 0x0A
#define PLUS 0x2B
#define E 0x45
#define O 0x4F
#define R 0x52
#define K 0x4B
uint32_t state = 0; // we will store this var in heap because we need everytime to know the last state
int32_t result = 2;  //sustain the state to be in process
int checkIfError=0;
int isOKorERROR=0; // checks if the next CRLF will end the message
int is_message= 0;  //will check if there exists some messages like +something ,because we want to know how much CR LF we expect

int32_t validator(uint8_t character){
    //RULES:  
    /*
        var result will contain everytime a value which will be returned in our main call
        0- correct message 
        1- incorrect message 
        2- it started but it's not done
    */
   //TODO : CHECK the error for the at_simple_error_ok.txt && test_file_simple_at_ok.txt
   printf("\nstate: %d\n",state);
   char str[2];
    sprintf(str,"%c",character);
    printf("\n%s\n",str);
    if(character==CR){
        printf("CR");
    }else if(character==LF){
        printf("LF");
    }
    switch (state)
    {
        case 0 : {
            if(character==CR){
                printf("%d",character);
                    state=1;
                }
            else{
                    state=12;
                }
            break;
        }
        case 1:{
            if(is_message==1){
                if(character==LF){
                    //to manage the case <CR><LF>message<CR><LF><CR><LF>anything else
                        is_message=0;
                        state=0;
                    }
                else if(character!=LF){
                        state=12;
                    }
            }
            else if(isOKorERROR==1){
                //end of message
                if(character==LF){
                        state=8;
                    }
                else if(character!=LF){
                        state=12;
                    }
            }
            else{
                if(character==LF){
                        state=2;
                    }
                else if(character!=LF){
                        state=12;
                    }
            }
            break;
        } 
        case 2:{
            if(character==E){
                state=13;
            }else if(character==O){
                state=17;
            }
            else if(character==PLUS){
                state= 9;
            }
            break;
        }
        case 8: {
        
            if(checkIfError==0){
                //correct answer
                result = 0;
            }else{
                //wrong answer
                result = 1;
            }
            break;
        }
        case 9:{
            if(character!=CR){
                //add the content in at_RESULT - lines;
                is_message = 1;
                state = 9;
            }else{
                //count the at_RESULT lines
                state = 0;
            }
            break;
        }
        case 10:{
            isOKorERROR=1;
            if(character==CR){
                state=0;
            }else{
                state=12;
            }
            break;
        }
        case 12:{
            state = 8;
            checkIfError=1;
            break;
        }
        case 13:{
            if(character==R){
                state =14;
            }
            else{
                state =12;
            }
            break;
        }
        case 14:{
            if(character==R){
                state =15;
            }else{
                state=12;
            }
            break;
        }
        case 15:{
            if(character==O){
                state=16;
            }
            else{
                state=12;
            }
        }
        case 16:{
            if(character==R){
                state = 10;
            }
            break;
        }
        case 17:{
            if(character==K){
                state = 10;
            }
            else{
                state=12;
            }
            break;
        }
    }
    return result;
}