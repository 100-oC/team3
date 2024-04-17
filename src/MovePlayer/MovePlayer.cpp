#include"MovePlayer.h"
#include"DxLib.h"
#include"../input/input.h"

//�W�����v�{�^�����@�\���鎞��
float JumpFrgCount;

//�d�͂̉��Z
float Yspeed;	

//�W�����v�̉�
int jumpCount;
//�W�����v�t���O
bool jump;

//�W�����v�p������
void MovePlayerInit()
{
	JumpFrgCount = 0.0f;
	Yspeed = 0.0f;
	jumpCount = 0;
	jump = false;
}

//�ړ�����
void MovePlayer(float &x, float &y)
{
	//���W��ۑ�
	float playerZx = x;
	//���W�̕ۑ�
	float playerZy = y;

	//������߂�
	float speed = CIRCLE_PLAYER_SPD_FAST * PLAYER_SPEED;

	//�E�ړ�����
	if (Input::Key::Keep(KEY_INPUT_RIGHT) || Input::Key::Keep(KEY_INPUT_D))
	{
		playerZx += speed;
	}
	//���ړ�����
	else if (Input::Key::Keep(KEY_INPUT_LEFT) || Input::Key::Keep(KEY_INPUT_A))
	{
		playerZx -= speed;
	}

	//��ړ�����
	else if (Input::Key::Keep(KEY_INPUT_UP) || Input::Key::Keep(KEY_INPUT_W))
	{
		playerZy -= speed;
	}

	//���ړ�����
	else if (Input::Key::Keep(KEY_INPUT_DOWN) || Input::Key::Keep(KEY_INPUT_S))
	{
		playerZy += speed;
	}

	//���W�̌���
	x = playerZx;
	y = playerZy;
}

//�W�����v
void JumpPlayer(float& x, float& y)
{
	//���W��ۑ�
	float playerZx = x;
	//���W�̕ۑ�
	float playerZy = y;

	Yspeed += GRAVITY;

	//�������u�ԂɃW�����v�񐔂����Z
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		jumpCount++;
	}

	//�W�����v����
	if (!jump)
	{
		if (Input::Key::Keep(KEY_INPUT_SPACE))
		{
			//���̎��ԓ������W�����v�ł���
			if (JumpFrgCount <= 0.15f)
			{
				//�W�����v���ԃv���X
				JumpFrgCount += 1.0f / 60;
				//�W�����v����
				Yspeed = JUMP_HEIGHT;
			}
		}
		//�������玞�Ԃ����Z�b�g
		else
		{
			JumpFrgCount = 0.0f;
		}
	}

	//�W�����v�񐔂��ō��ɂȂ��jump��true�ɂ��Ĉȍ~�W�����v�����Ȃ�
	if (jumpCount >= 1)
	{
		jump = true;
	}

	//�d�͂̉��Z
	playerZy += Yspeed;
		
	//������i���݂͉�ʉ����j
	if (playerZy >= 480.0f)
	{
		//���̏���
		groundProcess(playerZy);
	}

	//���W���m��
	y = playerZy;
}

//�n�ʂ̏���
void groundProcess(float& Zy)
{
	//�Œ�
	Zy = 480.0f;

	//�v���C���[�ɂ�����d�͂����Z�b�g
	Yspeed = 0.0f;

	//�W�����v�ł���悤�ɂ���
	jump = false;

	//�W�����v�����񐔂̃��Z�b�g
	jumpCount = 0;
}