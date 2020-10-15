#include "arduino_consts.h"
extern shared_board board;

void knight_turn_message(){
	board.tft->fillRect(0,display_height,display_width,24, TFT_BLACK);
	board.tft->setCursor(0,display_height);
	board.tft->setTextColor(TFT_WHITE);
	board.tft->setTextSize(2);
	board.tft->print("Your turn, knight! Best of luck! ");

}

void dragon_turn_message(){
	board.tft->fillRect(0,display_height,display_width,24, TFT_BLACK);
	board.tft->setCursor(0,display_height);
	board.tft->setTextColor(TFT_RED);
	board.tft->setTextSize(2);
	board.tft->print("Tis the great dragon's turn! ");

}

void missing_key_msg(){
	Serial.println("Find the rest of the keys to open the gate!");
	board.tft->fillRect(0,display_height,display_width,24, TFT_BLACK);
	board.tft->setCursor(0,display_height);
	board.tft->setTextColor(board.tft->color565(0xE5, 0xD8, 0x22));
	board.tft->setTextSize(2);
	board.tft->print("Collect all keys to open the gate! ");
	delay(1500);
}

void got_key_msg(){
	Serial.println("Got key!");
	board.tft->fillRect(0,display_height,display_width,24, TFT_BLACK);
	board.tft->setCursor(0,display_height);
	board.tft->setTextColor(board.tft->color565(0xE5, 0xD8, 0x22));
	board.tft->setTextSize(2);
	board.tft->print("Key found!");
	delay(1000);
}


void instructions_screen(){
	board.tft->fillScreen(TFT_BLACK);
    board.tft->fillRect(0,display_height,display_width,24, TFT_BLACK);
    board.tft->setCursor(0,0);
    board.tft->setTextColor(TFT_WHITE);
    board.tft->setTextSize(2);
    board.tft->setTextWrap(true);
    board.tft->print("Greetings, knight! "); // 38
    board.tft->setTextColor(TFT_BLUE);
    board.tft->print("(blue pixel) ");
    board.tft->setTextColor(TFT_WHITE);
    board.tft->setCursor(0,15);
    board.tft->print("your task is to take back your kingdom");
    board.tft->setCursor(0,30);
    board.tft->print("by collecting keys ");
    board.tft->setTextColor(board.tft->color565(0xE5, 0xD8, 0x22));
    board.tft->print("(gold pixels) ");
    board.tft->setTextColor(TFT_WHITE);
    board.tft->print("and");
    board.tft->setCursor(0,45);
    board.tft->print("going through the gates ");
    board.tft->setTextColor(board.tft->color565(0xC2, 0xc2, 0xA3));
    board.tft->print("(grey pixel.)");
    board.tft->setCursor(0,60);
    board.tft->setTextColor(TFT_WHITE);
    board.tft->print("But beware the dragon ");
    board.tft->setTextColor(TFT_RED);
    board.tft->print("(red pixel) ");
    board.tft->setTextColor(TFT_WHITE);
    board.tft->print("and");
    board.tft->setCursor(0,75);
    board.tft->print("push blocks (black pixels) to trap it.");
    board.tft->setCursor(0,100);
    board.tft->print("Use the joystick to preview moves. Once");
    board.tft->setCursor(0,115);
    board.tft->print("you've selected your move, lock it down");
    board.tft->setCursor(0,130);
    board.tft->print("by clicking in the joystick.");
    board.tft->setCursor(110,210);
    board.tft->setTextSize(3);
    board.tft->print("Click to begin! ");
}

void lost_screen(){
	board.tft->fillScreen(TFT_BLACK);
	board.tft->setCursor(0,display_height/2);
	board.tft->setTextColor(TFT_RED);
	board.tft->setTextSize(4);
	board.tft->setTextWrap(true);
	
	//board.tft->print("The knight has been captured!");
	int GameOver[11][17] = {{1,0,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0},
	{0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1},{0,1,1,1,1,0,0,0,1,0,1,0,1,0,1,0,0},
	{0,1,0,0,1,0,1,0,1,0,1,1,1,0,1,0,1},{1,0,0,1,1,0,1,0,1,0,1,1,1,0,1,1,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,0,0,1,1,0,1,0,1,1,0,1,1,0,1,1},
	{1,0,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1},{1,0,1,1,0,1,0,1,0,1,0,0,1,0,0,1,1},
	{1,0,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1},{1,1,0,0,1,1,1,0,1,1,1,0,1,0,1,0,1}};

	int cursorx=65;
	int cursory=100;

	for (int i=0; i<11; i++) {
		cursory=100;
		for (int j=0; j<17; j++) {

			if (GameOver[i][j]==0) {
				board.tft->fillRect(cursory,cursorx,16,16,TFT_WHITE);
			}

			cursory+=16;
		}
		cursorx+=16;
	}


	delay(2000);
	board.tft->fillScreen(TFT_BLACK);

}

void level_up_screen(){
	board.tft->fillScreen(TFT_BLACK);

	int LevelUp[11][17]= {{0,1,1,1,1,0,1,0,1,0,1,1,0,1,0,1,1},
	{0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1},{0,1,1,1,0,0,1,0,1,0,1,0,0,1,0,1,1},
	{0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1},{1,0,0,1,1,0,1,1,0,1,1,1,0,1,1,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,0,1,0,1,1,0,1,1,0,1,1,1,1},
	{1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1},{1,1,1,1,0,1,0,1,0,0,1,1,0,1,1,1,1},
	{1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1},{1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1}};

	int cursorx=65;
	int cursory=110;

	for (int i=0; i<11; i++) {
		cursory=110;
		for (int j=0; j<17; j++) {

			if (LevelUp[i][j]==0) {
				board.tft->fillRect(cursory,cursorx,16,16,TFT_WHITE);
			}

			cursory+=16;
		}
		cursorx+=16;
	}

	delay(2000);
	board.tft->fillScreen(TFT_BLACK);
}

	


void title_screen() {
	int Title[18][36] = {
	{0,0,0,1,1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},
	{0,1,1,0,1,1,1,1,1,1,0,1,0,1,1,0,0,1,1,0,1,1,0,1,1,1,1,0,1,1,0,1,1,1,0,0},
	{0,1,1,0,1,0,1,1,0,1,0,0,1,1,0,0,1,1,0,0,0,1,0,0,1,1,0,1,0,1,1,1,1,0,0,1}, 
	{0,1,1,0,1,0,1,1,0,1,0,0,1,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,0}, 
	{0,0,0,1,1,0,1,1,0,1,0,1,0,1,0,0,1,1,1,0,1,1,0,1,1,1,1,0,1,0,1,1,1,0,0,1}, 
	{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,0,1,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,0,1,1,1}, 
	{1,1,1,0,1,1,0,1,0,0,1,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,1,1,1,1}, 
	{1,1,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,1,0,1,1,1}, 
	{1,1,1,0,0,0,1,1,0,1,1,1,1,0,1,0,1,1,0,0,1,1,0,1,1,0,1,1,0,1,0,0,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};


	int cursorx=50;
	int cursory=25;

	for (int i=0; i<18; i++) {
		cursory=25;
		for (int j=0; j<36; j++) {

			if (Title[i][j]==0) {
				board.tft->fillRect(cursory,cursorx,12,12,TFT_WHITE);
			}

			cursory+=12;
		}
		cursorx+=12;
	}

	delay(3500);
	board.tft->fillScreen(TFT_BLACK);
}


void end_screen(){
	board.tft->fillScreen(TFT_BLACK);

	int End[5][10]= {{0,0,0,1,0,1,1,1,1,1},{0,1,1,1,1,1,0,1,0,1}, 
		{0,0,1,1,0,1,0,0,1,0},{0,1,1,1,0,1,0,1,1,0},{0,1,1,1,0,1,0,1,1,0}};

	int cursorx=100;
	int cursory=150;

	for (int i=0; i<5; i++) {
		cursory=150;
		for (int j=0; j<10; j++) {

			if (End[i][j]==0) {
				board.tft->fillRect(cursory,cursorx,16,16,TFT_WHITE);
			}

			cursory+=16;
		}
		cursorx+=16;
	}

	while(true){}
}
