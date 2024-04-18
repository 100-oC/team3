#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"

//‰Šú‰»
void Play::Init()
{

	//’Êíˆ—‚ÖˆÚ“®
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//’Êíˆ—
void Play::Step()
{


}

//•`‰æˆ—
void Play::Draw()
{

}

//I—¹ˆ—
void Play::Fin()
{

	//Ÿ‚ÌƒV[ƒ“‚ÉˆÚ“®
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
