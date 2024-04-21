#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"
#include "../../Player/Player.h"
#include "../../Map/Map.h"

Player player;
Map map;

//初期化
void Play::Init()
{
	// プレイヤー初期化
	player.Init();
	map.Init(0);


	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//通常処理
void Play::Step()
{
	// プレイヤー処理
	player.Step();
	map.Step();

	//描画==================

	map.Draw(1);
	// プレイヤー描画
	player.Draw();


}

//描画処理
void Play::Draw()
{
	map.Fin();
}

//終了処理
void Play::Fin()
{

	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
