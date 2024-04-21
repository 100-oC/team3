#include <Dxlib.h>
#include "Player.h"
#include "../Input/Input.h"

#define ANIME_MAX 4		// �A�j���̍ő吔
#define ANIME_TIME 13	// �A�j���̎���

Player player[MAX_PLAYER];

int animTime[MAX_PLAYER] = { 0 };	// �A�j���̕ύX����
int anim[MAX_PLAYER] = { 0 };		// ���݂̃A�j��

void Player::Init() {

	// �����n
	player[0].m_statepos = { 0.0f,0.0f };
	player[1].m_statepos = { 1240.0f,680.0f };

	for (int i = 0; i < MAX_PLAYER; i++) {
		player[i].m_pos = player[i].m_statepos;
		player[i].m_living_flg = true;
	}

	// �v���C���[�̏�������
	player[0].m_turn_flg = true;
	player[1].m_turn_flg = false;

	// �摜�n���h��
	player[0].m_hndl[0] = LoadGraph(NORMAL1);
	player[0].m_hndl[1] = LoadGraph(MOVE1);
	player[1].m_hndl[0] = LoadGraph(NORMAL2);
	player[1].m_hndl[1] = LoadGraph(MOVE2);

}

void Player::Step() {

	// 1�v���C���[����
	if (CheckHitKey(KEY_INPUT_D) != 0) {	// �E�ړ�
		player[0].m_speed.x += SPEED;
		player[0].m_turn_flg = true;
	}
	if (CheckHitKey(KEY_INPUT_A) != 0) {	// ��
		player[0].m_speed.x -= SPEED;
		player[0].m_turn_flg = false;
	}
	if (CheckHitKey(KEY_INPUT_W) != 0)		// ��
		player[0].m_speed.y -= SPEED;
	if (CheckHitKey(KEY_INPUT_S) != 0)		// ��
		player[0].m_speed.y += SPEED;

	// 2�v���C���[����
	if (CheckHitKey(KEY_INPUT_RIGHT) != 0) { // �E�ړ�
		player[1].m_speed.x += SPEED;
		player[1].m_turn_flg = true;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) != 0) {	 // ��
		player[1].m_speed.x -= SPEED;
		player[1].m_turn_flg = false;
	}
	if (CheckHitKey(KEY_INPUT_UP) != 0)		 // ��
		player[1].m_speed.y -= SPEED;
	if (CheckHitKey(KEY_INPUT_DOWN) != 0)	 // ��
		player[1].m_speed.y += SPEED;

	// �v���C���[�̍��W�X�V
	for (int i = 0; i < 2; i++) {
		player[i].m_pos.x += player[i].m_speed.x;
		player[i].m_pos.y += player[i].m_speed.y;
	}

	// �v���C���[�����x �ő�l,�ŏ��l�̐ݒ�
	for (int i = 0; i < 2; i++) {
		if (player[i].m_speed.x > MAX_SPEED) {
			player[i].m_speed.x = MAX_SPEED;
		}
		else if (player[i].m_speed.x < -MAX_SPEED) {
			player[i].m_speed.x = -MAX_SPEED;
		}

		if (player[i].m_speed.y > MAX_SPEED) {
			player[i].m_speed.y = MAX_SPEED;
		}
		else if (player[i].m_speed.y < -MAX_SPEED) {
			player[i].m_speed.y = -MAX_SPEED;
		}
	}

	// �v���C���[�����x����
	for (int i = 0; i < 2; i++) {
		player[i].m_speed.x -= player[i].m_speed.x / 32;
		player[i].m_speed.y -= player[i].m_speed.y / 32;
	}

	// �v���C���[���L�����ꂽ�Ƃ�
	for (int i = 0; i < 2; i++) {
		if (player[i].m_living_flg != true) {
			player[i].m_pos = player[i].m_statepos;
			player[i].m_living_flg = true;
		}
	}

}

void Player::Draw() {

	if (player[0].m_living_flg == true) {
		if (anim[0] == 0) {
			DrawRectGraphF(player[0].m_pos.x, player[0].m_pos.y, 0, 0, 40, 40, player[0].m_hndl[0], true, player[0].m_turn_flg);
		}
		else if (anim[0] == 1) {
			DrawRectGraphF(player[0].m_pos.x, player[0].m_pos.y, 0, 40, 40, 40, player[0].m_hndl[0], true, player[0].m_turn_flg);
		}
		else if (anim[0] == 2) {
			DrawRectGraphF(player[0].m_pos.x, player[0].m_pos.y, 40, 0, 40, 40, player[0].m_hndl[0], true, player[0].m_turn_flg);
		}
		else if (anim[0] == 3) {
			DrawRectGraphF(player[0].m_pos.x, player[0].m_pos.y, 40, 40, 40, 40, player[0].m_hndl[0], true, player[0].m_turn_flg);
		}

	}
	if (player[1].m_living_flg == true) {
		if (anim[1] == 0) {
			DrawRectGraphF(player[1].m_pos.x, player[1].m_pos.y, 0, 0, 40, 40, player[1].m_hndl[0], true, player[1].m_turn_flg);
		}
		else if (anim[1] == 1) {
			DrawRectGraphF(player[1].m_pos.x, player[1].m_pos.y, 0, 40, 40, 40, player[1].m_hndl[0], true, player[1].m_turn_flg);
		}
		else if (anim[1] == 2) {
			DrawRectGraphF(player[1].m_pos.x, player[1].m_pos.y, 40, 0, 40, 40, player[1].m_hndl[0], true, player[1].m_turn_flg);
		}
		else if (anim[1] == 3) {
			DrawRectGraphF(player[1].m_pos.x, player[1].m_pos.y, 40, 40, 40, 40, player[1].m_hndl[0], true, player[1].m_turn_flg);
		}

	}

	for (int i = 0; i < MAX_PLAYER; i++) {
		animTime[i]++;
		if (animTime[i] == ANIME_TIME) {
			animTime[i] = 0;
			anim[i]++;
			if (anim[i] == ANIME_MAX) {
				anim[i] = 0;
			}
		}
	}


	// (��)
	/*
	if (player[0].m_living_flg == true) {
		DrawBox(player[0].m_pos.x, player[0].m_pos.y,
			player[0].m_pos.x + 40.0f, player[0].m_pos.y + 40.0f, GetColor(0, 255, 0), true);
	}
	if (player[1].m_living_flg == true) {
		DrawBox(player[1].m_pos.x, player[1].m_pos.y,
			player[1].m_pos.x + 40.0f, player[1].m_pos.y + 40.0f, GetColor(155, 0, 255), true);
	}
	*/

}

void Player::Fin() {
	for (int i = 0; i < MAX_PLAYER; i++) {
		for (int j = 0; j < 2; j++) {

			DeleteGraph(player[i].m_hndl[j]);
		}
	}
}


VECTOR Player::Getpos(int n) { return player[n].m_pos; };

void Player::Setpos(VECTOR pos,int n) {
	player[n].m_pos = pos;
}


float Player::GetXpos(int n) { return player[n].m_pos.x; };

void Player::SetXpos(float x,int n) {
	player[n].m_pos.x = x;
}


float Player::GetYpos(int n) { return player[n].m_pos.y; };

void Player::SetYpos(float y,int n) {
	player[n].m_pos.y = y;
}


VECTOR Player::GetStatepos(int n) { return player[n].m_statepos; };

void Player::SetStatepos(VECTOR statepos, int n) {
	player[n].m_statepos = statepos;
}


int Player::GetCarrymeat(int n) { return player[n].m_carry_meat; };

void Player::SetCarrymeat(int carrymeat, int n) {
	player[n].m_carry_meat = carrymeat;
}


int Player::GetGoalmeat(int n) { return player[n].m_goal_meat; };

void Player::SetGoalmeat(int goalmeat, int n) {
	player[n].m_goal_meat = goalmeat;
}
