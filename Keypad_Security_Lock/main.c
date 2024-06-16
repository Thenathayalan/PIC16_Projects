/*
 * File:   main.c
 * Author: thenathayalan
 *
 * Created on May 13, 2024, 8:20 PM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include "keypad.h" // Check this file for wiring the Keypad
#include "LCD.h"    // Check this file for wiring the Lcd

#define _XTAL_FREQ 20000000 // 20Mhz Clock Crystal

#define length 4    // Password length

int index = 0;
char passwd[length]={'1','2','3','4'};  // Default Password Change it
char input_pwd[length];
char val = 'n';

void main(){
    
    TRISA = 0x00;   // set PORTA as output connect relay pin to RA0
    PORTA = 0x01;   // Set RA0 as HIGH | For active high Relay set this as 0x00 
    keypad_init();
    lcd_init();
    lcd_clear();
    
    set_cursor(3,1);
    write_string("Secure Valute");
    set_cursor(2,2);
    write_string("Password: ");
    
    while(1){
        val = get_key();
        if(index<4 && val!='n'){
            set_cursor(index+11,2);
            write_char('*');
            input_pwd[index]=val;
            index++;
        }else if(val == 'D'){   // Press D to Check Password
            if(memcmp(passwd, input_pwd, length)==0){
                lcd_clear();
                set_cursor(3,1);
                write_string("Pin  Matched");
                PORTA = 0x00;   // Set RA0 as LOW | For active high Relay set this as 0x01 
                set_cursor(5,2);
                write_string("UNLOCKED");
            }else{
                lcd_clear();
                set_cursor(3,1);
                write_string("Pin Mismatch");
                set_cursor(2,2);
                write_string("Retry in 3 sec");
                __delay_ms(3000);
                break;
            }
        }else if(val == 'A'){   // Press A to Lock
            lcd_clear();
            set_cursor(6,1);
            write_string("Status");
            set_cursor(6,2);
            PORTA = 0x01;       // Set RA0 as HIGH | For active high Relay set this as 0x00 
            write_string("LOCKED");
            __delay_ms(2000);
            break;
        }
    }
}