#include "MoveManager.h"
MoveManager::MoveManager(int agentNum)
{
	this->agentNum = agentNum;

}

void MoveManager::setField()
{
	//DataBase&database = DataBase::GetInstance();
	int a = database.height;
	int b = database.width;
	for (int i = 0; i < database.height; i++) {
		for (int j = 0; j < database.width; j++) {
			tiled_state[j][i] = 0;
			agent_pos[j][i] = -1;
		}
	}
		
			
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < agentNum; j++)
			agent_pos[database.teams[i].agents[j].y][database.teams[i].agents[j].x] = i * agentNum + j;
	if (!moved_id.empty()) {
		moved_id.clear();
		moved_id.shrink_to_fit();
	}
}

void MoveManager::setAction(std::vector<Action> actions)
{
	this->actions = actions;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < agentNum; j++) {
			if (actions[i * agentNum + j].type == "move") {
				tiled_state[database.teams[i].agents[j].y+ actions[i * agentNum + j].direction.y]
					[database.teams[i].agents[j].x+ actions[i * agentNum + j].direction.x] += (1 << (i * agentNum + j));
			}
		}
	}
		
}



bool MoveManager::canMove(int agentID)
{
	//agentID -= database.teams[0].agents[0].agentID;
	if (actions[agentID].type == "remove")return false;
	if (actions[agentID].direction.x == 0 && actions[agentID].direction.y == 0)return true;//�����Ȃ��Ȃ�ok
	Vector2 v;//�ψق�����̍��W
	v.x = database.teams[(agentID / agentNum)].agents[agentID % agentNum].x + actions[agentID].direction.x;
	v.y = database.teams[(agentID / agentNum)].agents[agentID % agentNum].y + actions[agentID].direction.y;
	if (v.x >= database.width || v.y >= database.height)return false;
	if (v.x <0 || v.y <0)return false;
	if (agent_pos[v.y][v.x] == agentID)return true;//�����邱�Ƃ��m�F�ς�
	if (database.tiled[v.y][v.x] == 2 - (agentID / agentNum))return false;//�G�}�X
	if (tiled_state[v.y][v.x] == (1 << agentID)) {//�ق��ɂ��̃}�X�ɗ���agent���Ȃ��Ƃ��Ȃ��ɂȂ�
		if (agent_pos[v.y][v.x] == -1) {
			agent_pos[v.y][v.x] = agentID;
			agent_pos[v.y - actions[agentID].direction.y][v.x - actions[agentID].direction.x] = -1;
			return true;
		}//�ړ���Ȃɂ����Ȃ�
		if (canMove(agent_pos[v.y][v.x])) {
			agent_pos[v.y][v.x] = agentID;
			agent_pos[v.y - actions[agentID].direction.y][v.x - actions[agentID].direction.x] = -1;
			return true;
		}//�ړ����agent���ړ�
		return false;
	}
	return false;
}

bool MoveManager::canRemove(int agentID)
{
	Vector2 v;//�������W
	v.x = database.teams[(agentID / agentNum)].agents[agentID % agentNum].x + actions[agentID].direction.x;
	v.y = database.teams[(agentID / agentNum)].agents[agentID % agentNum].y + actions[agentID].direction.y;
	//if (!database.tiled[v.y][v.x] == 2 - (agentID / agentNum))return false;//�G�}�X�łȂ�
	if (agent_pos[v.y][v.x] == -1)return true;
	return false;
}
