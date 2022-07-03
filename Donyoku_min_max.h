#pragma once

#include "Algorithm.h"
#include "Database.h"
#include "Vector2.hpp"

class Donyoku_Min_Max : public Algorithm
{
private:
	vector<pair<int, vector<Vector2>>> cands;
	vector<Action> actions;
	Vector2 closely_plus_point_pos;
public:
	Donyoku_Min_Max(int teamID) :Algorithm(teamID) {}
	void execute(int ahead);
	vector<Action> getActions() { return actions; }
	Vector2 getCloselyPlusPointPos() { return closely_plus_point_pos; }
private:
	void makeTree(Node* root, Vector2 center, const vector<vector<pair<int, Vector2>>>& cand_point_list, int ahead, int score);
	void calcOptActions(Node* root, vector<vector<int>>& tiled, pair<int, vector<Vector2>>& cand, pair<int, vector<Vector2>>& comp, Vector2& move_pos, Vector2 agent_pos, int ahead, int cnt);
	void seekCloselyPlusPointPos(Vector2 agent_pos);
	bool isOtherAgentPos(Vector2 agent_pos);
	bool isOtherAgentMovePos(Vector2 move_pos);
	int  getTotalAreaScore(int teamID, vector<vector<int>> tiled, bool is_myself) const;
	int  getMaxInPoints();
	void initTiled(vector<vector<int>>& tiled);

};

