#include "AInside.h"
#include <algorithm>

#define INF (1<<20)//�ł����l


AInside::AInside(int teamID) :Algorithm(teamID)
{
	for (int i = 0; i < database.width; i++) {
		for (int j = 0; j < database.height; j++)
			points[j][i] = -INF;
	}				
	destination.x = database.width / 2;
	destination.y = database.height / 2;
	points[destination.y][destination.x] = 0;
}

void AInside::execute(int ahead)
{
	moveselectpoint = new MoveSelectedPoint(teamID);
	moveselectpoint->setDestination(destination);
	for (int i = 0; i < agents.size(); i++) {
		Action temp;
		temp.direction = moveselectpoint->explore(agents[i].agentID);
		if (database.tiled[agents[i].y + temp.direction.y][agents[i].x + temp.direction.x]!=teamID
			&& database.tiled[agents[i].y + temp.direction.y][agents[i].x + temp.direction.x] != 0) {
			temp.type = "remove";
		}
		else {
			temp.type = "move";
		}
		temp.agentID = agents[i].agentID;
		actions.push_back(temp);
	}
}


int AInside::explore(Vector2 v,int x, int y) {
	v.x += x;
	v.y += y;

	if (points[v.y][v.x] != -INF)return points[v.y][v.x];//�P�x�������[�g�Ȃ�
	//kabe
	if (v.x == -1)return -INF;
	if (v.y == -1)return -INF;
	if (v.x == database.width)return -INF;
	if (v.y == database.height)return -INF;

	return tree(v,max((int)abs(v.x-destination.x), 
		(int)abs(v.y-destination.y)));
}



int AInside::tree(Vector2 v,int cnt)
{
	

	int point=0;
	if (v.x != destination.x|| v.y != destination.y) {
		if (v.x != destination.x&&v.y!=destination.y) {
			point = max(point, explore(v,transition.x,transition.y));
		}
		if (abs(v.x-destination.x) != cnt) {
			point = max(point, explore(v, 0, transition.y));
		}
		if (abs(v.y - destination.y) != cnt) {
			point = max(point, explore(v, transition.x, 0));
		}
	}

	points[v.y][v.x] = point;

	//�ړI�n�i�����j�܂ł̍ō��_��
	if (database.tiled[v.y][v.x] == teamID - database.teams[0].teamID)return point;
	else if (database.tiled[v.y][v.x] == 0)point + database.points[v.y][v.x];
	return point+ (database.points[v.y][v.x]*2);
}
