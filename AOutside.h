#pragma once
#include "Algorithm.h"
#include "Vector2.hpp"

class AOutside :
	public Algorithm
{
private:
	int status;
	int destination;//2��2�i��:�c�������A�}�C�i�X���v���X��
	int fieldDP[20][20];
	DataBase& database = DataBase::GetInstance();
public:
	AOutside(int teamID);
	void execute(int ahead);
	int explore(Vector2 v, int x, int y);
	int tree(Vector2 v);
};

