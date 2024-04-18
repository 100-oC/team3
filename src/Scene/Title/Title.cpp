#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"

//‰Šú‰»
void Title::Init()
{

	//’Êíˆ—‚ÖˆÚ“®
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//’Êíˆ—
void Title::Step()
{

	
}

//•`‰æˆ—
void Title::Draw()
{

}

//I—¹ˆ—
void Title::Fin()
{

	//Ÿ‚ÌƒV[ƒ“‚ÉˆÚ“®
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
