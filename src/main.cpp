//ウィンドウを表示するプログラム（ひな形）

#include "DxLib.h"	//DXライブラリのインクルード
#include "Player/Player.h"
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


	///*
	// プレイヤー情報
	struct Player {
		VECTOR pos = { 0.0f,0.0f };		// 座標
		VECTOR statepos = { 0.0f,0.0f };// 初期地点(リスポーン地点座標)
		VECTOR speed = { 0.0f ,0.0f };	// 移動速度
		int hndl;						// 画像ハンドル
		bool living_flg = true;			// 生存しているかフラグ(trueで生存)
	};
	Player player[2];

	// 初期地（仮）
	player[0].statepos = { 0.0f,0.0f };
	player[1].statepos = { 1240.0f,680.0f };

	player[0].pos = player[0].statepos;
	player[1].pos = player[1].statepos;
	//*/

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



		// 【プレイヤー処理】
		// 1プレイヤー操作
		if (CheckHitKey(KEY_INPUT_D) != 0)	// 右移動
			player[0].speed.x += 0.5f;
		if (CheckHitKey(KEY_INPUT_A) != 0)	// 左
			player[0].speed.x -= 0.5f;
		if (CheckHitKey(KEY_INPUT_W) != 0)	// 上
			player[0].speed.y -= 0.5f;
		if (CheckHitKey(KEY_INPUT_S) != 0)	// 下
			player[0].speed.y += 0.5f;

		// 2プレイヤー操作
		if (CheckHitKey(KEY_INPUT_RIGHT) != 0)	// 右移動
			player[1].speed.x += 0.5f;
		if (CheckHitKey(KEY_INPUT_LEFT) != 0)	// 左
			player[1].speed.x -= 0.5f;
		if (CheckHitKey(KEY_INPUT_UP) != 0)		// 上
			player[1].speed.y -= 0.5f;
		if (CheckHitKey(KEY_INPUT_DOWN) != 0)	// 下
			player[1].speed.y += 0.5f;

		// プレイヤーの座標更新
		for (int i = 0; i < 2; i++) {
			player[i].pos.x += player[i].speed.x;
			player[i].pos.y += player[i].speed.y;
		}

		// プレイヤー加速度 最大値,最小値の設定
		for (int i = 0; i < 2; i++) {
			if (player[i].speed.x > 5.0f) {
				player[i].speed.x = 5.0f;
			}
			else if (player[i].speed.x < -5.0f) {
				player[i].speed.x = -5.0f;
			}

			if (player[i].speed.y > 5.0f) {
				player[i].speed.y = 5.0f;
			}
			else if (player[i].speed.y < -5.0f) {
				player[i].speed.y = -5.0f;
			}
		}

		// プレイヤー加速度減少
		for (int i = 0; i < 2; i++) {
			player[i].speed.x -= player[i].speed.x / 32;
			player[i].speed.y -= player[i].speed.y / 32;
		}

		// プレイヤーがキルされたとき
		for (int i = 0; i < 2; i++) {
			if (player[i].living_flg != true) {
				player[i].pos = player[i].statepos;
				player[i].living_flg = true;
			}
		}


		// プレイヤー描画(仮)
		if (player[0].living_flg == true) {
			DrawBox(player[0].pos.x, player[0].pos.y,
				player[0].pos.x + 40.0f, player[0].pos.y + 40.0f, GetColor(0, 255, 0), true);
		}
		if (player[1].living_flg == true) {
			DrawBox(player[1].pos.x, player[1].pos.y,
				player[1].pos.x + 40.0f, player[1].pos.y + 40.0f, GetColor(155, 0, 255), true);
		}

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

