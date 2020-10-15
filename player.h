#ifndef __PLAYER_H
#define __PLAYER_H

#include "arduino_consts.h"

class Player{
	public:
		Player(int x, int y);
		Player(){};

		~Player(){}; 

		// void setCoordinate(Coordinate coord);

		void move();

		void draw();
	
		int getx();

		void setx(int x);

		int gety();

		void sety(int y);
		


	protected: // accessible by child classes
		int x;
		int y;
};

#endif