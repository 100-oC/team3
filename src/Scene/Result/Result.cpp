#include"DxLib.h"
#include"Result.h"
#include"../Scene.h"

int winner;

//������
void Result::Init()
{
	for (int i = 0; i < RESULT_MAX_NUM; i++)
	{
		hndl[i] = LoadGraph(RESULT_IMAGE_PATH[i]);
	}

	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//�ʏ폈��
void Result::Step()
{
	//�X�y�[�X����������
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;
	}

}

//�`�揈��
void Result::Draw()
{
	DrawGraph(0, 0, hndl[RESULT_GROUND], true);
	DrawGraph(0, 0, hndl[RESULT_WINNER1P + winner], true);
}

//�I������
void Result::Fin()
{

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
