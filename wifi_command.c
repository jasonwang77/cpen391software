
#include "project.h"


void Init_Wifi (void)
{
	WIFI_Control = 0x15;
	WIFI_Baud = 0x01;
}

int WifiConnected(void)
{
	// return TRUE if any data received from 6850 connected to wifi
	// or FALSE otherwise
	if ( (WIFI_Status & 0x01) == 0x00 )
		return FALSE;
	else{
		return TRUE;
	}
}


int WifiReceivedData(void)
{
	// return TRUE if any data received from 6850 connected to wifi
	// or FALSE otherwise
	if ( (WIFI_Status & 0x01) == 0x00 )
		return FALSE;
	else{
		return TRUE;
	}
}


/*****************************************************************************
**   wait for screen or SENSOR
*****************************************************************************/

void WifiWaitForData()
{
	while(!WifiReceivedData() && !WifiConnected())
				;
}


int putcharWifi(int c)
{

	while ( (WIFI_Status & 0x02) == 0x00 ) {}
	WIFI_TxData = c;

	return c ; // return c
}

int getcharWifi( void )
{
	while ( (WIFI_Status & 0x01) == 0x00 ) {}
	return WIFI_RxData;
}



void wifi_sendCommand(char * str) {

	int j = 0;
	while(str[j] != '\0'){
		putcharWifi(str[j]);
		j++;
	}
}


