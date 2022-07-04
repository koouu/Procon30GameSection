#include "DrawManager.h"
#include <time.h>
#define def 55

DrawManager::DrawManager()
{
	
}

void DrawManager::drawTile()
{
	Vector2 scr; int depth;
	GetScreenState(&scr.x, &scr.y, &depth);

	int length = def * ((double)scr.x / 1920.0);

	for (int i = 0; i < database.height; i++) {
		for (int j = 0; j < database.width; j++) {
			if (database.tiled[i][j] == database.teams[0].teamID) {
				DrawBox(length * j, length * i, length * (j + 1), length * (i + 1), red, TRUE);
			}
			if (database.tiled[i][j] == database.teams[1].teamID) {
				DrawBox(length * j, length * i, length * (j + 1), length * (i + 1), blue, TRUE);
			}
		}
	}
}

void DrawManager::drawNowLine(int count, Vector2 direction) {
	Vector2 scr; int depth;
	GetScreenState(&scr.x, &scr.y, &depth);
	int length = def * ((double)scr.x / 1920.0);
	//if (player) {
		DrawLine((database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].x + direction.x + 0.5) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].y + direction.y + 0.5) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].x + 0.5) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].y + 0.5) * length, 0xFF00FF);
		DrawLine((database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].x + direction.x + 0.49) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].y + direction.y + 0.5) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].x + 0.49) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].y + 0.5) * length, 0xFF00FF);
		DrawLine((database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].x + direction.x + 0.51) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].y + direction.y + 0.5) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].x + 0.51) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].y + 0.5) * length, 0xFF00FF);
		DrawLine((database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].x + direction.x + 0.5) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].y + direction.y + 0.49) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].x + 0.5) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].y + 0.49) * length, 0xFF00FF);
		DrawLine((database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].x + direction.x + 0.5) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].y + direction.y + 0.51) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].x + 0.5) * length,
			(database.teams[count / database.teams[0].agents.size()].agents[count % database.teams[0].agents.size()].y + 0.51) * length, 0xFF00FF);
	//}
	
}

void DrawManager::drawCompetition(ECompetitionStatus status)
{
	SetFontSize(30);
	switch (status) {
	case eBeforeGame:DrawFormatString(800, 580, white, "�J�n�O"); break;
	case eWaitInput:DrawFormatString(800, 580, white, "�C���^�[�o��"); break;
	case eOperateAlgorithm:DrawFormatString(800, 580, white, "�×~"); break;
	case ePlayerInput:DrawFormatString(800, 580, white, "�v���C���[����"); break;
	case eSendjson:DrawFormatString(800, 580, white, "���M"); break;
	}
}

//�g�̐���
void DrawManager::drawFrame()
{
	Vector2 scr; int depth;
	GetScreenState(&scr.x, &scr.y, &depth);

	int length = def * ((double)scr.x / 1920.0);

	for (int i = 0; i < database.height; i++) {
		for (int j = 0; j < database.width; j++) {
			DrawBox(length * j, length * i, length * (j + 1), length * (i + 1), white, FALSE);
		}
	}
}

//�}�X���Ƃ̃|�C���g
void DrawManager::drawPoints()
{
	SetFontSize(22);
	SetFontThickness(1);
	Vector2 scr; int depth;
	GetScreenState(&scr.x, &scr.y, &depth);

	int length = def * ((double)scr.x / 1920.0);

	for (int i = 0; i < database.height; i++) {
		for (int j = 0; j < database.width; j++) {
			DrawFormatString((length * j) + 2, length * i, white, "%d", database.points[i][j]);
		}
	}



}
void DrawManager::drawAgent() {
	SetFontSize(18);
	SetFontThickness(2);

	Vector2 scr; int depth;
	GetScreenState(&scr.x, &scr.y, &depth);

	int length = def * ((double)scr.x / 1920.0);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < database.teams[0].agents.size(); j++) {
			DrawFormatString((length * database.teams[i].agents[j].x) + 2, length * database.teams[i].agents[j].y + 16,
				yellow, "%d", j+1);
		}
	}
}

void DrawManager::drawLine2(int teamID, vector<Action> moving_point,int select_agent) {
	Vector2 scr; int depth;
	GetScreenState(&scr.x, &scr.y, &depth);
	int length = def * ((double)scr.x / 1920.0);
	int i = 0;
	int teamID_01;
	int rivalID;
	for (int i = 0; i < 2; i++) {
		if (teamID == database.teams[i].teamID)teamID_01 = i;
	}

	if (!(database.turn >= database.limit_turn))
		for (auto p : moving_point) {
			DrawLine((database.teams[teamID_01].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.5) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.5) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].x + 0.5) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].y + 0.5) * length, select_agent-1!=i? green: 0xcc00cc);
			DrawLine((database.teams[teamID_01].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.51) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.5) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].x + 0.51) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].y + 0.5) * length, select_agent - 1 != i ? green : 0xcc00cc);
			DrawLine((database.teams[teamID_01].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.49) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.5) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].x + 0.49) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].y + 0.5) * length, select_agent - 1 != i ? green : 0xcc00cc);
			DrawLine((database.teams[teamID_01].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.5) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.51) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].x + 0.5) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].y + 0.51) * length, select_agent - 1 != i ? green : 0xcc00cc);
			DrawLine((database.teams[teamID_01].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.5) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.49) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].x + 0.5) * length,
				(database.teams[teamID_01].agents[i % database.teams[0].agents.size()].y + 0.49) * length, select_agent - 1 != i ? green : 0xcc00cc);
			


			/*DrawLine((database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.5) * length,
				(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.5) * length,
				(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + p.direction.x ) * length,
				(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + 0.5) * length, green);


			DrawLine((database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.5) * length,
				(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.5) * length,
				(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x +   0.5) * length,
				(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + p.direction.y) * length, green);

			*/i++;
		}
}

void DrawManager::drawTime()
{
	time(NULL);
	SetFontSize(30);
	DrawFormatString(800, 250, 0x00cccc, "���͎���");
	DrawFormatString(860, 280, 0x00cccc, "%d�b", database.turnMillis/1000);
	DrawFormatString(1000, 250, 0xcc00cc, "�C���^�[�o��");
	DrawFormatString(1135, 280, 0xcc00cc, "%d�b", database.intervalMillis/1000);
	DrawFormatString(800, 320, (time(NULL) - database.startedAtUnixTime) % ((database.intervalMillis + database.turnMillis)/1000)>= database.turnMillis/1000? 0xcc00cc:0x00cccc,
		"���ݎ��� : %d�b", (time(NULL)-database.startedAtUnixTime)%((database.intervalMillis+database.turnMillis) / 1000));
}



void DrawManager::drawTurn()
{
}

void DrawManager::drawLine(vector<Action> moving_point)
{
	
	Vector2 scr; int depth;
	GetScreenState(&scr.x, &scr.y, &depth);
	int length = def * ((double)scr.x / 1920.0);
	int i = 0;
	if(!(database.turn>=database.limit_turn))
	for (auto p : moving_point) {
		DrawLine((database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + p.direction.x+0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y+ p.direction.y + 0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + 0.5)* length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + 0.5)* length, green);
		DrawLine((database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.49) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + 0.49) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + 0.5) * length, green);
		DrawLine((database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.51) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + 0.51) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + 0.5) * length, green);
		DrawLine((database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.49) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + 0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + 0.49) * length, green);
		DrawLine((database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.51) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + 0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + 0.51) * length, green);



		/*DrawLine((database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + p.direction.x ) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + 0.5) * length, green);
		

		DrawLine((database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x + p.direction.x + 0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + p.direction.y + 0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].x +   0.5) * length,
			(database.teams[i / database.teams[0].agents.size()].agents[i % database.teams[0].agents.size()].y + p.direction.y) * length, green);
		
		*/i++;
	}
	//ScreenFlip();

}

void DrawManager::drawState(string argolithmName)
{
	SetFontSize(30);
	DrawFormatString(800, 30, red, "Team_ID:%d", database.teams[0].teamID);
	DrawFormatString(800, 60, red, "�^�C�� :%d", database.teams[0].tilePoint);
	DrawFormatString(800, 90, red, "�̈�   :%d", database.teams[0].areaPoint);
	DrawFormatString(800, 120, red, "���v   :%d", (database.teams[0].tilePoint) + (database.teams[0].areaPoint));

	DrawFormatString(1000, 30, blue, "Team_ID:%d", database.teams[1].teamID);
	DrawFormatString(1000, 60, blue, "�^�C�� :%d", database.teams[1].tilePoint);
	DrawFormatString(1000, 90, blue, "�̈�   :%d", database.teams[1].areaPoint);
	DrawFormatString(1000, 120, blue, "���v   :%d", (database.teams[1].tilePoint) + (database.teams[1].areaPoint));

	
	if (database.turn >= database.limit_turn) {
		DrawFormatString(800, 530, yellow, "�o�߃^�[��: %d / %d", database.limit_turn, database.limit_turn);
	}
	else {
		DrawFormatString(800, 530, white, "�o�߃^�[��: %d / %d", database.turn + 1, database.limit_turn);
	}

}

void DrawManager::drawOperatingAgent(int teamID, int inputnum,bool player)
{
	int a = database.teams[1].agents[database.teams[1].agents.size() - 1].agentID;
	if (teamID == database.teams[1].teamID && inputnum > database.teams[1].agents.size()*2) {
		DrawFormatString(800, 300, red, "Enter�œ��͊���");
		DrawFormatString(800, 330, red, "B�L�[�œ��̓��Z�b�g");
	}else if(!player){
		DrawFormatString(800, 300, teamID == database.teams[1].teamID? blue:red, "AI����");
	}
	else {
		DrawFormatString(800, 300, teamID == database.teams[1].teamID ? blue : red, "����G�[�W�F���g");
		DrawFormatString(800, 330, teamID == database.teams[1].teamID ? blue : red, "�`�[��%d : �G�[�W�F���g%d", teamID, (inputnum-1)% database.teams[1].agents.size()+1);
	}
	
}


void DrawManager::drawResult(int winner)
{
	if (winner == -1) {
		DrawFormatString(800, 300,green, "��������");
	}
	else {
		DrawFormatString(800, 300, winner == database.teams[1].teamID ? blue : red, "�`�[��%d�̏���", winner);
	}
	
}