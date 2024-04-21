#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"

//初期化
void Title::Init()
{
	//初期化、画像の読み込み
	for (int i = 0; i < TITLE_MAX_NUM; i++)
	{
		// タイトル画像の読込
		hndl[i] = LoadGraph(TITLE_IMAGE_PATH[i]);
		x[i] = SCREEN_SIZE_X / 2;
		y[i] = SCREEN_SIZE_Y / 2;
		size[i] = 1.0f;
		fade[i] = 255;
	}

	//座標を中央に設定
	for (int i = TITLE_MEAT1; i < TITLE_START; i++)
	{
		size[i] = 0.0f;
	}

	x[TITLE_MEAT1] = 950;
	y[TITLE_MEAT1] = 320;

	x[TITLE_MEAT2] = 1050;
	y[TITLE_MEAT2] = 290;

	fade[TITLE_GROUND] = 0;
	fade[TITLE_START] = 0;

	lighting = false;
	progress = 0;
	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

enum TITLE_PROGRESS
{
	TITLE_GROUND_FADEIN,
	TITLE_MAKE_TITLE,
	TITLE_START_GAME,
};

//通常処理
void Title::Step()
{
	switch (progress)
	{
	case TITLE_GROUND_FADEIN:	//背景がfadeイン

		GroundFadeIn();

		break;

	case TITLE_MAKE_TITLE:	//画面作り

		MakeTitle();

		break;

	case TITLE_START_GAME:	//入力待ち

		StartGame();

		break;


	default:
		break;
	}

	//タイトル完成
	MakeFinish();
}

//描画処理
void Title::Draw()
{
	for (int i = 0; i < TITLE_MAX_NUM; i++)
	{
		//fadeで透明度変更
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[i]);
		DrawRotaGraph(x[i], y[i],size[i],0.0f, hndl[i], true);	//描画
		//表示を元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

//終了処理
void Title::Fin()
{

	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}

//=========================================================

	//背景のフェードイン
void Title::GroundFadeIn()
{
	//地面
	if (fade[TITLE_GROUND] < 255)
	{
		fade[TITLE_GROUND] += 10;
	}
	else
	{
		fade[TITLE_GROUND] = 255;
		progress++;
	}

}

//画面作り
void Title::MakeTitle()
{
	if (size[TITLE_TITLE] < 1.0f)
	{
		size[TITLE_TITLE] += 0.01f;
	}
	else
	{
		size[TITLE_TITLE] = 1.0f;
	}

	if (size[TITLE_TITLE] >= 1.0f && size[TITLE_MEAT1] < 1.0f)
	{
		size[TITLE_MEAT1] += 0.05f;
	}
	else if (size[TITLE_TITLE] >= 1.0f && size[TITLE_MEAT1] >= 1.0f)
	{
		size[TITLE_MEAT1] = 1.0f;
	}

	if (size[TITLE_MEAT1] >= 0.3f && size[TITLE_MEAT2] < 1.0f)
	{
		size[TITLE_MEAT2] += 0.05f;
	}
	else if (size[TITLE_MEAT1] >= 0.3f && size[TITLE_MEAT2] >= 1.0f)
	{
		size[TITLE_MEAT2] = 1.0f;
	}

	if (size[TITLE_MEAT2] >= 0.5f && size[TITLE_PLAYER] < 1.0f)
	{
		size[TITLE_PLAYER] += 0.03f;
	}
	else if (size[TITLE_MEAT2] >= 0.5f && size[TITLE_PLAYER] >= 1.0f)
	{
		size[TITLE_PLAYER] = 1.0f;
	}

	if (size[TITLE_PLAYER] >= 0.3f && size[TITLE_MANUSL] < 1.0f)
	{
		size[TITLE_MANUSL] += 0.1f;
	}
	else if (size[TITLE_PLAYER] >= 0.3f && size[TITLE_MANUSL] >= 1.0f)
	{
		size[TITLE_MANUSL] = 1.0f;
	}

	if (size[TITLE_PLAYER] == 1.0f && size[TITLE_MANUSL] == 1.0f)
	{
		progress++;
	}

}

//入力待ち
void Title::StartGame()
{
	//UIの点滅
//現れる
	if (lighting)
	{
		fade[TITLE_START] += 5;

		if (fade[TITLE_START] >= 255)
		{
			lighting = false;
		}
	}
	//消える
	else
	{
		fade[TITLE_START] -= 5;

		if (fade[TITLE_START] <= 0)
		{
			lighting = true;
		}
	}

	//スペースを押したら
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
	}

}

//タイトル完成
void Title::MakeFinish()
{
	//画面未完成時にスペースで完成
	if (progress != TITLE_START_GAME)
	{
		if (Input::Key::Push(KEY_INPUT_SPACE))
		{
			for (int i = 0; i < TITLE_START; i++)
			{
				x[i] = SCREEN_SIZE_X / 2;
				y[i] = SCREEN_SIZE_Y / 2;
				size[i] = 1.0f;
				fade[i] = 255;
			}

			x[TITLE_MEAT1] = 950;
			y[TITLE_MEAT1] = 320;

			x[TITLE_MEAT2] = 1050;
			y[TITLE_MEAT2] = 290;

			//入力待ちへ
			progress = TITLE_START_GAME;
		}
	}

}