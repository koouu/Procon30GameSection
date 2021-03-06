#pragma once
#include "Database.h"
class MoveManager
{
private:
	DataBase& database = DataBase::GetInstance();
	int tiled_state[20][20];
	int agent_pos[20][20];
	std::vector<Action> actions;
	int agentNum;
	vector<int> moved_id;
public:
	MoveManager(int agentNum);
	void setField();
	void setAction(std::vector<Action> actions);//フラグたて
	bool canMove(int agentID);//動けるとtrue
	bool canRemove(int agentID);//消せるとtrue
	bool existAgent(Vector2 v);//v座標にagentいるか
};

