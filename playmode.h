#pragma once
#include"modebase.h"
#include"structs.h"
#include"AgentPosition.h"
#include"readjson.h"
#include "DataBaseManager.h"
#include "Donyoku.h"
#include "MoveManager.h"

class PlayMode :
	public ModeBase

{
private:
	PlayerData playerData[2];
	Config config;
	FieldV2 field;  
	readjson json;
	int turn;
	DataBase& database = DataBase::GetInstance();
	DataBaseManager* databasemanager;
	//DrawManager* drawmanager;
	int inputcount;//add_oomori
	vector<Action> input;//add_oomori
	const int INVALID = -1; //ñ≥å¯ add_oomori
	const int CONFLICT = 0; //ã£çá add_oomori
	const int VALID = 1;    //óLå¯ add_oomori
	vector<Action> moveposi;//add_oomori_ver.2
	Action nowInput;
	Algorithm *algorithm;
	MoveManager* movemanager;
	//AgentPosition *aPos;
public:
	void aPos();
	PlayMode(int playerPattern,Config config);
	void PlayModeEnd();
	Config getConfig();
	EGameModeStatus Process();
	bool Draw();
	void Move();//add_oomori_ver.2
	void Remove();//add_oomPlayeori_ver.2
	void InputEnd();
	void Input(int agent_id);
	void reset();
};

