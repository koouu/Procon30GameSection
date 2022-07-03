#pragma once
#include<iostream>
#include<vector>
#include "Vector2.hpp"

//ê›íË
struct Config
{
	int turnNum;
	Vector2 fieldSize;
	int agentNum;
	int repetitionNum;
	bool randMode;
	bool jsonMode;
};

struct FieldV2{
	int field[20][20];
	int tileOwner[20][20];
};



//PlayerDataÇÃAgentóp
#define AGENTID first
#define POS second

struct PlayerData
{
	bool player;//AIÇ©êlÇ©
	int teamID;
	std::vector<std::pair<int,Vector2>> Agent;//ID,Pos
	int tilePoint;
	int areaPoint;
	//std::vector<Vector2> position;
};