#include "Database.h"
#include "Vector2.hpp"
#include <set>

//タイルポイント合計を返す
int DataBase::getTotalTileScore(int teamID) const {
	int score = 0;
	for (int i = 0; i < (int)tiled.size(); ++i)
		for (int j = 0; j < (int)tiled[i].size(); ++j) {
			if (tiled[i][j] != teamID) continue;
			score += points[i][j];
		}
	return score;
}

//領域ポイントの合計を返す
int DataBase::getTotalAreaScore(int teamID) const {
	const short offset[][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } ,{ 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 } };

	set<Vector2> visited;//確保タイルの座標リスト
	for (int i = 0; i < (int)tiled.size(); ++i)
		for (int j = 0; j < (int)tiled[i].size(); ++j) {
			if (tiled[i][j] != teamID) continue;
			visited.insert(Vector2(j, i));
		}

	set<Vector2> touch, next;
	for (int i = 0; i < height; ++i) {
		touch.insert(Vector2(0, i)); touch.insert(Vector2(width - 1, i));
	}
	for (int i = 0; i < width; ++i) {
		touch.insert(Vector2(i, 0)); touch.insert(Vector2(i, height - 1));
	}

	while (!touch.empty()) {
		next.clear();
		for (auto nowPos : touch) {
			if (visited.find(nowPos) != visited.end()) continue;
			visited.insert(nowPos);
			for (int i = 0; i < 8; ++i) {
				const Vector2 np(nowPos.x + offset[i][0], nowPos.y + offset[i][1]);
				if (np.x >= 0 && np.y >= 0 && np.x < width && np.y < height)
					next.insert(np);
			}
		}
		touch.swap(next);
	}

	int score = 0;

	for (int i = 0; i < (int)points.size(); ++i)
		for (int j = 0; j < (int)points[i].size(); ++j) {
			if (visited.find(Vector2(j, i)) != visited.end())
				continue;
			score += abs(points[i][j]);
		}
	return score;
}
DataBase::DataBase() {

}

void DataBase::getDataBase(int width,int height,vector<vector<int>>points,
	long long startedAtUnixTime,int turn,vector<vector<int>> tiled,
	vector<Team> teams,vector<Agent> actions,int limit_turn)
{
	this-> width= width;
	this->height= height;
	this-> points= points;
	this->startedAtUnixTime= startedAtUnixTime;
	this->turn= turn;
	this->tiled =tiled;
	this->teams=teams;
	this->actions= actions;
	this->limit_turn= limit_turn;

}
