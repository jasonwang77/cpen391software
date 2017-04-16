//arduino.c


#include "project.h"
#include <stdio.h>


/*
 * Functions to get data from Arduino and update the gas values
 */
int getcharSensor( void )
{
 // poll Rx bit in 6850 status register. Wait for it to become '1'
 // read received character from 6850 RxData register.

	while ( (SENSOR_Status & 0x01) == 0x00 ) {}
	return SENSOR_RxData;
}





//updates the gas value
void update(void){
	int control;
	int mq5_b1;
	int mq5_b2;
	int mq135_b1;
	int mq135_b2;
	int mq2_b1;
	int mq2_b2;
	int mq4_b1;
	int mq4_b2;
	int mq5_Val;
	int mq135_Val;
	int mq2_Val;
	int mq4_Val;


	//check control,
	do{
		control = getcharSensor();
	}while(control != 0x80);

	//data for mq5
		mq5_b1 = getcharSensor();
		mq5_b2 = getcharSensor();
		mq5_Val = ((mq5_b1 & 0x1f) << 5) | (mq5_b2 & 0x1f) ;
		//printf("mq5 = %d, ", mq5_Val);
	//data for mq135
		mq135_b1 = getcharSensor();
		mq135_b2 = getcharSensor();
		mq135_Val = ((mq135_b1 & 0x1f) << 5) | (mq135_b2 & 0x1f) ;
		//printf("mq135 = %d, ", mq135_Val);
	//data for mq2
		mq2_b1 = getcharSensor();
		mq2_b2 = getcharSensor();
		mq2_Val = ((mq2_b1 & 0x1f) << 5) | (mq2_b2 & 0x1f) ;
		//printf("mq2 = %d, ", mq2_Val);
	//data for mq4
		mq4_b1 = getcharSensor();
		mq4_b2 = getcharSensor();
		mq4_Val = ((mq4_b1 & 0x1f) << 5) | (mq4_b2 & 0x1f) ;
		//printf("mq4 = %d \n", mq4_Val);
		
		if (BTTestForReceivedData()) {
			while(BTTestForReceivedData()){
				getcharBT();
			}


			char buf_mq5[sizeof(int)*3+2];
			char buf_mq135[sizeof(int)*3+2];
			char buf_mq2[sizeof(int)*3+2];
			char buf_mq4[sizeof(int)*3+2];
			snprintf(buf_mq5, sizeof buf_mq5, "%d", mq5_Val);
			snprintf(buf_mq135, sizeof buf_mq135, "%d", mq135_Val);
			snprintf(buf_mq2, sizeof buf_mq2, "%d", mq2_Val);
			snprintf(buf_mq4, sizeof buf_mq4, "%d", mq4_Val);

			sendMessageBT(buf_mq5);

			putcharBT(' ');

			sendMessageBT(buf_mq135);

			putcharBT(' ');

			sendMessageBT(buf_mq2);

			putcharBT(' ');

			sendMessageBT(buf_mq4);


			putcharBT('\r');


		}



		// enter warning state
		if (mq5_Val >= WARNING_NAGS) {
			// warning state
			enter_warning_state (CH4);
		} else if (mq135_Val >= WARNING_AIRQ) {
			// warning state
			enter_warning_state (NOX);
		} else if (mq4_Val >= WARNING_CH4) {
			// warning state
			enter_warning_state (CO);
		} else if (mq2_Val > WARNING_SMOKE) {
			// warning state
			enter_warning_state (SMOKE);
		} else if (SWITCHES == 1) {
			// warning state
			enter_warning_state(SMOKE);
		}

		// while in gas demo state
		if (current_state != MENU) {
			last_height = 0;
			switch(current_state){
				case CO: graph_updateGasValue(mq4_Val); break;
				case SMOKE: graph_updateGasValue(mq2_Val); break;
				case CH4: graph_updateGasValue(mq5_Val); break;
				case NOX: graph_updateGasValue(mq135_Val); break;
			}
		}

}
