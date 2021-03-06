#include "project.h"
#include <stdio.h>

current_state = MENU;	// initialize it to menu


//variables to hold the gas values
int mq5;
int mq135;

/********************************************************************************
 * Main function
 *******************************************************************************/

void main()
{

	//printf("Starting cpen391 project\n");


	Init_Bluetooth();
	Init_Sensor();
	Init_Touch();

	graph_goto_menu();


   while(TRUE){

//	   printf("Waiting for data...\n");
	   WaitForData();
//	   printf("data received\n");
	   //determine if the data came from the screen or from SENSOR
	   if(ScreenTouched()){
		   //if the data came from touch screen, decode the coordinates
		   Point p1 = GetPress();
		   Point p2 = GetRelease();
		   printf("Press point: x = %d, y = %d\n", p1.x, p1.y);
		   printf("Release point: x = %d, y = %d\n", p2.x, p2.y);

		   // jump to special gas state 
		   if (current_state == MENU) {
				if(p1.x >174 && p1.x <374 && p1.y >49 && p1.y < 214){
					current_state = CO;		// change state
					graph_showGasFrame(CO);	// show CH4 frame
				} else if (p1.x >174 && p1.x <374 && p1.y >264 && p1.y < 429) {
					current_state = SMOKE;		// change state
					graph_showGasFrame(SMOKE);	// show smoke frame
				} else if (p1.x >424 && p1.x <624 && p1.y >49 && p1.y < 214) {
					current_state = CH4;		// change state
					graph_showGasFrame(CH4);	// show natural gas frame
				} else if (p1.x >424 && p1.x <624 && p1.y >264 && p1.y < 429) {
					current_state = NOX;		// change state
					graph_showGasFrame(NOX);	// show air quality frame
				}
		   }
		   
		   // jump back to menu if showing gas value
		   else {
			   wifi_message_sent = 0;
			   graph_goto_menu();
		   }
		   
	   }
	   if(SensorReceivedData()){
		   //if the data is from the Arduino, update gas value 
			update();
//			printf("calling update\n");

	   }
   }

}
