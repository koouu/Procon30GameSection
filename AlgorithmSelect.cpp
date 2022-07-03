#include "AlgorithmSelect.h"
#include "keyexport.h"
#include "Dxlib.h"
#include "AInside.h"
#include "Donyoku_min_max.h"

AlgorithmSelect::AlgorithmSelect(int teamID)
{
	algorithmName = eDonyoku4;
	algorithm=new Donyoku(teamID);
	this->teamID=teamID;
}

EAlgorithmStatus AlgorithmSelect::getAlgorithm()
{
	CKeyExport_S& keyManager = CKeyExport_S::GetInstance();
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_D) > 0)algorithm = new Donyoku(teamID);
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_W) > 0)algorithm = new Donyoku_Min_Max(teamID);

	if (keyManager.ExportKeyStateFrame(KEY_INPUT_1) > 0) { algorithmName = eDonyoku1;  }
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_2) > 0) { algorithmName = eDonyoku2;  }
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_3) > 0) { algorithmName = eDonyoku3;  }
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_4) > 0) { algorithmName = eDonyoku4; }
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_5) > 0) { algorithmName = eDonyoku5; }
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_I) > 0) { algorithmName = eGotoInside; }
	if (keyManager.ExportKeyStateFrame(KEY_INPUT_O) > 0) { algorithmName = eGotoOutside; }

	return algorithmName;
}

void AlgorithmSelect::operateAlgorithm() {
	algorithm = new Donyoku(teamID);
	switch (algorithmName) {
	case eDonyoku1:algorithm->execute(1); return; //algorithm->getActions();
	case eDonyoku2:algorithm->execute(2); return; //algorithm->getActions();
	case eDonyoku3:algorithm->execute(3); return; //algorithm->getActions();
	case eDonyoku4:algorithm->execute(4); return; //algorithm->getActions();
	case eDonyoku5:algorithm->execute(5); return;
	case eGotoOutside:return;
	case eGotoInside:algorithm = new AInside(teamID); algorithm->execute(4); return;
	}
};

std::vector<Action> AlgorithmSelect::getAction()
{
	//switch(algorithmName)
	
	return algorithm->getActions();
}
