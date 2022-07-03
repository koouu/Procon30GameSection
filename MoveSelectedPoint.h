#pragma once
#include "Vector2.hpp"
#include "Database.h"
#include "Algorithm.h"
class MoveSelectedPoint:public Algorithm
{
private:
	Vector2 destination;
	DataBase& database = DataBase::GetInstance();
	vector<Action> actions;
public:
	MoveSelectedPoint(int teamID) :Algorithm(teamID) {}
	void setDestination(Vector2 destination);
	Vector2 explore(int agentID);
	void execute(int ahead);
	vector<Action> getActions() { return actions; }
};

