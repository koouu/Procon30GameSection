#include "Donyoku.h"
#include "DxLib.h"
#include <utility>
#include <algorithm>

void Donyoku::execute(int ahead) {
	cands.clear(); cands.shrink_to_fit(); //cands初期化
	actions.clear(); actions.shrink_to_fit(); //actions初期化

	DataBase& database = DataBase::GetInstance();
	auto points = database.points;
	auto width = database.width;
	auto height = database.height;

	for (int i = 0; i < (int)agents.size(); ++i) {
		vector<vector<pair<int, Vector2>>> cand_point_list;//エージェントの周りの点数リスト

		auto agent = agents[i];
		for (int elem_x = agent.x - ahead; elem_x <= agent.x + ahead; ++elem_x) {
			vector<pair<int, Vector2>> temp;
			for (int elem_y = agent.y - ahead; elem_y <= agent.y + ahead; ++elem_y) {
				int point;
				if (elem_x == agent.x && elem_y == agent.y)//エージェントの位置にゴミ値
					point = trash_num;
				else if (elem_x < 0 || elem_y < 0)//フィールド外にゴミ値
					point = trash_num;
				else if (elem_x >= width || elem_y >= height)//フィールド外にゴミ値
					point = trash_num;
				else
					point = points[elem_y][elem_x];

				int dx = elem_x - agent.x;
				int dy = elem_y - agent.y;
				temp.push_back(make_pair(point, Vector2(dx, dy)));
			}
			cand_point_list.push_back(temp);
		}

		Node* root = new Node();
		Node::init(root);

		Vector2 center(ahead, ahead);
		makeTree(root, center, cand_point_list, ahead, 0);//行動選択肢の木構造作成
		root->info = make_pair(Donyoku::trash_num, Vector2(0, 0));

		vector<Vector2> temp;
		pair<int, vector<Vector2>> cand = make_pair(0, temp);//最終的な経路
		pair<int, vector<Vector2>> comp = make_pair(0, temp);//最善経路と比較するための	
		Vector2 agent_pos(agent.x, agent.y);
		const int cnt = ahead;
		auto tiled = database.tiled;

		calcOptActions(root, tiled, cand, comp, agent_pos, agent_pos, ahead, cnt);//候補検索

		if (ahead != 1) {
			Vector2 left = cand.second[0];
			Vector2 right = cand.second[1];
			if (!isOtherAgentMovePos(right)) {
				Vector2 diff = left + right;
				if (abs(diff.x) < 2 && abs(diff.y) < 2) {
					left = left + agent_pos;
					right = right + left;

					int left_point = (tiled[left.y][left.x] == teamID) ? 0 : points[left.y][left.x];
					int right_point = (tiled[right.y][right.x] == teamID) ? 0 : points[right.y][right.x];
					if (left_point == 0 && right_point == 0) {
						cand.second.erase(cand.second.begin() + 1);
					}
					else if (left_point < right_point) {
						cand.second[0] = right - agent_pos;
						cand.second[1] = left - right;
					}
				}
			}
		}

		cands.push_back(cand);

		Action action;
		action.agentID = agent.agentID;
		action.direction = cand.second[0];
		action.type = "move";
		if (action.direction == Vector2(0, 0))
			action.type = "stay";
		else {
			Vector2 target = action.direction + Vector2(agent.x, agent.y);
			int tile_state = database.tiled[target.y][target.x];
			if (tile_state != 0) {
				if (tile_state != teamID)
					action.type = "remove";
			}
		}

		actions.push_back(action);

		seekCloselyPlusPointPos(agent_pos);
		Vector2 a = closely_plus_point_pos;;
	}
}

void Donyoku::makeTree(Node* root, Vector2 center, const vector<vector<pair<int, Vector2>>>& cand_point_list, int ahead, int score) {
	vector<Vector2> temp;
	int cnt = 0;
	for (int elem_x = center.x - 1; elem_x <= center.x + 1; ++elem_x) {
		for (int elem_y = center.y - 1; elem_y <= center.y + 1; ++elem_y) {
			//if (cand_point_list[elem_x][elem_y].first == Donyoku::trash_num) continue;
			//if (elem_x == center.x && elem_y == center.y) continue;

			pair<int, Vector2> info = make_pair(cand_point_list[elem_x][elem_y].first, Vector2(elem_x - center.x, elem_y - center.y));
			root->children[cnt] = new Node();
			root->children[cnt]->info = info;
			if (ahead != 1)
				makeTree(root->children[cnt], Vector2(elem_x, elem_y), cand_point_list, ahead - 1, info.first);
			++cnt;
		}
	}
}

void Donyoku::calcOptActions(Node* root, vector<vector<int>>& tiled, pair<int, vector<Vector2>>& cand, pair<int, vector<Vector2>>& comp, Vector2& move_pos, Vector2 agent_pos, int ahead, int cnt) {

	if (ahead != 1) {
		for (int i = 0; i < 9; ++i) {
			if (root->children[i]->info.first == Donyoku::trash_num)//壁と元居た座標は除外
				continue;
			bool is_other_move_pos = false;
			bool is_other_pos = false;
			for (auto agent : agents) {
				Vector2 temp(agent.x, agent.y);
				if (temp == agent_pos)continue;//自分以外
				int diff_x = abs(agent_pos.x - temp.x);
				int diff_y = abs(agent_pos.y - temp.y);
				if (diff_x >= 6 && diff_y >= 6)continue;
				if (isOtherAgentPos(move_pos + root->children[i]->info.second))//移動先がエージェント位置除外
					is_other_pos = true;
				if (!cands.empty()) {//n手目が他のエージェント一手目の移動先との衝突回避
					if (diff_x >= 3 && diff_y >= 3)continue;
					if (isOtherAgentMovePos(move_pos + root->children[i]->info.second))
						is_other_move_pos = true;
				}
			}
			if (is_other_move_pos)
				continue;
			if (is_other_pos)
				continue;

			//if (ahead == cnt) {//一手目
			//	if (isOtherAgentPos(move_pos + root->children[i]->info.second))//移動先がエージェント位置除外
			//		continue;
			//}

			move_pos = move_pos + root->children[i]->info.second;
			Vector2 prev_move_pos = move_pos;
			int move_tile_state = tiled[move_pos.y][move_pos.x];

			if (move_tile_state == 0) {//フリータイルの時 (ここらへん汚い)
				comp.first += root->children[i]->info.first;
				comp.second.push_back(root->children[i]->info.second);
				tiled[move_pos.y][move_pos.x] = teamID;
				calcOptActions(root->children[i], tiled, cand, comp, move_pos, agent_pos, ahead - 1, cnt);
				move_pos = move_pos - root->children[i]->info.second;
				comp.first -= root->children[i]->info.first;
				comp.second.pop_back();
			}
			else if (move_tile_state != teamID) {//相手タイルの時
				comp.first += root->children[i]->info.first;
				comp.second.push_back(root->children[i]->info.second);
				tiled[move_pos.y][move_pos.x] = 0;
				move_pos = move_pos - root->children[i]->info.second;
				calcOptActions(root, tiled, cand, comp, move_pos, agent_pos, ahead - 1, cnt);
				comp.first -= root->children[i]->info.first;
				comp.second.pop_back();
			}
			else {//自タイルの時
				comp.second.push_back(root->children[i]->info.second);
				calcOptActions(root->children[i], tiled, cand, comp, move_pos, agent_pos, ahead - 1, cnt);
				move_pos = move_pos - root->children[i]->info.second;
				comp.second.pop_back();
			}
			tiled[prev_move_pos.y][prev_move_pos.x] = move_tile_state;
		}
		return;
	}

	vector<pair<int, Vector2>> infoes;//移動先候補の点数リスト

	for (Node* node : root->children) {
		if (node->info.first == Donyoku::trash_num)//元居たとこは除外
			continue;
		bool is_other_move_pos = false;
		bool is_other_pos = false;
		for (auto agent : agents) {
			Vector2 temp(agent.x, agent.y);
			if (temp == agent_pos)continue;//自分以外
			int diff_x = abs(agent_pos.x - temp.x);
			int diff_y = abs(agent_pos.y - temp.y);
			if (diff_x >= 6 && diff_y >= 6)continue;
			if (isOtherAgentPos(move_pos + node->info.second))//移動先がエージェント位置除外
				is_other_pos = true;
			if (!cands.empty()) {//n手目が他のエージェント一手目の移動先との衝突回避
				if (diff_x >= 3 && diff_y >= 3)continue;
				if (isOtherAgentMovePos(move_pos + node->info.second))
					is_other_move_pos = true;
			}
		}
		if (is_other_move_pos)
			continue;
		if (is_other_pos)
			continue;

		//Vector2 reverce(-(root->info.second.x), -(root->info.second.y));
		//if (node->info.second == reverce)//行って戻るを除外
		//	continue;
		bool is_staying = (node->info.second == Vector2(0, 0)) ? true : false;

		Vector2 m_pos = move_pos + node->info.second;
		int move_tile_state = tiled[m_pos.y][m_pos.x];
		pair<int, Vector2> in = node->info;
		if (is_staying)
			in.first = 0;
		if (move_tile_state == teamID) {
			in.first = 0;
		}

		infoes.push_back(in);
	}

	//移動先候補の点数リストを降順にソート
	sort(infoes.begin(), infoes.end(),
		[](const pair<int, Vector2>& a, const pair<int, Vector2>& b) {return a.first > b.first; });

	int max_score = infoes[0].first;

	comp.first += max_score;
	comp.second.push_back(infoes[0].second);

	if (cand.second.empty()) {
		cand = comp;
	}
	else if (cand.first < comp.first) {
		cand = comp;
	}

	comp.first -= max_score;
	comp.second.pop_back();
}

void Donyoku::seekCloselyPlusPointPos(Vector2 agent_pos) {
	DataBase& database = DataBase::GetInstance();
	auto width = database.width;
	auto height = database.height;
	auto points = database.points;
	int range_x = abs(width - 1 - agent_pos.x);
	int range_y = abs(height - 1 - agent_pos.y);
	int range = (range_x > range_y) ? range_x : range_y;
	for (int i = 1; i <= range; ++i) {
		vector<pair<int, Vector2>> temp;
		int elem_x = agent_pos.x - i;
		if (elem_x < 0)continue;
		for (int elem_y = agent_pos.y - i; elem_y <= agent_pos.y + i; ++elem_y) {
			if (elem_y < 0)continue;
			if (elem_y >= height)continue;
			int point = points[elem_y][elem_x];
			if (point < 0)continue;
			temp.push_back(make_pair(point, Vector2(elem_x, elem_y)));
		}

		elem_x = agent_pos.x + i;
		if (elem_x >= width)continue;
		for (int elem_y = agent_pos.y - i; elem_y <= agent_pos.y + i; ++elem_y) {
			if (elem_y < 0)continue;
			if (elem_y >= height)continue;
			int point = points[elem_y][elem_x];
			if (point < 0)continue;
			temp.push_back(make_pair(point, Vector2(elem_x, elem_y)));
		}

		int elem_y = agent_pos.y - i;
		if (elem_y < 0)continue;
		for (int elem_x = agent_pos.x - i; elem_x <= agent_pos.x + i; ++elem_x) {
			if (elem_x < 0)continue;
			if (elem_x >= width)continue;
			int point = points[elem_y][elem_x];
			if (point < 0)continue;
			temp.push_back(make_pair(point, Vector2(elem_x, elem_y)));
		}

		elem_y = agent_pos.y + i;
		if (elem_y >= height)continue;
		for (int elem_x = agent_pos.x - i; elem_x <= agent_pos.x + i; ++elem_x) {
			if (elem_x < 0)continue;
			if (elem_x >= width)continue;
			int point = points[elem_y][elem_x];
			if (point < 0)continue;
			temp.push_back(make_pair(point, Vector2(elem_x, elem_y)));
		}

		if (temp.empty())
			continue;

		sort(temp.begin(), temp.end(),
			[](const pair<int, Vector2>& a, const pair<int, Vector2>& b) {return a.first > b.first; });

		closely_plus_point_pos = temp[0].second;
		break;
	}
}

bool Donyoku::isOtherAgentPos(Vector2 agent_pos) {
	DataBase& database = DataBase::GetInstance();
	for (auto team : database.teams) {
		auto agents = team.agents;//エージェント情報
		for (auto agent : agents) {
			Vector2 temp(agent.x, agent.y);
			if (temp == agent_pos)
				return true;
		}
	}
	return false;
}

bool Donyoku::isOtherAgentMovePos(Vector2 move_pos) {
	DataBase& database = DataBase::GetInstance();
	for (auto team : database.teams) {
		if (team.teamID != teamID)continue;
		auto agents = team.agents;//エージェント情報
		for (int i = 0; i < cands.size(); ++i) {
			Vector2 agent_pos(agents[i].x, agents[i].y);
			Vector2 temp = agent_pos + cands[i].second[0];
			if (move_pos == temp)
				return true;
		}
	}
	return false;
}

void Donyoku::initTiled(vector<vector<int>>& tiled) {
	DataBase& database = DataBase::GetInstance();
	tiled = database.tiled;
}
