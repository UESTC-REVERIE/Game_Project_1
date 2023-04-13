#ifndef _MAP_H
#define _MAP_H


#include"map.h"

#include<iostream>
#include<easyx.h>
#include<vector>

class position {
public:
	int x;
	int y;
	int G;
	int H;
	int F;
	position* connection;

	position();
	position(int x, int y);
	std::vector<position> GetNeighbors();
	void SetG(int G);
	void SetH(int H);
	int GetDistance(position pos);
};

class Wall {
public:
	position collision[4];
	position pos;
	int width;
	int height;
	COLORREF color=WHITE;

	Wall();
	Wall(int x, int y, int width, int height);
	Wall(int x, int y, int width, int height,COLORREF color);
	virtual ~Wall();

	void print();
	void print(COLORREF color);
	void Update();
};

void InitMap();

extern std::vector<Wall*> walls;
extern int paramx[4];
extern int paramy[4];
#endif