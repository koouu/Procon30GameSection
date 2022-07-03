#pragma once
#include "Algorithm.h"
#include "Vector2.hpp"
#include "MoveSelectedPoint.h"
class AInside :
	public Algorithm
{
	Vector2 destination;
	Vector2 transition;
	int points[20][20];
	DataBase& database = DataBase::GetInstance();
	vector<Action> actions;
	MoveSelectedPoint *moveselectpoint;

public:
	AInside(int teamID);
	void execute(int ahead);//É~ÉJÉì
	int explore(Vector2 v,int x, int y);
	vector<Action> getActions() { return actions; }
	int tree(Vector2 v, int cnt);//äÆê¨
};

