#include "MoveSelectedPoint.h"

void MoveSelectedPoint::setDestination(Vector2 destination)
{
	this->destination = destination;
}

Vector2 MoveSelectedPoint::explore(int agentID)
{
	
	int dx, dy;
	for (int i = 0; i < agents.size(); i++) {
		if (agents[i].agentID == agentID) {
			agentID = i + agents[0].agentID;
		}
	}
	dx = destination.x - agents[agentID - agents[0].agentID].x;
	dy = destination.y - agents[agentID - agents[0].agentID].y;
	
	Vector2 v(agents[agentID - agents[0].agentID].x, agents[agentID - agents[0].agentID].y);
	Vector2 dv;
	if (dx == 0)dv.x = 0;
	else dv.x = dx / abs(dx);
	if (dy == 0)dv.y = 0;
	else dv.y = dy / abs(dy);
	std::pair<int, Vector2> max(-10101, {});
	if (abs(dx) == abs(dy)) {
		return Vector2(dv.x,dv.y);
	}
	else if (abs(dx) > abs(dy)) {
		int dif = abs(dx) - abs(dy);
		
		
		for (int i = 0; i < (1 << abs(dx)); i++) {
			int cnt = 0;
			for (int j = 0; j < abs(dx); j++) {
				if (i & (1 << j))cnt++;
			}
			if (cnt != dif)continue;
			int point = 0;
			for (int j = 0; j < abs(dx); j++) {
				if (database.tiled[v.y + (dv.y * ((i & (1 << j))!=0))][v.x + dv.x]!=teamID&&
					database.tiled[v.y + (dv.y * ((i & (1 << j)) != 0))][v.x + dv.x] != 0)
					point += database.points[v.y + (dv.y* ((i & (1 << j)) != 0))][v.x + dv.x] * 2;
				else point += database.points[v.y + (dv.y * ((i & (1 << j)) != 0))][v.x + dv.x];

			}
			if (point > max.first)max = make_pair(point, Vector2(dv.x, (dv.y * (i & (1 << 0)))));
		}
	}
	else {
		int dif = abs(dy) - abs(dx);


		for (int i = 0; i < (1 << abs(dy)); i++) {
			int cnt = 0;
			for (int j = 0; j < abs(dy); j++) {
				if (i & (1 << j))cnt++;
			}
			if (cnt != dif)continue;
			int point = 0;
			for (int j = 0; j < abs(dy); j++) {
				if (database.tiled[v.y + (dv.y )][v.x + (dv.x * ((i & (1 << j)) != 0))] != teamID &&
					database.tiled[v.y + (dv.y)][v.x + (dv.x * ((i & (1 << j)) != 0))] != 0)
					point += database.points[v.y + (dv.y )][v.x + (dv.x * (i & ((1 << j)) != 0))] * 2;
				else point += database.points[v.y + (dv.y )][v.x + (dv.x * ((i & (1 << j)) != 0))];

			}
			if (point > max.first)max = make_pair(point, Vector2(dv.x * (i & (1 << 0)), (dv.y)));
		}

	}
	return max.second;
}

void MoveSelectedPoint::execute(int ahead)
{
}
