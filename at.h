#ifndef __AT_H
#define __AT_H

#include<stdint.h>
#define MAX_STRING_COUNTER 1000//it will contain a max of 1000 strings
#define MAX_STRING_LENGTH 128 // max length of the string will be 128
#define CR 0x0D
#define LF 0x0A
#define PLUS 0x2B
#define E 0x45
#define O 0x4F
#define R 0x52
#define K 0x4B
int32_t validator(uint8_t character);
typedef struct {
    uint8_t ok; //if ok = 1 means ok , if ok = 0 means error
    uint32_t line_counter; // it will count how much lines like +something:data will appear
    uint32_t currentLineLength[MAX_STRING_COUNTER];
    uint8_t lines[MAX_STRING_COUNTER][MAX_STRING_LENGTH+1];
}AT_STATUS_DATA;
extern AT_STATUS_DATA at_RESULT;
#endif