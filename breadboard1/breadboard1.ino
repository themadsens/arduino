#include <MaxMatrix.h>
#include "fonts.h"


void printCharWithShift(char c, int shift_speed);
void printStringWithShift(char* s, int shift_speed);
void printCharWithShiftRev(char c, int shift_speed);
void printStringWithShiftRev(char* s, int shift_speed);

// 8x8 LED blocks
const int data     = 13;  // DIN pin of MAX7219 module
const int load     =  2;  // CS pin of MAX7219 module
const int clock    =  3;  // CLK pin of MAX7219 module
const int maxInUse =  2;  // how many MAX7219 are connected

const int button   =  0;  // Button on A0;

MaxMatrix m(data, load, clock, maxInUse); // define Library

byte buffer[10];
char string1[] = " MadsenSoft.dk **";  // Scrolling Text
void setup(){
    m.init(); // module MAX7219
    m.setIntensity(5); // LED Intensity 0-15
    printStringWithShift(string1, 100);  // Send scrolling Text
}
void loop(){
    byte c;
    delay(100);
    m.shiftLeft(false, true);
    printStringWithShiftRev(string1, 100);  // Send scrolling Text
}
// Put extracted character on Display
void printCharWithShift(char c, int shift_speed){
    if (c < 32) return;
    c -= 32;
    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(maxInUse*8, 0, buffer);
    m.setColumn(maxInUse*8 + buffer[0], 0);
    for (int i=0; i<buffer[0]+1; i++) 
    {
        delay(shift_speed);
        m.shiftLeft(false, false);
    }
}
// Extract characters from Scrolling text
void printStringWithShift(char* s, int shift_speed){
    while (*s != 0){
        printCharWithShift(*s, shift_speed);
        s++;
    }
}

unsigned char reversebyte(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

// Put extracted character on Display - Reversed
void printCharWithShiftRev(char c, int shift_speed){
    if (c < 32) return;
    c -= 32;
    for (i = 0; i < 7 ; i++) {
        char c = pgm_read_byte(CH + 7*c + 6 - i);
        buffer[i] = reversebyte(c);

    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(maxInUse*8, 0, buffer);
    m.setColumn(maxInUse*8 + buffer[0], 0);
    for (int i=0; i<buffer[0]+1; i++) 
    {
        delay(shift_speed);
        m.shiftLeft(false, false);
    }
}
// Extract characters from Scrolling text - Reversed
void printStringWithShiftRev(char* s, int shift_speed){
    char *cp = s + strlen(s) - 1;
    while (cp >= s) {
        printCharWithShiftRev(*cp, shift_speed);
        cp--;
    }
}
