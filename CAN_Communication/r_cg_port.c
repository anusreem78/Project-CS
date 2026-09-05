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
* File Name    : r_cg_port.c
* Version      : CodeGenerator for RL78/F14 V2.03.07.02 [08 Nov 2021]
* Device(s)    : R5F10PPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for PORT module.
* Creation Date: 11-09-2024
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    P3 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0;
    PSRSEL = _00_PSR30_NORMAL;
    PM3 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE |
          _E0_PM3_DEFAULT;
	  
	  	POM1  = 0x00;                         //PORT 1 0th PIN IS SELECTED AS A NORMAL OUTPUT MODE.
	
	PM1   = 0x00;                         //PORT 1 0th PIN IS OUTPUT MODE AND OUT PUT BUFFER IS ON.
	
	P1    = 0x01;                         //PORT 1 0th PIN SET AS OUTPUT HIGH.	
	
//	PIOR4 = 0x00;                      
   
	PM1   = 0x02;                     //PORT 1 1st PIN IS INPUT MODE AND OUTPUT BUFFER IS OFF.
 
	PIM1  = 0x00;                     //PORT 1 1st  PIN IS SET TO NORMAL INPUT BUFFER. 
	
	PITHL1 = 0x00;                    //PORT 1 1st PIN IS SET TO SCHMITT1 INPUT TYPE. */
}

/* Start user code for adding. Do not edit comment generated here */
/*	POM1  = 0x00;                         //PORT 1 0th PIN IS SELECTED AS A NORMAL OUTPUT MODE.
	
	PM1   = 0x00;                         //PORT 1 0th PIN IS OUTPUT MODE AND OUT PUT BUFFER IS ON.
	
	P1    = 0x01;                         //PORT 1 0th PIN SET AS OUTPUT HIGH.	
	
//	PIOR4 = 0x00;                      
   
	PM1   = 0x02;                     //PORT 1 1st PIN IS INPUT MODE AND OUTPUT BUFFER IS OFF.
 
	PIM1  = 0x00;                     //PORT 1 1st  PIN IS SET TO NORMAL INPUT BUFFER. 
	
	PITHL1 = 0x00;                    //PORT 1 1st PIN IS SET TO SCHMITT1 INPUT TYPE. */
	
/* End user code. Do not edit comment generated here */
