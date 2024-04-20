#include <Dxlib.h>
#include "Player.h"

// main�ɏ��������̃N���X���������z����...
// �ƂŃN���X����Ƃ��܂�...

Player player[MAX_PLAYER];


void Player::Init() {

	// �����n
	player[0].m_statepos = { 0.0f,0.0f };
	player[1].m_statepos = { 1240.0f,680.0f };

	for (int i = 0; i < MAX_PLAYER; i++) {
		player[i].m_pos = player[i].m_statepos;
		player[i].m_living_flg = true;
	}

}

void Player::Step() {

	// 1�v���C���[����
	if (CheckHitKey(KEY_INPUT_D) != 0)	// �E�ړ�
		player[0].m_speed.x += 0.5f;
	if (CheckHitKey(KEY_INPUT_A) != 0)	// ��
		player[0].m_speed.x -= 0.5f;
	if (CheckHitKey(KEY_INPUT_W) != 0)	// ��
		player[0].m_speed.y -= 0.5f;
	if (CheckHitKey(KEY_INPUT_S) != 0)	// ��
		player[0].m_speed.y += 0.5f;

	// 2�v���C���[����
	if (CheckHitKey(KEY_INPUT_RIGHT) != 0)	// �E�ړ�
		player[1].m_speed.x += 0.5f;
	if (CheckHitKey(KEY_INPUT_LEFT) != 0)	// ��
		player[1].m_speed.x -= 0.5f;
	if (CheckHitKey(KEY_INPUT_UP) != 0)		// ��
		player[1].m_speed.y -= 0.5f;
	if (CheckHitKey(KEY_INPUT_DOWN) != 0)	// ��
		player[1].m_speed.y += 0.5f;

	// �v���C���[�̍��W�X�V
	for (int i = 0; i < 2; i++) {
		player[i].m_pos.x += player[i].m_speed.x;
		player[i].m_pos.y += player[i].m_speed.y;
	}

	// �v���C���[�����x �ő�l,�ŏ��l�̐ݒ�
	for (int i = 0; i < 2; i++) {
		if (player[i].m_speed.x > 5.0f) {
			player[i].m_speed.x = 5.0f;
		}
		else if (player[i].m_speed.x < -5.0f) {
			player[i].m_speed.x = -5.0f;
		}

		if (player[i].m_speed.y > 5.0f) {
			player[i].m_speed.y = 5.0f;
		}
		else if (player[i].m_speed.y < -5.0f) {
			player[i].m_speed.y = -5.0f;
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
		DrawBox(player[0].m_pos.x, player[0].m_pos.y,
			player[0].m_pos.x + 40.0f, player[0].m_pos.y + 40.0f, GetColor(0, 255, 0), true);
	}
	if (player[1].m_living_flg == true) {
		DrawBox(player[1].m_pos.x, player[1].m_pos.y,
			player[1].m_pos.x + 40.0f, player[1].m_pos.y + 40.0f, GetColor(155, 0, 255), true);
	}

}


VECTOR Player::GetStatePos(int n) { return player[n].m_pos; };

void Player::SetStatepos(VECTOR statepos,int n) {
	player[n].m_statepos = statepos;
}
