#pragma once
#include"structs.h"
enum EGameModeStatus;

class ModeBase
{
	//play��select
public:
	ModeBase(){};
	virtual ~ModeBase(){};

	virtual Config getConfig()=0;
	virtual EGameModeStatus Process() = 0;
	virtual bool Draw() = 0;
	

private:

};