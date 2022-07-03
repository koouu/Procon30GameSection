#pragma once
#include "singleton.h"
class Game : public ISingleton<Game> {
	//ƒQ[ƒ€‚Ìƒ‹[ƒv
	friend ISingleton<Game>;
	Game() {};
	~Game() {};
public:
	bool startGameLoop();
};

