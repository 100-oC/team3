#include"DxLib.h"
#include"TimeLimit.h"
#include"../FrameRate/FrameRate.h"
#include"../Scene/Scene.h"

//int currentTime;	//���݂̎���

//������
void TimeLimit::Init()
{
	//�摜�ǂݍ���
	LoadDivGraph(TIME_IMAGE_PATH,10,5,2,44,64,imageHandle);

	//�������Ԑݒ�
	currentTime = 3;
	timeCount = 0.0;

	start = false;
}

//�ʏ폈��
void TimeLimit::Step()
{
	//���Ԃ��J�E���g
	timeCount += 1.0f / FRAME_RATE;

	//�J�E���g���P�b�ɂȂ�����
	if (timeCount >= 1)
	{
		//���݂̎��Ԃ�����
		currentTime--;
		//�J�E���g��߂�
		timeCount = 0.0f;

		if (currentTime <= 10&&start)
		{
			Sound::Se::Play(SE_TIME);
		}
	}

	//�������Ԃ�0�ɂȂ�����
	if (currentTime <= 0)
	{
		if (!start)
		{
			currentTime = TIME_LIMIT;
			start = true;
			Sound::Se::Play(SE_START);
		}
		else
		{
			Sound::Se::Play(SE_FINISH);
			g_CurrentSceneID = SCENE_ID_FIN_PLAY;
		}
	}
}

//�`��
void TimeLimit::Draw(int type)
{
	if (type == 0&&start)
	{
		//�\�̈�
		int imageNum = currentTime / 10;	//�摜�p����
		DrawGraph(SCREEN_SIZE_X / 2 - 44, 10, imageHandle[imageNum], true);

		//��̈�
		imageNum = currentTime % 10;	//�摜�p����
		DrawGraph(SCREEN_SIZE_X / 2, 10, imageHandle[imageNum], true);
	}
	else if (type == 1&&!start)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 0.3f);
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(0, 0, 0), true);
		//�\�������ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//��̈�
		int imageNum = currentTime % 10;	//�摜�p����
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 10.0f, 0.0f, imageHandle[imageNum], true);
	}
	
}

//�I������
void TimeLimit::Fin()
{
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
