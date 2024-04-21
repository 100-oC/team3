#pragma once

#include "../Item/Meat/Meat.h"

#define NORMAL1 "data/play/normal1_40.png"
#define NORMAL2 "data/play/normal2_40.png"
#define MOVE1	"data/play/move1_40.png"
#define MOVE2	"data/play/move2_40.png"

#define MEAT	"data/play/meat_14.png"

const int MAX_PLAYER = 2;							// �v���C���[�̍ő吔
const float SPEED = 0.25f;							// �v���C���[�̑��x
const float MAX_SPEED = 5.0f;						// �v���C���[�̍ő呬�x

class Player {
private:
	VECTOR m_pos = { 0.0f,0.0f };					// ���W
	VECTOR m_savePos = { 0.0f,0.0f };				// �ꎞ�ۑ��p���W
	VECTOR m_statepos = { 0.0f,0.0f };				// �����n�_(���X�|�[���n�_���W)
	VECTOR m_speed = { 0.0f ,0.0f };				// �ړ����x

	int m_hndl[2];									// �摜�n���h��
	int m_meathndl;									// �^�ԓ��̃n���h��

	bool m_living_flg = true;						// �������Ă��邩�t���O(true�Ő���)
	bool m_turn_flg = false;						// �v���C���[�̌����ύX
	bool m_move_flg = false;						// �v���C���[�������Ă��邩

	bool m_up_flg = false;						// �v���C���[�̏㉺
	int m_carry_meat = 0;							// ���݉^��ł�����̐�
	VECTOR m_carry_pos[MAX_MEAT] = {0.0f,0.0f};		// ���݉^��ł�����̍��W
	float m_carry_speed = 1.0f;						// ���݉^��ł�����̑��x
	int m_goal_meat = 0;							// ���ݎ����̃��X�n�ɉ^�񂽓��̐�

	int m_animTime = 0;								// �A�j���̕ύX����
	int m_anim = 0;									// ���݂̃A�j��

public:
	void Init();
	void Step();
	void Draw();
	void Fin();


	VECTOR Getpos(int n);							// ���W�擾
	void Setpos(VECTOR pos, int n);					// ���W�ݒ�	(n�͔z��̗v�f)

	float GetXpos(int n);							// X���W�擾
	void SetXpos(float x, int n);					// X���W�ݒ�

	float GetYpos(int n);							// Y���W�擾
	void SetYpos(float y, int n);					// Y���W�ݒ�

	VECTOR GetStatepos(int n);						// ���X�|�[���n�_�擾
	void SetStatepos(VECTOR statepos, int n);		// ���X�|�[���n�_�ݒ�

	int GetCarrymeat(int n);						// ���݉^��ł�����̐��擾
	void SetCarrymeat(int carrymeat, int n);		// ���݉^��ł�����̐��ݒ�

	int GetGoalmeat(int n);							// ���ݎ����̃��X�n�ɉ^�񂽓��̐��擾
	void SetGoalmeat(int goalmeat, int n);			// ���ݎ����̃��X�n�ɉ^�񂽓��̐��ݒ�

};