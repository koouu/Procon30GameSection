#pragma once
#include"modebase.h"
#include"structs.h"
#include"readjson.h"
#include "enums.h"
#include "AlgorithmSelect.h"

class CompetitionMode:
	public ModeBase
{
private:
	readjson json;
	DataBase& database = DataBase::GetInstance();
	EAlgorithmStatus algorithmName;
	AlgorithmSelect* algorithmselect;
	vector<Action> actions;
	int competition_status;
	bool madeDataBase;
	int select_agent;
	string s;
	int teamID;
public:
	CompetitionMode(int turn);
	bool Draw();
	EGameModeStatus Process();
	Config getConfig();
	void setByPlayer();
	void checkRemove();
};

