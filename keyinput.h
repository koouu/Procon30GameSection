#pragma once
#include "singleton.h"
class CKeyInput_S : public ISingleton<CKeyInput_S> {
	// �L�[���͊Ď��A���ʂ�CKeyExport_S�N���X�֓`�d
	friend ISingleton<CKeyInput_S>;
	CKeyInput_S() {};
	~CKeyInput_S() {};
public:
	bool GetKeyState();
};

