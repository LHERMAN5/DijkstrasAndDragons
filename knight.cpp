#include "knight.h"
//#include "consts_and_types.h"
//#include "main.h"
//#include <Arduino.h>
using namespace std;

extern shared_board board;

void Knight::setKey(int k){
	key= k;
}

int Knight::getKey(){
	return key;
}
bool Knight::blockedIn(int knightx, int knighty) {
  int blockedSides = 0;

  if (knightx==0 || 
    (board.level_map[knightx-1][knighty]==0 && board.level_map[knightx-2][knighty]== 0) || 
    (knightx==1 && board.level_map[knightx-1][knighty]==0) ||
    (board.level_map[knightx-1][knighty]==3)) {

    blockedSides++;
  }
  if (knightx==(BLOCKH-1) || 
    (board.level_map[knightx+1][knighty]==0 && board.level_map[knightx+2][knighty]==0) || 
    (knightx==(BLOCKH-2) && board.level_map[knightx+1][knighty]==0) ||
    (board.level_map[knightx+1][knighty]==3)) {

    blockedSides++;
  }
  if (knighty==0 || 
    (board.level_map[knightx][knighty-1]==0 && board.level_map[knightx][knighty-2]==0) || 
    (knighty==1 && board.level_map[knightx][knighty-1]==0) ||
    (board.level_map[knightx][knighty-1]==3)) {

    blockedSides++;
  }
  if (knighty==(BLOCKW-1) || 
    (board.level_map[knightx][knighty+1]==0 && board.level_map[knightx][knighty+2]==0) || 
    (knighty==(BLOCKW-2) && board.level_map[knightx][knighty+1]==0) ||
    (board.level_map[knightx][knighty+1]==3)) {

    blockedSides++;
  }


  return blockedSides==4;
}
void Knight::fillPreview(direction olddir, int knightx, int knighty) {
  
  int cell;
  int xblock;
  int yblock;
  uint16_t colour;

  if(olddir == left) {
    xblock = knightx;
    yblock = knighty-1;
  }
  else if(olddir == right) {
    xblock = knightx;
    yblock = knighty+1;
  }
  else if(olddir == down) {
    xblock = knightx+1;
    yblock = knighty;
  }
  else if(olddir == up) {
    xblock = knightx-1;
    yblock = knighty;
  }

  switch(board.level_map[xblock][yblock]){
    case 0: // block
      colour = TFT_BLACK;
      break;
    case 1: // path
      colour = TFT_WHITE;
      break;
    case 3: // dragon
      colour = TFT_RED;
      break;
    case 4: // gate
      colour = board.tft->color565(0x00, 0x66, 0x33);
      break;
    case 5: // key
      colour = board.tft->color565(0xE5, 0xD8, 0x22);
      break;
  }

  board.tft->fillRect(yblock*BLKPXL,xblock*BLKPXL,BLKPXL,BLKPXL,colour);

}

void Knight::pushBlock(direction dir, int playerx, int playery) {
  
    if (dir == left) {
        board.level_map[playerx][playery-1] = 0;
        board.level_map[playerx][playery] = 1;
    }
    else if (dir == right) {
        board.level_map[playerx][playery+1] = 0;
        board.level_map[playerx][playery] = 1;
    }
    else if (dir == up) {
        board.level_map[playerx-1][playery] = 0;
        board.level_map[playerx][playery] = 1;
    }
    else if (dir == down) {
        board.level_map[playerx+1][playery] = 0;
        board.level_map[playerx][playery] = 1;
    }
}
/**
void Knight::knightTurn(int knightx, int knighty, int dragonx, int dragony) {
  
  if (blockedIn(knightx, knighty)) {
    Serial.println("no possible moves");
    lost_screen();
    running = false;
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
          board.tft->fillRect((knighty-1)*BLKPXL,knightx*BLKPXL,BLKPXL,BLKPXL,TFT_YELLOW);
          olddir = dir;
          dir = left;
        }
        else if (knighty > 1 && board.level_map[knightx][knighty-1]==0 && board.level_map[knightx][knighty-2]==1) {
          board.tft->fillRect((knighty-1)*BLKPXL,knightx*BLKPXL,BLKPXL,BLKPXL,TFT_GREEN);
          olddir = dir;
          dir = left;
        }
      }
      else if (xVal < JOY_CENTRE - JOY_DEADZONE) {

        if(knighty < BLOCKW-1 && board.level_map[knightx][knighty+1]!=0) {
          board.tft->fillRect((knighty+1)*BLKPXL,knightx*BLKPXL,BLKPXL,BLKPXL,TFT_YELLOW);
          olddir = dir;
          dir = right;
        }
        
        else if (knighty < BLOCKW-2 && board.level_map[knightx][knighty+1]==0 && board.level_map[knightx][knighty+2]==1) {
          board.tft->fillRect((knighty+1)*BLKPXL,knightx*BLKPXL,BLKPXL,BLKPXL,TFT_GREEN);
          olddir = dir;
          dir = right;
        }
      }
      else if (yVal < JOY_CENTRE - JOY_DEADZONE) {

        if(knightx > 0 && board.level_map[knightx-1][knighty]!=0) {
          board.tft->fillRect(knighty*BLKPXL,(knightx-1)*BLKPXL,BLKPXL,BLKPXL,TFT_YELLOW);
          olddir = dir;
          dir = up;
        }
        else if (knightx > 1 && board.level_map[knightx-1][knighty]==0 && board.level_map[knightx-2][knighty]==1) {
          board.tft->fillRect(knighty*BLKPXL,(knightx-1)*BLKPXL,BLKPXL,BLKPXL,TFT_GREEN);
          olddir = dir;
          dir = up;
        } 
      }
      else if (yVal > JOY_CENTRE + JOY_DEADZONE) {

        if(knightx < BLOCKH-1 && board.level_map[knightx+1][knighty]!=0) {
          board.tft->fillRect(knighty*BLKPXL,(knightx+1)*BLKPXL,BLKPXL,BLKPXL,TFT_YELLOW);
          olddir = dir;
          dir = down;
        }
        else if (knightx < BLOCKH-2 && board.level_map[knightx+1][knighty]==0 && board.level_map[knightx+2][knighty]==1) {
          board.tft->fillRect(knighty*BLKPXL,(knightx+1)*BLKPXL,BLKPXL,BLKPXL,TFT_GREEN);
          olddir = dir;
          dir = down;
        }
      }

          
          if (olddir!=dir) {
               fillPreview(olddir, knightx, knighty);
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
        shared.knight.setKey();
    }



    if (board.level_map[shared.knight.getx()][shared.knight.gety()]==0) {
        pushBlock(dir, shared.knight.getx(), shared.knight.gety());
    }

    board.level_map[shared.knight.getx()][shared.knight.gety()]=2;
    board.level_map[knightx][knighty]=1;


    //olddir = center;
    //dir = center;

    drawMap(false); 

}


/**

void pushBlock(direction dir, int playerx, int playery) {
    //Serial.print("Pushblock ");
    //Serial.print(playerx);
    //Serial.println(playery);
    if (dir == left) {
        board.level_map[playerx][playery-1] = 0;
        board.level_map[playerx][playery] = 1;
    }
    else if (dir == right) {
        board.level_map[playerx][playery+1] = 0;
        board.level_map[playerx][playery] = 1;
    }
    else if (dir == up) {
        board.level_map[playerx-1][playery] = 0;
        board.level_map[playerx][playery] = 1;
    }
    else if (dir == down) {
        board.level_map[playerx+1][playery] = 0;
        board.level_map[playerx][playery] = 1;
    }
}

void knightTurn(int knightx, int knighty, int dragonx, int dragony) {

    direction dir = center;  
    direction olddir = center;


    bool stickPushed = false;


    while(!stickPushed || dir == center) {
        int xVal = analogRead(JOY_HORIZ);
          int yVal = analogRead(JOY_VERT);
          int buttonVal = digitalRead(JOY_SEL);

          if (xVal > JOY_CENTRE + JOY_DEADZONE) {

  			if(knighty > 0 && board.level_map[knightx][knighty-1]==1) {
  				board.tft->fillRect((knighty-1)*64,knightx*64,64,64,TFT_YELLOW);
  				olddir = dir;
   				dir = left;
  			}
  			else if (knighty > 1 && board.level_map[knightx][knighty-1]==0 && board.level_map[knightx][knighty-2]==1) {
  				board.tft->fillRect((knighty-1)*64,knightx*64,64,64,TFT_GREEN);
  				olddir = dir;
   				dir = left;
  			}
  		}
  		else if (xVal < JOY_CENTRE - JOY_DEADZONE) {

  			if(knighty < 6 && board.level_map[knightx][knighty+1]==1) {
  				board.tft->fillRect((knighty+1)*64,knightx*64,64,64,TFT_YELLOW);
  				olddir = dir;
    			dir = right;
  			}
  			
  			else if (knighty < 5 && board.level_map[knightx][knighty+1]==0 && board.level_map[knightx][knighty+2]==1) {
  				board.tft->fillRect((knighty+1)*64,knightx*64,64,64,TFT_GREEN);
  				olddir = dir;
    			dir = right;
  			}
  		}
  		else if (yVal < JOY_CENTRE - JOY_DEADZONE) {

  			if(knightx > 0 && board.level_map[knightx-1][knighty]==1) {
  				board.tft->fillRect(knighty*64,(knightx-1)*64,64,64,TFT_YELLOW);
  				olddir = dir;
    			dir = up;
  			}
  			else if (knightx > 1 && board.level_map[knightx-1][knighty]==0 && board.level_map[knightx-2][knighty]==1) {
  				board.tft->fillRect(knighty*64,(knightx-1)*64,64,64,TFT_GREEN);
  				olddir = dir;
    			dir = up;
  			}	
  		}
  		else if (yVal > JOY_CENTRE + JOY_DEADZONE) {

  			if(knightx < 4 && board.level_map[knightx+1][knighty]==1) {
  				board.tft->fillRect(knighty*64,(knightx+1)*64,64,64,TFT_YELLOW);
  				olddir = dir;
    			dir = down;
  			}
  			else if (knightx < 3 && board.level_map[knightx+1][knighty]==0 && board.level_map[knightx+2][knighty]==1) {
  				board.tft->fillRect(knighty*64,(knightx+1)*64,64,64,TFT_GREEN);
  				olddir = dir;
    			dir = down;
  			}
  		}

          
          if (olddir!=dir) {
               fillPreview(olddir, knightx, knighty);
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




    if (board.level_map[shared.knight.getx()][shared.knight.gety()]==0) {
        pushBlock(dir, shared.knight.getx(), shared.knight.gety());
    }

    board.level_map[shared.knight.getx()][shared.knight.gety()]=2;
    board.level_map[knightx][knighty]=1;


    //olddir = center;
    //dir = center;

}
**/