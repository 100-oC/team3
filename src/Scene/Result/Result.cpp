#include"DxLib.h"
#include"Result.h"
#include"../Scene.h"

//‰Šú‰»
void Result::Init()
{

	//’Êíˆ—‚ÖˆÚ“®
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//’Êíˆ—
void Result::Step()
{


}

//•`‰æˆ—
void Result::Draw()
{

}

//I—¹ˆ—
void Result::Fin()
{

	//Ÿ‚ÌƒV[ƒ“‚ÉˆÚ“®
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
