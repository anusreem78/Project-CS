#include "tm1637_no_space.h"

#define PORT1 P1
#define PORT12 P12
#define SDA_PIN 3
#define CLK_PIN 4
#define BRIGHTNESS 7
#define ON 1

#define TM1637_I2C_COMM1  0x40
#define TM1637_I2C_COMM2  0xC0
#define TM1637_I2C_COMM3  0x80


uint8_t Brightness  = ( BRIGHTNESS & 0x7) | (ON ? 0x08 : 0x00);
const uint8_t digitToSegment[] = {
    // XGFEDCBA
    0b00111111,    // 0
    0b00000110,    // 1
    0b01011011,    // 2
    0b01001111,    // 3
    0b01100110,    // 4
    0b01101101,    // 5
    0b01111101,    // 6
    0b00000111,    // 7
    0b01111111,    // 8
    0b01101111,    // 9
    0b01110111,    // A
    0b01111100,    // b
    0b00111001,    // C
    0b01011110,    // d
    0b01111001,    // E
    0b01110001     // F
};

const uint8_t minusSegments = 0b01000000;

/***********************************************************************************************************************
* Function Name: start_condition 
* Description  : This function generate that start condition for I2C.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
 void start_condition(void ){
 
      TM1637_DataLow();
      TM1637_DelayUsec(5);
      
}

 /***********************************************************************************************************************
* Function Name: stop_condition 
* Description  : This function generate that stop condition for I2C.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

 void stop_condition(void) {
	
    
    TM1637_DataLow();
    TM1637_DelayUsec(5);
    TM1637_ClkHigh();
    TM1637_DelayUsec(5);
    TM1637_DataHigh();
    TM1637_DelayUsec(5);
    
   
}
 /***********************************************************************************************************************
* Function Name: writeByte 
* Description  : This function is used to write the data in the I2C bus.
* Arguments    : 8bit data which is to be written 
* Return Value : true (1) or false (0) 
***********************************************************************************************************************/
bool writeByte( uint8_t data_write){
    uint8_t i, data = data_write;
    
    // 8 Data Bits
    for ( i = 0; i < 8; i++) {
      
        TM1637_ClkLow();
	TM1637_DelayUsec(5);

        // Set data bit
        if (data & 0x01)
           
	    TM1637_DataHigh();
        else
            
	     TM1637_DataLow();

        
        TM1637_DelayUsec(5);
        
	TM1637_ClkHigh();
	TM1637_DelayUsec(5);
        data = data >> 1;
    }

    
    TM1637_ClkLow();       //check for data low
    TM1637_DelayUsec(5);
    TM1637_DataLow();
    TM1637_ClkHigh();
    TM1637_DelayUsec(5);
    TM1637_ClkLow();
    TM1637_DelayUsec(5);
    
    return true;
}

/***********************************************************************************************************************
* Function Name: showDots 
* Description  : This function is used to display dot in tm1637.
* Arguments    : first argument as one or zero to turn ON or OFF the display
                 second argument as in which digit.
* Return Value : None
***********************************************************************************************************************/
static void showDots(uint8_t dots, uint8_t* digits) {
	int i;
    for (i = 0; i < 4; ++i) {
        digits[i] |= (dots & 0x80);
        dots <<= 1;
    }
}

 /***********************************************************************************************************************
* Function Name: showNumberBaseEx 
* Description  : This function is used extact the address as per data to display in the TM1637.
* Arguments    : This is 8bit buffer base which say decimal or hexadecimal value 
                 This 16bit buffer num which is used to display value  
                 uint8_t dots - ON or OFF dot on display
		 bool leading_zero - 1 use all 4 digit 
		                     0 use only digit required 
		 uint8_t length   -length to display
		 uint8_t pos      - which position you want
* Return Value : None
***********************************************************************************************************************/
 static void showNumberBaseEx( int8_t base, uint16_t num, uint8_t dots, bool leading_zero, uint8_t length, uint8_t pos) {
 uint8_t digits[4];
 int i; 
 
	bool negative = false;
    if (base < 0) {
        base = -base;
        negative = true;
    }

    

    if (num == 0 && !leading_zero) {
        for (i = 0; i < (length - 1); i++)
            digits[i] = 0;
        digits[length - 1] = TM1637Display_encodeDigit(0);
    } else {
        for (i = length - 1; i >= 0; --i) {
            uint8_t digit = num % base;

            if (digit == 0 && num == 0 && leading_zero == false)
                digits[i] = 0;
            else
                digits[i] = TM1637Display_encodeDigit(digit);

            if (digit == 0 && num == 0 && negative) {
                digits[i] = minusSegments;
                negative = false;
            }

            num /= base;
        }

        if (dots != 0) {
            showDots(dots, digits);
        }
    }
    TM1637Display_setSegments(Brightness,digits, length, pos);
}

/***********************************************************************************************************************
* Function Name: TM1637Display_init
* Description  : This function is used to initilize.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void TM1637Display_init( void ){
	 TM1637Display_showNumberDec(Display_zero,DISPLAY_ALL,LENGHTH_DISPLAY,POSITION);
   
   
}
/***********************************************************************************************************************
* Function Name: TM1637Display_setBrightness 
* Description  : This function is used to set the Brightness.
* Arguments    : Brightness 0-7
                 bool - 1 ON display 
		        0 OFF display
* Return Value : None
***********************************************************************************************************************/
/*
void TM1637Display_setBrightness( uint8_t brightness, bool on) {
   *Brightness  = (brightness & 0x7) | (on ? 0x08 : 0x00);
}
*/
/***********************************************************************************************************************
* Function Name: TM1637Display_setSegments
* Description  : This function is used generate I2C frame as per TM1637.
* Arguments    : Take argument as Brightness
                                  segments[]
				  length
				  position
* Return Value : None
***********************************************************************************************************************/
void TM1637Display_setSegments(uint8_t Brightness, const uint8_t segments[], uint8_t length, uint8_t pos) {
	uint8_t k;
    start_condition();
    writeByte( TM1637_I2C_COMM1);
    stop_condition();

    start_condition();
    writeByte( TM1637_I2C_COMM2 + (pos & 0x03));

    for ( k = 0; k < length; k++)
        writeByte( segments[k]);

    stop_condition();

    start_condition();
    writeByte( TM1637_I2C_COMM3 + ( Brightness & 0x0f));
    stop_condition();
}
/***********************************************************************************************************************
* Function Name: TM1637Display_clear
* Description  : This function is used to Clear the display.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void TM1637Display_clear(void) {
    uint8_t data[] = { 0, 0, 0, 0 };
    TM1637Display_setSegments( Brightness,data, 4, 0);
}
/***********************************************************************************************************************
* Function Name: TM1637Display_showNumberDec
* Description  : This function is used to Display for decimal number.
* Arguments    : it take 4 arguments 
                 num - number which to  be display 
		 leading_zero - use required digit on display 
		 length - how much length
		 pos - which position to be display 0-3 
* Return Value : None
***********************************************************************************************************************/
void TM1637Display_showNumberDec( int num, bool leading_zero, uint8_t length, uint8_t pos) {
    TM1637Display_showNumberDecEx( num, 0, leading_zero, length, pos);
}
/***********************************************************************************************************************
* Function Name: TM1637Display_showNumberDecEx
* Description  : This function is used to Display for decimal number.
* Arguments    : it take 5 arguments 
                 num - number which to  be display 
		 dots - ON or OFF dot on in the display
		 leading_zero - use required digit on display 
		 length - how much length
		 pos - which position to be display 0-3 
* Return Value : None
***********************************************************************************************************************/
void TM1637Display_showNumberDecEx( int num, uint8_t dots, bool leading_zero, uint8_t length, uint8_t pos) {
    showNumberBaseEx( num < 0 ? -10 : 10, num < 0 ? -num : num, dots, leading_zero, length, pos);
}
/***********************************************************************************************************************
* Function Name: TM1637Display_showNumberHexEx
* Description  : This function is used to Display for Hexdecimal number.
* Arguments    : it take 5 arguments 
                 num - number which to  be display 
		 dots - ON or OFF dot on in the display
		 leading_zero - use required digit on display 
		 length - how much length
		 pos - which position to be display 0-3 
* Return Value : None
***********************************************************************************************************************/
void TM1637Display_showNumberHexEx( uint16_t num, uint8_t dots, bool leading_zero, uint8_t length, uint8_t pos) {
    showNumberBaseEx( 16, num, dots, leading_zero, length, pos);
}
/***********************************************************************************************************************
* Function Name: TM1637Display_encodeDigit 
* Description  : This function is used to take address for particular digit.
* Arguments    : digit 
* Return Value : 8bit value 
***********************************************************************************************************************/
uint8_t TM1637Display_encodeDigit(uint8_t digit) {
    return digitToSegment[digit & 0x0f];
}
/***********************************************************************************************************************
* Function Name: TM1637_DelayUsec
* Description  : This function is used to generate delay.
* Arguments    : milli second 
* Return Value : None
***********************************************************************************************************************/
void TM1637_DelayUsec(int milli)
{
  volatile int count;
  while(milli > 0){
	  count = 1000;
	  while(count > 0){
	count--;	  
	  }
	  milli--;
  }
}
/***********************************************************************************************************************
* Function Name: TM1637_ClkHigh 
* Description  : This function is used to clock pin High.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void TM1637_ClkHigh(void)
{
	
   PORT1 = PORT1|(1<<CLK_PIN);
      
}

/***********************************************************************************************************************
* Function Name: TM1637_ClkLow 
* Description  : This function is used to clock pin low.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void TM1637_ClkLow(void)
{
	
      PORT1=PORT1&(~(1<<CLK_PIN));
	
}

/***********************************************************************************************************************
* Function Name: TM1637_DataHigh
* Description  : This function is used to Data pin High.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void TM1637_DataHigh(void)
{
	
     PORT1=PORT1|(1<<SDA_PIN);
    
}

/***********************************************************************************************************************
* Function Name: TM1637_DataLow 
* Description  : This function is used to Data pin low.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void TM1637_DataLow(void)
{
	 
     PORT1 = PORT1 &(~(1<<SDA_PIN));
      
}
void TM1637Display_message(uint8_t *message) {
	uint8_t k;
		
    start_condition();
    writeByte( TM1637_I2C_COMM1 );
    stop_condition();

    start_condition();
    writeByte( TM1637_I2C_COMM2 + ( 0x00 & 0x03 ));

    for ( k = 0; k < 4; k++)
        writeByte( message[k] );   
        stop_condition();

        start_condition();
         writeByte( TM1637_I2C_COMM3 + ( Brightness & 0x0f ));
        stop_condition();
}
