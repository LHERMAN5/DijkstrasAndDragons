// #include "arduino_consts.h"
#include "levels_and_players.h"
#include "messages_and_screens.h"

using namespace std;
MCUFRIEND_kbv tft;
shared_vars shared;
shared_board board;

int playerMode = 0; 

int level = 1;
int keyx = 0;
int keyy = 0;
int gatex = 0;
int gatey = 0;
int numkeys = 0;
// bool canOpenGate = false;
bool keySpace=false;

direction dir = center; 
direction olddir = center;


void drawMap(bool levelInit) {
    int cursorx=0;
    int cursory=0;
    int cell;
    uint16_t colour;
    if(levelInit){
    	numkeys = 0;
    	shared.knight.setKey(0);
    }


    if (board.level_map[gatex][gatey]!=3 && board.level_map[gatex][gatey]!=2) {
    	board.level_map[gatex][gatey]=4;
    }

    for (int i=0; i<BLOCKH; i++) {
        cursory=0;
        for (int j=0; j<BLOCKW; j++) {
        	if(levelInit){
        		// Serial.print("level");
        		// Serial.println(level);
        		switch(level){ // // load level map into shared map

        			case 1:
        				level=1;
        				//Serial.println("case 1");
        				board.level_map[i][j]= level1[i][j]; 
        				break;

        			case 2:
        				level=2;
        				//Serial.println("case 2 ");
        				board.level_map[i][j]= level2[i][j]; 
        				break;
        			case 3:
        				level=3;
        				//Serial.println("case 3 ");
        				board.level_map[i][j]= level3[i][j]; 
        				break;
        			case 4:
        				level=4;
        				//Serial.println("case 4 ");
        				board.level_map[i][j]= level4[i][j]; 
        				break;
        			case 5:
        				level=5;
        				//Serial.println("case 4 ");
        				board.level_map[i][j]= level5[i][j]; 
        				break;
        		}	
        		if(board.level_map[i][j]==5){
                    Serial.println("key");

                    numkeys++;
                    Serial.println(numkeys);
                }
        		
        	}
            cell = board.level_map[i][j];
            //Serial.print(cell);
            
            switch(cell){
					case 0: // block
						//colour = tft.color565(0x99, 0x4C, 0x00);
						colour = TFT_BLACK;
						break;
					case 1: // path
						colour = TFT_WHITE;
						break;
					case 2: // knight
						//colour = tft.color565(0xA0, 0xA0, 0xA0);
						colour = TFT_BLUE;
						shared.knight.setx(i);
						shared.knight.sety(j);
						break;
					case 3: // dragon
						//colour = tft.color565(0xFF, 0x00, 0x00);
						colour = TFT_RED;
						shared.dragon.setx(i);
						shared.dragon.sety(j);
						
						break;
					case 4: // gate
						colour = tft.color565(0xC2, 0xC2, 0xA3); // grey
						gatex = i;
						gatey = j;
						break;
					case 5: // key
						colour = tft.color565(0xE5, 0xD8, 0x22);
						keyx = i;
						keyy = j;
						break;
			}
			tft.fillRect(cursory,cursorx,BLKPXL,BLKPXL,colour);
			/**
			Serial.print(" ");
            Serial.print(i);
            Serial.print(" ");
            Serial.println(j);
            **/

            cursory+=BLKPXL;

        }
        cursorx+=BLKPXL;
    }
}

void gameLoop(); 

void lost_sequence(){
	lost_screen();
	// delay(2000);
	//board.tft->fillScreen(TFT_BLACK);
	drawMap(true);// remove+1
	playerMode = 0;
	while(true){
		gameLoop();
	}
	// reload prev level

}

void level_up_sequence(){
  level++;

	if(level > MAX_LEVEL){
		end_screen();
	}
	else{
    level_up_screen();
    playerMode=0;
		drawMap(true);// remove+1

		while(true){
			gameLoop();
		}
	}
	
}

void knightTurn(int knightx, int knighty, int dragonx, int dragony) {
	
	if (shared.knight.blockedIn(knightx, knighty)) {
		Serial.println("no possible moves");
		lost_sequence();
		//running = false;
	}

    direction dir = center;  
    direction olddir = center;


    bool stickPushed = false;


    while(!stickPushed || dir == center) {
        int xVal = analogRead(JOY_HORIZ);
          int yVal = analogRead(JOY_VERT);
          int buttonVal = digitalRead(JOY_SEL);



          if (xVal > JOY_CENTRE + JOY_DEADZONE) {

  			if(knighty > 0 && board.level_map[knightx][knighty-1]!=0) {
  				tft.fillRect((knighty-1)*BLKPXL,knightx*BLKPXL,BLKPXL,BLKPXL,TFT_YELLOW);
  				olddir = dir;
   				dir = left;
  			}
  			else if (knighty > 1 && board.level_map[knightx][knighty-1]==0 && board.level_map[knightx][knighty-2]==1) {
  				tft.fillRect((knighty-1)*BLKPXL,knightx*BLKPXL,BLKPXL,BLKPXL,TFT_GREEN);
  				olddir = dir;
   				dir = left;
  			}
  		}
  		else if (xVal < JOY_CENTRE - JOY_DEADZONE) {

  			if(knighty < BLOCKW-1 && board.level_map[knightx][knighty+1]!=0) {
  				tft.fillRect((knighty+1)*BLKPXL,knightx*BLKPXL,BLKPXL,BLKPXL,TFT_YELLOW);
  				olddir = dir;
    			dir = right;
  			}
  			
  			else if (knighty < BLOCKW-2 && board.level_map[knightx][knighty+1]==0 && board.level_map[knightx][knighty+2]==1) {
  				tft.fillRect((knighty+1)*BLKPXL,knightx*BLKPXL,BLKPXL,BLKPXL,TFT_GREEN);
  				olddir = dir;
    			dir = right;
  			}
  		}
  		else if (yVal < JOY_CENTRE - JOY_DEADZONE) {

  			if(knightx > 0 && board.level_map[knightx-1][knighty]!=0) {
  				tft.fillRect(knighty*BLKPXL,(knightx-1)*BLKPXL,BLKPXL,BLKPXL,TFT_YELLOW);
  				olddir = dir;
    			dir = up;
  			}
  			else if (knightx > 1 && board.level_map[knightx-1][knighty]==0 && board.level_map[knightx-2][knighty]==1) {
  				tft.fillRect(knighty*BLKPXL,(knightx-1)*BLKPXL,BLKPXL,BLKPXL,TFT_GREEN);
  				olddir = dir;
    			dir = up;
  			}	
  		}
  		else if (yVal > JOY_CENTRE + JOY_DEADZONE) {

  			if(knightx < BLOCKH-1 && board.level_map[knightx+1][knighty]!=0) {
  				tft.fillRect(knighty*BLKPXL,(knightx+1)*BLKPXL,BLKPXL,BLKPXL,TFT_YELLOW);
  				olddir = dir;
    			dir = down;
  			}
  			else if (knightx < BLOCKH-2 && board.level_map[knightx+1][knighty]==0 && board.level_map[knightx+2][knighty]==1) {
  				tft.fillRect(knighty*BLKPXL,(knightx+1)*BLKPXL,BLKPXL,BLKPXL,TFT_GREEN);
  				olddir = dir;
    			dir = down;
  			}
  		}

          
          if (olddir!=dir) {
               shared.knight.fillPreview(olddir, knightx, knighty);
           }

          if (buttonVal==0 && (yVal <= JOY_CENTRE + JOY_DEADZONE) && (yVal >= JOY_CENTRE - JOY_DEADZONE) && (xVal >= JOY_CENTRE - JOY_DEADZONE) && (xVal <= JOY_CENTRE + JOY_DEADZONE)){
              stickPushed = true;
          }
    }



   	if (dir==left) {
		shared.knight.sety(knighty-1);
		//knighty=knighty-1;
	}
	else if (dir==right) {
		shared.knight.sety(knighty+1);
		//knighty=knighty+1;
	}
	else if (dir==up) {
		shared.knight.setx(knightx-1);
		//knightx=knightx-1;
	}
	else if (dir == down) {
		shared.knight.setx(knightx+1);
		//knightx= knightx+1;
	}


	if (board.level_map[shared.knight.getx()][shared.knight.gety()]==5) {
		got_key_msg();

        shared.knight.setKey(shared.knight.getKey()+1);
    }



    if (board.level_map[shared.knight.getx()][shared.knight.gety()]==0) {
        shared.knight.pushBlock(dir, shared.knight.getx(), shared.knight.gety());
    }

    board.level_map[knightx][knighty]=1;
    board.level_map[shared.knight.getx()][shared.knight.gety()]=2;
    


    //olddir = center;
    //dir = center;

    drawMap(false); 

}
void gameLoop(){
	if(playerMode==0){
		tft.fillRect(0,display_height,tft_width,24, TFT_BLACK);
		knight_turn_message();
		//delay(2500);
		// Serial.println("knight turn");
		knightTurn(shared.knight.getx(),shared.knight.gety(), shared.dragon.getx(),shared.dragon.gety());
		playerMode = 1;
		if(shared.knight.getx() == gatex && shared.knight.gety() == gatey){
        	if(shared.knight.getKey() == numkeys){
            	level_up_sequence();
        	}
        	else{
            	missing_key_msg();

        	}
        
    	}

	}
	else if(playerMode==1){

		for(int i = 0; i < 2; i++){
            // Serial.println("dragon turn");
            dragon_turn_message();
            //delay(2500);
			Coordinate dragdir = {shared.dragon.getx(), shared.dragon.gety()};
			Coordinate knightdir = {shared.knight.getx(), shared.knight.gety()};
		
		

			Coordinate nextmove = shared.dragon.captureKnight(dragdir,knightdir);
			//Serial.print("move x ");
			//Serial.println(nextmove.x);
			//Serial.print("move y ");
			//Serial.println(nextmove.y);
			if(nextmove.x == -1 || nextmove.y ==-1){
				Serial.println("invalid move");
			}
		
			else{
				if (keySpace) {
					board.level_map[dragdir.x][dragdir.y] = 5;
					keySpace = false;
				}
				else {
					board.level_map[dragdir.x][dragdir.y] = 1;
				}
				if (board.level_map[nextmove.x][nextmove.y] == 5) {
					keySpace = true;
				}
				board.level_map[nextmove.x][nextmove.y] = 3; 
				drawMap(false); 

			}

			if(shared.knight.getx() == shared.dragon.getx() && shared.knight.gety() == shared.dragon.gety()){
				Serial.println("caught");
				lost_sequence();
				
			}
		}
		//delay(50);
		playerMode = 0;
	}
}



void setup() {
    init();
    pinMode(JOY_SEL, INPUT_PULLUP);
    Serial.begin(9600);

    board.tft = &tft;

    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);
    board.tft->fillScreen(TFT_BLACK);

    shared.dragon.setx(0);
	shared.dragon.sety(0);

	shared.knight.setx(0);
	shared.knight.sety(0);
   	
}

int main(){
	setup();
	title_screen();
	instructions_screen();
	while(digitalRead(JOY_SEL)){};
  tft.fillScreen(TFT_BLACK);
	drawMap(true);
	playerMode = 0;
	while(true){
		gameLoop();
		Serial.println("looping");
	};

	
	
	Serial.println("done");
	Serial.end();
	return 0;
}