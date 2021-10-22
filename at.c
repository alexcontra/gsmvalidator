#include<stdint.h>
#include "at.h"

uint32_t state = 0; // we will store this var in heap because we need everytime to know the last state
int32_t validator(uint8_t character){
    int32_t result = -1;  //sustain the state to be in process
    int is_message= 0;  //will check if there exists some messages like +something ,because we want to know how much CR LF we expect
    //RULES:  
    /*
        Result will contain everytime a value which will be returned in our main call
        0- correct message 
        1- incorrect message 
        2- it started but it's not done
    */
    printf("%d",character);
    switch (state)
    {
        case 0 : {
            if(character==CR){
                    result=2;//start the message
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
            }else{
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
            //end of message 
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
            if(character==CR){
                state=0;
            }else{
                state=12;
            }
            break;
        }
        case 12:{
            state = 8;
            result = 1; //wrong message based on some syntax error
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