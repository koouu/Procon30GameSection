#pragma once
#include "singleton.h"
#include "enums.h"
#include "modebase.h"
class GameControl :
	public ISingleton<GameControl>
{
private:
	//���[�h�Ǘ�
	friend ISingleton<GameControl>;
	GameControl();
	~GameControl();
	ModeBase* m_pNowMode;

	bool ChangeMode(bool& Ans, EGameModeStatus pDest);
public:
	bool MainLoopProcess(bool& Ans);
};