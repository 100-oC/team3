//ウィンドウを表示するプログラム（ひな形）

#include "DxLib.h"	//DXライブラリのインクルード

// define
#define	SCREEN_SIZE_X	640	// X方向の画面サイズを指定
#define	SCREEN_SIZE_Y	480	// Y方向の画面サイズを指定

// Win32アプリケーションは WinMain関数 から始まる
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//ウィンドウの名前を変える
	SetMainWindowText("ﾃｷﾄｰ");

	//ウィンドウの状態を設定する
	ChangeWindowMode(true);

	// 画面サイズを変更
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//DXライブラリの初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	//描画するスクリーンを設定する
	SetDrawScreen(DX_SCREEN_BACK);

	//-----------------------------------------
	//一番最初に１回だけやる処理をここに書く

	//-----------------------------------------

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			//エスケープキーが押されたら終了
			break;
		}

		//画面に表示されたものを初期化
		ClearDrawScreen();

		//-----------------------------------------
		//ここからゲームの本体を書くことになる
		//-----------------------------------------



		//-----------------------------------------
		//ループの終わりに
		//フリップ関数
		ScreenFlip();

	}

	//-----------------------------------------
	//最後に１回だけやる処理をここに書く


	//-----------------------------------------
	//DXライブラリの後処理
	DxLib_End();

	return 0;
}

