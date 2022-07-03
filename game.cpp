#include "DxLib.h"
#include "game.h"
#include "keyexport.h"
#include "selectmode.h"
#include "enums.h"
#include "GameControl.h"

bool Game::startGameLoop() {
	CKeyInput_S& KeyIn_Ins = CKeyInput_S::GetInstance();
	GameControl& GameIns = GameControl::GetInstance();
	CKeyExport_S& KeyOutIns = CKeyExport_S::GetInstance();
	bool Check = true, Ans = true;
	while (Check && !DxLib::ProcessMessage() && !DxLib::ClearDrawScreen()) {
		clsDx();
		Check = KeyIn_Ins.GetKeyState();
		Check &= GameIns.MainLoopProcess(Ans);
		ScreenFlip();
	}
	return Ans;
}