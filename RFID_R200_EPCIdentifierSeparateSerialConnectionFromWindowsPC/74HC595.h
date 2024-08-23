#ifndef _74HC595
#define _74HC595

int bits[] = {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000};
int mask[] = {0b11111110, 0b11111101, 0b11111011, 0b11110111, 0b11101111, 0b11011111, 0b10111111, 0b01111111};

int data = 4; // data pin on 74HC595
int clock = 6; // clock pin on 74HC595
int latch = 5; // latch pin on 74HC595
byte leds = 0b0; // led index number controlled by 74HC595

int on = 1; // set the global variable on
int off = 0; // set the global variable on

#endif