#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"
#include "../../Player/Player.h"
#include "../../Map/Map.h"
#include"../../TimeLimit/TimeLimit.h"

Player player;
Map mapData;
TimeLimit timeLimit;

//初期化
void Play::Init()
{
	// プレイヤー初期化
	player.Init();
	mapData.Init(0);
	timeLimit.Init();

	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//通常処理
void Play::Step()
{
	if (timeLimit.GetStart())
	{
		// プレイヤー処理
		player.Step();
	}
	mapData.Step();
	timeLimit.Step();
}

//描画処理
void Play::Draw()
{
	mapData.Draw(1);
	timeLimit.Draw();
	// プレイヤー描画
	player.Draw();

	timeLimit.Draw(1);
}

//終了処理
void Play::Fin()
{
	player.Fin();
	mapData.Fin();
	timeLimit.Fin();

	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
