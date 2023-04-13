#ifndef _MARIO_H
#define _MARIO_H

#include"map.h"
#include<cstdio>
#include<vector>
#include<Utility>
#include<graphics.h>

class Me {
public:
	Me();
	Me(int x, int y);
	virtual ~Me();
	position pos;
	position collision[4];

	void Update();
	void move();
	void die();
	void dash(int dir);
	void print();
	void UpdateCollision(position newPos);
	bool EnterCollision(position newPos);
};


extern Me* player;
#endif