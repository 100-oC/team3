#include <Dxlib.h>
#include "Player.h"

// mainに書いたものクラス分け引っ越し中...
// 家でクラス化作業します...

Player player[MAX_PLAYER];


void Player::Init() {

	// 初期地（仮）
	player[0].m_statepos = { 0.0f,0.0f };
	player[1].m_statepos = { 1240.0f,680.0f };

	for (int i = 0; i < MAX_PLAYER; i++) {
		player[i].m_pos = player[0].m_statepos;
		player[i].m_living_flg = true;
	}

}

void Player::Step() {



}

void Player::Draw() {



}