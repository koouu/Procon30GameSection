#include "playmode.h"
#include "enums.h"
#include "keyexport.h"
#include "makefield.h"
#include"DxLib.h"
#include <fstream>
#include <sstream>
#include"Database.h"
#include <utility>      //add_oomori
#include "DrawManager.h"
#include "Donyoku.h"
#include "AInside.h"
#include "AOutside.h"


PlayMode::PlayMode(int playerPattern,Config config) {
	
	if (config.jsonMode) {
		json.read();
		this->config.fieldSize = Vector2(database.width, database.height);
		this->config.agentNum = database.teams[0].agents.size();
		this->config.turnNum = config.turnNum;
		database.limit_turn = config.turnNum;
		for (int i = 0; i < playerPattern; i++)playerData[i].player = 1;
		playerData[0].teamID = database.teams[0].teamID;
		playerData[1].teamID = database.teams[1].teamID;
		field.field[0][0] = -999;
		for (int i = 0; i < config.agentNum*2; i++) {
			pair<int, Vector2> p;
			p.first = database.teams[i / config.agentNum].agents[i % config.agentNum].agentID;
			p.second = Vector2(database.teams[i / config.agentNum].agents[i % config.agentNum].x, database.teams[i / config.agentNum].agents[i % config.agentNum].y);
			playerData[i / config.agentNum].Agent.push_back(p);
		}
		databasemanager = new DataBaseManager(config, field, playerData);
	}
	else {
		playerData[0].player = playerData[1].player = playerData[0].areaPoint = playerData[1].areaPoint = 0;
		playerData[0].teamID = 0;
		playerData[1].teamID = 1;
		for (int i = 0; i < playerPattern; i++)playerData[i].player = 1;
		this->config = config;
		MakeField* makefield = new MakeField(config.randMode, config.fieldSize);
		field = makefield->make();
		aPos();
		for (int i = 0; i < config.fieldSize.y; i++)for (int j = 0; j < config.fieldSize.x; j++)field.tileOwner[i][j] = -1;
		for (int i = 0; i < config.agentNum; i++) {
			field.tileOwner[playerData[0].Agent[i].POS.y][playerData[0].Agent[i].POS.x] = playerData[0].teamID;
			field.tileOwner[playerData[1].Agent[i].POS.y][playerData[1].Agent[i].POS.x] = playerData[1].teamID;
			playerData[0].Agent[i].first = i;
			playerData[1].Agent[i].first = i + config.agentNum;
		}
		databasemanager = new DataBaseManager(config, field, playerData);
		databasemanager->makeDateBase();
		delete makefield;
		
		
	}
	turn = 0;
	inputcount = 0;
	nowInput = { 0, "move", {0, 0}, -1 };
	
	movemanager = new MoveManager(this->config.agentNum);
	

}

void PlayMode::PlayModeEnd()
{
	delete movemanager;
	delete algorithm;
}



void PlayMode::reset() {
	inputcount = 0;
	input.clear();
	input.shrink_to_fit();
	moveposi.clear();
	moveposi.shrink_to_fit();

}

void PlayMode::aPos() {
	int time = 0;
	int n = config.agentNum;
	while (n >= 1) {
		int xr;
		int yr;
		Vector2 v;
		bool hit = true;
		while (hit) {
			bool bo = true;
			xr = GetRand(-1 + (config.fieldSize.x / 2));
			yr = GetRand(-1 + (config.fieldSize.y / 2));
			v.x = xr;
			v.y = yr;
			for (int i = 0; i < time; i++) {
				if (playerData [i % 2].Agent[i * 2].POS.x == v.x && playerData[i % 2].Agent[i * 2].POS.y == v.y) {
					bo = false;
					break;
				}
			}
			hit = !bo;
		}
		std::pair<int, Vector2> temp;
		temp.AGENTID = time*2;
		temp.POS = v;
		playerData[time % 2].Agent.push_back(temp);
		temp.POS.y = config.fieldSize.y - yr - 1;
		playerData[1-time % 2].Agent.push_back(temp);
		if (n >= 2) {
			temp.POS.x = config.fieldSize.x - xr - 1;
			playerData[time % 2].Agent.push_back(temp);
			temp.POS.y = yr;
			playerData[1 - time % 2].Agent.push_back(temp);
		}
		time++;
		n -= 2;
	}
	
}



Config PlayMode::getConfig()
{
	return config;
}

EGameModeStatus PlayMode::Process()
{
	

	CKeyExport_S& key = CKeyExport_S::GetInstance();
	if (database.turn > database.limit_turn) {
		if (key.ExportKeyStateFrame(KEY_INPUT_RETURN) > 0||1) {
			delete movemanager;
			delete algorithm;
			delete databasemanager;
			return eAIGame;
		}
	}
	else {
		if (key.ExportKeyState(KEY_INPUT_B) > 0) {
			reset();
		}
		if (inputcount < config.agentNum * 2) {
			
			if (playerData[inputcount / config.agentNum].player) {
				InputEnd();

			}
			else {
				algorithm = new Donyoku(inputcount / config.agentNum + 1);
				algorithm->execute(5);
				vector<Action> actions = algorithm->getActions();
				Action action;
				for (int i = 0; i < config.agentNum; i++) {
					action = actions[i];
					input.push_back(action);
					inputcount++;
				}
			}
		}
		//if (inputcount >= config.agentNum * 2&& key.ExportKeyState(KEY_INPUT_RETURN) > 0) {
		if (inputcount >= config.agentNum * 2){
			int hoogeee;
			hoogeee = 101010;
			for (int i = 0; i < config.agentNum * 2; i++) {
				Vector2 v;
				v.x = database.teams[(i / config.agentNum)].agents[i % config.agentNum].x;
				v.y = database.teams[(i / config.agentNum)].agents[i % config.agentNum].y;
				if (v.x + input[i].direction.x < 0 || v.x + input[i].direction.x >= config.fieldSize.x ||
					v.y + input[i].direction.y < 0 || v.y + input[i].direction.y >= config.fieldSize.y) {
					input[i].direction = { 0,0 };
				}
			}
			movemanager->setField();
			movemanager->setAction(input);
			for (int i = 0; i < config.agentNum * 2; i++) {
				if (input[i].type == "move") {
					if (movemanager->canMove(i)) {

					}
					else {
						input[i].type = "stay";
						input[i].direction = { 0,0 };
					}
				}
			}
			for (int i = 0; i < config.agentNum * 2; i++) {
				if (input[i].type == "remove") {
					if (movemanager->canRemove(i)) {

					}
					else {
						input[i].type = "stay";
						input[i].direction = { 0,0 };
					}
				}
			}
			for (int i = 0; i < config.agentNum * 2; i++) {
				Action temp;
				temp.agentID = i;
				Vector2 v;
				v.x = database.teams[(i / config.agentNum) ].agents[i % config.agentNum].x;
				v.y = database.teams[(i / config.agentNum) ].agents[i % config.agentNum].y;
				temp.direction = v + input[i].direction;
				temp.type = input[i].type;
				temp.apply = input[i].apply;
				moveposi.push_back(temp);
			}
			databasemanager->updateDataBase(moveposi);
			reset();
		}
	}
	
	if (key.ExportKeyStateFrame(KEY_INPUT_ESCAPE) > 0) {
		return eAIGame;
	}
	return eContinue;
}

bool PlayMode::Draw()
{
	DrawManager drawmanager;
	drawmanager.drawTile();
	drawmanager.drawFrame();
	drawmanager.drawPoints();
	drawmanager.drawAgent();
	drawmanager.drawState("l—Í");
	drawmanager.drawOperatingAgent((inputcount >= config.agentNum)+1, inputcount+1);
	if(playerData[inputcount / config.agentNum].player&&inputcount<config.agentNum*2)
	drawmanager.drawNowLine(inputcount, nowInput.direction);
	drawmanager.drawLine(input);
	return true;
}


//O‚à‚è‚­‚ñ
/*



o
m
o
r
i







*/
//void PlayMode::Move() {
//	int team_id = playerData[0].teamID;
//	int i;
//	for (int j = 0; j < config.agentNum * 2; j++) {
//		team_id = playerData[j % config.agentNum].teamID;
//		if (j >= config.agentNum) {
//			i = j - config.agentNum;
//		}
//		else {
//			i = j;
//		}
//
//		Action hoge = { input[team_id].agentID,
//					   input[j].type,
//					   {playerData[team_id].Agent[j].second.x + input[j].direction.x,
//						playerData[team_id].Agent[j].second.x + input[j].direction.x} };
//		moveposi.push_back(hoge);
//		if (moveposi[i].direction.x > config.fieldSize.x - 1 || moveposi[j].direction.x < 0 ||
//			moveposi[i].direction.y > config.fieldSize.y - 1 || moveposi[j].direction.y < 0) {
//			moveposi[i].apply = INVALID;
//			input[i].apply = INVALID;
//			moveposi[i].type = "stay";
//			moveposi[j].direction = moveposi[j].direction - input[j].direction;
//		}
//	}
//	for (int j = 0; j < config.agentNum * 2; j++) {
//		team_id = playerData[j % config.agentNum].teamID;
//		if (j >= config.agentNum) {
//			i = j - config.agentNum;
//		}
//		else {
//			i = j;
//		}
//		if (moveposi[j].type == "move") {
//			if (field.tileOwner[moveposi[j].direction.x][moveposi[j].direction.y] == playerData[1 - team_id].teamID) {
//				input[j].apply = INVALID;
//				moveposi[j].apply = INVALID;
//				moveposi[j].type = "stay";
//				moveposi[j].direction = moveposi[j].direction - input[j].direction;
//			}
//			for (int k = j + 1; k < config.agentNum * 2; k++) {
//				if (moveposi[j].apply == VALID && moveposi[k].apply == VALID) {
//					if (moveposi[j].direction == moveposi[k].direction) {
//						input[k].apply = CONFLICT;
//						moveposi[k].apply = CONFLICT;
//						moveposi[k].type = "stay";
//						moveposi[k].direction = moveposi[k].direction - input[k].direction;
//						if (moveposi[k].type == "move" || moveposi[k].type == "stay") {
//							input[j].apply = CONFLICT;
//							moveposi[j].apply = CONFLICT;
//							moveposi[j].type = "stay";
//							moveposi[j].direction = moveposi[j].direction - input[j].direction;
//						}
//					}
//				}
//			}
//		}
//	}
//} // add_oomori change_oomori_ver.2

//move‚Æremove

//void PlayMode::Move() {
//	//int team_id = playerData[0].teamID;
//	for (int i = 0; i < 2; i++) {
//		int team_id = i;
//		for (int j = 0; j < config.agentNum ; j++) {
//			
//			Action hoge = { input[j + i * config.agentNum].agentID,
//						   input[j + i * config.agentNum].type,
//						   playerData[team_id].Agent[j].second+ input[j + i * config.agentNum].direction};
//			moveposi.push_back(hoge);
//			if (moveposi[j+i* config.agentNum].direction.x > config.fieldSize.x - 1 || moveposi[j + i * config.agentNum].direction.x < 0 ||
//				moveposi[j + i * config.agentNum].direction.y > config.fieldSize.y - 1 || moveposi[j + i * config.agentNum].direction.y < 0) {
//				moveposi[j + i * config.agentNum].apply = INVALID;
//				input[j+i * config.agentNum].apply = INVALID;
//				moveposi[j + i * config.agentNum].type = "stay";
//				moveposi[j + i * config.agentNum].direction = moveposi[j + i * config.agentNum].direction - input[j + i * config.agentNum].direction;
//			}
//		}
//	}
//	
//	for (int i = 0; i < 2; i++) {
//		int team_id = playerData[i].teamID;
//		for (int j = 0; j < config.agentNum ; j++) {
//			team_id = playerData[i].teamID;
//			
//			if (moveposi[j + i * config.agentNum].type == "move") {
//				if (field.tileOwner[moveposi[j + i * config.agentNum].direction.x][moveposi[j + i * config.agentNum].direction.y] == playerData[1 - team_id].teamID) {
//					input[j + i * config.agentNum].apply = INVALID;
//					moveposi[j + i * config.agentNum].apply = INVALID;
//					moveposi[j + i * config.agentNum].type = "stay";
//					moveposi[j + i * config.agentNum].direction = moveposi[j].direction - input[j].direction;
//				}
//				for (int k = j + 1; k < config.agentNum * 2; k++) {
//					if (moveposi[j + i * config.agentNum].apply == VALID && moveposi[k].apply == VALID) {
//						if (moveposi[j + i * config.agentNum].direction == moveposi[k].direction) {
//							input[k].apply = CONFLICT;
//							moveposi[k].apply = CONFLICT;
//							moveposi[k].type = "stay";
//							moveposi[k].direction = moveposi[k].direction - input[k].direction;
//							if (moveposi[k].type == "move" || moveposi[k].type == "stay") {
//								input[j + i * config.agentNum].apply = CONFLICT;
//								moveposi[j + i * config.agentNum].apply = CONFLICT;
//								moveposi[j + i * config.agentNum].type = "stay";
//								moveposi[j + i * config.agentNum].direction = moveposi[j + i * config.agentNum].direction - input[j + i * config.agentNum].direction;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	
//} // add_oomori change_oomori_ver.2 ‚¾‚Á‚½‚â‚Â
//
//void PlayMode::Remove() {
//	for (int i = 0; i < config.agentNum * 2; i++) {
//		if (input[i].type == "remove") {
//			if (input[i].apply != INVALID && field.tileOwner[moveposi[i].direction.x][moveposi[i].direction.y] == 0) {
//				input[i].apply = INVALID;
//				moveposi[i].apply = INVALID;
//				moveposi[i].type = "stay";
//				moveposi[i].direction = moveposi[i].direction - input[i].direction;
//			}
//			else {
//				for (int j = i + 1; j < config.agentNum * 2; j++) {
//					if (moveposi[i].direction == moveposi[j].direction) {
//						if (moveposi[j].type == "move" || moveposi[j].type == "stay") {
//							moveposi[i].apply = CONFLICT;
//							input[i].apply = CONFLICT;
//							moveposi[i].type = "stay";
//							moveposi[i].direction = moveposi[i].direction - input[i].direction;
//						}
//					}
//				}
//			}
//		}
//	}
//}

void PlayMode::InputEnd() {
	Action hoge;
	CKeyExport_S& key = CKeyExport_S::GetInstance();
	if (config.agentNum > inputcount) {
		if (playerData[0].player) {
			Input(0);
			if (key.ExportKeyState(KEY_INPUT_RETURN) > 0) {
				/*if (database.tiled[database.teams[0].agents[inputcount - config.agentNum].y+nowInput.direction.y]
					[database.teams[0].agents[inputcount - config.agentNum].x+nowInput.direction.x] == database.teams[1].teamID) {
					nowInput.type = "remove";
				}
				else {
					nowInput.type = "move";
				}*/
				if (database.tiled[database.teams[inputcount / config.agentNum].agents[inputcount % config.agentNum].y + nowInput.direction.y][database.teams[inputcount / config.agentNum].agents[inputcount % config.agentNum].x + nowInput.direction.x]
					== (!(inputcount / config.agentNum)) + 1)nowInput.type = "remove";
				inputcount++;
				input.push_back(nowInput);
				nowInput = { 0, "move", {0, 0}, -1 };
			}
		}
	}
	else {
		if (playerData[1].player) {
			Input(1);
			if (key.ExportKeyState(KEY_INPUT_RETURN) > 0 || 1){
				/*if (database.tiled[database.teams[1].agents[inputcount - config.agentNum].y]
					[database.teams[1].agents[inputcount - config.agentNum].x] == database.teams[0].teamID) {
					nowInput.type = "remove";
				}
				else {
					nowInput.type = "move";
				}*/
				database.teams[inputcount / config.agentNum].agents[inputcount % config.agentNum];
				if (database.tiled[database.teams[inputcount / config.agentNum].agents[inputcount % config.agentNum].y+nowInput.direction.y][database.teams[inputcount / config.agentNum].agents[inputcount % config.agentNum].x+nowInput.direction.x]
					== (!(inputcount / config.agentNum)) + 1)nowInput.type == "remove";
				inputcount++;
				input.push_back(nowInput);
				nowInput = { 0, "move", {0, 0}, -1 };
			}
		}
	}
} // add_oomori
void PlayMode::Input(int agent_id) {
	CKeyExport_S& key = CKeyExport_S::GetInstance();
	//nowInput = { 0, "empty", {2, 2}, -1 }; // pair.first : 0->stay 1->move , -1->remove , 2->error
											 // pair.second: -1<=x,y<=1 -> move direction , 2->error
	nowInput.agentID = agent_id;
	if (key.ExportKeyState(KEY_INPUT_UP)) {
		nowInput.direction.y --;
		if (nowInput.direction.y < -1)nowInput.direction.y = -1;
	}
	if (key.ExportKeyState(KEY_INPUT_DOWN)) {
		nowInput.direction.y++;
		if (nowInput.direction.y > 1)nowInput.direction.y = 1;
	}
	if (key.ExportKeyState(KEY_INPUT_RIGHT)) {
		nowInput.direction.x++;
		if (nowInput.direction.x > 1)nowInput.direction.x = 1;
	}
	if (key.ExportKeyState(KEY_INPUT_LEFT)) {
		nowInput.direction.x--;
		if (nowInput.direction.x < -1)nowInput.direction.x = -1;
	}
	if (key.ExportKeyState(KEY_INPUT_R)) {
		nowInput.type = "remove";
	}
	if (key.ExportKeyState(KEY_INPUT_M)) {
		nowInput.type = "move";
	}
} // add_oomori
