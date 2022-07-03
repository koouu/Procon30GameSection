#pragma once
#include "DxLib.h"
#include "Database.h"
#include "enums.h"

class DrawManager
{
private:
	int black = GetColor(0, 0, 0);
	int white = GetColor(205, 205, 205);
	int red = GetColor(205, 20, 0);
	int blue = GetColor(0, 20, 205);
	int green = GetColor(0, 255, 0);
	int yellow = GetColor(255, 255, 0);
	vector<Vector2> line_start;
	DataBase& database = DataBase::GetInstance();
public:
	DrawManager();
	void drawTile();
	void drawFrame();
	void drawPoints();
	void drawState(string argolithmName);
	void drawOperatingAgent(int teamID, int AgentID);
	void drawAgent();
	void drawTurn();
	void drawLine(vector<Action> moving_point);
	void drawNowLine(int count, Vector2 v);
	void drawCompetition(ECompetitionStatus status);
	void drawLine2(int teamID, vector<Action> moving_point,int select_agent);
	void drawTime();

};

