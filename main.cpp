/* Name: Lauren Herman, Justine Ventura
ID: 1583304, 1564671
CMPUT 275 WI 20

Final Project: Dijsktra’s and Dragons
*/
#include "levels_and_players.h"
#include "messages_and_screens.h"

using namespace std;
MCUFRIEND_kbv tft;
shared_vars shared;
shared_board board;

//initialize the player mode
int playerMode = 0; 

// level global vars
int level = 1;
int keyx = 0;
int keyy = 0;
int gatex = 0;
int gatey = 0;
int numkeys = 0;
bool keySpace=false;

//initialize direction of joystick
direction dir = center; 
direction olddir = center;

/**
* Redraws level map
* @param levelInit if this is a new level, in which case must load new level map
**/
void drawMap(bool levelInit) {
    int cursorx=0;
    int cursory=0;
    int cell;
    uint16_t colour;
    if(levelInit){ // reset vars for new level
        numkeys = 0;
        shared.knight.setKey(0);
    }

    //if the space at the location of the gate is not occupied by the player or dragon then it is set as the gate
    if (board.level_map[gatex][gatey]!=3 && board.level_map[gatex][gatey]!=2) {
        board.level_map[gatex][gatey]=4;
    }

    for (int i=0; i<BLOCKH; i++) {
        cursory=0;
        for (int j=0; j<BLOCKW; j++) {
            if(levelInit){
                    switch(level){ // load level map into shared map

                    case 1:
                        level=1;
                        board.level_map[i][j]= level1[i][j]; 
                        break;

                    case 2:
                        level=2;
                        board.level_map[i][j]= level2[i][j]; 
                        break;
                    case 3:
                        level=3;
                        board.level_map[i][j]= level3[i][j]; 
                        break;
                    case 4:
                        level=4;
                        board.level_map[i][j]= level4[i][j]; 
                        break;
                    case 5:
                        level=5;
                        board.level_map[i][j]= level5[i][j]; 
                        break;
                }    
                if(board.level_map[i][j]==5){ // record number of keys in this level
                  numkeys++;
                }
                
            }
            // draw each square according to the current map
            cell = board.level_map[i][j];
            switch(cell){
                    case 0: // block
                        colour = TFT_BLACK;
                        break;
                    case 1: // path
                        colour = TFT_WHITE;
                        break;
                    case 2: // knight
                        colour = TFT_BLUE;
                        shared.knight.setx(i);
                        shared.knight.sety(j);
                        break;
                    case 3: // dragon
                        colour = TFT_RED;
                        shared.dragon.setx(i);
                        shared.dragon.sety(j);
                        break;
                    case 4: // gate
                        colour = tft.color565(0xC2, 0xC2, 0xA3); 
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
            
            cursory+=BLKPXL;
        }
        cursorx+=BLKPXL;
    }
}

void gameLoop();  // forward declaration

/*
* Prints “game over” to screen and restarts level
*/
void lost_sequence(){
    lost_screen();
    drawMap(true);
    playerMode = 0;
    while(true){
        gameLoop();
    }
    
}
/*
* Prints “level up” to screen and loads next level
*/

void level_up_sequence(){
  level++;
    //if there are no more levels go to end screen
    if(level > MAX_LEVEL){
        end_screen();
    }//else load next level
    else{
    level_up_screen();
    playerMode=0;
        drawMap(true);// remove+1

        while(true){
            gameLoop();
        }
    }
    
}
/*
*Gets the knight’s next location though player input by checking for and previewing valid moves
*/
void knightTurn(int knightx, int knighty, int dragonx, int dragony) {
  //if there are no possible moves go to game over screen
  if (shared.knight.blockedIn(knightx, knighty)) {
      Serial.println("no possible moves");
      lost_sequence();
      //running = false;
  }
  //reset the direction of the joystick to center
  direction dir = center;  
  direction olddir = center;

  //initialize variable for joystick button
  bool stickPushed = false;

  //loop while the stick is not pushed and a direction is not selected
  while(!stickPushed || dir == center) {
    //get joystick data
    int xVal = analogRead(JOY_HORIZ);
    int yVal = analogRead(JOY_VERT);
    int buttonVal = digitalRead(JOY_SEL);

    // the joystick is pointed left
    if (xVal > JOY_CENTRE + JOY_DEADZONE) {
        // if the space to the left is not blocked, fill a yellow preview space
        if(knighty > 0 && board.level_map[knightx][knighty-1]!=0) {            
          tft.fillRect((knighty-1)*BLKPXL,knightx*BLKPXL,BLKPXL,BLKPXL,TFT_YELLOW);
          //record previous direction and current direction
          olddir = dir;
          dir = left;
        }
        // if the space to the left is a block with an open space behind it, fill a green preview space  
        else if (knighty > 1 && board.level_map[knightx][knighty-1]==0 && board.level_map[knightx][knighty-2]==1) {
          tft.fillRect((knighty-1)*BLKPXL,knightx*BLKPXL,BLKPXL,BLKPXL,TFT_GREEN);
          olddir = dir;
          dir = left;
        }
    } //joystick is to the right
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
    } // joystick is up
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
    }// joystick is down
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

    //if the direction has changed fill in the preview with its original colour
    if (olddir!=dir) {
         shared.knight.fillPreview(olddir, knightx, knighty);
    }
    //if the stick is pushed in and centered stickPushed is true
    if (buttonVal==0 && (yVal <= JOY_CENTRE + JOY_DEADZONE) && (yVal >= JOY_CENTRE - JOY_DEADZONE) && (xVal >= JOY_CENTRE - JOY_DEADZONE) && (xVal <= JOY_CENTRE + JOY_DEADZONE)){
        stickPushed = true;
    }
  }

  // move knight coordinates
  //if the direction selected is left move the knight coordinates 1 to the left
  if (dir==left) {
    shared.knight.sety(knighty-1);
  }
  else if (dir==right) {
    shared.knight.sety(knighty+1);
  }
  else if (dir==up) {
    shared.knight.setx(knightx-1);
  }
  else if (dir == down) {
    shared.knight.setx(knightx+1);
  }

  //if the knight is on a space with a key print a message and update the key count
  if(board.level_map[shared.knight.getx()][shared.knight.gety()]==5) {
    got_key_msg();
    shared.knight.setKey(shared.knight.getKey()+1);
  }

  //if the knight is on a space with a block push the block in the given direction
  if(board.level_map[shared.knight.getx()][shared.knight.gety()]==0) {
    shared.knight.pushBlock(dir, shared.knight.getx(), shared.knight.gety());
  }

  //set the old position of the knight to a path and the new position to the knight
  board.level_map[knightx][knighty]=1;
  board.level_map[shared.knight.getx()][shared.knight.gety()]=2;
   
  //redraw the map
  drawMap(false); 

}

/*
* Main function for controlling player moves and flow of game 
*/
void gameLoop(){

    if(playerMode==0){
        tft.fillRect(0,display_height,tft_width,24, TFT_BLACK);
        knight_turn_message();
        knightTurn(shared.knight.getx(),shared.knight.gety(), shared.dragon.getx(),shared.dragon.gety());
        playerMode = 1;
        // knight is at the gate
        if(shared.knight.getx() == gatex && shared.knight.gety() == gatey){
            if(shared.knight.getKey() == numkeys){ // sufficient number of keys
                level_up_sequence();
            }
            else{
                missing_key_msg();

            }
        }

    }
    else if(playerMode==1){

    for(int i = 0; i < 2; i++){ // must loop twice or else dragon will always lag the knight
            dragon_turn_message();
            Coordinate dragdir = {shared.dragon.getx(), shared.dragon.gety()};
            Coordinate knightdir = {shared.knight.getx(), shared.knight.gety()};
            Coordinate nextmove = shared.dragon.captureKnight(dragdir,knightdir);
            if(nextmove.x == -1 || nextmove.y ==-1){
                Serial.println("invalid move");
            }
        
            else{
                if (keySpace) {//if the dragon is on a key, set the space to a key and set the variable keySpace to false
                    board.level_map[dragdir.x][dragdir.y] = 5;
                    keySpace = false;
                }
                else {//otherwise set the space to a path
                    board.level_map[dragdir.x][dragdir.y] = 1;
                }//if the dragon will move onto a key next keySpace is true
                if (board.level_map[nextmove.x][nextmove.y] == 5) {
                    keySpace = true;
                }
                //change the next position of the dragon to the dragon
                board.level_map[nextmove.x][nextmove.y] = 3; 
                drawMap(false); //redraw map

            }
            // dragon caught knight
            if(shared.knight.getx() == shared.dragon.getx() && shared.knight.gety() == shared.dragon.gety()){
                lost_sequence();
                
            }
        }
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

    //set the initial positions of the characters to 0
    shared.dragon.setx(0);
    shared.dragon.sety(0);

    shared.knight.setx(0);
    shared.knight.sety(0);
       
}

int main(){
    setup();
    title_screen();
    instructions_screen();
    while(digitalRead(JOY_SEL)){};//wait until joystick is clicked
    tft.fillScreen(TFT_BLACK);
    drawMap(true);//initialize map
    playerMode = 0;//go to knight mode next
    while(true){
        gameLoop();//loop the game functions
    };

    Serial.end();
    return 0;
}

