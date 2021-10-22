#ifndef __AT_H
#define __AT_H

#include<stdint.h>
#define MAX_STRING_COUNTER 1000 //it will contain a max of 1000 strings
#define MAX_STRING_LENGHT 128 // max length of the string will be 128
int32_t validator(uint8_t character);
typedef struct {
    uint8_t ok; //if ok = 1 means ok , if ok = 0 means error
    uint32_t line_counter; // it will count how much lines like +something:data will appear
    uint8_t lines[MAX_STRING_COUNTER][MAX_STRING_LENGHT+1];
}AT_STATUS_DATA;
extern AT_STATUS_DATA at_RESULT; 
#endif