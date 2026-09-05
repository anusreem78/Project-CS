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
* Creation Date: 25-07-2024
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
#include "tm1637_no_space.h"
//#include "can.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */


#define ID_CHECK 0x18FEEE00


extern uint8_t Brightness;

void R_MAIN_UserInit(void);



/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/*************function declaration*****************/
uint8_t message_er1_l[4]={ 0x0 ,0x79 , 0x3F , 0x38 };  //EOL
uint8_t message_er2_c[4]={ 0x0,0x79 , 0x3F , 0x39 };   //EOC
uint8_t message_er3_f[4]={ 0x0 ,0x79 , 0x3F , 0x71 };  //EOF
uint8_t message_er4_0[4]={ 0x0 , 0x0 ,0x79 , 0x3F };   //EO
uint8_t message_er5_r[4]={ 0x0 ,0x79 , 0x77 ,0x77};    //ERR
// hardware function 
void hdwinit(void);

// Delay function provided by the hardware abstraction layer
void Delay(uint32_t t);
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
int16_t Raw_value;
int16_t Rec_value=0;
uint8_t check=1;
//int tmval=-45;
uint8_t BIP=0;  //2 test

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
	//timer init 
	R_PORT_Create();
	R_TAU0_Create();
        R_TAU0_Channel0_Start();
	R_TAU0_Channel1_Start();
	R_TAU0_Channel2_Start();
	
        TM1637Display_init();
	
	//can Init
	CAN_Initial();	
	Delay(2000); 
	TRANSITION_TO_OPERRATING_AND_COMMUNICATION_MODE();
	while (1U)
	{
		
		CAN_RECEIVE_AND_READ_FUN( &RX_ID, &RX_IDE, &RX_RTR, &RX_DLC, &RX_DATA ); 
		
		if ( RX_ID == ID_CHECK )
		{    
			RX_ID = 0;
			check = 1;
			Raw_value = RX_DATA[0];
			Rec_value = Raw_value - 40;
			TM1637Display_showNumberDec( Rec_value , DISPLAY_ALL , LENGHTH_DISPLAY , POSITION );
			
			 if(Rec_value >= 110){
				 
	                  BIP = 3;
	      
                          }
     
			 else if( Rec_value >= 100 && Rec_value <= 109 ){
	                 
			 BIP = 2;
			 
                          }
                         else if(  Rec_value >= 90 && Rec_value <= 99){
				 
                          BIP = 1;
			  
                           }
                         else{
				 
	                 BIP = 0;
			 
                         }
	
			
			
		}
		
		

	}



	/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
	hdwinit();
	EI();
        
	
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: HAL_Delay
* Description : This function introduces a delay in milliseconds using a simple loop.
* Arguments : t - The delay time in milliseconds
* Return Value : None
***********************************************************************************************************************/
void Delay(uint32_t t)
{
	uint32_t Time = t * 9;
	while (--Time) {}
}

/* End user code. Do not edit comment generated here */
