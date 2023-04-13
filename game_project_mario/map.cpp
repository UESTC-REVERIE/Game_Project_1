#include"map.h"
#include"me.h"
#include"game.h"
#include"enemy.h"
#include<vector>
#include<graphics.h>
int paramx[4] = { 0,1,0,1 };
int paramy[4] = { 0,0,1,1 };
std::vector<Wall*> walls;

position::position() {
	G = 2000;
	H = 2000;
	F = G + H;
};
position::position(int x, int y) {
	this->x = x;
	this->y = y;
	G = 2000;
	H = 2000;
	F = G + H;
}
std::vector<position> position::GetNeighbors() {
	std::vector<position> neighs = { {x,y + ENEMY_SPEED},{x,y-ENEMY_SPEED}, {x - ENEMY_SPEED,y},{x+ENEMY_SPEED,y} };
	return neighs;
}

void position::SetG(int G) {
	this->G = G;
	this->F = G + H;
}

void position::SetH(int H) {
	this->H = H;
	this->F = G + H;
}
int position::GetDistance(position pos) {
	return abs(x - pos.x) + abs(y - pos.y);
}
Wall::Wall() {

}
Wall::Wall(int x, int y, int width, int height) {
	pos.x = x;
	pos.y = y;
	this->width = width;
	this->height = height;
	//分别表示左上、右上、左下、右下
	for (int i = 0; i < 4; i++) {
		collision[i].x = x + paramx[i] * (width + 1);
		collision[i].y = y + paramy[i] * (height + 1);
	}
	print();
}
Wall::Wall(int x, int y, int width, int height, COLORREF color){
	pos.x = x;
	pos.y = y;
	this->width = width;
	this->height = height;
	//分别表示左上、右上、左下、右下,扩大了碰撞体体积
	for (int i = 0; i < 4; i++) {
		collision[i].x = x + paramx[i] * (width + 1);
		collision[i].y = y + paramy[i] * (height + 1);
	}
	print(color);
}
Wall::~Wall() {

}

void Wall::print() {
	color = WHITE;
	setfillcolor(WHITE);
	solidrectangle(pos.x, pos.y, pos.x + width, pos.y + height);
}

void Wall::print(COLORREF color) {
	this->color = color;
	setfillcolor(color);
	solidrectangle(pos.x, pos.y, pos.x + width, pos.y + height);
}

void Wall::Update() {

}

void InitMap() {
	Wall* wall1 = new Wall(60,60,30,150);
	walls.push_back(wall1);
	Wall* wall2 = new Wall(60,270, 30, 210);
	walls.push_back(wall2);
	Wall* wall3 = new Wall(150, 90, 120, 30);
	walls.push_back(wall3);
	Wall* wall4 = new Wall(150, 180, 30, 120);
	walls.push_back(wall4);
	Wall* wall5 = new Wall(150, 360, 30, 180);
	walls.push_back(wall5);
	Wall* wall6 = new Wall(240, 120, 30, 90);
	walls.push_back(wall6);
	Wall* wall7 = new Wall(240, 270, 90, 30);
	walls.push_back(wall7);
	Wall* wall8 = new Wall(180, 360, 150, 30);
	walls.push_back(wall8);
	Wall* wall9 = new Wall(240, 450, 120, 30);
	walls.push_back(wall9);
	Wall* wall10 = new Wall(270, 150, 90, 30);
	walls.push_back(wall10);
	Wall* wall11 = new Wall(330, 0, 120, 30);
	walls.push_back(wall11);
	Wall* wall12 = new Wall(330, 30, 30, 60);
	walls.push_back(wall12);
	Wall* wall13 = new Wall(390, 270, 30, 120);
	walls.push_back(wall13);

	Wall* UP_BROUND = new Wall(0, 0, WINDOW_WIDTH, 2,BLACK);
	walls.push_back(UP_BROUND);
	Wall* LEFT_BROUND = new Wall(-45, 0, 40, WINDOW_HEIGHT,BLACK);
	walls.push_back(LEFT_BROUND);
	Wall* DOWN_BROUND = new Wall(0, WINDOW_HEIGHT, WINDOW_WIDTH, 2, BLACK);
	walls.push_back(DOWN_BROUND);
	Wall* RIGHT_BROUND = new Wall(WINDOW_WIDTH, 0, 40, WINDOW_HEIGHT);
	walls.push_back(RIGHT_BROUND);
}