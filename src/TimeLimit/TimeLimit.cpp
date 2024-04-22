#include"DxLib.h"
#include"TimeLimit.h"
#include"../FrameRate/FrameRate.h"
#include"../Scene/Scene.h"

//int currentTime;	//現在の時間

//初期化
void TimeLimit::Init()
{
	//画像読み込み
	LoadDivGraph(TIME_IMAGE_PATH,10,5,2,44,64,imageHandle);

	//制限時間設定
	currentTime = 3;
	timeCount = 0.0;

	start = false;
}

//通常処理
void TimeLimit::Step()
{
	//時間をカウント
	timeCount += 1.0f / FRAME_RATE;

	//カウントが１秒になったら
	if (timeCount >= 1)
	{
		//現在の時間を減少
		currentTime--;
		//カウントを戻す
		timeCount = 0.0f;

		if (currentTime <= 10&&start)
		{
			Sound::Se::Play(SE_TIME);
		}
	}

	//制限時間が0になったら
	if (currentTime <= 0)
	{
		if (!start)
		{
			currentTime = TIME_LIMIT;
			start = true;
			Sound::Se::Play(SE_START);
		}
		else
		{
			Sound::Se::Play(SE_FINISH);
			g_CurrentSceneID = SCENE_ID_FIN_PLAY;
		}
	}
}

//描画
void TimeLimit::Draw(int type)
{
	if (type == 0&&start)
	{
		//十の位
		int imageNum = currentTime / 10;	//画像用数字
		DrawGraph(SCREEN_SIZE_X / 2 - 44, 10, imageHandle[imageNum], true);

		//一の位
		imageNum = currentTime % 10;	//画像用数字
		DrawGraph(SCREEN_SIZE_X / 2, 10, imageHandle[imageNum], true);
	}
	else if (type == 1&&!start)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 0.3f);
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(0, 0, 0), true);
		//表示を元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//一の位
		int imageNum = currentTime % 10;	//画像用数字
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 10.0f, 0.0f, imageHandle[imageNum], true);
	}
	
}

//終了処理
void TimeLimit::Fin()
{
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
