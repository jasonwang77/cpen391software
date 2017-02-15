#include "project.h"
#include "Colours.h"


#define	BLACK		0
#define	WHITE		1
#define	RED			2
#define	LIME		3
#define	BLUE		4
#define	YELLOW		5
#define	CYAN		6
#define	MAGENTA		7


// clear everything
void graph_clearAll(){
	int i;
	for (i=0;i<479;i++) {
		HLine(0,i,800,BLACK);
	}
}


void drawButton(int x, int y,int margin_top,int margin_bottom,int margin_left,int margin_right, int color, int backgroundcolour, char *word){
	int length = strlen(word);
	int i;

	//draw button
	for(i = y - margin_top; i < y + margin_bottom + 14; i++){
		HLine(x - margin_left, i, margin_right*2 + length * 11, backgroundcolour);
	}

	//write word
	for(i = 0; i < length; i++){
		OutGraphicsCharFont2a(x + i * 11, y, color, backgroundcolour, word[i], 0);
	}
}

void writeWord(int x, int y,int color, int backgroundcolour, char *word){
	int length = strlen(word);
	int i;

	//write word
	for(i = 0; i < length; i++){
		OutGraphicsCharFont2a(x + i * 11, y, color, backgroundcolour, word[i], 0);
	}
}


// main menu
void graph_goto_menu() {
	graph_clearAll();

	drawButton(254,125, 20, 20, 20, 20, BLACK, YELLOW, "CO");

	drawButton(491,120, 20, 20, 20, 20, BLACK, YELLOW, "CH4");

	drawButton(243, 340, 20, 20, 20, 20, BLACK, YELLOW, "Smoke");

	drawButton(513, 335, 20, 20, 20, 20, BLACK, YELLOW, "NOx & CO2");
}

void drawAxisVal(int maxPPM){
	int i;

	int val = maxPPM;
	int step = val / 10;

	for(i = 73; i < 430; i = i+35){
		char str[15];
		sprintf(str, "%d",val);
		writeWord(160, i, WHITE, BLACK, str);
		val = val - step;
	}
}

void graph_showGasFrame(int gas) {
	// clear the screen
	graph_clearAll();

	// print gas name
	switch(gas){
		case CO:
				drawButton(300,50, 20, 20, 20, 20,WHITE,BLACK,"CO");
				drawAxisVal(100);
				break;
		// Smoke
		case SMOKE:
				drawButton(300,50, 20, 20, 20, 20,WHITE,BLACK,"SMOKE");
				drawAxisVal(500);
				break;
		// Natural Gas
		case CH4:
				drawButton(300,50, 20, 20, 20, 20,WHITE,BLACK,"CH4");
				drawAxisVal(500);
				break;
		// Air Quality
		case NOX:
				drawButton(300,50, 20, 20, 20, 20,WHITE,BLACK,"NOx & CO2");
				drawAxisVal(500);
				break;
		default: printf("Unexpected gas name ...");

	}

	// print label
	// PPM
	writeWord(150, 50, WHITE, BLACK, "PPM");

	int i;
	//draw more horizontal lines from 0 - 500 and label them
	for(i = 80; i < 430; i = i+35){
		HLine(200, i, 300, RED);
	}

	// print axices
	VLine(200, 80, 350, WHITE);		// y-axis
	HLine(200, 430, 300, WHITE);	// x-axis
}


// global variable to remember the last height value of the bar
last_height = 0;		// initialize it to zero
void graph_updateGasValue(int val) {
	// check if input is valid
	if (val > 1024 || val < 0) return;
	// get the height of the bar
	int height = 350 * val / 1024;

	// change the bar image according to the difference between the current hight and the last height
	int i;
	if (height > last_height) {
		for (i=429-last_height; i>429-height; i--) {
			HLine(300, i, 100, YELLOW);
		}
	} else if (height < last_height) {
		for (i=429-last_height; i<429-height; i++) {
			HLine(300, i, 100, BLACK);
		}
	}

	// update last height
	last_height = height;
}
