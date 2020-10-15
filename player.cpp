#include "player.h"

Player::Player(int x, int y)
{
	this->x = x;
	this->y = y;
}

void move(){};

void draw(){};


int Player::getx(){
	return x;
}

void Player::setx(int xnew){
	x = xnew;
}

int Player::gety(){
	return y;
}

void Player::sety(int ynew){
	y = ynew;
}