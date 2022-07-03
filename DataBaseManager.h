#pragma once
#include <iostream>
#include "structs.h"
#include "Database.h"
class DataBaseManager
{
private:
	Config config;
	DataBase& database = DataBase::GetInstance();
	std::vector<std::vector<int>> points;
	std::vector<std::vector<int>> tiled;
	std::vector<Team>team;
public:
	DataBaseManager(Config config, FieldV2 field, PlayerData playerData[]);
	void updateDataBase(vector<Action> actions);
	void makeDateBase();
	 
};

