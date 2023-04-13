#define _stprintf
#define _CRT_SECURE_NO_WARNINGS
#include"me.h"
#include"game.h"
#include"enemy.h"
#include<graphics.h>
#include<vector>
#include<easyx.h>
#include<string>
#include<cstring>
#include<iostream>
#include<fstream>
Me* player;

Me::Me() {
	pos.x = 0;
	pos.y = 0;
	for (int i = 0; i < 4; i++) {
		collision[i].x = pos.x + paramx[i] * ME_SIZE;
		collision[i].y = pos.y + paramy[i] * ME_SIZE;
	}
}
Me::Me(int x, int y) {
	pos.x = x;
	pos.y = y;
	for (int i = 0; i < 4; i++) {
		collision[i].x = x + paramx[i] * ME_SIZE;
		collision[i].y = y + paramy[i] * ME_SIZE;
	}
}
Me::~Me() {}

void Me::print() {
	settextcolor(YELLOW);
	settextstyle(ME_SIZE, ME_SIZE,_T("ºÚÌå"));
	outtextxy(pos.x, pos.y, 'M');
}

void Me::dash(int dir) {
	position newPos = pos;
	if (dir == RIGHT) {
		while (!EnterCollision(newPos) && newPos.x > 0 && newPos.x < WINDOW_WIDTH) {
			pos.x = newPos.x;
			newPos.x = pos.x + ME_SIZE;
		}	
	}
	if (dir == LEFT) {
		while (!EnterCollision(newPos) && newPos.x > 0 && newPos.x < WINDOW_WIDTH) {
			pos.x = newPos.x;
			newPos.x = pos.x - ME_SIZE;
		}
			
	}
	if (dir == UP) {
		while (!EnterCollision(newPos) && newPos.y > 0 && newPos.y < WINDOW_HEIGHT) {
			pos.y = newPos.y;
			newPos.y = pos.y - ME_SIZE;
		}
			
	}
	if (dir == DOWN) {
		while (!EnterCollision(newPos) && newPos.y > 0 && newPos.y < WINDOW_HEIGHT) {
			pos.y = newPos.y;
			newPos.y = pos.y + ME_SIZE;
		}
	}
}
void Me::move() {
	if (command != EMPTY) {
		clearrectangle(pos.x+2, pos.y+2, pos.x + ME_SIZE-2, pos.y + ME_SIZE-2);
	}
	position newPos=pos;
	if (command == RIGHT) {
		if (DASH) dash(RIGHT);
		else newPos.x=pos.x + ME_COMMON_SPEED;
	}
	if (command == LEFT) {
		if (DASH) dash(LEFT);
		else newPos.x=pos.x - ME_COMMON_SPEED;
	}
	if (command == UP) {
		if (DASH) dash(UP);
		else newPos.y=pos.y - ME_COMMON_SPEED;
	}
	if (command == DOWN) {
		if (DASH) dash(DOWN);
		else newPos.y=pos.y + ME_COMMON_SPEED;
	}

	if (!DASH) {
		if (!EnterCollision(newPos)) {
			pos = newPos;
		}
		else {
			pos = pos;
		}
	}
	UpdateCollision(pos);
}

void Me::Update() {
	move();
	print();

}
void Me::UpdateCollision(position newPos) {
	for (int i = 0; i < 4; i++) {
		collision[i].x = newPos.x + paramx[i] * ME_SIZE;
		collision[i].y = newPos.y + paramy[i] * ME_SIZE;
	}
}
bool Me::EnterCollision(position newPos) {
	UpdateCollision(newPos);
	for (int i = 0; i < walls.size(); i++) {
		if (collision[0].x > walls[i]->collision[0].x&&collision[0].x<walls[i]->collision[1].x) {
			if (collision[0].y < walls[i]->collision[2].y && collision[0].y > walls[i]->collision[0].y) return true;
			if (collision[2].y < walls[i]->collision[2].y && collision[2].y > walls[i]->collision[0].y) return true;
			if (collision[0].y < walls[i]->collision[0].y && collision[2].y > walls[i]->collision[2].y) return true;
		}
		else if (collision[1].x > walls[i]->collision[0].x && collision[1].x < walls[i]->collision[1].x) {
			if (collision[0].y < walls[i]->collision[2].y && collision[0].y > walls[i]->collision[0].y) return true;
			if (collision[2].y < walls[i]->collision[2].y && collision[2].y > walls[i]->collision[0].y) return true;
			if (collision[0].y < walls[i]->collision[0].y && collision[2].y > walls[i]->collision[2].y) return true;
		}
	}
	return false;
}

void Me::die() {
	float score;
	float TIME = (clock() - BEGIN_TIME)/1000;
	std::fstream inFile("datas\\score.txt");
	inFile >> score;
	inFile.close();
	std::ofstream outFile("datas\\score.txt");
	if (score < TIME) {
		score = TIME;
	}
	outFile << score;
	outFile.close();
	TCHAR s[40];
	_stprintf(s, _T("Best score:%.2fs"),score);
	while (!GetAsyncKeyState(VK_ESCAPE)) {
		settextcolor(RED);
		settextstyle(30, 30, _T("Fixedsys"));
		outtextxy(0,0, L"You Die!");
		settextstyle(10, 10, _T("Fixedsys"));
		outtextxy(35, 30, L"press ESC to exit");
		settextstyle(20, 10, L"Fixedsys");
		settextcolor(YELLOW);
		outtextxy(120, 60, s);
		FlushBatchDraw();
		Sleep(100);
	}
	exit(0);
}
