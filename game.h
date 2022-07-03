#pragma once
#include "singleton.h"
class Game : public ISingleton<Game> {
	//ゲームのループ
	friend ISingleton<Game>;
	Game() {};
	~Game() {};
public:
	bool startGameLoop();
};

