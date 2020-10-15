/* Name: Lauren Herman, Justine Ventura
ID: 1583304, 1564671
CMPUT 275 WI 20

Final Project: Dijsktra’s and Dragons
*/

#ifndef __KNIGHT_H
#define __KNIGHT_H

#include "player.h"

class Knight: public Player
{
    public:
        Knight(){};
        Knight(int x, int y):Player(x,y){};
        void Knight::setKey(int k);

        int Knight::getKey();

        bool blockedIn(int knightx, int knighty);

        void pushBlock(direction dir, int playerx, int playery);

        void fillPreview(direction olddir, int knightx, int knighty);

    protected:
        int key;

};

#endif


