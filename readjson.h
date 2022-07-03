#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include"structs.h"
#include"picojson.h"
#include "Database.h"



class readjson
{
private:
	int teamID;
	int limit_turn;
	int turnMillis;
	int intervalMillis;
public:
	void read();
	void write(std::vector<Action> action);
	int readBefore();
};

