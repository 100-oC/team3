#include <Dxlib.h>
#include "Player.h"

// mainに書いたものクラス分け引っ越し中...
// 家でクラス化作業します...

Player player[MAX_PLAYER];


void Player::Init() {

	// 初期地
	player[0].m_statepos = { 0.0f,0.0f };
	player[1].m_statepos = { 1240.0f,680.0f };

	for (int i = 0; i < MAX_PLAYER; i++) {
		player[i].m_pos = player[i].m_statepos;
		player[i].m_living_flg = true;
	}

}

void Player::Step() {

	// 1プレイヤー操作
	if (CheckHitKey(KEY_INPUT_D) != 0)	// 右移動
		player[0].m_speed.x += 0.5f;
	if (CheckHitKey(KEY_INPUT_A) != 0)	// 左
		player[0].m_speed.x -= 0.5f;
	if (CheckHitKey(KEY_INPUT_W) != 0)	// 上
		player[0].m_speed.y -= 0.5f;
	if (CheckHitKey(KEY_INPUT_S) != 0)	// 下
		player[0].m_speed.y += 0.5f;

	// 2プレイヤー操作
	if (CheckHitKey(KEY_INPUT_RIGHT) != 0)	// 右移動
		player[1].m_speed.x += 0.5f;
	if (CheckHitKey(KEY_INPUT_LEFT) != 0)	// 左
		player[1].m_speed.x -= 0.5f;
	if (CheckHitKey(KEY_INPUT_UP) != 0)		// 上
		player[1].m_speed.y -= 0.5f;
	if (CheckHitKey(KEY_INPUT_DOWN) != 0)	// 下
		player[1].m_speed.y += 0.5f;

	// プレイヤーの座標更新
	for (int i = 0; i < 2; i++) {
		player[i].m_pos.x += player[i].m_speed.x;
		player[i].m_pos.y += player[i].m_speed.y;
	}

	// プレイヤー加速度 最大値,最小値の設定
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

	// プレイヤー加速度減少
	for (int i = 0; i < 2; i++) {
		player[i].m_speed.x -= player[i].m_speed.x / 32;
		player[i].m_speed.y -= player[i].m_speed.y / 32;
	}

	// プレイヤーがキルされたとき
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
