#include"me.h"
#include"enemy.h"
#include"game.h"
#include<vector>
#include<graphics.h>

std::vector<Enemy*> enemies;
int enemiesPos[3][2] = { {0,0},{390,60},{440,510} };
Enemy::Enemy() :Me() {
	id = enemies.size();
};
Enemy::Enemy(int x, int y) :Me(x, y) {
	id = enemies.size();
};
Enemy::~Enemy() {};


std::vector<position> Enemy::AStar() {
	std::vector<position> open;
	std::vector<position> close;

	position* temp=new position(pos.x, pos.y);
	temp->SetG(0);
	temp->SetH(temp->GetDistance(player->pos));
	open.push_back(*temp);

	while (!open.empty()) {
		//记得申请新空间，避免相同地址复用
		position* cur = new position(pos.x,pos.y);//默认F值设为无穷大
		std::vector<position>::iterator it = open.begin();
		std::vector<position>::iterator curPtr = open.begin();
		//在open中找出F最小的值,此处可以进一步用堆优化
		while (it != open.end()) {
			if ((*it).F < cur->F || ((*it).F == cur->F && (*it).H < cur->H)) {
				*cur = *it;
				curPtr = it;
			}
			it++;
		}
		open.erase(curPtr);
		close.push_back(*cur);
		//结果检验
		if (cur->x == player->pos.x && cur->y == player->pos.y) {
			std::vector<position> path;
			while (cur->connection != nullptr) {
				path.push_back(*cur);
				cur = cur->connection;
			}

			return path;
		}

		std::vector<position> neighbors = cur->GetNeighbors();
		for (int i = 0; i < neighbors.size(); i++) {
			bool inOpen = false;
			bool inClose = false;
			for (int j = 0; j < close.size(); j++) {
				if (close[j].x == neighbors[i].x && close[j].y == neighbors[i].y) {
					inClose = true;
				}
			}
			for (int j = 0; j < open.size(); j++) {
				if (open[j].x == neighbors[i].x && open[j].y == neighbors[i].y) {
					inOpen = true;
				}
			}
			if (inClose) continue;
			int neighborG = cur->G + cur->GetDistance(neighbors[i]);
			//将周围可行点放入open
			bool collision = EnterCollision(neighbors[i]);
			if (EnterCollision(neighbors[i])) {continue;}
			if (!inOpen || neighborG < neighbors[i].G ) {
				neighbors[i].SetG(neighborG);
				neighbors[i].connection = cur;

				if (!inOpen) {
					neighbors[i].SetH(neighbors[i].GetDistance(player->pos));
					open.push_back(neighbors[i]);
				}
			}

		}
	}

	return {};
}
std::vector<std::vector<position>> paths(ENEMY_NUMS);
void Enemy::printPath() {
	for (int i = 0;i < paths[id].size(); i++) {
		putpixel(paths[id][i].x, paths[id][i].y, BLACK);
	}
	paths[id] = AStar();	
	for (int i = 0; i < paths[id].size(); i++) {
		putpixel(paths[id][i].x, paths[id][i].y, WHITE);
	}
}
void Enemy::Hunter() {
	int dex;
	clearrectangle(pos.x, pos.y, pos.x + ME_SIZE, pos.y + ME_SIZE);
	dex = paths[id].size() > 0 ? paths[id].size() - 1 : -1;
	if (dex >= 0) pos = paths[id][dex];
	if (abs(pos.x - player->pos.x) <= ENEMY_SPEED && abs(pos.y - player->pos.y) <= ENEMY_SPEED) {
		player->die();
	}

}
void Enemy::print() {
	settextcolor(RED);
	settextstyle(ME_SIZE, ME_SIZE, _T("黑体"));
	outtextxy(pos.x, pos.y, 'G');
}

void Enemy::Update() {
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->id != this->id && abs(enemies[i]->pos.x - this->pos.x)<ME_SIZE && abs(enemies[i]->pos.y - this->pos.y)<ME_SIZE) {
			clearrectangle(this->pos.x, this->pos.y, this->pos.x + ME_SIZE, this->pos.y + ME_SIZE);
			this->pos.x = enemiesPos[id][0];
			this->pos.y = enemiesPos[id][1];
		}
	}
	//printPath();
	paths[id] = AStar();
	Hunter();
	print();
}