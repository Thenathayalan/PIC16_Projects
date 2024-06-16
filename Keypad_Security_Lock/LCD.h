/*
 * File:   LCD.h
 * Author: thenathayalan
 *
 * Created on May 13, 2024, 8:20 PM
 */

#define _XTAL_FREQ 20000000
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

void lcd_bit(char bit)
{
    if(bit& 1)
        D4 = 1;
    else
        D4 = 0;
    if(bit& 2)
        D5 = 1;
    else
        D5 = 0;
    if(bit& 4)
        D6 = 1;
    else
        D6 = 0;
    if(bit& 8)
        D7 = 1;
    else
        D7 = 0;
}

void lcd_cmd(char cmd)
{
    RS = 0;
    lcd_bit(cmd);
    EN = 1;
    __delay_ms(4);
    EN = 0;
}

lcd_clear()
{
    lcd_cmd(0);
    lcd_cmd(1);
}

void lcd_init()
{
  TRISD = 0x00;
  lcd_bit(0x00);
  __delay_ms(30);
  lcd_cmd(0x03);
  __delay_ms(5);
  lcd_cmd(0x03);
  __delay_ms(11);
  lcd_cmd(0x03); 
  lcd_cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  lcd_cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  lcd_cmd(0x08); //Select Row 1
  lcd_cmd(0x00); //Clear Row 1 Display
  lcd_cmd(0x0C); //Select Row 2
  lcd_cmd(0x00); //Clear Row 2 Display
  lcd_cmd(0x06);
}

void write_char(char data)
{
    char lower, upper;
    lower = data & 0x0F; //0000 1111 = 1111
    upper = data & 0xF0; //1111 0000 >> 4 = 1111
    RS = 1;
    lcd_bit(upper >> 4);
    EN = 1;
    __delay_ms(4);
    EN = 0;
    lcd_bit(lower);
    EN = 1;
    __delay_ms(4);
    EN = 0;
    __delay_ms(4);
}

void write_string(char *str)
{
  int i;
  for(i=0;str[i]!='\0';i++)
    write_char(str[i]);
}

void set_cursor(unsigned char c, unsigned char r)
{
  unsigned char Temp,Low4,High4;
  if(r == 1)
  {
    Temp = 0x80 + c - 1; //0x80 is used to move the cursor
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    lcd_cmd(High4);
    lcd_cmd(Low4);
  }
  if(r == 2)
  {
    Temp = 0xC0 + c - 1;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    lcd_cmd(High4);
    lcd_cmd(Low4);
  }
}

void lcd_sr()
{
  lcd_cmd(0x01);
  lcd_cmd(0x0C);
}

void lcd_sl()
{
  lcd_cmd(0x01);
  lcd_cmd(0x08);
}
