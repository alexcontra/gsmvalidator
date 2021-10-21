#include<stdint.h>
#define CR 0x0D
#define LF 0x0A
uint32_t state =0; // we will store this var in heap because we need everytime to know the last state
int32_t validator(uint8_t character){
    int32_t result = 2;  //sustain the state to be in process

    //RULES:  
    /*
        Result will contain everytime a value which will be returned in our main call
        0- correct message 
        1- incorrect message 
        if there is no output between 0 or 1 it's not done
    */
    //implement of the switch statement.

    return result;
}