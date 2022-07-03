
#include "keyexport.h"
CKeyExport_S::CKeyExport_S() {
	for (int i = 0; i < 256; i++)
		m_NowKeyState[i] = 0;
}
void CKeyExport_S::KeyStateUpdate(char* pInput) {
	// [prm]p1;�L�[���͏�񂪓������ϐ��̃|�C���^(m1�Ŏw�肵���T�C�Y�̔z��ł��邱��)
	// [act]CKeyInput_S����̃A�N�Z�X��p�Bm2���X�V����B
	for (int i = 0; i < GetInputArrayMax_C; i++)
		if (pInput[i]) m_NowKeyState[i]++;
		else m_NowKeyState[i] = 0;
}
bool CKeyExport_S::ExportKeyState(int KeyHandle, int LessFrame, int MaxFrame) const {
	// [prm]p2;�����L�[�t���[����(����ȏ�Ȃ�true)
	// [act]�w��L�[��p2�t���[���ȏ㉟����Ă��邩�Ԃ�
	//		p1���ُ�l( 0�`m1-1 �ȊO)�Ȃ�false��Ԃ��B
	if (KeyHandle < 0 || KeyHandle >= GetInputArrayMax_C) return false;
	bool Ans = (m_NowKeyState[KeyHandle] >= LessFrame);
	Ans &= (m_NowKeyState[KeyHandle] <= MaxFrame);
	return Ans;
}
int CKeyExport_S::ExportKeyStateFrame(int KeyHandle) const {
	// [act]�w��̃L�[���A���ŉ�����Ă���t���[������Ԃ��B
	//		p1���ُ�l�Ȃ�-1��Ԃ��B
	if (KeyHandle < 0 || KeyHandle >= GetInputArrayMax_C) return -1;
	return m_NowKeyState[KeyHandle];
}