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
* Creation Date: 19-09-2024
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "r_cg_wdt.h"
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
const uint8_t tx_buf[2] = {0x11,0x22};
float temperature;
uint8_t slave_address;
uint8_t i2c_read_address;
uint8_t i2c_write_address;
int16_t raw_temp;
uint8_t temp_register = 0x00;

void hdwinit(void);
MD_STATUS R_UART0_Send(uint8_t * const tx_buf, uint16_t tx_num);
void R_SAU0_Create(void);
float Read_LM75_Temperature(void);
void HAL_Delay(uint32_t t);
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
    //R_UART1_Start();
    R_SAU0_Create();
    R_IIC00_Create();
    R_IIC00_StartCondition();    
    while (1U)
    {
      temperature = Read_LM75_Temperature();            
      HAL_Delay(1);
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

void HAL_Delay(uint32_t t)
{
	uint32_t Time = t * 9;
	while (--Time) {}
}


// Function to read temperature from LM75
float Read_LM75_Temperature(void)
{
    uint8_t temp_data[2] = {0};   // Array to store the two bytes of temperature data
    MD_STATUS status;

    slave_address = 0x48; // LM75 base address
    i2c_read_address = (slave_address << 1) | 0x01; // Address for read operation (0x91 if all address pins are GND)
    i2c_write_address = (slave_address << 1)| 0x00;  // Address for write operation
        
    // Start I2C communication
    
    //Send slave address with the read/write bit   
     
    R_IIC00_Master_Send(0x90, &temp_register, 1);
    HAL_Delay(500);
 
    //Receive
    R_IIC00_Master_Receive(0x91, &temp_data, 2);
    
    HAL_Delay(500);
    
    // Send stop condition
  //  R_IIC00_StopCondition();
    
        // Combine the two bytes of temperature data
    raw_temp = (temp_data[0] << 8) | temp_data[1];
    raw_temp >>= 7;  // Shift right to account for LM75's 9-bit resolution

   /* if (raw_temp & 0x0100) {
        raw_temp |= 0xFE00;  // Sign-extend for negative numbers
    }*/
        // Calculate temperature in Celsius (LM75 resolution is 0.125°C per LSB)
    temperature = raw_temp * 0.5;
    return temperature;       // Return the calculated temperature value
    
}
/* End user code. Do not edit comment generated here */
