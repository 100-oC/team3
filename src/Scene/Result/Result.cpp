#include"DxLib.h"
#include"Result.h"
#include"../Scene.h"

int winner;

//初期化
void Result::Init()
{
	for (int i = 0; i < RESULT_MAX_NUM; i++)
	{
		hndl[i] = LoadGraph(RESULT_IMAGE_PATH[i]);
	}

	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//通常処理
void Result::Step()
{
	//スペースを押したら
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;
	}

}

//描画処理
void Result::Draw()
{
	DrawGraph(0, 0, hndl[RESULT_GROUND], true);
	DrawGraph(0, 0, hndl[RESULT_WINNER1P + winner], true);
}

//終了処理
void Result::Fin()
{

	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
