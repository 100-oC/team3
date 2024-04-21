#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"
#include "../../Player/Player.h"
#include "../../Map/Map.h"

Player player;
Map map;

//������
void Play::Init()
{
	// �v���C���[������
	player.Init();
	map.Init(0);


	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�ʏ폈��
void Play::Step()
{
	// �v���C���[����
	player.Step();
	map.Step();

	//�`��==================

	map.Draw(1);
	// �v���C���[�`��
	player.Draw();


}

//�`�揈��
void Play::Draw()
{
	map.Fin();
}

//�I������
void Play::Fin()
{

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
