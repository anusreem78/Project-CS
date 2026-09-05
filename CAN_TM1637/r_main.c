
/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/F13 V2.03.07.02 [08 Nov 2021]
* Device(s)    : R5F10BAG
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 08-11-2023
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */

//#include "can.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */


#define ID 0x18FEEE00

//TM1637 DISPLAY FUNCTION PROTOTYPE
void R_MAIN_UserInit(void);
void TM1637_Init(void);
void TM1637_Demo(void);
void TM1637_DisplayDecimal(int v, int displaySeparator);
void TM1637_SetBrightness(char brightness);
void TM1637_Start(void);
void TM1637_Stop(void);
void TM1637_ReadResult(void);
void TM1637_WriteByte(unsigned char b);
void TM1637_DelayUsec(int );
void TM1637_ClkHigh(void);
void TM1637_ClkLow(void);
void TM1637_DataHigh(void);
void TM1637_DataLow(void);


const char segmentMap[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
    0x00
};




/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/*************function declaration*****************/


// hardware function 
void hdwinit(void);

// Delay function provided by the hardware abstraction layer
void HAL_Delay(uint32_t t);
extern void R_Systeminit(void);
extern void CAN_Initial(void);
extern void TRANSITION_TO_OPERRATING_AND_COMMUNICATION_MODE(void);
extern void CALL_CAN_TRANSMIT_FUN(void);
extern void PIN_CREATE(void);
extern void CAN_RECEIVE_AND_READ_FUN(uint32_t* RX_ID, uint8_t* RX_IDE, uint8_t* RX_RTR, uint8_t* RX_DLC, uint8_t* RX_DATAS);
uint32_t RX_ID;   // Receive message identifier
uint8_t RX_IDE;
uint8_t RX_RTR;
uint8_t RX_DLC;
uint8_t RX_DATA[8];
uint8_t tm_value=0;

/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void main(void)
{
	
	R_MAIN_UserInit();
	/* Start user code. Do not edit comment generated here */


	/***********Init function*************/
	//TM1637
	TM1637_Init();
	TM1637_SetBrightness(7);
	//can Init
	CAN_Initial();	//*********************************************
	HAL_Delay(2000);
	TRANSITION_TO_OPERRATING_AND_COMMUNICATION_MODE();

	while (1U)
	{
		TM1637_Init();
	        TM1637_SetBrightness(7);
		//HAL_Delay(2000);
		
		CAN_RECEIVE_AND_READ_FUN(&RX_ID, &RX_IDE, &RX_RTR, &RX_DLC, &RX_DATA); // for receiving the data through CAN 
		
		if (RX_ID == ID)
		{      
			
			tm_value=RX_DATA[0];
			TM1637_DisplayDecimal(tm_value, 0);// 1 for seperator ON 
			
		}


	}



	/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description : This function adds user code before implementing main function.
* Arguments : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{

	/* Start user code. Do not edit comment generated here */
	EI();
        hdwinit();
	
	/* End user code. Do not edit comment generated here */
}
/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: HAL_Delay
* Description : This function introduces a delay in milliseconds using a simple loop.
* Arguments : t - The delay time in milliseconds
* Return Value : None
***********************************************************************************************************************/
void HAL_Delay(uint32_t t)
{
	uint32_t Time = t * 9;
	while (--Time) {}
}
//TM1637 DISPALY FUNCTION


void TM1637_ClkHigh(void)
{

    P1=P1|1<<4;
    
}

void TM1637_ClkLow(void)
{
	 P1=P1&(~(1<<4));
}

void TM1637_DataHigh(void)
{
	P1=P1|1<<3;
}

void TM1637_DataLow(void)
{
	 P1=P1&(~(1<<3));
}
// DEMO FOR TM1637
void TM1637_Demo(void)
{
	uint8_t i = 0;

	TM1637_Init();
	TM1637_SetBrightness(7);

	while(1){
		TM1637_DisplayDecimal(i++, 0);
	}
}


void TM1637_Init(void)
{
	 // Ensure power is stable
    TM1637_DelayUsec(1000); // Delay 1ms for power stabilization
    // Perform a reset sequence
    TM1637_Stop();
    TM1637_Start();
    TM1637_Stop();  

    // Set brightness to a default value
   
    TM1637_SetBrightness(8);
}


void TM1637_DisplayDecimal(int v, int displaySeparator)
{    int i;
    unsigned char digitArr[4];
    for (i = 0; i < 4; ++i) {
        digitArr[i] = segmentMap[v % 10];
        if (i == 2 && displaySeparator) {
            digitArr[i] |= 1 << 7;
        }
        v /= 10;
    }

    TM1637_Start();
    TM1637_WriteByte(0x40);
    TM1637_ReadResult();
    TM1637_Stop();

    TM1637_Start();
    TM1637_WriteByte(0xc0);
    TM1637_ReadResult();

    for ( i = 0; i < 4; ++i) {
        TM1637_WriteByte(digitArr[3 - i]);
        TM1637_ReadResult();
    }

    TM1637_Stop();
}

// Valid brightness values: 0 - 8.
// 0 = display off.
void TM1637_SetBrightness(char brightness)
{
    // Brightness command:
    // 1000 0XXX = display off
    // 1000 1BBB = display on, brightness 0-7
    // X = don't care
    // B = brightness
    TM1637_Start();
    //TM1637_WriteByte(0x87+ brightness);
    TM1637_WriteByte(0x8f);
    TM1637_ReadResult();
    TM1637_Stop();
}

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

void TM1637_Stop(void)
{
    TM1637_ClkLow();
    TM1637_DelayUsec(5);// add delay in need
    TM1637_DataLow();
    TM1637_DelayUsec(5);
    TM1637_ClkHigh();
    TM1637_DelayUsec(5);
    TM1637_DataHigh();
    TM1637_DelayUsec(5);
  
}

void TM1637_ReadResult(void)
{
    TM1637_ClkLow();
    TM1637_DelayUsec(5);

    TM1637_ClkHigh();
    TM1637_DelayUsec(5);
    TM1637_ClkLow();
    TM1637_DelayUsec(5);
}

void TM1637_WriteByte(unsigned char b)
{
	int i;
	for ( i = 0; i < 8; ++i) {
		TM1637_ClkLow();
		if (b & 0x01) {
			TM1637_DataHigh();
		}
		else {
			TM1637_DataLow();
		}
		TM1637_DelayUsec(5);
		b >>= 1;
		TM1637_ClkHigh();
		TM1637_DelayUsec(5);
	}
}

void TM1637_DelayUsec(int second)
{
  volatile int count;
  while(second>0){
	  count=1000;
	  while(count>0){
	count--;	  
	  }
	  second--;
  }
}



/* End user code. Do not edit comment generated here */
