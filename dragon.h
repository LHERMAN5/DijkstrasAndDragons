/* Name: Lauren Herman, Justine Ventura
ID: 1583304, 1564671
CMPUT 275 WI 20

Final Project: Dijsktra’s and Dragons
*/


#ifndef DRAGON_H
#define DRAGON_H

#include "player.h"
#include "linked_list.h"

struct Coordinate{ 
    int x;
    int y;
};

struct llNode{
    Coordinate coordinates;
    int dist; // distance from dragon 
};

class Dragon: public Player
{    
    public:
        Dragon(){};
        
        Dragon(int x, int y):Player(x,y){};
        
        ~Dragon(){}; // deconstructor

        bool getHasKnight();

        void setHasKnight(bool v);

        bool isValid(int row, int col);

        Coordinate captureKnight(Coordinate dragon, Coordinate knight);
    
    private:
         bool hasKnight; // if dragon as caught the knight        

};
#endif

