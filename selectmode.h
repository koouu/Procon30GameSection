#pragma once
#include"DXLib.h"
#include<iostream>
#include"modebase.h"
#include"structs.h"
enum EGameModeStatus;
class SelectMode:public ModeBase
{
private:
	//セレクト画面
	Config config;
	int arrow;
public:

	SelectMode(Config lastConfig) ;
	~SelectMode();
	EGameModeStatus Process();
	Config getConfig();

	bool Draw();
};

