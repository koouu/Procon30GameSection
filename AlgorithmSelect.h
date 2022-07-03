#pragma once
#include"enums.h"
#include "Vector2.hpp"
#include <vector>
#include "Donyoku.h"

class AlgorithmSelect
{
	EAlgorithmStatus algorithmName;
	Algorithm* algorithm;
	std::vector<Action> actions;
	int teamID;
public:
	AlgorithmSelect(int teamID);
	EAlgorithmStatus getAlgorithm();
	std::vector<Action> getAction();
	void operateAlgorithm();
};

