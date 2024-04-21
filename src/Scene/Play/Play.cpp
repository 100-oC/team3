#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"
#include "../../Player/Player.h"
#include "../../Map/Map.h"
#include"../../TimeLimit/TimeLimit.h"

Player player;
Map map;
TimeLimit timeLimit;

//������
void Play::Init()
{
	// �v���C���[������
	player.Init();
	map.Init(0);
	timeLimit.Init();

	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�ʏ폈��
void Play::Step()
{
	// �v���C���[����
	player.Step();
	map.Step();
	timeLimit.Step();
}

//�`�揈��
void Play::Draw()
{
	map.Draw(1);
	timeLimit.Draw();
	// �v���C���[�`��
	player.Draw();
}

//�I������
void Play::Fin()
{
	player.Fin();
	map.Fin();
	timeLimit.Fin();

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
