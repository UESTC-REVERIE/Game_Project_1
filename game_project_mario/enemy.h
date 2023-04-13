#ifndef _ENEMY_H
#define _ENEMY_H

#include"me.h"
#include<vector>

class Enemy :public Me {

public:
	int id;
	void Update();
	void print();
	Enemy();
	Enemy(int x, int y);
	~Enemy();
	std::vector<position> AStar();
	void printPath();
	void Hunter();
};

extern std::vector<Enemy*> enemies;
extern int enemiesPos[3][2];
#endif // !_ENEMY_H