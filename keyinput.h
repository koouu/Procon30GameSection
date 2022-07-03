#pragma once
#include "singleton.h"
class CKeyInput_S : public ISingleton<CKeyInput_S> {
	// キー入力監視、結果をCKeyExport_Sクラスへ伝播
	friend ISingleton<CKeyInput_S>;
	CKeyInput_S() {};
	~CKeyInput_S() {};
public:
	bool GetKeyState();
};

