/***********************************/
//*****     can.c FILE      ****//
/***********************************/      

/***HEADER FILE INCLUSION ***/
#include "iodefine.h"
#include "can.h"
//#include "pin.h"

void CAN_Initial(void)
{
		
	PER2 = CAN_INPUT_CLOCK_SUPPLY;		//  ENABLING THE CAN INPUT CLOCK SUPPLY ,Enables reading from and writing to the SFR used by CAN. 
	
                                            	
	while(GSTS == 0x0008){  }		/*	CAN MODULE INITIALIZE THE CAN RAM ,AFTER THE CAN MODULE OPERATION IS ENABLED.
	                                                RAM INITIALIZATION TIME 276 CYCLES OF FCLK(CPU/PERIPHERAL HARDWARE CLOCK FREQUENCY) 
	                                                CONTROL MOVES TO NEXT INSTRUCTION,WHEN THE CAN RAM INITIALIZATION IS COMPLETED.	    */
	                                  	                                   	
	
	GCTRL = 0x0001;			/*	AFTER RESET, INITIAL VALUE OF GCTRL REGISTER IS 0X05,MEANS BY DEDFAULT CAN IS IN GLOBAL STOP MODE 
	                                        WRITING 0X0001 TO THIS REGISTER CAN MODE CHANGES TO GLOBAL RESET MODE.
	                                        3 FCLK CYCLES IS NEEDED TO CHANGE GLOBAL STOP MODE TO  GLOBAL RESET MODE.	*/
					   
	                                   
	while(GSTS == 0x0000){	}		//	CONTROL MOVES TO NEXT INSTRUCTION,WHEN THE CAN MODE TRANSITIONED TO GLOBAL RESET MODE.		   
					   
					   
	
	
	C0CTRL = 0x0001;		/*	AFTER RESET, INITIAL VALUE OF C0CTRL REGISTER IS 0X05,MEANS BY DEDFAULT CAN IS IN CHANNEL STOP MODE 
	                                        WRITING 0X0001 TO THIS REGISTER CAN MODE CHANGES TO CHANNEL RESET MODE.
	                                        3 FCLK CYCLES IS NEEDED TO CHANGE CHANNEL STOP MODE TO  CHANNEL RESET MODE.	*/
	                                   
 
					   
 	while(C0STSL == 0x0000){   }		//CONTROL MOVES TO NEXT INSTRUCTION,WHEN THE CAN MODE TRANSITIONED TO CHANNEL RESET MODE.
	       
		       
       
       
        GCFGL= 0x000A;
			/*	TRANSMIT ID PRIORITY,DLC CHECK and mirror function  ARE  ENABLED AND CAN CLOCK SOURCE SELECTED(FCLK/2)8MZ. 
                                TIMESTAMP CLOCK SOURCE (FCLK/2),DIVISION RATION IS 0.	*/
	
				    
	
				    
	//GCFGL= 0x0002;			/*	TRANSMIT ID PRIORITY,DLC CHECK IS ENABLED,MIRROR FUNCTION ARE  DISABLED AND CAN CLOCK SOURCE SELECTED(FCLK/2)8MZ. 
					        //TIMESTAMP CLOCK SOURCE (FCLK/2),DIVISION RATION IS 0.		*/		   
		
	GCFGH=0x01F4;                   //      interval timer 	prescalar is 500,when interval timer transmission function is used for tx-rx fifo buffers.
					  
	//C0CFGL = 0x0001;		//	BAUD RATE PRESCALAR IS P=1(WHILE CALCULATING (P+1)).
	
	//C0CFGH = 0x0014;		//	TOTAL TQ IS 8.COMMUNICATION SPEED IS 500 kbps.(FCAN(8MHZ)/BAUD RATE PRESCALAR (P+1) X  TQ COUNT FOR 1 BIT (8)) 
	
	C0CFGL = 0x0001;		//	BAUD RATE PRESCALAR IS P=1(WHILE CALCULATING (P+1)).
	
	C0CFGH = 0x003A;		//	TOTAL TQ IS 16.COMMUNICATION SPEED IS 500 kbps.(FCAN(16MHZ)/BAUD RATE PRESCALAR (P+1) X  TQ COUNT FOR 1 BIT (16)) 
	
	//C0CFGL = 0x0003;		//	BAUD RATE PRESCALAR IS P=1(WHILE CALCULATING (P+1)).
	
	//C0CFGH = 0x003A;		//	TOTAL TQ IS 16.COMMUNICATION SPEED IS 250 kbps.(FCAN(16MHZ)/BAUD RATE PRESCALAR (P+1) X  TQ COUNT FOR 1 BIT (16)) 
      
	//C0CFGL = 0x0001;		//	BAUD RATE PRESCALAR IS P=1(WHILE CALCULATING (P+1)).
	
	//C0CFGH = 0x0014;		//	TOTAL TQ IS 8.COMMUNICATION SPEED IS 1 mbps.(FCAN(16MHZ)/BAUD RATE PRESCALAR (P+1) X  TQ COUNT FOR 1 BIT (16)) 
	
      /*** RECEIVE RULE SETTING ***/
      
  //decode till there
      
	GRWCR = 0x0000;			//	RAM PAGE BIT IS SET 0 ,SO THAT RECEIVE RULE REGISTERS ARE ALLOCATED (AVAILABLE) TO WRITE RECEIVE RULES.
	
	GAFLCFG = 0x0001;		//	I HAVE SET ONLY ONE RECEIVE RULE 0.TOTAL 16 RECEIVE IS AVAILABLE PER CHANNEL.ONE RECEIVE RULE CONTAINS 12 BYTES DATA.
      
	GAFLIDL0 = 0x07AA;                //	I HAVE WRITTEN A 11 BI ID(0X07AA) IN RECEIVE RULE SET TX_ID REGISTER.
      
	//GAFLIDH0 = 0x27AA;             //	STANDARD IDE ,DATA FRAME ,11 BIT ID (0X7AA),OWN CAN NODE WILL BE RECEIVED TRANMIT MESSAGES LIKE WRITTEN IN RECEIVE RULE REGISTER. 
    
	//GAFLIDH0 = 0x07AA;               //	STANDARD IDE ,DATA FRAME ,11 BIT ID (0X7AA),RECEIVING MESSAGES FROM ANOTHER CAN NODE.
	
	
	GAFLIDH0 = 0x87AA;               //	EXTENDED IDE ,DATA FRAME ,11 BIT ID (0X7AA),RECEIVING MESSAGES FROM ANOTHER CAN NODE.
    
	//GAFLML0 = 0xFFFF;              //	RECEIVE RULE TX_ID MASK (COMPARE) REGISTER,ITS ENABLED.(IT COMPARES RECEIVED MESSAGE TX_ID ).
      
	GAFLML0 = 0x0000;                //	RECEIVE RULE TX_ID MASK (COMPARE) REGISTER,ITS DISABLED.(ITS NOT  COMPARES RECEIVED MESSAGE TX_ID AND REGARDED AS MATCHED ).     
      
	//GAFLMH0 = 0xDFFF;              //	IDE,RTR,11 BIT ID COMPARE REGISTER,ITS ENABLED.
     
	GAFLMH0 = 0x0000;                //	IDE,RTR,11 BIT ID COMPARE REGISTER,ITS DISABLED.IN RECEIVE RULE RECEIVING MESSAGES ARE REGARDED AS MATCHED.
      
     
	//GAFLPL0 = 0x0010;              //	CAN0 transmit/receive FIFO buffer 0 is Selected ,and this buffer is used for stored the messages.
      
	//GAFLPL0 = 0x8000;                //	receive buffer is selected and this buffer is used for store the messages.
    
	GAFLPL0 |= 0x0001;                //	receive fifo buffer 0 is selected and this buffer is used for store the messages.
	
	GAFLPH0 = 0x1AAA;                //	DLC LENGTH FIXED AT 1,WE HAVE TO TRANSMIT LENGTH IS (>=1<=8) ,12 BIT LABEL INFORMATION IS ADDED (AAA). 
      
     
	/***  SETTING RAM PAGE BIT TO 1 ***/
      
	GRWCR = 0x0001;                   /*	RAM PAGE BIT SET TO 1,receive buffer, receive FIFO buffer,transmit/receive FIFO buffer, 
                                                transmit buffer, transmit history data access registerS ALLOCATED.(AVAILABLE TO WRITE).	*/
					
					
	/*** RECEIVE BUFFER SETTING PROCEDURE ***/
     
	//RMNB = 0x0001;
                                         /*	HERE RECEIVE BUFFER IS SET FOR RECEIVING THE MESSAGES.
	                          ONE RECEIVE BUFFERS ARE SELECTED TO STORE MESSAGES.RECEIVE BUFFRES 0.
                                                TRANSMIT BUFFERS WILL BE SET IN CHANNEL COMMUNICATION MODE.	*/  

					   
	/*** tx-rx fifo buffer configuration for receiving mode  ***/	
	//CFCCL0 = 0x1100; 
					   
	                              /*	transmit receive buffer depth is 4 messages,	
                                                interrupt will generated ,when each messages received or transmitted.
					        transmit receive fifo buffer is now not enabled.	*/
    
	//CFCCH0 = 0x0000;                     //	transmit receive fifo buffer is in receiver mode.
	
	
	/*** tx-rx fifo buffer configuration for transmitting mode  ***/
	//CFCCL0 = 0x1100;             /*	transmit receive buffer depth is 4 messages,	
                                               /*(interrupt source) interrupt will generated ,when each messages received or transmitted.
					        transmit receive fifo buffer is now not enabled.	*/
	
						
        //CFCCH0 = 0x0A01;        
	                                     /*	transmit receive fifo buffer is in transmit mode,.*/
                                              /*  message transmission interval time prescalar is 10.
						Interval timer clock source is  Clock selected by the CFITR bit.
						Clock obtained by frequency-dividing fCLK/2 by the ITRCP[15:0] value.this clock is selected by CFITR bit.
						*/

	  
       /*receive fifo buffer setting procedure */						
		
       RFCC0 = 0x1100;                        /*	A receive fifo buffer depth is 4 messagess
                                                        Interrupt source is  each time message received.
							as if now receive fifo buffer is not enabled  */
       						
     
	/*** INTERRUPT SETTING for tx-rx fifo buffer ***/
     
     
	//CFCCL0|=0x0006;                      //	transmit receive fifo buffer transmit and receive interrupts are enabled. 
	
	/*** Interrupt setting for receive fifo buffer ***/
	
	 RFCC0 |= 0x0002;                      //       receive fifo buffer  receive interrupts is enabled.
    
					 
	/*** ERROR RECOVERY SETTING BUS OFF STATE ***/
    
	C0CTRH = 0x0000;                     //		ISO11898-1 compliant is selected for bus off recovery.
     
				       
	      
   
	//while(C0STSL ==0x0000){ }             //	if this statement is executed means communication is ready.
	               
     
	//while(C0STSH!=0x0000){  }                 //	just for reading the error count.
    
	//while(C0ERFLL!=0x0000){  }                //	just for reading the what errors occured.
   
   
    
}

void TRANSITION_TO_OPERRATING_AND_COMMUNICATION_MODE(void)
{
      
	/*** TRANSITION TO GLOBAL OPERATING MODE ***/
    
	
    
	GCTRL &= 0x0000; 		  /*	WRITING 0X0000 TO THIS REGISTER CAN MODE CHANGES TO GLOBAL OPEARING  MODE.
	                                  10 FCLK CYCLES IS NEEDED TO CHANGE GLOBAL STOP MODE TO  GLOBAL OPERATING MODE.	*/	       
				       
     
	while(GCTRL != 0x0000){	}	   //	CONTROL MOVES TO NEXT INSTRUCTION,WHEN THE CAN MODE TRANSITIONED TO GLOBAL OPERATING MODE.		   
					   
		
	
	
	/*** transmit receive fifo buffer enabling if buffer contains no messages (buffer empty) ***/
     //	if(CFSTS0==0x0001){
     //   	CFCCL0 |= 0x0001;
     //	} 

       /*** receive fifo buffer enabling if buffer contains no messages	***/
       	
        	RFCC0 |= 0x0001;          //	receive fifo buffer is enabled.
	 
	
     
	/*** TRANSITION TO CHANNEL COMMUNICATION MODE ***/
   
    
   
	C0CTRL &= 0x0000;          /*	WRITING 0x0000 TO THIS REGISTER CAN MODE CHANGES TO CHANNEL COMMUNICATION  MODE.
	                               2 CAN0 BIT TIMES  IS NEEDED TO CHANGE CHANNEL RESET MODE  TO  CHANNEL COMMUNICATION MODE.	*/  
				
				
				
	C0CTRL = 0x0008;			//	When this 3rd bit is set to 1, forcible return from the bus off state is made. This bit is always read as 0.
				 
      				 
	while(C0CTRL != 0x0000){  }           //	CONTROL MOVES TO NEXT INSTRUCTION,WHEN THE CAN MODE TRANSITIONED TO CHANNEL COMMUNICATIION MODE.

      

}  

//void CAN_TRANSMIT_DATA_WRITE_FUN(uint16_t TX_ID,uint8_t TX_IDE,uint8_t TX_RTR,uint8_t TX_DLC,uint8_t *TX_DATA)
//void CAN_TRANSMIT_DATA_WRITE_FUN(void)
void CAN_TRANSMIT_DATA_WRITE_FUN(uint8_t *TX_data)
{
	
   /*** Writing the data into the transmit receive fifo buffer  ***/		
	
//	if((CFSTS0&0x0003)==0x0001){                            //      tx-rx status buffer contains no messages and fifo buffer is not full means writing the messages into the tx-rx fifo buffer. 
			
	                    	                         //      tx-rx fifo buffer in transmit mode means we can write the data into the data buffers
		
//		CFIDL0 = TX_ID;                          //      I HAVE WRITTEN A 11 BIT IDENTIFIER TO THIS REGISTER.
		
//		CFIDH0 |= (TX_IDE<<15) | (TX_RTR<<14) | (TX_ID<<0);      //	TX_IDE,TX_RTR,11 BIT IDENTIFIER IS WRITTEN.
		
//		CFPTR0 |= (TX_DLC<<12);                                  //     TX_DLC LENGTH IS WRITTEN.
		
//		CFDF00  = TX_DATA[0];
//	        CFDF00 |= 8<<TX_DATA[1];
		
//		CFDF10  = TX_DATA[2];
//	        CFDF10 |= 8<<TX_DATA[3];
		
//		CFDF20  = TX_DATA[4];
//	        CFDF20 |= 8<<TX_DATA[5];
		
//		CFDF30  = TX_DATA[6];
//	        CFDF30 |= 8<<TX_DATA[7];
		
//		CFPCTR0=0x00FF;                                      //writing 0x00ff to this register control moves next stage to write the data in fifo buffer.
		
//	}
//	else{ }
		
	
   /*** Writing the data into the transmit buffer  ***/	
 /*    	TMIDL0 = TX_ID;                                    //	I HAVE WRITTEN A 11 BIT IDENTIFIER TO THIS REGISTER.
	
	TMIDH0 |= (TX_IDE<<15) | (TX_RTR<<14) | (TX_ID<<0);      //	TX_IDE,TX_RTR,11 BIT IDENTIFIER IS WRITTEN.
	
        TMPTR0  |= (TX_DLC<<12);                           //	TX_DLC LENGTH IS WRITTEN.
	
	TMDF00 = TX_DATA[0];                                  //	TX_DATA IS WRITTEN TO TRANSMIT BUFFER 0.   
	TMDF00 = TX_DATA[1];
	
	TMDF01 =TX_DATA[2];
	TMDF01 =TX_DATA[3];
	
	TMDF02 =TX_DATA[4];
	TMDF02 =TX_DATA[5];
	
	TMDF03 =TX_DATA[6];
	TMDF03 =TX_DATA[7];  */
	
	//TMIDL0 = 0x7A4;                                    //	I HAVE WRITTEN A 11 BIT IDENTIFIER TO THIS REGISTER.
	
	//TMIDH0 =0X07A4;      //	TX_IDE,TX_RTR,11 BIT IDENTIFIER IS WRITTEN.
	
        //TMPTR0  = 0x8000;                           //	TX_DLC LENGTH IS WRITTEN.
	
	
	uint8_t a=0x55;
	
	TMIDL0= 0X7A3;
	
	TMIDH0 =0X07A3;
	
        TMPTR0  = 0x8000;
	
	TMIDL1= 0X7A3;
	
	TMIDH1 =0X07A3;
	
        TMPTR1  = 0x8000;
	
	TMIDL2= 0X7A6;
	
	TMIDH2 =0X07A3;
	
        TMPTR2  = 0x8000;
	
   	TMDF00 |= (TX_data[0]<< 0);
	TMDF00 |= (TX_data[1]<< 8); 
		
	TMDF01|=(0x22<<0);
	TMDF01|=(0x22<<8);
		
	TMDF02|=(a<<0);
	TMDF02|=(a<<8);
		
	TMDF03|=(0x66<<0);
	TMDF03|=(0x77<<8);
	
	
	
	
	TMDF10 |= (TX_data[2]<< 0) ;
	TMDF10 |= (TX_data[3] << 8) ; 
		
	TMDF11|=(0x22<<0);
	TMDF11|=(0x22<<8);
		
	TMDF12|=(a<<0);
	TMDF12|=(a<<8);
		
	TMDF13|=(0x66<<0);
	TMDF13|=(0x77<<8);
	
	TMDF20|=(TX_data[4]<<0);
	TMDF20|=(TX_data[5]<<8);
		
	TMDF21|=(0x22<<0);
	TMDF21|=(0x22<<8);
		
	TMDF22|=(a<<0);
	TMDF22|=(a<<8);
		
	TMDF23|=(0x12<<0);
	TMDF23|=(0x34<<8);
	
	TMDF30|=(TX_data[6]<<0);
	TMDF30|=(TX_data[7]<<8);
		
	TMDF31|=(0x22<<0);
	TMDF31|=(0x22<<8);
		
	TMDF32|=(a<<0);
	TMDF32|=(a<<8);
		
	TMDF33|=(0x12<<0);
	TMDF33|=(0x34<<8);
	
	a++;
	
}	

void CALL_CAN_TRANSMIT_FUN(void)
{

	/*** Transmission using transmit buffers ***/
	TMC0 = 0x00;
	TMC0 = 0x01;                                              //	TRANSMISSION IS REQUESTED.
	
	
			if((TMSTS0 & 0xF9) == 0x00)	//check if no other transmit request is present or transmission is in progress
			TMC0 = 0x01;
			
	//while(TMSTS0 != 0x04){   }                      //	CONTROL MOVES TO NEXT STATEMENT,WHEN THE TRANSMISSION HAS BEEN COMPLETED.   

	
	TMSTS0=0x00;
	
 //	if(C0ERFLL !=0x0000){
	
 //       	C0CTRL = 0x0001; 
		
                                                              /*    AFTER RESET, INITIAL VALUE OF C0CTRL REGISTER IS 0X05,MEANS BY DEDFAULT CAN IS IN CHANNEL STOP MODE 
	                                                            WRITING 0X0001 TO THIS REGISTER CAN MODE CHANGES TO CHANNEL RESET MODE.
	                                                            3 FCLK CYCLES IS NEEDED TO CHANGE CHANNEL STOP MODE TO  CHANNEL RESET MODE.		*/
	                                   
 
					   
//		while(C0STSL == 0x0000){  }            //	CONTROL MOVES TO NEXT INSTRUCTION,WHEN THE CAN MODE TRANSITIONED TO GLOBAL RESET MODE.
	       
//		C0ERFLL &=0x0000;                     //	here all error flages are cleared.
			      
			      
		
//		C0CTRL &= 0x0000;
                                                      /*	WRITING 0x0000 TO THIS REGISTER CAN MODE CHANGES TO CHANNEL COMMUNICATION  MODE.
	                                                        2 CAN0 BIT TIMES  IS NEEDED TO CHANGE CHANNEL RESET MODE  TO  CHANNEL COMMUNICATION MODE.	*/ 
			      
//		while(C0CTRL != 0x0000){   }          //	CONTROL MOVES TO NEXT INSTRUCTION,WHEN THE CAN MODE TRANSITIONED TO CHANNEL COMMUNICATIION MODE.

                               
			       

								    
//	}
		
// 	while(TMSTS0 != 0x04){   }                      //	CONTROL MOVES TO NEXT STATEMENT,WHEN THE TRANSMISSION HAS BEEN COMPLETED.   

	/*** transmission using transmit receive fifo buffers ***/
	
//	CFCCL0 |=0x0001;                                //tx-rx fifo buffer is available,messages in the fifo buffer    
	                                                //and heighest priority message has been determined means transmission starts.
	
	
}

void CAN_RECEIVE_AND_READ_FUN(uint32_t *RX_ID,uint8_t *RX_IDE,uint8_t *RX_RTR,uint8_t *RX_DLC,uint8_t *RX_DATAS)
{
	
	/*** reading procedure for tx-rx receive fifo buffer,if  tx-rx receive fifo buffer is used for store the messages ***/
	
//	  if((CFSTS0 & 0x0001)== 0x0000) //CHECKING WHETHER THE RECEIVE BUFFER CONTAINS NEW MESSAGE OR NOT,IF NEW MESSAGE CONTAINS MEANS WE CAN READ. 
//	    {
		
//		*RX_ID = (uint16_t)CFIDL0;                        //    USING THIS RX_ID BUFFER WE CAN READ THE 11 BIT IDENTIFIER.
	
//		*RX_IDE = (uint8_t)(CFIDH0>>15);            	  //	USING THIS RX_IDE BUFFER WE CAN REAN THE IDE BIT.STANDARD OR EXTENTED.
	
//		*RX_ID = (uint16_t)(CFIDH0 & 0x0FFF);             //    USING THIS REGISTER ALSO WE CAN READ THE 11 BIT IDENTIFIER.
	
//		*RX_RTR = (uint8_t)((CFIDH0 & 0x4000)>>14);       //	USING THIS RX_RTR BUFFER WE CAN READ THE RTR BIT.DATA FRAME OR REMOTE FRAME. 
	
//		*RX_DLC =(uint8_t) (CFPTR0>>12);                  //	USING THIS BUFFER WE CAN READ THE DLC LENGH 
	
		//RX_DATAS[0] = (uint8_t)CFDF00;                 //	USING THIS BUFFER WE CAN READ THE DATA WHAT WAS RECEIVED.
//		RX_DATAS[0] = (CFDF00 >> 0) & 0XFF;               //	USING THIS BUFFER WE CAN READ THE DATA WHAT WAS RECEIVED.
//		RX_DATAS[1] = (CFDF00 >> 8) & 0XFF;               //	USING THIS BUFFER WE CAN READ THE DATA WHAT WAS RECEIVED.
	 
//		RX_DATAS[2] = (CFDF10 >> 0) & 0XFF;
//		RX_DATAS[3] = (CFDF10 >> 8) & 0XFF;
		
//		RX_DATAS[4] = (CFDF20 >> 0) & 0XFF;
//		RX_DATAS[5] = (CFDF20 >> 8) & 0XFF;
		
//		RX_DATAS[6] = (CFDF30 >> 0) & 0XFF;
//		RX_DATAS[7] = (CFDF30 >> 8) & 0XFF;
		
//		CFPCTR0=0xFFFF;   //	setting 0xffff in this register,read pointer control moves to next unread message in the transmit receive fifo buffer. 
	 
//   } 
//   else{
	   
//   } 

   
	/***  reading from  receive buffer if receive buffer is used for store the messages    ***/
   
//	while(RMND0!=0x0000){                                     //CHECKING WHETHER THE RECEIVE BUFFER CONTAINS NEW MESSAGE OR NOT,IF NEW MESSAGE CONTAINS MEANS WE CAN READ. 
		
//	 	GCTRL = 0x0001; 
		                      				 /*	transtion to global operation mode to global reset mode, 
	                                                                after that only we have clear receive buffer register RMND0.	*/             
		            
//		RMND0=0x0000;                             //	CLEARING THE RECEIVE BUFFER RECEIVE COMPLETE REGISTER.
	
//		*RX_ID = (uint16_t)RMIDL0;                //	USING THIS RX_ID BUFFER WE CAN READ THE 11 BIT IDENTIFIER.
	
//		*RX_IDE = (uint8_t)(RMIDH0>>15);            //	USING THIS RX_IDE BUFFER WE CAN REAN THE IDE BIT.STANDARD OR EXTENTED.
	
//	        *RX_ID = (uint16_t)(RMIDH0 & 0x0FFF);        //	USING THIS REGISTER ALSO WE CAN READ THE 11 BIT IDENTIFIER.
	
//	        *RX_RTR = (uint8_t)((RMIDH0 & 0x4000)>>14);   //  USING THIS RX_RTR BUFFER WE CAN READ THE RTR BIT.DATA FRAME OR REMOTE FRAME. 
	
//	        *RX_DLC =(uint8_t) (RMPTR0>>12);            //	USING THIS BUFFER WE CAN READ THE DLC LENGH 
	
//	        *RX_DATAS = (uint8_t)RMDF00;               //	USING THIS BUFFER WE CAN READ THE DATA WHAT WAS RECEIVED.
	
//	        RX_DATAS[0] = (RMDF00 >> 0) & 0XFF;
//	        RX_DATAS[1] = (RMDF00 >> 8) & 0XFF;
//	}
//	GCTRL &= 0x0000;                    //	transtion to global operrating mode.  	
	
	
	/***  reading from  receive FIFO buffer if receive FIFO buffer is used for store the messages    ***/
	
   if( (RFSTS0 & 0x0001) == 0x0000) //CHECKING WHETHER THE RECEIVE fifo BUFFER CONTAINS NEW MESSAGE OR NOT,IF NEW MESSAGE CONTAINS MEANS WE CAN READ. 
	    {
		
		//*RX_ID = RFIDL0;                        //    USING THIS RX_ID BUFFER WE CAN READ THE 11 BIT IDENTIFIER.
	
		*RX_IDE = (uint8_t)(RFIDH0>>15);           //	USING THIS RX_IDE BUFFER WE CAN READ THE IDE BIT.STANDARD OR EXTENTED.
	
		//*RX_ID = ( RFIDL0|(RFIDH0&1FFF)<<16);     //    USING THIS REGISTER ALSO WE CAN READ THE 11 BIT IDENTIFIER.
	
		
		*RX_ID =(((uint32_t)RFIDH0<<16) | RFIDL0) & 0x1FFFFFFF;
		*RX_RTR = (uint8_t)((RFIDH0 & 0x4000)>>14);       //	USING THIS RX_RTR BUFFER WE CAN READ THE RTR BIT.DATA FRAME OR REMOTE FRAME. 
	
		*RX_DLC =(uint8_t) (RFPTR0>>12);                  //	USING THIS BUFFER WE CAN READ THE DLC LENGH 
	
		//RX_DATAS[0] = (uint8_t)CFDF00;                 //	USING THIS BUFFER WE CAN READ THE DATA WHAT WAS RECEIVED.
		RX_DATAS[0] = (RFDF00 >> 0) & 0XFF;               //	USING THIS BUFFER WE CAN READ THE DATA WHAT WAS RECEIVED.
		RX_DATAS[1] = (RFDF00 >> 8) & 0XFF;               //	USING THIS BUFFER WE CAN READ THE DATA WHAT WAS RECEIVED.
	 
	        RX_DATAS[2] = (RFDF10 >> 0) & 0XFF;
		RX_DATAS[3] = (RFDF10 >> 8) & 0XFF;
		
		RX_DATAS[4] = (RFDF20 >> 0) & 0XFF;
		RX_DATAS[5] = (RFDF20 >> 8) & 0XFF;
		
		RX_DATAS[6] = (RFDF30 >> 0) & 0XFF;
		RX_DATAS[7] = (RFDF30 >> 8) & 0XFF;
		
		
		
		RFPCTR0=0xFFFF;   //	setting 0xffff in this register,read pointer control moves to next unread message in the transmit receive fifo buffer. 
	 
   } 
   else{
	   
   } 
   		
	
	
	
	
}

/*struct CAN_TX
{
	uint16_t 11_BIT_ID;
	
	uint8_t TX_IDE;
	
	uint8_t TX_RTR;
	
	uint8_t TX_DLC;
	
	uint8_t TX_DATA;
	
}; */

