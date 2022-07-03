#pragma once
#include "Database.h"

class Algorithm {
protected:
	int teamID;
	vector<Agent> agents;
public:
	Algorithm(int teamID) :teamID(teamID) {
		DataBase& database = DataBase::GetInstance();
		auto teams = database.teams;
		Team team;//©ƒ`[ƒ€î•ñ
		for (auto t : teams) {
			if (t.teamID == teamID)
				team = t;
		}
		agents = team.agents;
	}
	virtual void execute(int ahead) = 0;
	virtual vector<Action> getActions() = 0;
public:
	const static int trash_num = -999;
};


class Node {
public:
	pair<int, Vector2> info;
	Node* children[9];

public:
	static void init(Node* root) {
		for (Node* node : root->children) {
			node = nullptr;
		}
		root->info = make_pair(Algorithm::trash_num, Vector2(0, 0));
	}
};
