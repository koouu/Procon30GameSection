#include "CompetitionMode.h"
#include "DxLib.h"
#include "keyexport.h"
#include "DrawManager.h"
#include "Curl.h"
#include "AInside.h"

CompetitionMode::CompetitionMode(int turn) {
	//database.limit_turn = turn;
	competition_status = 0;

	Curl::recieveBeforeMatch();
	
	teamID = json.readBefore();
	//Algorithm* ains=new AInside(1);
	int a;
	a = 10 * 10;
	s = "move";
	madeDataBase = false;
	algorithmselect = new AlgorithmSelect(teamID);
	select_agent = 0;
	algorithmName = algorithmselect->getAlgorithm();
	//teamID = 1;
}

EGameModeStatus CompetitionMode::Process()
{
	CKeyExport_S& keyManager = CKeyExport_S::GetInstance();
	
	if (keyManager.ExportKeyState(KEY_INPUT_RETURN) > 0) {
		
		competition_status++;
		if (competition_status > eSendjson )competition_status = eWaitInput;
	}
	switch (competition_status) {

	case eBeforeGame:
		
		
		competition_status++;
		
		
		break;//;
	//case :
	case eWaitInput://‚±‚±‚É–ß‚é
		select_agent = 0;
		algorithmName = algorithmselect->getAlgorithm();
		break;
	
	case eOperateAlgorithm:
		
		Curl::recieveMatchState();
		
		madeDataBase = true;
		json.read();
		competition_status++;
		
		algorithmselect->operateAlgorithm(); 
		actions = algorithmselect->getAction();
		json.write(actions);
		
		Curl::sendAction();//‚Æ‚è‚ÜæÃ—~‘—‚Á‚Æ‚­
		
		competition_status= ePlayerInput;
		break;
	case ePlayerInput:
		setByPlayer();
		break;
	case eSendjson:
		checkRemove();
		json.write(actions);
		
		Curl::sendAction();
		
		competition_status = eWaitInput;
	}
	
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_Z) > 0)
	return eSelectMode;
	return eContinue;
}

bool CompetitionMode::Draw()
{
	DrawManager drawmanager;
	drawmanager.drawCompetition((ECompetitionStatus)competition_status);
	if (madeDataBase) {
		drawmanager.drawTile();
		drawmanager.drawFrame();
		drawmanager.drawPoints();
		drawmanager.drawAgent();
		drawmanager.drawLine2(teamID, actions, select_agent);
		drawmanager.drawTime();



		switch (algorithmName) {
		case eDonyoku1:drawmanager.drawState("1ŽèææÃ—~"); break;
		case eDonyoku2:drawmanager.drawState("2ŽèææÃ—~"); break;
		case eDonyoku3:drawmanager.drawState("3ŽèææÃ—~"); break;
		case eDonyoku4:drawmanager.drawState("4ŽèææÃ—~"); break;
		case eDonyoku5:drawmanager.drawState("5ŽèææÃ—~"); break;
		case eGotoOutside:drawmanager.drawState("ŠO‘¤‚Ögo"); break;
		case eGotoInside:drawmanager.drawState("“à‘¤‚Ögo"); break;
		}
	}
	
	
	return true;
}



Config CompetitionMode::getConfig()
{
	return Config();
}

void CompetitionMode::setByPlayer()
{
	CKeyExport_S& keyManager = CKeyExport_S::GetInstance();
	if (keyManager.ExportKeyState(KEY_INPUT_1) > 0) {
		select_agent = 1;
		s = "move";
	}
	if (keyManager.ExportKeyState(KEY_INPUT_2) > 0) {
		select_agent = 2;
		s = "move";
	}
	if (keyManager.ExportKeyState(KEY_INPUT_3) > 0) {
		select_agent = 3;
		s = "move";
	}
	if (keyManager.ExportKeyState(KEY_INPUT_4) > 0) {
		select_agent = 4;
		s = "move";
		
	}
	if (keyManager.ExportKeyState(KEY_INPUT_5) > 0) {
		select_agent = 5;
		s = "move";
	}
	if (keyManager.ExportKeyState(KEY_INPUT_6) > 0) {
		select_agent = 6;
		s = "move";
	}
	if (keyManager.ExportKeyState(KEY_INPUT_7) > 0) {
		select_agent = 7;
		s = "move";
	}
	if (keyManager.ExportKeyState(KEY_INPUT_8) > 0) {
		select_agent = 8;
		s = "move";
		
	}
	if (select_agent != 0 && select_agent <= actions.size()) {
		if (keyManager.ExportKeyState(KEY_INPUT_M) > 0) {
			s = "move";
		}
		if (keyManager.ExportKeyState(KEY_INPUT_R) > 0) {
			s = "remove";
		}
		actions[select_agent - 1].type = s;
		if (keyManager.ExportKeyState(KEY_INPUT_UP)>0) {
			actions[select_agent-1].direction.y--;
			if (actions[select_agent - 1].direction.y < -1)actions[select_agent - 1].direction.y = -1;
		}
		if (keyManager.ExportKeyState(KEY_INPUT_DOWN)>0) {
			actions[select_agent - 1].direction.y++;
			if (actions[select_agent - 1].direction.y > 1)actions[select_agent - 1].direction.y = 1;
		}
		if (keyManager.ExportKeyState(KEY_INPUT_RIGHT)>0) {
			actions[select_agent - 1].direction.x++;
			if (actions[select_agent - 1].direction.x > 1)actions[select_agent - 1].direction.x = 1;
		}
		if (keyManager.ExportKeyState(KEY_INPUT_LEFT)>0) {
			actions[select_agent - 1].direction.x--;
			if (actions[select_agent - 1].direction.x < -1)actions[select_agent - 1].direction.x = -1;
		}
		
	}

	if (keyManager.ExportKeyState(KEY_INPUT_ESCAPE) > 0) {
		actions = algorithmselect->getAction();
	}
}

void CompetitionMode::checkRemove()
{
	int teamID_01;
	int rivalID;
	for (int i = 0; i < 2; i++) {
		if (teamID == database.teams[i].teamID)teamID_01 = i;
	}
	for (int i = 0; i < actions.size(); i++) {
		if (database.tiled[database.teams[teamID_01].agents[i].y + actions[i].direction.y][database.teams[teamID_01].agents[i].x + actions[i].direction.x] == database.teams[!teamID_01].teamID) {
			actions[i].type = "remove";
		}
	}
}

