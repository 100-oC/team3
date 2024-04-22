#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"
#include "../../Player/Player.h"
#include "../../Map/Map.h"
#include"../../TimeLimit/TimeLimit.h"

Player player;
Map mapData;
TimeLimit timeLimit;

//������
void Play::Init()
{
	// �v���C���[������
	player.Init();
	mapData.Init(0);
	timeLimit.Init();

	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�ʏ폈��
void Play::Step()
{
	if (timeLimit.GetStart())
	{
		// �v���C���[����
		player.Step();
	}
	mapData.Step();
	timeLimit.Step();
}

//�`�揈��
void Play::Draw()
{
	mapData.Draw(1);
	timeLimit.Draw();
	// �v���C���[�`��
	player.Draw();

	timeLimit.Draw(1);
}

//�I������
void Play::Fin()
{
	player.Fin();
	mapData.Fin();
	timeLimit.Fin();

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
