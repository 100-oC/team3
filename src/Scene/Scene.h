#pragma once
#include"../FrameRate/FrameRate.h"
#include"../Input/Input.h"

// define
#define	SCREEN_SIZE_X	1280	// X方向の画面サイズを指定
#define	SCREEN_SIZE_Y	720		// Y方向の画面サイズを指定

enum SCENE_ID
{
	//タイトル関連
	SCENE_ID_INIT_TITLE = 0,
	SCENE_ID_LOOP_TITLE,
	SCENE_ID_FIN_TITLE,

	//プレイ関連
	SCENE_ID_INIT_PLAY,
	SCENE_ID_LOOP_PLAY,
	SCENE_ID_FIN_PLAY,

	//ゲームクリア関連
	SCENE_ID_INIT_RESULT,
	SCENE_ID_LOOP_RESULT,
	SCENE_ID_FIN_RESULT,

};

extern SCENE_ID g_CurrentSceneID;

//シーン分け
void Scene();