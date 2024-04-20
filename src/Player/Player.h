#pragma once

#define PATH1 "data/play/normal1_40.png"

const int MAX_PLAYER = 2;	// �v���C���[�̍ő吔

class Player {
private:
	VECTOR m_pos = { 0.0f,0.0f };		// ���W
	VECTOR m_statepos = { 0.0f,0.0f };	// �����n�_(���X�|�[���n�_���W)
	VECTOR m_speed = { 0.0f ,0.0f };	// �ړ����x
	int m_hndl;							// �摜�n���h��
	bool m_living_flg = true;			// �������Ă��邩�t���O(true�Ő���)

public:
	void Init();
	void Step();
	void Draw();


	VECTOR GetStatePos(int n);						// ���X�|�[���n�_�擾
	void SetStatepos(VECTOR statepos, int n);		// ���X�|�[���n�_�ݒ�

};