#include "DxLib.h"
#include"game.h"
#include <new>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//DxLib::ChangeWindowMode(1);					// �E�B���h�E���[�h��
	//SetWindowSizeChangeEnableFlag(true);
    SetGraphMode(1260, 760, 32);
	//SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_MAXIMUM);//���j�^�[�̉𑜓x���ő�ɂ��āASetGraphMode �Ŏw�肵���𑜓x�̉�ʂ��g�債�ĕ\��
	//SetFullScreenScalingMode(DX_FSSCALINGMODE_NEAREST);//�ŋߓ_���[�h(�s�N�Z�����l�p����������\�������)
	//SetBackgroundColor(0, 0, 0);

	DxLib::SetAlwaysRunFlag(TRUE);				// �A�N�e�B�u����Ȃ��Ƃ����������s��
	DxLib::SetOutApplicationLogValidFlag(FALSE);// ���O���t�@�C���ɏo�͂��Ȃ�
	if (DxLib::DxLib_Init()) return false;		// DxLib����������
	DxLib::SetDrawScreen(DX_SCREEN_BACK);		// ����ʏ�������

	bool Result = true;
	try {
		Game& LoopIns = Game::GetInstance();
		Result = LoopIns.startGameLoop();
	}
	catch (std::bad_alloc) {
		DxLib::ErrorLogAdd("�������m�ێ��ɖ�肪�������܂����B\n");
		Result = false;
	}
	if (!Result)
		DxLib::ErrorLogAdd("�\�t�g�������I�����܂����B\n");
	DxLib_End();

		// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}