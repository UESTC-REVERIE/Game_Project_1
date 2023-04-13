#ifndef _GAME_H
#define _GAME_H

extern int command;
extern bool DASH;
extern float BEGIN_TIME;
const int ENEMY_NUMS = 2;

const int WINDOW_HEIGHT = 540;
const int WINDOW_WIDTH = 470;

const int ME_SIZE = 30;
const int WALL_SIZE = 30;

const int ME_COMMON_SPEED = 20;
const int ME_DASH_SPEED = 40;
const int ME_COMMON_PAUSE = 50;
const int ME_DASH_PAUSE = 5;

const int ENEMY_SPEED = 10;

const int PAUSE_TIME = 50;
const int DASH_PAUSE_TIME = 10;


const int EMPTY = -2;
const int ESC = -1;
const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;

void GetCommand();
void Start();
void Update();

#endif

