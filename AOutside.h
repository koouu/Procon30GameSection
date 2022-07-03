#pragma once
#include "Algorithm.h"
#include "Vector2.hpp"

class AOutside :
	public Algorithm
{
private:
	int status;
	int destination;//2桁2進数:縦か横か、マイナスかプラスか
	int fieldDP[20][20];
	DataBase& database = DataBase::GetInstance();
public:
	AOutside(int teamID);
	void execute(int ahead);
	int explore(Vector2 v, int x, int y);
	int tree(Vector2 v);
};

