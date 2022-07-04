#include "selectmode.h"
#include "keyexport.h"
#include<iostream>
#include"enums.h"
#include "gameconfigmanager.h"


SelectMode::SelectMode(Config config) {
	
	
	this->config = config;
	arrow = 1;
}

SelectMode::~SelectMode()
{
}



EGameModeStatus SelectMode::Process()
{
	CKeyExport_S& keyManager = CKeyExport_S::GetInstance();
	const short columnMax = 4;
	bool isConf = false;
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_T) > 0) {
		isConf = true;
		if (keyManager.ExportKeyState(KEY_INPUT_UP))   config.turnNum += 5;
		if (keyManager.ExportKeyState(KEY_INPUT_DOWN)) config.turnNum -= 5;
		if (config.turnNum > 30) config.turnNum = 10;
		if (config.turnNum < 10)  config.turnNum = 30;
		
	}
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_W) > 0) {
		isConf = true;
		if (keyManager.ExportKeyState(KEY_INPUT_UP))   ++config.fieldSize.x;
		if (keyManager.ExportKeyState(KEY_INPUT_DOWN)) --config.fieldSize.x;
		if (config.fieldSize.x > 20) config.fieldSize.x = 10;
		if (config.fieldSize.x< 10)  config.fieldSize.x = 20;
	}
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_H) > 0) {
		isConf = true;
		if (keyManager.ExportKeyState(KEY_INPUT_UP))   ++config.fieldSize.y;
		if (keyManager.ExportKeyState(KEY_INPUT_DOWN)) --config.fieldSize.y;
		if (config.fieldSize.y > 20) config.fieldSize.y = 10;
		if (config.fieldSize.y < 10)  config.fieldSize.y = 20;
	}
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_A) > 0) {
		isConf = true;
		if (keyManager.ExportKeyState(KEY_INPUT_UP))   ++config.agentNum;
		if (keyManager.ExportKeyState(KEY_INPUT_DOWN)) --config.agentNum;
		if (config.agentNum > 8) config.agentNum = 2;
		if (config.agentNum < 2)  config.agentNum = 8;
	}
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_C) > 0) {
		isConf = true;
		if (keyManager.ExportKeyState(KEY_INPUT_UP))   config.randMode=true;
		if (keyManager.ExportKeyState(KEY_INPUT_DOWN)) config.randMode=false;
	}

	/*if (keyManager.ExportKeyStateFrame(KEY_INPUT_R) > 0) {
		isConf = true;
		if (keyManager.ExportKeyState(KEY_INPUT_UP))   config.repetitionNum += 1000;
		if (keyManager.ExportKeyState(KEY_INPUT_DOWN)) config.repetitionNum -= 1000;
		if (config.repetitionNum > 10001) config.repetitionNum = 1;
		if (config.repetitionNum< 1)  config.repetitionNum = 10001;

	}
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_J) > 0) {
		isConf = true;
		if (keyManager.ExportKeyState(KEY_INPUT_UP))   config.jsonMode = true;
		if (keyManager.ExportKeyState(KEY_INPUT_DOWN)) config.jsonMode = false;

	}*/

	if (!isConf) {
		if (keyManager.ExportKeyState(KEY_INPUT_UP))   --arrow;
		if (keyManager.ExportKeyState(KEY_INPUT_DOWN)) ++arrow;
		arrow = (columnMax + arrow) % columnMax;
	}
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_ESCAPE)) {
		if (keyManager.ExportKeyStateFrame(KEY_INPUT_Z))
			if (keyManager.ExportKeyStateFrame(KEY_INPUT_Q))
				return eEnd;
	}

	if (keyManager.ExportKeyState(KEY_INPUT_RETURN)) {
		switch (arrow) {
		case 0: return ePlayingGame;
		case 1: return ePlayWithAI;
		case 2: return eAIGame;
		case 3: return eEnd;
		case 4: return eShowingReplay;
		case 5: return eCompetition;
		default: return eErrEnd;
		}
	}
	return eContinue;
}

Config SelectMode::getConfig()
{
	return config;
}






bool SelectMode::Draw()
{
	SetFontSize(30);
	SetFontThickness(1);
	CKeyExport_S& keyManager = CKeyExport_S::GetInstance();
	DxLib::DrawString(0, 0, "第30回全国高専プログラミングコンテスト競技部門 シュミレータ", 0xFFFFFF);
	DxLib::DrawString(0, 40, "モードを選択してください:", 0x0000FF);
	DxLib::DrawString(30, 90, "有人プレイ開始", 0xFFFFFF);
	DxLib::DrawString(30, 120, "AI同士", 0xFFFFFF);
	DxLib::DrawString(30, 150, "AI同士で対戦", 0xFFFFFF);
	DxLib::DrawString(30, 180, "終了", 0xFFFFFF);
	//DxLib::DrawString(30, 210, "リプレイ閲覧（未完成）", 0xAA0000);
    //DxLib::DrawString(30, 240, "大会用", 0xAA0000);


	DxLib::DrawString(0, 90 + 30 * arrow, "→", 0xFFFF00);

	bool colorFlag = keyManager.ExportKeyStateFrame(KEY_INPUT_T) > 0;
	DxLib::DrawFormatString(0, 300, colorFlag ? 0xFFFF00 : 0xFFFFFF,
		"[T] Gane Turns[10, 30]: %3d",config.turnNum);
	colorFlag = keyManager.ExportKeyStateFrame(KEY_INPUT_W) > 0;
	DxLib::DrawFormatString(0, 330, colorFlag ? 0xFFFF00 : 0xFFFFFF,
		"[W] Field Width[10, 20] : %3d", config.fieldSize.x);
	colorFlag = keyManager.ExportKeyStateFrame(KEY_INPUT_H) > 0;
	DxLib::DrawFormatString(0, 360, colorFlag ? 0xFFFF00 : 0xFFFFFF,
		"[H] Field Height[10, 20]: %3d", config.fieldSize.y);
	colorFlag = keyManager.ExportKeyStateFrame(KEY_INPUT_A) > 0;
	DxLib::DrawFormatString(0, 390, colorFlag ? 0xFFFF00 : 0xFFFFFF,
		"[A] Agent Num[2, 8]: %3d", config.agentNum);
	colorFlag = keyManager.ExportKeyStateFrame(KEY_INPUT_C) > 0;
	DxLib::DrawFormatString(0, 420, colorFlag ? 0xFFFF00 : 0xFFFFFF,
		"[C] Config Random: %s", config.randMode ? "ON":"OFF");
	/*colorFlag = keyManager.ExportKeyStateFrame(KEY_INPUT_R) > 0;
	DxLib::DrawFormatString(0, 450, colorFlag ? 0xFFFF00 : 0xFFFFFF,
		"[R] Repetition[1, 10001]: %3d", config.repetitionNum);
	colorFlag = keyManager.ExportKeyStateFrame(KEY_INPUT_J) > 0;
	DxLib::DrawFormatString(0, 480, colorFlag ? 0xFFFF00 : 0xFFFFFF,
		"[J] Config json: %s", config.jsonMode ? "ON" : "OFF");*/
	

	return true;
}
