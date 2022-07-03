#pragma once

#include <iostream>
#include <vector>
#include <string>
#include"singleton.h"
#include"Vector2.hpp"


using namespace std;

class Agent
{
public:
	int agentID;
	int x;
	int y;
};

class Team
{
public:
	int teamID;
	vector<Agent> agents;
	int tilePoint;
	int areaPoint;
};

class Action
{
public:
	int agentID;
	string type;
	Vector2 direction;
	int apply;
};

class DataBase:
	public ISingleton<DataBase>
{
private:
	friend ISingleton<DataBase>;
public:
	DataBase();
	void getDataBase(int width, int height, vector<vector<int>>points,
		long long startedAtUnixTime, int turn, vector<vector<int>> tiled,
		vector<Team> teams, vector<Agent> actions, int limit_turn);
	int getTotalTileScore(int teamID)const;
	int getTotalAreaScore(int teamID) const;
	int width;
	int height;
	vector<vector<int>> points;
	long long startedAtUnixTime;
	int turn;
	vector<vector<int>> tiled;
	vector<Team> teams;
	vector<Agent> actions;
	int limit_turn;
	int intervalMillis;
	int turnMillis;
};
