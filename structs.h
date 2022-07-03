#pragma once
#include<iostream>
#include<vector>
#include "Vector2.hpp"

//�ݒ�
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



//PlayerData��Agent�p
#define AGENTID first
#define POS second

struct PlayerData
{
	bool player;//AI���l��
	int teamID;
	std::vector<std::pair<int,Vector2>> Agent;//ID,Pos
	int tilePoint;
	int areaPoint;
	//std::vector<Vector2> position;
};