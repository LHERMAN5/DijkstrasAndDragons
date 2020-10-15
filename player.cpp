#include "player.h"

Player::Player(int x, int y)
{
    this->x = x;
    this->y = y;
}

void move(){};

void draw(){};


int Player::getx(){//get the player x value
    return x;
}

void Player::setx(int xnew){//set the player x value
    x = xnew;
}

int Player::gety(){//get the player y value
    return y;
}

void Player::sety(int ynew){//set the player y value
    y = ynew;
}

