/*Name: Lauren Herman, Justine Ventura
ID: 1583304, 1564671
CMPUT 275 WI 20

Final Project: Dijsktra’s and Dragons
*/

#include "knight.h"
using namespace std;

extern shared_board board;

void Knight::setKey(int k){//set number of keys collected
    key= k;
}

int Knight::getKey(){//get number of keys collected
    return key;
}
/*
*Function that finds out whether the knight is blocked in with no possible moves
*/
bool Knight::blockedIn(int knightx, int knighty) {
  int blockedSides = 0;
//for each direction check if the knight is against the edge of the screen or is against a block which is against the edge of the screen or is against two consecutive blocks, add one to blockedSides for each side on which the player is blocked
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

//compare the number of blockedSides to 4, return true if the player is blocked in on all sides
  return blockedSides==4;
}

/*
*Fills the previous preview when the player selects a new block to preview
*/
void Knight::fillPreview(direction olddir, int knightx, int knighty) {
  
  int cell;
  int xblock;
  int yblock;
  uint16_t colour;
//finds the block which was previously previewed and sets that blocks x and y
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
//find the type of block it is from the level map and gets the appropriate colour
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
//fill in the block
  board.tft->fillRect(yblock*BLKPXL,xblock*BLKPXL,BLKPXL,BLKPXL,colour);

}
/*
*Pushes a block one space forward in the given direction
*/
void Knight::pushBlock(direction dir, int playerx, int playery) {
  //set the place the block was before to a path and set the new position of the block to a block
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

