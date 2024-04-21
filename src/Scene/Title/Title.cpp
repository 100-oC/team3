#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"

//������
void Title::Init()
{
	//�������A�摜�̓ǂݍ���
	for (int i = 0; i < TITLE_MAX_NUM; i++)
	{
		// �^�C�g���摜�̓Ǎ�
		hndl[i] = LoadGraph(TITLE_IMAGE_PATH[i]);
		x[i] = SCREEN_SIZE_X / 2;
		y[i] = SCREEN_SIZE_Y / 2;
		size[i] = 1.0f;
		fade[i] = 255;
	}

	//���W�𒆉��ɐݒ�
	for (int i = TITLE_MEAT1; i < TITLE_START; i++)
	{
		size[i] = 0.0f;
	}

	x[TITLE_MEAT1] = 950;
	y[TITLE_MEAT1] = 320;

	x[TITLE_MEAT2] = 1050;
	y[TITLE_MEAT2] = 290;

	fade[TITLE_GROUND] = 0;
	fade[TITLE_START] = 0;

	lighting = false;
	progress = 0;
	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

enum TITLE_PROGRESS
{
	TITLE_GROUND_FADEIN,
	TITLE_MAKE_TITLE,
	TITLE_START_GAME,
};

//�ʏ폈��
void Title::Step()
{
	switch (progress)
	{
	case TITLE_GROUND_FADEIN:	//�w�i��fade�C��

		GroundFadeIn();

		break;

	case TITLE_MAKE_TITLE:	//��ʍ��

		MakeTitle();

		break;

	case TITLE_START_GAME:	//���͑҂�

		StartGame();

		break;


	default:
		break;
	}

	//�^�C�g������
	MakeFinish();
}

//�`�揈��
void Title::Draw()
{
	for (int i = 0; i < TITLE_MAX_NUM; i++)
	{
		//fade�œ����x�ύX
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[i]);
		DrawRotaGraph(x[i], y[i],size[i],0.0f, hndl[i], true);	//�`��
		//�\�������ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

//�I������
void Title::Fin()
{

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}

//=========================================================

	//�w�i�̃t�F�[�h�C��
void Title::GroundFadeIn()
{
	//�n��
	if (fade[TITLE_GROUND] < 255)
	{
		fade[TITLE_GROUND] += 10;
	}
	else
	{
		fade[TITLE_GROUND] = 255;
		progress++;
	}

}

//��ʍ��
void Title::MakeTitle()
{
	if (size[TITLE_TITLE] < 1.0f)
	{
		size[TITLE_TITLE] += 0.01f;
	}
	else
	{
		size[TITLE_TITLE] = 1.0f;
	}

	if (size[TITLE_TITLE] >= 1.0f && size[TITLE_MEAT1] < 1.0f)
	{
		size[TITLE_MEAT1] += 0.05f;
	}
	else if (size[TITLE_TITLE] >= 1.0f && size[TITLE_MEAT1] >= 1.0f)
	{
		size[TITLE_MEAT1] = 1.0f;
	}

	if (size[TITLE_MEAT1] >= 0.3f && size[TITLE_MEAT2] < 1.0f)
	{
		size[TITLE_MEAT2] += 0.05f;
	}
	else if (size[TITLE_MEAT1] >= 0.3f && size[TITLE_MEAT2] >= 1.0f)
	{
		size[TITLE_MEAT2] = 1.0f;
	}

	if (size[TITLE_MEAT2] >= 0.5f && size[TITLE_PLAYER] < 1.0f)
	{
		size[TITLE_PLAYER] += 0.03f;
	}
	else if (size[TITLE_MEAT2] >= 0.5f && size[TITLE_PLAYER] >= 1.0f)
	{
		size[TITLE_PLAYER] = 1.0f;
	}

	if (size[TITLE_PLAYER] >= 0.3f && size[TITLE_MANUSL] < 1.0f)
	{
		size[TITLE_MANUSL] += 0.1f;
	}
	else if (size[TITLE_PLAYER] >= 0.3f && size[TITLE_MANUSL] >= 1.0f)
	{
		size[TITLE_MANUSL] = 1.0f;
	}

	if (size[TITLE_PLAYER] == 1.0f && size[TITLE_MANUSL] == 1.0f)
	{
		progress++;
	}

}

//���͑҂�
void Title::StartGame()
{
	//UI�̓_��
//�����
	if (lighting)
	{
		fade[TITLE_START] += 5;

		if (fade[TITLE_START] >= 255)
		{
			lighting = false;
		}
	}
	//������
	else
	{
		fade[TITLE_START] -= 5;

		if (fade[TITLE_START] <= 0)
		{
			lighting = true;
		}
	}

	//�X�y�[�X����������
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
	}

}

//�^�C�g������
void Title::MakeFinish()
{
	//��ʖ��������ɃX�y�[�X�Ŋ���
	if (progress != TITLE_START_GAME)
	{
		if (Input::Key::Push(KEY_INPUT_SPACE))
		{
			for (int i = 0; i < TITLE_START; i++)
			{
				x[i] = SCREEN_SIZE_X / 2;
				y[i] = SCREEN_SIZE_Y / 2;
				size[i] = 1.0f;
				fade[i] = 255;
			}

			x[TITLE_MEAT1] = 950;
			y[TITLE_MEAT1] = 320;

			x[TITLE_MEAT2] = 1050;
			y[TITLE_MEAT2] = 290;

			//���͑҂���
			progress = TITLE_START_GAME;
		}
	}

}