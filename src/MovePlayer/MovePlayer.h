#pragma once

#define CIRCLE_PLAYER_SPD		(2)		//���@�̑��x
#define CIRCLE_PLAYER_SPD_FAST	(5)		//���@�̑������x

//�L�����̃W�����v�̍���
const float JUMP_HEIGHT = -15;
//�L�����̈ړ��X�s�[�h
const float PLAYER_SPEED = 1.5f;

// �d�͉����x
const float GRAVITY = 1.0f;	

//�W�����v�p������
void MovePlayerInit();

//�ړ�����
void MovePlayer(float& x, float& y);

//�W�����v����
void JumpPlayer(float& x, float& y);

//�n�ʂ̏���
void groundProcess(float& Zy);