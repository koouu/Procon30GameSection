#include "DxLib.h"
#include"game.h"
#include <new>

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//DxLib::ChangeWindowMode(1);					// ウィンドウモードに
	//SetWindowSizeChangeEnableFlag(true);
    SetGraphMode(1260, 760, 32);
	//SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_MAXIMUM);//モニターの解像度を最大にして、SetGraphMode で指定した解像度の画面を拡大して表示
	//SetFullScreenScalingMode(DX_FSSCALINGMODE_NEAREST);//最近点モード(ピクセルが四角くくっきり表示される)
	//SetBackgroundColor(0, 0, 0);

	DxLib::SetAlwaysRunFlag(TRUE);				// アクティブじゃないときも処理を行う
	DxLib::SetOutApplicationLogValidFlag(FALSE);// ログをファイルに出力しない
	if (DxLib::DxLib_Init()) return false;		// DxLib初期化処理
	DxLib::SetDrawScreen(DX_SCREEN_BACK);		// 裏画面書き込み

	bool Result = true;
	try {
		Game& LoopIns = Game::GetInstance();
		Result = LoopIns.startGameLoop();
	}
	catch (std::bad_alloc) {
		DxLib::ErrorLogAdd("メモリ確保時に問題が発生しました。\n");
		Result = false;
	}
	if (!Result)
		DxLib::ErrorLogAdd("ソフトが強制終了しました。\n");
	DxLib_End();

		// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}