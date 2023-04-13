#define _stprintf
#define _CRT_SECURE_NO_WARNINGS
#include"game.h"
#include"me.h"
#include"enemy.h"
#include<graphics.h>
#include<time.h>
#include<string>
int command;
bool DASH;
float BEGIN_TIME=0;
void initEnemies() {
	
	for (int i = 0; i < ENEMY_NUMS; i++) {
		Enemy* enemy = new Enemy(enemiesPos[i][0], enemiesPos[i][1]);
		enemies.push_back(enemy);
	}
}
void Start() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	InitMap();
	player = new Me(0,450);
	initEnemies();
	BEGIN_TIME = clock();
}
void UI() {
	float TIME = (clock() - BEGIN_TIME)/1000;
	for (int i = 0; i < enemies.size(); i++) {
		int posx = enemiesPos[enemies[i]->id][0];
		int posy = enemiesPos[enemies[i]->id][1];
		rectangle(posx, posy, posx + ME_SIZE, posy + ME_SIZE);
	}
	TCHAR s[40];
	_stprintf(s, _T("%.2f"), TIME);
	settextcolor(YELLOW);
	settextstyle(20, 10, L"Fixedsys");
	outtextxy(270, 10, s);
}
void Update() {
	GetCommand();
	player->Update();
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->Update();
	}
	UI();
}

void GetCommand() {
	command = EMPTY;
	DASH = false;
	if (GetAsyncKeyState('A'))
		command= LEFT;
	if (GetAsyncKeyState('D'))
		command = RIGHT;
	if (GetAsyncKeyState('W'))
		command = UP;
	if (GetAsyncKeyState('S'))
		command = DOWN;
	if (GetAsyncKeyState(VK_SPACE))
		DASH = true;
	
}

