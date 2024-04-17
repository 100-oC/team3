//ウィンドウを表示するプログラム（ひな形）

#include "DxLib.h"	//DXライブラリのインクルード
#include "MovePlayer/MovePlayer.h"
#include "Input/Input.h"

// define
#define	SCREEN_SIZE_X	1280	// X方向の画面サイズを指定
#define	SCREEN_SIZE_Y	720		// Y方向の画面サイズを指定

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



	// プレイヤー情報
	struct Player {
		VECTOR pos = { 0.0f,0.0f };		// 座標
		VECTOR speed = { 1.0f ,1.0f };	// 移動速度
		int hndl;						// 画像ハンドル
	};
	Player player;

	MovePlayerInit();

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



		// プレイヤー処理
		if (CheckHitKey(KEY_INPUT_D) != 0 || CheckHitKey(KEY_INPUT_RIGHT) != 0)	// 右移動
			player.pos.x += player.speed.x;
		if (CheckHitKey(KEY_INPUT_A) != 0 || CheckHitKey(KEY_INPUT_LEFT) != 0)	// 左
			player.pos.x -= player.speed.x;
		if (CheckHitKey(KEY_INPUT_W) != 0 || CheckHitKey(KEY_INPUT_UP) != 0)	// 上
			player.pos.y -= player.speed.y;
		if (CheckHitKey(KEY_INPUT_S) != 0 || CheckHitKey(KEY_INPUT_DOWN) != 0)	// 下
			player.pos.y += player.speed.y;

		// プレイヤー描画(仮)
		DrawBox(player.pos.x, player.pos.y,
			player.pos.x + 40.0f, player.pos.y + 40.0f, GetColor(0, 255, 0), true);

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

