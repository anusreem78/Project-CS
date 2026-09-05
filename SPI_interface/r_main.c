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
* Creation Date: 19-02-2025
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
#include <stddef.h>
#include <stdbool.h>
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

#define W25Q_WRITE_ENABLE    	0x06
#define W25Q_PAGE_PROGRAM    	0x02
#define W25Q_READ_DATA       	0x03 
#define W25Q_WRITE_DISABLE   	0x04
#define W25Q_READ_STATUS_REG 	0x05
#define W25Q_BUSY_BIT_MASK   	0x01  
#define W25Q_SECTOR_ERASE_CMD   0x20
#define W25Q_RESET_CMD 		0x66
#define W25Q_WRITE_DISABLE	0x04

uint8_t data_to_write[4] = { 0x01, 0x02, 0x03, 0x04};
uint8_t read_data[3] = {0};
uint8_t W25Q_id[3];
uint8_t zero[3]= {0xab,0xbc,0xcd};

uint32_t id;

extern uint16_t count_ms ;
extern uint8_t t;
void hdwinit(void);

void W25Q_Page_Program(uint32_t address, uint8_t *data, uint16_t length);
void W25Q_Read_Data(uint32_t address, uint8_t *buffer, uint16_t length);
void W25Q_Sector_Erase(uint32_t address);
void W25Q_Read_ID(void);
void W25Q_Reset(void);
void W25Q_Write_Disable(void);
void W25Q_Write_Enable(void);

void CS_LOW(void);
void CS_HIGH(void);

void Delay_ms(uint16_t ms);

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
    
    R_SAU0_Create();
    R_CSI00_Create();
    R_CSI00_Start();
    
    CS_HIGH();
    
    W25Q_Read_ID();
    Delay_ms(5);
       
    CS_LOW();    
    R_CSI00_Send_Receive(zero, 3,read_data);
    CS_HIGH();
    
    /*
    //W25Q_Sector_Erase(0x000010);        
    W25Q_Page_Program(0x000010, data_to_write, 4);
    Delay_ms(1000);    
    W25Q_Read_Data(0x000010, read_data, 4);
    Delay_ms(1000); */
    
    R_CSI00_Stop();
    
    while (1U)
    {  
  
    } 
   
    /*End user code. Do not edit comment generated here */
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

void Delay_ms(uint16_t ms)
{
	count_ms = 0;
	R_TAU0_Channel0_Start();
	while(count_ms < ms);
	R_TAU0_Channel0_Stop();
}

void CS_LOW(void)
{
	 PM1 &= ~0x10U;  /* Set P1.4 as output */
}
void CS_HIGH(void)
{
	P1 |= 0x10U;   // Set P1.4 (CS) high
}

void W25Q_Read_ID(void) {
    uint8_t cmd = 0x9F; //0x9F
    
    //W25Q_Write_Enable();    
    CS_LOW();  
    R_CSI00_Send_Receive(&cmd, 1, zero);  
    R_CSI00_Send_Receive(zero, 3, W25Q_id);  
    Delay_ms(20);
    CS_HIGH();
}

void W25Q_Write_Enable(void)
{
    uint8_t command = W25Q_WRITE_ENABLE;
    
    CS_LOW();
    R_CSI00_Send_Receive(&command, 1, NULL);  // Send the Write Enable command
    CS_HIGH();
}

void W25Q_Write_Disable(void)
{
    uint8_t command = W25Q_WRITE_DISABLE;
    
    CS_LOW();
    R_CSI00_Send_Receive(&command, 1, NULL);  // Send the Write Enable command
    CS_HIGH();
}

// Function to write data to a specific address in the flash memory
void W25Q_Page_Program(uint32_t address, uint8_t *data, uint16_t length)
{
    uint8_t command[4];  
    command[0] = W25Q_PAGE_PROGRAM;
    command[1] = (address >> 16) & 0xFF;  // Address MSB
    command[2] = (address >> 8) & 0xFF;   // Address middle byte
    command[3] = (address) & 0xFF;        // Address LSB
   
    W25Q_Write_Enable();   
    CS_LOW();
    R_CSI00_Send_Receive(command, 4, NULL);    // Send the command and address
    R_CSI00_Send_Receive(data, length, NULL);  // Send the data
    CS_HIGH();
    W25Q_Write_Disable();
}

void W25Q_Read_Data(uint32_t address, uint8_t *buffer, uint16_t length)
{
    uint8_t command[4]; 
    // Prepare the Read Data command
    command[0] = W25Q_READ_DATA;  // Replace with actual read command
    command[1] = (address >> 16) & 0xFF;  // Address MSB
    command[2] = (address >> 8) & 0xFF;   // Address middle byte
    command[3] = (address) & 0xFF;        // Address LSB

   
    CS_LOW();
    R_CSI00_Send_Receive(command, 4, NULL);  // Send the command and address
    R_CSI00_Send_Receive(NULL, length, buffer);  // Read the data
    CS_HIGH();
}

void W25Q_Sector_Erase(uint32_t address) {
    uint8_t cmd_buffer[4];
    
    W25Q_Write_Enable();
    
    cmd_buffer[0] = W25Q_SECTOR_ERASE_CMD;
    cmd_buffer[1] = (address >> 16) & 0xFF;
    cmd_buffer[2] = (address >> 8) & 0xFF;
    cmd_buffer[3] = address & 0xFF;
    
    CS_LOW();
    R_CSI00_Send_Receive(cmd_buffer, 4, NULL);
    CS_HIGH();
    
}

void W25Q_Reset() {
    uint8_t cmd_reset[2];    
    cmd_reset[0] = W25Q_RESET_CMD;
    cmd_reset[1] = 0x99;
    CS_LOW();  // Pull CS low to select the chip
    R_CSI00_Send_Receive(&cmd_reset, 2, NULL); // Send the RESET command
    CS_HIGH(); // Pull CS high to deselect the chip        
}


/* End user code. Do not edit comment generated here */
