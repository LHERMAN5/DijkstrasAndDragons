#include "dragon.h"

extern shared_board board;

void Dragon::setHasKnight(bool val){
	hasKnight = val;
}

bool Dragon::getHasKnight(){
	return hasKnight;
}


bool Dragon::isValid(int row, int col){
    return(row>=0) && (row < BLOCKH) && (col>=0) && (col< BLOCKW);
}
// coords of cells surrounding dragon left, down, up, right
int adjrow[] = {-1,0,0,1}; 
int adjcol[] = {0,-1,1,0};


Coordinate Dragon::captureKnight(Coordinate dragon, Coordinate knight){ 
   
    bool visited[BLOCKH][BLOCKW];
   
    for(int i = 0; i < BLOCKH; i++){
        for(int j =0; j < BLOCKW;j++){
            visited[i][j] = false;
        }
    }

    visited[dragon.x][dragon.y] = true;

    Coordinate path[BLOCKH][BLOCKW];
    int pathcounter = 0;

    LinkedList<llNode> ll; // treat like queue
    llNode startCell = {dragon, 0};
    ll.insertFront(startCell); // add to queue

    int row, col;
    while(ll.size() > 0){
        llNode curr = ll.getFirst()->item; // get first cell
        Coordinate currCoord = curr.coordinates;
    
        if(currCoord.x == knight.x && currCoord.y == knight.y){
            int r = currCoord.x;
            int c = currCoord.y;
            int oldr=0; 
            // back track to find the next step to take, like a search tree
            while(path[r][c].x !=dragon.x || path[r][c].y !=dragon.y){
                oldr = r;
                r= path[r][c].x;
                c = path[oldr][c].y;
                if(!isValid(r,c)){
                    return {-1,-1}; // dragon cannot move
                }
            }
            return {r, c}; // return coordinate for next move
        }
        ll.removeFront(); // dequeue
        for(int i =0; i < 4; i++){
            row = currCoord.x + adjrow[i];
            col = currCoord.y + adjcol[i];

            if(!visited[row][col] && isValid(row,col) && board.level_map[row][col]!= 0) 
            {
                // mark as visited
                visited[row][col] = true;
                // enqueue 
                llNode adjcell = {{row,col}, curr.dist+1};
                ll.insertBack(adjcell);

                // add to path
                path[row][col] = currCoord; // new points maps to point it came from 

            }
        }
        
    }

    return {-1,-1}; // dragon cannot move
}
// add movement here