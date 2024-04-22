#include"DxLib.h"
#include"Scene.h"
#include"Title/Title.h"
#include"Play/Play.h"
#include"Result/Result.h"

SCENE_ID g_CurrentSceneID = SCENE_ID_INIT_TITLE;

Title title;
Play play;
Result result;

void Scene()
{
	switch (g_CurrentSceneID)
	{
		//タイトルシーン初期化
	case SCENE_ID_INIT_TITLE:

		Sound::Init();
		title.Init();
		Sound::Bgm::Play(BGM_TITLE);

		break;

		//タイトルシーン通常処理
	case SCENE_ID_LOOP_TITLE:

		title.Step();
		title.Draw();


		break;

		//タイトルシーン終了処理
	case SCENE_ID_FIN_TITLE:

		title.Fin();
		Sound::Bgm::StopSound(BGM_TITLE);

		break;

//===========================================

		//プレイシーン初期化
	case SCENE_ID_INIT_PLAY:

		play.Init();
		Sound::Bgm::Play(BGM_PLAY);

		break;
		//プレイシーン通常処理
	case SCENE_ID_LOOP_PLAY:

		play.Step();
		play.Draw();

		break;
		//プレイシーン終了処理
	case SCENE_ID_FIN_PLAY:

		play.Fin();
		Sound::Bgm::StopSound(BGM_PLAY);

		break;

//===========================================

		//リザルトシーン初期化処理
	case SCENE_ID_INIT_RESULT:

		result.Init();
		Sound::Bgm::Play(BGM_RESULT);

		break;

		//リザルトシーン通常処理
	case SCENE_ID_LOOP_RESULT:

		result.Step();
		result.Draw();

		break;

		//リザルトシーン終了処理
	case SCENE_ID_FIN_RESULT:

		result.Fin();
		Sound::Bgm::StopSound(BGM_RESULT);

		break;
	}
}
