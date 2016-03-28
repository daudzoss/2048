#include <stdint.h>
#include "lcd.h"

// for proper \n => \r\n behavior, need outString()
#include <pic24_all.h>

void printlcd(char const* str) {
  uint16_t i;
  for (i = 0; str[i]; i++)
   LCD_PutChar(str[i]);
  outString(str);
}

void printlcd4d(uint16_t val) {
 char num[5];
 uint16_t i;

 num[0] = ' ';
 num[1] = ' ';
 num[2] = ' ';
 num[3] = '0';
 num[4] = '\0';

 for (i = 3; val > 0; i--) {
  uint16_t dig;

  if (i < 0) {
   num[0] = 'O';
   num[1] = 'v';
   num[2] = 'r';
   num[3] = 'f';
   break;
  }
  dig = val % 10;
  val = val / 10;
  num[i] = ((char) dig) + '0';
 }
 
 printlcd(num);
}

void osimple(uint16_t* grid, uint16_t gridbytes, uint16_t value) {
 uint16_t i, j;

 if (grid) {
  for (i = 0; i < gridbytes>>3; i++) {
   outString("\n");
   for (j = 0; j < 4; j++)
    if ((value = *grid++) > 0)
     printlcd4d(value);
    else
     printlcd("[__]");
  }
 } else {
  printlcd("Congratulations!You reached ");
  printlcd4d(value);
 }
 outString("\n");
}

uint8 spress(void);

void summary(uint16_t score) {
 if (score & 1)
  printlcd("\nYou won with a good score: ");
 else
  printlcd("\nYou fell short. You scored ");

 printlcd4d(score & 0xfffe);
 printlcd(".");
 outString("\n");
}

void ssetup(void) {
 CONFIG_RD6_AS_DIG_INPUT(); // S3 (H)
 CONFIG_RD7_AS_DIG_INPUT(); // S6 (J)
 CONFIG_RA7_AS_DIG_INPUT(); // S5 (K)
 CONFIG_RD13_AS_DIG_INPUT(); // S4 (L)
}

uint8 S3pressed(void) {
  return (PORTDbits.RD6 == 0) ? 1 : 0;
}

uint8 S6pressed(void) {
  return (PORTDbits.RD7 == 0) ? 1 : 0;
}

uint8 S5pressed(void) {
  return (PORTAbits.RA7 == 0) ? 1 : 0;
}

uint8 S4pressed(void) {
  return (PORTDbits.RD13 == 0) ? 1 : 0;
}

uint8 dbounc(uint8 (*f)(void), uint8 c) {
  uint16 b = 0xffff;

  do {
    b <<= 1;
    b |= (*f)();
    doHeartbeat();
  } while (b);
  return c;
}

uint8 spress(void) {
 doHeartbeat();
 if (S3pressed()) return dbounc(S3pressed, 'h');   
 if (S6pressed()) return dbounc(S6pressed, 'j');
 if (S5pressed()) return dbounc(S5pressed, 'k');
 if (S4pressed()) return dbounc(S4pressed, 'l');
 return 0;
}
