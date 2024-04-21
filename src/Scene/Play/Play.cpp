#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"
#include "../../Player/Player.h"
#include "../../Map/Map.h"
#include"../../TimeLimit/TimeLimit.h"

Player player;
Map map;
TimeLimit timeLimit;

//初期化
void Play::Init()
{
	// プレイヤー初期化
	player.Init();
	map.Init(0);
	timeLimit.Init();

	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//通常処理
void Play::Step()
{
	// プレイヤー処理
	player.Step();
	map.Step();
	timeLimit.Step();
}

//描画処理
void Play::Draw()
{
	map.Draw(1);
	timeLimit.Draw();
	// プレイヤー描画
	player.Draw();
}

//終了処理
void Play::Fin()
{
	player.Fin();
	map.Fin();
	timeLimit.Fin();

	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
