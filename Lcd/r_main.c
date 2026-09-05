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
* Version      : CodeGenerator for RL78/F14 V2.03.07.02 [08 Nov 2021]
* Device(s)    : R5F10PPJ
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 03-09-2024
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
void hdwinit(void);
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
void delay(long d)
{
	while(d--);
}

void printdata(unsigned char data)
{
	/*
	//Bit0, D0 , P63
	if ((data&0x01)==(0x01))
	{
		P6 = P6|(1<<3);
	}
	else
	{
		P6 = P6&(~(1<<3));
	}
	//Bit1
	if ((data&0x02)==(0x02))
	{
		P6 = P6|(1<<5);
	}
	else
	{
		P6 = P6&(~(1<<5));
	}
	//Bit2
	if ((data&0x04)==(0x04))
	{
		P6 = P6|(1<<7);
	}
	else
	{
		P6 = P6&(~(1<<7));
	}
	//Bit3
	if ((data&0x08)==(0x08))
	{
		P15 = P15|(1<<5);
	}
	else
	{
		P15 = P15&(~(1<<5));
	}*/
	//Bit4
	if ((data&0x10)==(0x10))
	{
		P15 = P15|(1<<6);
	}
	else
	{
		P15 = P15&(~(1<<6));
	}
	//Bit5
	if ((data&0x20)==(0x20))
	{
		P14 = P14|(1<<0);
	}
	else
	{
		P14 = P14&(~(1<<0));
	}
	//Bit6
	if ((data&0x40)==(0x40))
	{
		P7 = P7|(1<<7);
	}
	else
	{
		P7 = P7&(~(1<<7));
	}
	//Bit7
	if ((data&0x80)==(0x80))
	{
		P7 = P7|(1<<5);
	}
	else
	{
		P7 = P7&(~(1<<5));
	}
}

void lcd_data(unsigned char ch_data)
{
	printdata(ch_data);
	P7 =P7 |(1<<2);		// RS High 
	P7 =P7 &(~(1<<0));	//RW low
	P3 =P3|(1<<2);		// Enable High
	delay(10000);
	P3 =P3&(~(1<<2));	//Enable Low
	printdata(ch_data<<4);
	P7 =P7 |(1<<2);	
	P7 =P7 &(~(1<<0));
	P3 =P3|(1<<2);
	delay(2000);
	P3 =P3&(~(1<<2));	
}

void lcd_cmd(unsigned char cmd)
{
	printdata(cmd);
	P7 = P7 &(~(1<<2));
	P7 = P7 &(~(1<<0));
	P3 = P3|(1<<2);
	delay(10000);
	P3 = P3&(~(1<<2));
	printdata(cmd<<4);
	P7 = P7 &(~(1<<2));
	P7 = P7 &(~(1<<0));
	P3 = P3|(1<<2);
	delay(2000);
	P3 = P3&(~(1<<2));
}

void lcd_string(unsigned char str[], unsigned char length)
{
	unsigned char i=0;
	for(i=0;i<length;i++)
	{
		lcd_data(str[i]);
	}
}

void lcd_init(void)
{
	lcd_cmd(0x03);
	lcd_cmd(0x02);	//LCD in 4 bit mode, Cursor in home pos
	lcd_cmd(0x28);	// Initialise  LCD in 4 bit mode
	lcd_cmd(0x0C);	//Cursor ON
	lcd_cmd(0x06);
	//lcd_cmd(0x0E);//Display On and Cursor without Blinking.	
	lcd_cmd(0x01);	//Clear Screen
	delay(2000);
}
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
    lcd_init(); 
    while (1U)
    {  
    lcd_cmd(0x80);
    lcd_string("abcde",5); 
    lcd_cmd(0xC0);
    lcd_string("pqrst",5); 
    
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
   EI();
   hdwinit();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
