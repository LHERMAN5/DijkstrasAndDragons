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

		// void knightTurn(int knightx, int knighty, int dragonx, int dragony);
		/**
		void fillPreview(direction olddir, int knightx, int knighty);

		void pushBlock(direction dir, int playerx, int playery);

		void knightTurn(int knightx, int knighty, int dragonx, int dragony);

		void move();
		// TODO: Add keys, etc.
		**/
	protected:
		int key;

};

#endif
