/*
 * File:   Keypad.h
 * Author: thenathayalan
 *
 * Created on May 13, 2024, 8:20 PM
 */

#define _XTAL_FREQ 20000000
#define X1 RB0
#define X2 RB1
#define X3 RB2
#define X4 RB3
#define Y1 RB4
#define Y2 RB5
#define Y3 RB6
#define Y4 RB7

#define PORT_MODE PORTB
#define PORT_SET TRISB

void keypad_init(void)
{
    PORT_MODE = 0x00;
    PORT_SET = 0xF0;
    OPTION_REG &= 0x7F;
}

char keypad_scan(void)
{
    X1=0; X2=1; X3=1; X4=1;
    if(Y1==0) {__delay_ms(100); while(Y1==0); return '1';}
    if(Y2==0) {__delay_ms(100); while(Y2==0); return '2';}
    if(Y3==0) {__delay_ms(100); while(Y3==0); return '3';}
    if(Y4==0) {__delay_ms(100); while(Y4==0); return 'A';}
    
    X1=1; X2=0; X3=1; X4=1;
    if(Y1==0) {__delay_ms(100); while(Y1==0); return '4';}
    if(Y2==0) {__delay_ms(100); while(Y2==0); return '5';}
    if(Y3==0) {__delay_ms(100); while(Y3==0); return '6';}
    if(Y4==0) {__delay_ms(100); while(Y4==0); return 'B';}
    
    X1=1; X2=1; X3=0; X4=1;
    if(Y1==0) {__delay_ms(100); while(Y1==0); return '7';}
    if(Y2==0) {__delay_ms(100); while(Y2==0); return '8';}
    if(Y3==0) {__delay_ms(100); while(Y3==0); return '9';}
    if(Y4==0) {__delay_ms(100); while(Y4==0); return 'C';}
    
    X1=1; X2=1; X3=1; X4=0;
    if(Y1==0) {__delay_ms(100); while(Y1==0); return '*';}
    if(Y2==0) {__delay_ms(100); while(Y2==0); return '0';}
    if(Y3==0) {__delay_ms(100); while(Y3==0); return '#';}
    if(Y4==0) {__delay_ms(100); while(Y4==0); return 'D';}
    
    return 'n';
}

char get_key(void)
{
    char key = 'n';
    while(key == 'n')
        key = keypad_scan();
    return key;
}
