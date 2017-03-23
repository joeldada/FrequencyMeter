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

int main()
{
    unsigned int a;
    TRISB = 0x00;
    Lcd_Init();
    while(1)
    {
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("LCD Library for");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("MPLAB XC8");
        __delay_ms(2000);
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Developed By");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("Jocletech");
        __delay_ms(2000);
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("www.jocletech.com");

        for(a=0;a<15;a++)
        {
            __delay_ms(300);
            Lcd_Shift_Left();
        }

        for(a=0;a<15;a++)
        {
            __delay_ms(300);
            Lcd_Shift_Right();
        }

        Lcd_Clear();
        Lcd_Set_Cursor(2,1);
        Lcd_Write_Char('e');
        Lcd_Write_Char('S');
        __delay_ms(2000);
    }
    return 0;
}