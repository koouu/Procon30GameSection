#include "keyinput.h"
#include "DxLib.h"
#include "keyexport.h"

bool CKeyInput_S::GetKeyState() {
	// [act]�L�[�X�e�[�g�擾(DxLib::GetHitKeyStateAll)
	//		���ʂ�CKeyExport_S�N���X�֓`�d(ExIns.KeyStateUpdate)
	// [ret]�֐�������������
	// DxLib�̃L�[�{�[�h�擾���̔z��}�W�b�N�i���o�[
	const int GetInputArrayMax_C = 256;
	char KeyState[GetInputArrayMax_C];
	if (DxLib::GetHitKeyStateAll(KeyState)) return false;
	CKeyExport_S& ExIns = CKeyExport_S::GetInstance();
	ExIns.KeyStateUpdate(KeyState);
	return true;
}