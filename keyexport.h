#pragma once
#include "singleton.h"
#include "keyinput.h"
class CKeyExport_S : public ISingleton<CKeyExport_S> {
	// [act]�e�N���X�ւ̃L�[���͏�Ԃ��o��
	//		�V���O���g���ŊǗ�����Ă���(_S�̈Ӗ�)
	friend ISingleton<CKeyExport_S>;
	// CKeyInput_S��KeyStateUpdate�֐����g�p�����邽�߂�friend�錾
	friend CKeyInput_S;
	CKeyExport_S();
	~CKeyExport_S() {};
	void KeyStateUpdate(char* pInput);
	// DxLib�̃L�[�{�[�h�擾���̔z��}�W�b�N�i���o�[(m1)
	static const int GetInputArrayMax_C = 256;
	// �L�[���A���œ��͂���Ă���t���[��(m2)
	int m_NowKeyState[GetInputArrayMax_C];
public:
	bool ExportKeyState(int KeyHandle, int LessFrame = 1, int MaxFrame = 1) const;
	int ExportKeyStateFrame(int KeyHandle) const;
};