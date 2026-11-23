//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include "diag/Trace.h"
#include <string.h>
#include <stm32f0xx.h>
#include "cmsis/cmsis_device.h"

// ----------------------------------------------------------------------------
//
// read pot voltage and give it to dac
// measure signal frequency with TIM2 and show values on display
//

// ----- main() ---------------------------------------------------------------

// turn off these compiler warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

// register definitions are in stm32f051x8.h


// no prescaling for TIM2
#define myTIM2_PRESCALER ((uint16_t)0x0000)
// largest count before overflow
#define myTIM2_PERIOD ((uint32_t)0xFFFFFFFF)

#define myTIM3_PRESCALER ((uint16_t) 0xBB80) // TIM3 prescaler for 48MHz clock
#define myTIM3_PERIOD ((uint32_t) /*put a number here*/) // period still needs a value
void myGPIOA_Init(void);
void myGPIOB_Init(void);
void myGPIOC_Init(void);

void myTIM2_Init(void);
void myTIM3_Init(void);
void myEXTI_Init(void);
void myADC_Init(void);
void myDAC_Init(void);
void mySPI_Init(void);
void delay_ms(uint32_t);
// display functions using spi

...

void oled_Write(unsigned char);
void oled_Write_Cmd(unsigned char)
void oled_Write_Data(unsigned char)

void oled_config(void);

void refresh_OLED(void)

SPI_HandleTypeDef SPI_Handle;

float period = 0;
uint32_t edge = 0x0;
uint32_t count = 0x0000;
int source = 1;

unsigned int Freq = 0;  // measured frequency
unsigned int Res = 0;   // pot resistance

//
// commands to set up display
//
unsigned char oled_init_cmds[] =
{
    0xAE,
    0x20, 0x00,
    0x40,
    0xA0 | 0x01,
    0xA8, 0x40 - 1,
    0xC0 | 0x08,
    0xD3, 0x00,
    0xDA, 0x32,
    0xD5, 0x80,
    0xD9, 0x22,
    0xDB, 0x30,
    0x81, 0xFF,
    0xA4,
    0xA6,
    0xAD, 0x30,
    0x8D, 0x10,
    0xAE | 0x01,
    0xC0,
    0xA0
};


//
// each row is 8 bytes for one character
// ascii value gives the row so '4' uses Characters[52]
// send all 8 bytes to draw the character
//
unsigned char Characters[][8] = {
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // SPACE
    {0b00000000, 0b00000000, 0b01011111, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // !
    {0b00000000, 0b00000111, 0b00000000, 0b00000111, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // "
    {0b00010100, 0b01111111, 0b00010100, 0b01111111, 0b00010100,0b00000000, 0b00000000, 0b00000000},  // #
    {0b00100100, 0b00101010, 0b01111111, 0b00101010, 0b00010010,0b00000000, 0b00000000, 0b00000000},  // $
    {0b00100011, 0b00010011, 0b00001000, 0b01100100, 0b01100010,0b00000000, 0b00000000, 0b00000000},  // %
    {0b00110110, 0b01001001, 0b01010101, 0b00100010, 0b01010000,0b00000000, 0b00000000, 0b00000000},  // &
    {0b00000000, 0b00000101, 0b00000011, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // '
    {0b00000000, 0b00011100, 0b00100010, 0b01000001, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // (
    {0b00000000, 0b01000001, 0b00100010, 0b00011100, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // )
    {0b00010100, 0b00001000, 0b00111110, 0b00001000, 0b00010100,0b00000000, 0b00000000, 0b00000000},  // *
    {0b00001000, 0b00001000, 0b00111110, 0b00001000, 0b00001000,0b00000000, 0b00000000, 0b00000000},  // +
    {0b00000000, 0b01010000, 0b00110000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // ,
    {0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b00001000,0b00000000, 0b00000000, 0b00000000},  // -
    {0b00000000, 0b01100000, 0b01100000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // .
    {0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010,0b00000000, 0b00000000, 0b00000000},  // /
    {0b00111110, 0b01010001, 0b01001001, 0b01000101, 0b00111110,0b00000000, 0b00000000, 0b00000000},  // 0
    {0b00000000, 0b01000010, 0b01111111, 0b01000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // 1
    {0b01000010, 0b01100001, 0b01010001, 0b01001001, 0b01000110,0b00000000, 0b00000000, 0b00000000},  // 2
    {0b00100001, 0b01000001, 0b01000101, 0b01001011, 0b00110001,0b00000000, 0b00000000, 0b00000000},  // 3
    {0b00011000, 0b00010100, 0b00010010, 0b01111111, 0b00010000,0b00000000, 0b00000000, 0b00000000},  // 4
    {0b00100111, 0b01000101, 0b01000101, 0b01000101, 0b00111001,0b00000000, 0b00000000, 0b00000000},  // 5
    {0b00111100, 0b01001010, 0b01001001, 0b01001001, 0b00110000,0b00000000, 0b00000000, 0b00000000},  // 6
    {0b00000011, 0b00000001, 0b01110001, 0b00001001, 0b00000111,0b00000000, 0b00000000, 0b00000000},  // 7
    {0b00110110, 0b01001001, 0b01001001, 0b01001001, 0b00110110,0b00000000, 0b00000000, 0b00000000},  // 8
    {0b00000110, 0b01001001, 0b01001001, 0b00101001, 0b00011110,0b00000000, 0b00000000, 0b00000000},  // 9
    {0b00000000, 0b00110110, 0b00110110, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // :
    {0b00000000, 0b01010110, 0b00110110, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // ;
    {0b00001000, 0b00010100, 0b00100010, 0b01000001, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // <
    {0b00010100, 0b00010100, 0b00010100, 0b00010100, 0b00010100,0b00000000, 0b00000000, 0b00000000},  // =
    {0b00000000, 0b01000001, 0b00100010, 0b00010100, 0b00001000,0b00000000, 0b00000000, 0b00000000},  // >
    {0b00000010, 0b00000001, 0b01010001, 0b00001001, 0b00000110,0b00000000, 0b00000000, 0b00000000},  // ?
    {0b00110010, 0b01001001, 0b01111001, 0b01000001, 0b00111110,0b00000000, 0b00000000, 0b00000000},  // @
    {0b01111110, 0b00010001, 0b00010001, 0b00010001, 0b01111110,0b00000000, 0b00000000, 0b00000000},  // A
    {0b01111111, 0b01001001, 0b01001001, 0b01001001, 0b00110110,0b00000000, 0b00000000, 0b00000000},  // B
    {0b00111110, 0b01000001, 0b01000001, 0b01000001, 0b00100010,0b00000000, 0b00000000, 0b00000000},  // C
    {0b01111111, 0b01000001, 0b01000001, 0b00100010, 0b00011100,0b00000000, 0b00000000, 0b00000000},  // D
    {0b01111111, 0b01001001, 0b01001001, 0b01001001, 0b01000001,0b00000000, 0b00000000, 0b00000000},  // E
    {0b01111111, 0b00001001, 0b00001001, 0b00001001, 0b00000001,0b00000000, 0b00000000, 0b00000000},  // F
    {0b00111110, 0b01000001, 0b01001001, 0b01001001, 0b01111010,0b00000000, 0b00000000, 0b00000000},  // G
    {0b01111111, 0b00001000, 0b00001000, 0b00001000, 0b01111111,0b00000000, 0b00000000, 0b00000000},  // H
    {0b01000000, 0b01000001, 0b01111111, 0b01000001, 0b01000000,0b00000000, 0b00000000, 0b00000000},  // I
    {0b00100000, 0b01000000, 0b01000001, 0b00111111, 0b00000001,0b00000000, 0b00000000, 0b00000000},  // J
    {0b01111111, 0b00001000, 0b00010100, 0b00100010, 0b01000001,0b00000000, 0b00000000, 0b00000000},  // K
    {0b01111111, 0b01000000, 0b01000000, 0b01000000, 0b01000000,0b00000000, 0b00000000, 0b00000000},  // L
    {0b01111111, 0b00000010, 0b00001100, 0b00000010, 0b01111111,0b00000000, 0b00000000, 0b00000000},  // M
    {0b01111111, 0b00000100, 0b00001000, 0b00010000, 0b01111111,0b00000000, 0b00000000, 0b00000000},  // N
    {0b00111110, 0b01000001, 0b01000001, 0b01000001, 0b00111110,0b00000000, 0b00000000, 0b00000000},  // O
    {0b01111111, 0b00001001, 0b00001001, 0b00001001, 0b00000110,0b00000000, 0b00000000, 0b00000000},  // P
    {0b00111110, 0b01000001, 0b01010001, 0b00100001, 0b01011110,0b00000000, 0b00000000, 0b00000000},  // Q
    {0b01111111, 0b00001001, 0b00011001, 0b00101001, 0b01000110,0b00000000, 0b00000000, 0b00000000},  // R
    {0b01000110, 0b01001001, 0b01001001, 0b01001001, 0b00110001,0b00000000, 0b00000000, 0b00000000},  // S
    {0b00000001, 0b00000001, 0b01111111, 0b00000001, 0b00000001,0b00000000, 0b00000000, 0b00000000},  // T
    {0b00111111, 0b01000000, 0b01000000, 0b01000000, 0b00111111,0b00000000, 0b00000000, 0b00000000},  // U
    {0b00011111, 0b00100000, 0b01000000, 0b00100000, 0b00011111,0b00000000, 0b00000000, 0b00000000},  // V
    {0b00111111, 0b01000000, 0b00111000, 0b01000000, 0b00111111,0b00000000, 0b00000000, 0b00000000},  // W
    {0b01100011, 0b00010100, 0b00001000, 0b00010100, 0b01100011,0b00000000, 0b00000000, 0b00000000},  // X
    {0b00000111, 0b00001000, 0b01110000, 0b00001000, 0b00000111,0b00000000, 0b00000000, 0b00000000},  // Y
    {0b01100001, 0b01010001, 0b01001001, 0b01000101, 0b01000011,0b00000000, 0b00000000, 0b00000000},  // Z
    {0b01111111, 0b01000001, 0b00000000, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // [
    {0b00010101, 0b00010110, 0b01111100, 0b00010110, 0b00010101,0b00000000, 0b00000000, 0b00000000},  // back slash
    {0b00000000, 0b00000000, 0b00000000, 0b01000001, 0b01111111,0b00000000, 0b00000000, 0b00000000},  // ]
    {0b00000100, 0b00000010, 0b00000001, 0b00000010, 0b00000100,0b00000000, 0b00000000, 0b00000000},  // ^
    {0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000,0b00000000, 0b00000000, 0b00000000},  // _
    {0b00000000, 0b00000001, 0b00000010, 0b00000100, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // `
    {0b00100000, 0b01010100, 0b01010100, 0b01010100, 0b01111000,0b00000000, 0b00000000, 0b00000000},  // a
    {0b01111111, 0b01001000, 0b01000100, 0b01000100, 0b00111000,0b00000000, 0b00000000, 0b00000000},  // b
    {0b00111000, 0b01000100, 0b01000100, 0b01000100, 0b00100000,0b00000000, 0b00000000, 0b00000000},  // c
    {0b00111000, 0b01000100, 0b01000100, 0b01001000, 0b01111111,0b00000000, 0b00000000, 0b00000000},  // d
    {0b00111000, 0b01010100, 0b01010100, 0b01010100, 0b00011000,0b00000000, 0b00000000, 0b00000000},  // e
    {0b00001000, 0b01111110, 0b00001001, 0b00000001, 0b00000010,0b00000000, 0b00000000, 0b00000000},  // f
    {0b00001100, 0b01010010, 0b01010010, 0b01010010, 0b00111110,0b00000000, 0b00000000, 0b00000000},  // g
    {0b01111111, 0b00001000, 0b00000100, 0b00000100, 0b01111000,0b00000000, 0b00000000, 0b00000000},  // h
    {0b00000000, 0b01000100, 0b01111101, 0b01000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // i
    {0b00100000, 0b01000000, 0b01000100, 0b00111101, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // j
    {0b01111111, 0b00010000, 0b00101000, 0b01000100, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // k
    {0b00000000, 0b01000001, 0b01111111, 0b01000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // l
    {0b01111100, 0b00000100, 0b00011000, 0b00000100, 0b01111000,0b00000000, 0b00000000, 0b00000000},  // m
    {0b01111100, 0b00001000, 0b00000100, 0b00000100, 0b01111000,0b00000000, 0b00000000, 0b00000000},  // n
    {0b00111000, 0b01000100, 0b01000100, 0b01000100, 0b00111000,0b00000000, 0b00000000, 0b00000000},  // o
    {0b01111100, 0b00010100, 0b00010100, 0b00010100, 0b00001000,0b00000000, 0b00000000, 0b00000000},  // p
    {0b00001000, 0b00010100, 0b00010100, 0b00011000, 0b01111100,0b00000000, 0b00000000, 0b00000000},  // q
    {0b01111100, 0b00001000, 0b00000100, 0b00000100, 0b00001000,0b00000000, 0b00000000, 0b00000000},  // r
    {0b01001000, 0b01010100, 0b01010100, 0b01010100, 0b00100000,0b00000000, 0b00000000, 0b00000000},  // s
    {0b00000100, 0b00111111, 0b01000100, 0b01000000, 0b00100000,0b00000000, 0b00000000, 0b00000000},  // t
    {0b00111100, 0b01000000, 0b01000000, 0b00100000, 0b01111100,0b00000000, 0b00000000, 0b00000000},  // u
    {0b00011100, 0b00100000, 0b01000000, 0b00100000, 0b00011100,0b00000000, 0b00000000, 0b00000000},  // v
    {0b00111100, 0b01000000, 0b00111000, 0b01000000, 0b00111100,0b00000000, 0b00000000, 0b00000000},  // w
    {0b01000100, 0b00101000, 0b00010000, 0b00101000, 0b01000100,0b00000000, 0b00000000, 0b00000000},  // x
    {0b00001100, 0b01010000, 0b01010000, 0b01010000, 0b00111100,0b00000000, 0b00000000, 0b00000000},  // y
    {0b01000100, 0b01100100, 0b01010100, 0b01001100, 0b01000100,0b00000000, 0b00000000, 0b00000000},  // z
    {0b00000000, 0b00001000, 0b00110110, 0b01000001, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // {
    {0b00000000, 0b00000000, 0b01111111, 0b00000000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // |
    {0b00000000, 0b01000001, 0b00110110, 0b00001000, 0b00000000,0b00000000, 0b00000000, 0b00000000},  // }
    {0b00001000, 0b00001000, 0b00101010, 0b00011100, 0b00001000,0b00000000, 0b00000000, 0b00000000},  // ~
    {0b00001000, 0b00011100, 0b00101010, 0b00001000, 0b00001000,0b00000000, 0b00000000, 0b00000000}   // <-
};



void SystemClock48MHz( void )
{
//
// turn off pll
//
    RCC->CR &= ~(RCC_CR_PLLON);
//
// wait for pll to unlock
//
    while (( RCC->CR & RCC_CR_PLLRDY ) != 0 );
//
// set pll for 48MHz
//
    RCC->CFGR = 0x00280000;

//
// turn on pll
//
    RCC->CR |= RCC_CR_PLLON;

//
// wait for pll to lock
//
    while (( RCC->CR & RCC_CR_PLLRDY ) != RCC_CR_PLLRDY );

//
// use pll as system clock
//
    RCC->CFGR = ( RCC->CFGR & (~RCC_CFGR_SW_Msk)) | RCC_CFGR_SW_PLL;

//
// update system clock value
//
    SystemCoreClockUpdate();

}



int
main(int argc, char* argv[])
{

    volatile uint16_t potValRaw;
	volatile uint16_t potValResistance;
	volatile float potValVoltage;

	SystemClock48MHz();

    myGPIOA_Init();
    myGPIOB_Init();
    myGPIOC_Init();
    myDAC_Init();
    myADC_Init();
    myTIM2_Init();
    myTIM3_Init();
    mySPI_Init();
    myEXTI_Init();
    oled_config();
   

	while (1)
	{
                // poll adc
                if((ADC1->ISR & ADC_ISR_EOC) != 0) {

                    // read adc result and clear old overrun flag
                    potValRaw = (uint16_t)ADC1->DR;
                    ADC1->ISR = ADC_ISR_OVR;

                    // scale adc reading to voltage and pot resistance
                    potValVoltage = ((float)potValRaw * ADC_VOLTAGE) / 4095.0f;
                    potValResistance = ((uint32_t)potValRaw * POT_RESISTANCE) / 4095U;
                    Res = (unsigned int)potValResistance;

                    // give adc value to dac
                    DAC->DHR12R1 = potValRaw;

                    // refresh display when TIM3 update flag is set
                    if((TIM3->SR & TIm_SR_UIF) != 0) {

                        TIM3->SR = 0;
                        refresh_OLED();
                    }


                }
   
	}
 
}

void myGPIOA_Init() {

	// turn on GPIOA clock
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // PA0 user button as input
    GPIOA->MODER &= ~(GPIO_MODER_MODER0);
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR0);

    // PA1 ADC and PA4 DAC analog mode
    GPIOA->MODER |= GPIO_MODER_MODER1;
    GPIOA->MODER |= GPIO_MODER_MODER4;
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR4);

}
void myGPIOB_Init()
{
	// turn on GPIOB clock
	// Relevant register: RCC->AHBENR
	RCCC->AHBENR |= RC_AHBENR_GPIOBEN;

	// PB2 as input
	// Relevant register: GPIOB->MODER
	GPIOB->MODER &= ~(GPIO_MODER_MODER2); 

	/* a less cryptic view of what the foo &= ~(foobar) logic is doing */
	//	MODER register mask = 0011 0000
	// 	NOT mask = 1100 1111
	//  MODER register AND (NOT mask) --> 0000 0000 
	//  GPIO bits 4,5 00xx 0000 set to 00 = input mode


	// no pull up or pull down on PB2
	// Relevant register: GPIOB->PUPDR
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR2);


    /*
    
 GPIOB->MODER &= ~(GPIO_MODER_MODER2);
    GPIOB->MODER &= ~(GPIO_MODER_MODER3);
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR2 | GPIO_PUPDR_PUPDR3);

    // Start with CS# and RES# high.
    GPIOB->BSRR = (1U << 8) | (1U << 11);

    // PB8, PB9 and PB11 as outputs.
    GPIOB->MODER &= ~(GPIO_MODER_MODER8);
    GPIOB->MODER |= GPIO_MODER_MODER8_0;
    GPIOB->MODER &= ~(GPIO_MODER_MODER9);
    GPIOB->MODER |= GPIO_MODER_MODER9_0;
    GPIOB->MODER &= ~(GPIO_MODER_MODER11);
    GPIOB->MODER |= GPIO_MODER_MODER11_0;

    // PB13 and PB15 as alternate-function outputs, AF0 = SPI2.
    GPIOB->MODER &= ~(GPIO_MODER_MODER13);
    GPIOB->MODER |= GPIO_MODER_MODER13_1;
    GPIOB->MODER &= ~(GPIO_MODER_MODER15);
    GPIOB->MODER |= GPIO_MODER_MODER15_1;
    GPIOB->AFR[1] &= ~((uint32_t)0xF0F00000);
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR9 |
                      GPIO_PUPDR_PUPDR11 | GPIO_PUPDR_PUPDR13 |
                      GPIO_PUPDR_PUPDR15);
    
    */

}

void myGPIOC_Init(void)
{
    // turn on GPIOC clock
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    // PC8 and PC9 as led outputs
    GPIOC->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
    GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;
    GPIOC->BSRR = (1U << 8) | (1U << 25); // blue led for function generator
}

void myTIM2_Init()
{
	// turn on TIM2 clock
	// Relevant register: RCC->APB1ENR


	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	
	// count up and stop on overflow
	// buffer auto reload and interrupt on overflow only
	// Relevant register: TIM2->CR1
	TIM2->CR1 = ((uint16_t)0x008C);
	// set prescaler
	TIM2->PSC = myTIM2_PRESCALER;
	// set max count
	TIM2->ARR = myTIM2_PERIOD;

	// load timer settings
	// Relevant register: TIM2->EGR
	TIM2->EGR = ((uint16_t)0x0001);

    // clear timer flags
    TIM2->SR = 0;

	// set TIM2 interrupt priority to 1
	// Relevant register: NVIC->IP[3], or use NVIC_SetPriority
	NVIC_SetPriority(TIM2_IRQn, 1);

	// enable TIM2 interrupt
	// Relevant register: NVIC->ISER[0], or use NVIC_EnableIRQ
	NVIC_EnableIRQ(TIM2_IRQn);

	// interrupt when timer overflows
	// Relevant register: TIM2->DIER

	TIM2->DIER |= TIM_DIER_UIE;

	// TIM->CR1 |= TIM_CR1_CEN;
}

void myTIM3_Init(void)
{
    // turn on TIM3 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->CR1 = 0;
    TIM3->PSC = myTIM3_PRESCALER; // timer clock divided by prescaler + 1
    TIM3->ARR = myTIM3_PERIOD;   // update after period + 1 ticks
    // load settings then clear update flag
    TIM3->EGR = TIM_EGR_UG;
    TIM3->SR = 0;
    // start timer
    TIM3->CR1 |= TIM_CR1_CEN;
}

void myEXTI_Init()
{
	
	// map EXTI2 to PB2
	// Relevant register: SYSCFG->EXTICR[0]
	SYSCFG->EXTICR[0] |= 0x0100;

	// interrupt on rising edge
	// Relevant register: EXTI->RTSR

	EXTI->RTSR |= EXTI_RTSR_TR2;

	// allow EXTI2 interrupts
	// Relevant register: EXTI->IMR

	EXTI->IMR |= EXTI_IMR_MR2;

	// set EXTI2 interrupt priority to 0
	// Relevant register: NVIC->IP[2], or use NVIC_SetPriority

	NVIC_SetPriority(EXTI2_3_IRQn, 0);
	
	// enable EXTI2 interrupt
	// Relevant register: NVIC->ISER[0], or use NVIC_EnableIRQ

	NVIC_EnableIRQ(EXTI2_3_IRQn);

/*
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
    SYSCFG->EXTICR[0] &= ~((uint32_t)0x0000FF0F);
    SYSCFG->EXTICR[0] |= 0x00001100;

    EXTI->RTSR |= EXTI_RTSR_TR0 | EXTI_RTSR_TR2 | EXTI_RTSR_TR3;
    EXTI->FTSR &= ~(EXTI_FTSR_TR0 | EXTI_FTSR_TR2 | EXTI_FTSR_TR3);
    EXTI->PR = EXTI_PR_PR0 | EXTI_PR_PR2 | EXTI_PR_PR3;

    EXTI->IMR &= ~(EXTI_IMR_MR3);
    EXTI->IMR |= EXTI_IMR_MR0 | EXTI_IMR_MR2;

    // Equal priorities prevent nested changes to measurement variables.
    NVIC_SetPriority(EXTI0_1_IRQn, 1);
    NVIC_SetPriority(EXTI2_3_IRQn, 1);
    NVIC_EnableIRQ(EXTI0_1_IRQn);
    NVIC_EnableIRQ(EXTI2_3_IRQn);
*/


}

void EXTI0_1_IRQHandler(void)
{
    // user button handler still needs code
}


void TIM2_IRQHandler()
{
	// check if timer overflowed
	if ((TIM2->SR & TIM_SR_UIF) != 0)
	{
		TIM2->SR = 0;
        edge = 0;
        count = 0;

		// start timer again
		// Relevant register: TIM2->CR1

		TIM2->CR1 |= TIM_CR1_CEN;
	}
}
//
// signal measurement
//

void EXTI2_3_IRQHandler()
{
	// variables for this measurement

	// edge tracks first or second rising edge
	// time between the two edges is our period
	// first edge = 0
	// second edge = 1
	static uint8_t edge = 0x0;

	// store timer count
	uint32_t count_t;
	
	// period in microseconds and frequency in Hz
	float period;
	float frequency;

	// check if PB2 caused the interrupt
	if ((EXTI->PR & EXTI_PR_PR2) != 0)
	{
		//
		// first edge

		if(edge == 0x0) {

			// reset timer count
			TIM2->CNT = 0x0;

			// start timer
			TIM2->CR1 |= TIM1_CR1_CEN;
			
			// mark timer as started
			timerTriggered = 0x01;

				edge = 0x01;
		}


		// second edge
		else {

			// stop timer
			TIM2->CR1 &= ~TIM_CR1_CEN;

			// read timer count
			count_t = TIM2->CNT;

			
			// get period and frequency from count

			// 48 counts per microsecond so divide count by 48
			period = ((float)count_t / 48.0f);

			// frequency = 48MHz / count
			frequency = 48000000.0f / (float)count_t;



			// print as unsigned int since trace doesnt print floats here
			trace_printf("Period: %u us\n", (unsigned int)period);
			trace_printf("Frequency: %u Hz\n", (unsigned int)frequency);
			
			// reset edge flag
			edge = 0x0;
		}

		//
		// write 1 to clear pending flag
		
		EXTI->PR = EXTI_PR_PR2;

	}
}

void myADC_Init(void)
{
    // turn on adc and its 14MHz clock
    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
    RCC->CR2 |= RCC_CR2_HSI14ON;
    while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0);

    // adc disabled after reset, configure and calibrate before enable
    ADC1->CFGR2 = 0; // use HSI14 for adc clock
    // keep converting and overwrite old readings
    ADC1->CFGR1 = ADC_CFGR1_CONT | ADC_CFGR1_OVRMOD;
    ADC1->CFGR1 &= ~(ADC_CFGR1_ALIGN); // right align result
    ADC1->CHSELR = ADC_CHSELR_CHSEL1; // PA1 uses channel 1 
    ADC1->SMPR = 7; // longest sample time                  

    // calibrate adc and wait for it to finish
    ADC1->CR |= ADC_CR_ADCAL;
    while ((ADC1->CR & ADC_CR_ADCAL) != 0);
    delay_ms(1);

    // clear ready flag then enable adc
    ADC1->ISR = ADC_ISR_ADRDY;
    ADC1->CR |= ADC_CR_ADEN;
    while ((ADC1->ISR & ADC_ISR_ADRDY) == 0);
    // start conversions
    ADC1->CR |= ADC_CR_ADSTART;
}



void myDAC_Init() {
	// turn on dac clock
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
    DAC->DHR12R1 = 0; // start output at zero
    DAC->CR &= ~(DAC_CR_BOFF1); // turn on output buffer
    DAC->CR &= ~(DAC_CR_TEN1);  // no external trigger
    DAC->CR |= DAC_CR_EN1; // enable channel 1 on PA4
}

void mySPI_Init(void)
{
    // turn on SPI2 clock
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
    SPI2->CR1 = 0;
    SPI2->CR2 = ((uint16_t)0x0700); // 8 bit data

    // master sending on one line
    // software chip select and mode 0 with msb first
    SPI2->CR1 = SPI_CR1_MSTR | SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE |
                SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR;
    SPI2->CR1 |= SPI_CR1_SPE; // enable spi
}

void refresh_OLED( void )
{
    // 16 characters plus end of string
    unsigned char Buffer[17]; 

    snprintf( Buffer, sizeof( Buffer ), "R: %5u Ohms", Res );
    // buffer has the text to display
    // still need to select page and starting column
    // then send 8 bytes from Characters for each character

   


    snprintf( Buffer, sizeof( Buffer ), "F: %5u Hz", Freq );
    // buffer has the text to display
    // still need to select page and starting column
    // then send 8 bytes from Characters for each character

    ...


	// about 100ms between refreshes using TIM3 polling

    ...

}


void oled_Write_Cmd( unsigned char cmd )
{
    ... // make PB8 = CS# = 1
    ... // make PB9 = D/C# = 0
    ... // make PB8 = CS# = 0
    oled_Write( cmd );
    ... // make PB8 = CS# = 1
}

void oled_Write_Data( unsigned char data )
{
    ... // make PB8 = CS# = 1
    ... // make PB9 = D/C# = 1
    ... // make PB8 = CS# = 0 
    oled_Write( data );
    ... // make PB8 = CS# = 1
}


void oled_Write( unsigned char Value )
{

    // wait for TXE so spi can take another byte

    ...

    // send one byte through spi
    HAL_SPI_Transmit( &SPI_Handle, &Value, 1, HAL_MAX_DELAY );


    // wait for TXE then BSY to clear so last bit is sent

    ...

}


void oled_config( void )
{

// needs GPIOB clock and SPI2 clock on
// PB13 and PB15 need AF0

    SPI_Handle.Instance = SPI2;

    SPI_Handle.Init.Direction = SPI_DIRECTION_1LINE;
    SPI_Handle.Init.Mode = SPI_MODE_MASTER;
    SPI_Handle.Init.DataSize = SPI_DATASIZE_8BIT;
    SPI_Handle.Init.CLKPolarity = SPI_POLARITY_LOW;
    SPI_Handle.Init.CLKPhase = SPI_PHASE_1EDGE;
    SPI_Handle.Init.NSS = SPI_NSS_SOFT;
    SPI_Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    SPI_Handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
    SPI_Handle.Init.CRCPolynomial = 7;

//
// set up spi
//
    HAL_SPI_Init( &SPI_Handle );

//
// turn on spi
//
    __HAL_SPI_ENABLE( &SPI_Handle );


    // reset display with PB11 low then high
    // wait a few ms after each
    ...


//
// send display setup commands
//
    for ( unsigned int i = 0; i < sizeof( oled_init_cmds ); i++ )
    {
        oled_Write_Cmd( oled_init_cmds[i] );
    }


    // clear display memory
    // start at column 0 for each of the 8 pages
    // send 128 zero bytes per page

    ...


}



#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------