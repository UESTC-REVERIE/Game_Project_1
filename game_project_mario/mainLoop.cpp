#include"me.h"
#include"game.h"
#include"enemy.h"
#include<cstdio>
#include<iostream>
#include<graphics.h>


int main() {
	Start();
	BeginBatchDraw();
	while (1) {
		Update();
		FlushBatchDraw();
		Sleep(PAUSE_TIME);
	}
	EndBatchDraw();
}