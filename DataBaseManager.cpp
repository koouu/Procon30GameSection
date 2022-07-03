#include "DataBaseManager.h"

DataBaseManager::DataBaseManager(Config config, FieldV2 field,PlayerData playerData[])
{
	this->config = config;
	if (field.field[0][0] != -999) {
		for (int i = 0; i < config.fieldSize.y; i++) {
			std::vector<int> vv;
			std::vector<int> vt;
			for (int j = 0; j < config.fieldSize.x; j++) {
				vv.push_back(field.field[i][j]);
				vt.push_back(field.tileOwner[i][j]);
			}
			points.push_back(vv);
			tiled.push_back(vt);
		}
		for (int i = 0; i < 2; i++) {
			Team teamData;
			teamData.teamID = i;
			for (int j = 0; j < config.agentNum; j++) {
				Agent agent;
				agent.agentID = playerData[i].Agent[j].first;
				agent.x = playerData[i].Agent[j].second.x;
				agent.y = playerData[i].Agent[j].second.y;
				teamData.agents.push_back(agent);
			}
			team.push_back(teamData);
		}
	}
	
}


void DataBaseManager::makeDateBase()
{
	std::vector<Agent>actions;

	{//teamID–â‘è@‰‹}ˆ’u
		for (int i = 0; i < config.fieldSize.x; i++) {
			for (int j = 0; j < config.fieldSize.y; j++) {
				tiled[j][i]++;
			}
		}
		team[0].teamID++;
		team[1].teamID++;
	}
	
	database.getDataBase(config.fieldSize.x, config.fieldSize.y, points, 0,0, tiled, team, actions, config.turnNum);
	database.teams[0].tilePoint = database.getTotalTileScore(1);
	database.teams[1].tilePoint = database.getTotalTileScore(2);
}

void DataBaseManager::updateDataBase(vector<Action> actions)
{
	
	for (int i = 0; i < config.agentNum; i++) {
		if (actions[i].type == "remove") {
			database.tiled[actions[i].direction.y][actions[i].direction.x] = 0;
		}else{
			database.teams[0].agents[i].x = actions[i].direction.x;
			database.teams[0].agents[i].y = actions[i].direction.y;
			database.tiled[actions[i].direction.y][actions[i].direction.x] = 1;
		}
		if (actions[i + config.agentNum].type == "remove") {
			database.tiled[actions[i + config.agentNum].direction.y][actions[i + config.agentNum].direction.x] = 0;
		}
		else {
			database.teams[1].agents[i].x = actions[i + config.agentNum].direction.x;
			database.teams[1].agents[i].y = actions[i + config.agentNum].direction.y;
			database.tiled[actions[i + config.agentNum].direction.y][actions[i + config.agentNum].direction.x] = 2;
		}
	}
	database.turn++;
	for (int i = 0; i < 2; i++) {
		database.teams[i].tilePoint=database.getTotalTileScore(i+1);
		database.teams[i].areaPoint=database.getTotalAreaScore(i+1);
	}
}

