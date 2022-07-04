#include "GameControl.h"
#include "selectmode.h"
#include "playmode.h"
#include "readjson.h"
#include "CompetitionMode.h"
#include "keyexport.h"

GameControl::GameControl() {
	Config config;
	config.agentNum = 2;
	config.fieldSize = { 15,15 };
	config.turnNum = 15;
	config.repetitionNum = 1;
	config.randMode = false;
	config.jsonMode = false;
	m_pNowMode = new SelectMode(config);
}
bool GameControl::MainLoopProcess(bool& Ans) {
	EGameModeStatus Next = m_pNowMode->Process();
	m_pNowMode->Draw();

	if (Next != eContinue) {
		if (!ChangeMode(Ans, Next)) return false;
	}
	CKeyExport_S& keyManager = CKeyExport_S::GetInstance();
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_X) > 0) {
		return false;
	}

	return true;
}

bool GameControl::ChangeMode(bool& Ans, EGameModeStatus pDest) {
	Config config;
	config = m_pNowMode->getConfig();
	
	delete m_pNowMode;	m_pNowMode = nullptr;
	switch (pDest) {
	case eSelectMode:		m_pNowMode = new SelectMode(config); break;
	case ePlayingGame:		m_pNowMode = new PlayMode(2,config); break;
	case ePlayWithAI:		m_pNowMode = new PlayMode(1,config); break;
	case eAIGame:			m_pNowMode = new PlayMode(0,config); break;
	case eCompetition:      m_pNowMode = new CompetitionMode(config.turnNum); break;
	case eShowingReplay:	//m_pNowMode = new ShowingReplay; break;
	case eEnd:				Ans = true;  return false; break;
	default:				Ans = false; return false; break;
	}
	return true;
}

GameControl::~GameControl() {
	delete m_pNowMode;
}