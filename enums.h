#pragma once

enum EGameModeStatus {
	eSelectMode, ePlayingGame, ePlayWithAI, eAIGame, eShowingReplay, eCompetition,eContinue, eEnd, eErrEnd
};

enum EGameMainStatus {
	eInputName, eAgentInput, eAgentMove, eShowResult, eReplayAnalyze, eChooseReplay, eShowReplay
};

enum EAlgorithmStatus {
	eDonyoku1,eDonyoku2,eDonyoku3,eDonyoku4, eDonyoku5, eDonyoku6,eGotoOutside,eGotoInside
};

enum ECompetitionStatus {
	eBeforeGame, eWaitInput,eOperateAlgorithm,ePlayerInput,eSendjson
};