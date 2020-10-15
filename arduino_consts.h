#ifndef __ARDUINO_CONSTS_H
#define __ARDUINO_CONSTS_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>

#define JOY_VERT  A9 // should connect A9 to pin VRx
#define JOY_HORIZ A8 // should connect A8 to pin VRy
#define JOY_SEL   53

// digital pin high or low (1 or 0)
// analog is 0-1024(res)
#define JOY_CENTRE   512
#define JOY_DEADZONE  64

const int16_t tft_width = 480;
const int16_t tft_height = 320;


// message box dimensions
const int16_t msg_width = tft_width;
const int16_t msg_height = 24;

// display window size for the game map
const int16_t display_width = tft_width;
const int16_t display_height = tft_height - msg_height;

const int BLOCKW = 11;
const int BLOCKH = 7;
const int BLKPXL = 42;

struct shared_board{
	int level_map[BLOCKH][BLOCKW];
	MCUFRIEND_kbv* tft;
};

enum direction{up,down,left,right,center};

#endif