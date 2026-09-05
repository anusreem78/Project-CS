#include "tm1637.h"
#include "iodefine.h"

const char Map_value[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
    0x00
};

char mins[1]={0x40};

unsigned char Address_Position[4]={0xc0,0xc1,0xc2,0xc3};



/***********************************************************************************************************************
* Function Name: TM1637_ClkHigh
* Description  : This function is used to clock pin High.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void TM1637_ClkHigh(void)
{
	
   PORT1=PORT1|1<<CLK_PIN;
      
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
	
     PORT1=PORT1|1<<SDA_PIN;
}

/***********************************************************************************************************************
* Function Name: TM1637_DataLow 
* Description  : This function is used to Data pin low.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void TM1637_DataLow(void)
{
	 
      PORT1=PORT1&(~(1<<SDA_PIN));
}

/***********************************************************************************************************************
* Function Name: TM1637_Init
* Description  : This function is used to init function for TM1637.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void TM1637_Init(void)
{
    
    TM1637_Stop();
    TM1637_Start();
    TM1637_Stop();  
   
    TM1637_SetBrightness(7);
}

/***********************************************************************************************************************
* Function Name: TM1637_DisplayDecimal
* Description  : This function is used to display the value in decimal format.
* Arguments    : first value for value display and second argument as ON or OFF display separator
* Return Value : None
***********************************************************************************************************************/

void TM1637_DisplayDecimal(int value_display, int displaySeparator)
{    int i;
    unsigned char digitArr[4];
    for (i = 0; i < 4; ++i) {
        digitArr[i] = Map_value[value_display % 10];
        if (i == 2 && displaySeparator) {
            digitArr[i] |= 1 << 7;
        }
       value_display /= 10;
    }

    TM1637_Start();
    TM1637_WriteByte(Autoincre_mode); // For Auto increment 
    TM1637_ReadResult();
    TM1637_Stop();

    TM1637_Start();
    TM1637_WriteByte(Address_Position[0]); // C0 - C3 address
    TM1637_ReadResult();

    for ( i = 0; i < 4; ++i) {
	    
        TM1637_WriteByte(digitArr[3 - i]);
        TM1637_ReadResult();
    }

    TM1637_Stop();
    
    
}
/***********************************************************************************************************************
* Function Name: TM1637_SetBrightness
* Description  : This function is used for setting brightness level.
* Arguments    : Takes arguments from 0 to 7  
* Return Value : None
* Valid brightness values: 0 - 8.
* 0 = display off.
* Brightness command:
* 1000 0XXX = display off
* 1000 1BBB = display on, brightness 0-7
* X = don't care
* B = brightness   
***********************************************************************************************************************/

void TM1637_SetBrightness(char brightness)
{
    
    TM1637_Start();
    TM1637_WriteByte(0x87+ brightness);
    TM1637_ReadResult();
    TM1637_Stop();
}

/***********************************************************************************************************************
* Function Name: TM1637_Start
* Description  : This function is used to generate the start condition.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void TM1637_Start(void)
{
    TM1637_ClkHigh();
    TM1637_DataHigh();
    TM1637_DelayUsec(5);
    TM1637_DataLow();
    TM1637_DelayUsec(5);
    TM1637_ClkLow();
    TM1637_DelayUsec(5);
   
}

/***********************************************************************************************************************
* Function Name: TM1637_Stop
* Description  : This function is used generate the stop condition.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void TM1637_Stop(void)
{
    TM1637_ClkLow();
    TM1637_DelayUsec(5);
    TM1637_DataLow();
    TM1637_DelayUsec(5);
    TM1637_ClkHigh();
    TM1637_DelayUsec(5);
    TM1637_DataHigh();
    TM1637_DelayUsec(5);
  
}

/***********************************************************************************************************************
* Function Name: TM1637_ReadResult
* Description  : This function is used read the ack from the slave.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void TM1637_ReadResult(void)
{
    TM1637_ClkLow();
    TM1637_DelayUsec(5);

    TM1637_ClkHigh();
    TM1637_DelayUsec(5);
    TM1637_ClkLow();
    TM1637_DelayUsec(5);
}

/***********************************************************************************************************************
* Function Name: TM1637_WriteByte
* Description  : This function is used to clock pin low.
* Arguments    : It take argument as 1byte which may be command or data
* Return Value : None
***********************************************************************************************************************/

void TM1637_WriteByte(unsigned char One_byte)
{
	int i;
	for ( i = 0; i < 8; ++i) {
		TM1637_ClkLow();
		if (One_byte & 0x01) {
			TM1637_DataHigh();
		}
		else {
			TM1637_DataLow();
		}
		TM1637_DelayUsec(5);
		One_byte >>= 1;
		TM1637_ClkHigh();
		TM1637_DelayUsec(5);
	}
}

/***********************************************************************************************************************
* Function Name: TM1637_DelayUsec
* Description  : This function is used generate delay.
* Arguments    : It take argument as milli second 
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

