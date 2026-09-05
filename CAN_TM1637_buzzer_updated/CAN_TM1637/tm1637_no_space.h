#include "r_cg_macrodriver.h"


#define SEG_A   0b00000001
#define SEG_B   0b00000010
#define SEG_C   0b00000100
#define SEG_D   0b00001000
#define SEG_E   0b00010000
#define SEG_F   0b00100000
#define SEG_G   0b01000000

#define DEFAULT_BIT_DELAY  100
#define POSITION 0
#define Display_zero 0
#define LENGHTH_DISPLAY 4
#define DISPLAY_ALL 0



typedef enum { false, true } bool;



 bool writeByte( uint8_t b);
 void stop_condition( void ) ;
 void start_condition( void );
 void TM1637_DelayUsec( int milli );
 
 void TM1637Display_init(void);
 static void showDots(uint8_t dots, uint8_t* digits);
 static void showNumberBaseEx( int8_t base, uint16_t num, uint8_t dots, bool leading_zero, uint8_t length, uint8_t pos);
 void TM1637Display_setSegments( uint8_t Brightness,const uint8_t segments[], uint8_t length, uint8_t pos);
 void TM1637Display_clear( void );
 void TM1637Display_showNumberDec(int num, bool leading_zero, uint8_t length, uint8_t pos);
 void TM1637Display_showNumberDecEx(int num, uint8_t dots, bool leading_zero, uint8_t length, uint8_t pos);
 void TM1637Display_showNumberHexEx( uint16_t num, uint8_t dots, bool leading_zero, uint8_t length, uint8_t pos);
 uint8_t TM1637Display_encodeDigit(uint8_t digit);
 void TM1637_ClkLow(void);
 void TM1637_ClkHigh(void);
 void TM1637_DataHigh(void);
void TM1637_DataLow(void);
void TM1637Display_message(uint8_t*);

// __TM1637_H__
