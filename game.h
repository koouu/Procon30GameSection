#pragma once
#include "singleton.h"
class Game : public ISingleton<Game> {
	//�Q�[���̃��[�v
	friend ISingleton<Game>;
	Game() {};
	~Game() {};
public:
	bool startGameLoop();
};

