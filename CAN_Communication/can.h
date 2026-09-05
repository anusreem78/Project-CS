/***********************************/
//*****     can.h FILE      ****//
/***********************************/       

/***HEADER FILE INCLUSION ***/
#include<stdint.h>

/*** FUNCTION DECLARATIONS ***/ 
void CAN_Initial(void);
void TRANSITION_TO_OPERRATING_AND_COMMUNICATION_MODE(void);
//void CAN_TRANSMIT_DATA_WRITE_FUN(uint16_t ID,uint8_t IDE,uint8_t RTR,uint8_t DLC,uint8_t *DATA);
void CAN_RECEIVE_AND_READ_FUN(uint32_t *RX_ID,uint8_t *RX_IDE,uint8_t *RX_RTR,uint8_t *RX_DLC,uint8_t *RX_DATAS);
//void CAN_TRANSMIT_DATA_WRITE_FUN(void);
void CAN_TRANSMIT_DATA_WRITE_FUN(uint8_t* );
void CALL_CAN_TRANSMIT_FUN(void);
void CAN_RECEIVE_FUN(void);
 
 
/** MACROS INCLUSION **/
#define CAN_INPUT_CLOCK_SUPPLY     0x01; 

/*** VARIABLES DECLARATION ***/


 
 
 




	