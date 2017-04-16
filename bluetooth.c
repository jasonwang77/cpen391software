#include <stdio.h>
#include <unistd.h>
#include "project.h"


/**************************************************************************
** Subroutine to initialize the BT Port by writing some data
** to the internal registers.
** Call this function at the start of the program before you attempt
** to read or write to data via the BT port
**
** Refer to 6850 data sheet for details of registers and
***************************************************************************/

void Init_BT(void)
{
 // set up 6850 Control Register to utilize a divide by 16 clock,
 // set RTS low, use 8 bits of data, no parity, 1 stop bit,
 // transmitter interrupt disabled
 // program baud rate generator to use 115k baud

	BT_Control = 0x15; // binary 00010101
	BT_Baud = 0x01;	// program for 115k baud
}

int putcharBT(char c)
{
 // poll Tx bit in 6850 status register. Wait for it to become '1'
 // write 'c' to the 6850 TxData register to output the character

	while ( (BT_Status & 0x02) == 0x00 ) {}
	BT_TxData = c;

 return c ; // return c
}

int getcharBT( void )
{
 // poll Rx bit in 6850 status register. Wait for it to become '1'
 // read received character from 6850 RxData register.

	while ( (BT_Status & 0x01) == 0x00 ) {}
	return BT_RxData;
}

// the following function polls the 6850 to determine if any character
// has been received. It doesn't wait for one, or read it, it simply tests
// to see if one is available to read
int BTTestForReceivedData(void)
{
 // Test Rx bit in 6850 serial comms chip status register
 // if RX bit is set, return TRUE, otherwise return FALSE
	if ( (BT_Status & 0x01) == 0x00 )
		return FALSE;
	else
		return TRUE;

}

void sendMessageBT(char * str) {

	int j = 0;
	while(str[j] != '\0'){
		putcharBT(str[j]);
		j++;
	}
}

int Init_Bluetooth()
{
	  printf("Hello from Nios II!\n");
	  Init_BT();


//	  usleep(2000000);
//	  putcharBT('$');
//	  putcharBT('$');
//	  putcharBT('$');
//
//	  //printf(BT_TxData + "\n");
//	  usleep(2000000);
//
//	  putcharBT('S');
//	  putcharBT('F');
//	  putcharBT(',');
//	  putcharBT('1');
//	  putcharBT('\r');
//	  putcharBT('\n');
//
//
//	  usleep(2000000);
//
//	  putcharBT('S');
//	  putcharBT('N');
//	  putcharBT(',');
//	  putcharBT('2');
//	  putcharBT('0');
//	  putcharBT('1');
//	  putcharBT('7');
//	  putcharBT('t');
//	  putcharBT('e');
//	  putcharBT('a');
//	  putcharBT('m');
//	  putcharBT('2');
//	  putcharBT('8');
//	  putcharBT('\r');
//	  putcharBT('\n');
//
//	  usleep(2000000);
//
//	  putcharBT('S');
//	  putcharBT('P');
//	  putcharBT(',');
//	  putcharBT('2');
//	  putcharBT('8');
//	  putcharBT('\r');
//	  putcharBT('\n');
//
////	  char name0[] = "SF,1\r\n";
////	 	  int j = 0;
////	 	  while(name0[j] != '\0'){
////	 		  putcharBT(name0[j]);
////	 		  printf(name0[j]);
////	 		  j++;
////	 	  }
//
////
////	  char name[] = "SN,TM28\r\n";
////	  int i = 0;
////	  while(name[i] != '\0'){
////		  putcharBT(name[i]);
////		  i++;
////	  }
////
////
////	  char name2[] = "SP,TM28\r\n";
////	  	  int k = 0;
////	  while(name2[k] != '\0'){
////	  	putcharBT(name2[k]);
////	  	k++;
////	  }
//
//	  usleep(2000000);
//	  putcharBT('-');
//	  putcharBT('-');
//	  putcharBT('-');
//	  putcharBT('\r');
//	  putcharBT('\n');




//	  while (1) {
//		  if (SWITCHES == 1) {
//			  printf("Sending message to Android phone!\n");
//			  usleep(2000000);
//			  char mess[] = "Message from De1-Soc 0001 !!!\r\n";
//			  int j = 0;
//			  while(mess[j] != '\0'){
//				  putcharBT(mess[j]);
//				  j++;
//			  }
//		  }
//	  }



	  return 0;
}
