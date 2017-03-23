/*
 * File:   FreqMeter.c
 * Author: joel.dada
 *
 * Created on March 22, 2017, 5:19 PM
 */
#define _XTAL_FREQ 20000000

#define RS RB7
#define EN RB6
#define D4 RB5
#define D5 RB4
#define D6 RB3
#define D7 RB2

#include <xc.h>
#include "lcd.h";
#include <stdio.h>

// BEGIN CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
//END CONFIG

char i;

unsigned long pulseCounter; // number of RB0 transition
unsigned int timerCounterOverflow; // number of timer0 overflows
unsigned char str[10]; // display result string
unsigned char freqString[20];

void interrupt ISR() {
    if (INTF && INTE) {
        INTF = 0;
        pulseCounter++;
    } else if (T0IF && T0IE) {
        T0IF = 0;
        timerCounterOverflow++;
    }
}

int main() {
    unsigned int shiftPosition;
    TRISB = 0x01;
    OPTION_REG = 0b11011000;
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("LCD Library for");
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("MPLAB XC8");
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Developed By");
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("Jocletech");
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("www.jocletech.com");

    for (shiftPosition = 0; shiftPosition < 15; shiftPosition++) {
        __delay_ms(300);
        Lcd_Shift_Left();
    }

    for (shiftPosition = 0; shiftPosition < 15; shiftPosition++) {
        __delay_ms(300);
        Lcd_Shift_Right();
    }

    while (1) {
        INTCON = 0b10110000;
        pulseCounter = 0;
        timerCounterOverflow = 0;
        while (timerCounterOverflow < 19532);
        GIE = 0;
        sprintf(freqString, "Freq- %i", pulseCounter);
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String(freqString);
    }
    return 0;
}