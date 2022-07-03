#pragma once
#include<iostream>
#include<fstream>
#include "Database.h"
#define LOGFILE "log.csv"

class Log
{
private:
	std::ifstream ifs;
	std::ofstream ofs;
	DataBase& database = DataBase::GetInstance();
public:
	Log(char mode);
	void write();
	void read();
};

