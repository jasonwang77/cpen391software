#include<stdio.h>
#include<stdlib.h>
#include "project.h"
#include "Colours.h"

int wait_loop0 = 100;
int wait_loop1 = 600;
wifi_message_sent = 0;


// int to gas map
char* i2gMap (int gas) {
	//printf(gas);
	switch (gas) {
		case 1:	return "CO";
		case 2:	return "Smoke";
		case 3: return "CH4";
		case 4: return "NOX";
		default: return "Error Gas Type";
	}
}



// send gas warning text
/*
void send_warning_text(char gas[]) {
	Init_Wifi();
	wifi_sendCommand ("\r\n");
	wifi_sendCommand ("\r\n");
	wifi_sendCommand ("\r\n");
	wifi_sendCommand ("\r\n");
	wifi_sendCommand ("\r\n");


	//wifi_sendCommand ("gpio.mode(3,gpio.OUTPUT)");
	wifi_sendCommand ("dofile(\"send_text_message.lua\")");
	wifi_sendCommand ("\r\n");

	wifi_sendCommand ("wifi_send(\"");
	wifi_sendCommand (gas);
	wifi_sendCommand (" WARNING!!!\")");
	//wifi_sendCommand ("gpio.write(3,gpio.HIGH)");
	wifi_sendCommand ("\r\n");
}

*/

void send_to_firebase(int gas) {
	Init_Wifi();
	printf("Sending message to AWS ...\n");
	wifi_sendCommand ("\r\n");
	wifi_sendCommand ("\r\n");
	wifi_sendCommand ("\r\n");
	wifi_sendCommand ("\r\n");
	wifi_sendCommand ("\r\n");
	wifi_sendCommand ("\r\n");



//	wifi_sendCommand ("gpio.mode(3,gpio.OUTPUT)");
//	wifi_sendCommand ("\r\n");
//	wifi_sendCommand ("gpio.write(3,gpio.HIGH)");
//	wifi_sendCommand ("\r\n");
//
	usleep(2000000);
	wifi_sendCommand ("dofile(\"http-post.lua\")");
	usleep(200000);
	wifi_sendCommand ("\r\n");


	switch (gas) {
				case 1:
					usleep(2000000);
					wifi_sendCommand ("wifi_send(\"CO\")");
					usleep(200000);
					wifi_sendCommand ("\r\n");

					usleep(2000000);
					wifi_sendCommand ("wifi_send(\"CO\")");
					wifi_sendCommand ("\r\n");

					usleep(2000000);
					wifi_sendCommand ("wifi_send(\"CO\")");
					usleep(200000);
					wifi_sendCommand ("\r\n");
					break;
				case 23:
					usleep(2000000);
					wifi_sendCommand ("wifi_send(\"SMOKE\")");
					usleep(200000);
					wifi_sendCommand ("\r\n");

					usleep(2000000);
					wifi_sendCommand ("wifi_send(\"SMOKE\")");
					usleep(200000);
					wifi_sendCommand ("\r\n");

					usleep(2000000);
					wifi_sendCommand ("wifi_send(\"SMOKE\")");
					usleep(200000);
					wifi_sendCommand ("\r\n");
					break;
				case 2:
					usleep(2000000);
					wifi_sendCommand ("wifi_send(\"CH4\")");
					usleep(200000);
					wifi_sendCommand ("\r\n");

					usleep(2000000);
					wifi_sendCommand ("wifi_send(\"CH4\")");
					usleep(200000);
					wifi_sendCommand ("\r\n");

					usleep(2000000);
					wifi_sendCommand ("wifi_send(\"CH4\")");
					usleep(200000);
					wifi_sendCommand ("\r\n");
					break;
				case 4:
					usleep(2000000);
					wifi_sendCommand ("wifi_send(\"NOX\")");
					usleep(200000);
					wifi_sendCommand ("\r\n");

					usleep(2000000);
					wifi_sendCommand ("wifi_send(\"NOX\")");
					usleep(200000);
					wifi_sendCommand ("\r\n");

					usleep(2000000);
					wifi_sendCommand ("wifi_send(\"NOX\")");
					usleep(200000);
					wifi_sendCommand ("\r\n");
					break;
				default: break;
	}


}

warning_stop = 0;


// warning generator
void Warning(int gas) {

	// TODO: Send user a message
	//if (wifi_message_sent == 0) {
		//send_warning_text(i2gMap(gas));
//		switch (gas) {
//				case 1:	send_warning_text(i2gMap(gas));break;
//				case 2:	send_warning_text("Smoke");break;
//				case 3: send_warning_text("CH4");break;
//				case 4: send_warning_text("NOX");break;
//				default: break;
//		}
	//}
	//wifi_message_sent = 1;



	send_to_firebase(gas);


	while (ScreenTouched() == FALSE) {
		LEDS = 1023;
		HEX01 = 136;
		HEX23 = 136;
		HEX45 = 136;

		graph_paintAll(RED);
		writeWord(400, 240,WHITE, WHITE, i2gMap(gas));
		usleep(1000000);

		LEDS = 0;
		HEX01 = 256;
		HEX23 = 256;
		HEX45 = 256;
		graph_paintAll(BLACK);
		writeWord(400, 240,WHITE, WHITE, i2gMap(gas));
		usleep(1000000);

	}

}

// top level function for entering warning state
void enter_warning_state (int gas) {
	Warning(gas);
}








