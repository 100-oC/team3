#include <Dxlib.h>
#include "Player.h"
#include "../Input/Input.h"
#include"../Map/Map.h"
#include "../Item/Meat/Meat.h"
#include"../Scene/Scene.h"

#define ANIME_MAX 4		// アニメの最大数
#define ANIME_TIME 13	// アニメの時間

Player player[MAX_PLAYER];
Meat meat[MAX_MEAT];

int animTime[MAX_PLAYER] = { 0 };	// アニメの変更時間
int anim[MAX_PLAYER] = { 0 };		// 現在のアニメ

void Player::Init() {

	// 初期地
	player[0].m_statepos = { 50.0f,50.0f };
	player[1].m_statepos = { SCREEN_SIZE_X - 100,SCREEN_SIZE_Y - 100 };

	for (int i = 0; i < MAX_PLAYER; i++) {
		player[i].m_pos = player[i].m_statepos;
		player[i].m_living_flg = true;
		player[i].m_up_flg = true;
		player[i].m_carry_meat = 0;
		player[i].m_speed= DEFAULT_VECTOR;
		player[i].m_anim = 0;
		player[i].m_carry_meat = 0;
		player[i].m_goal_meat = 0;
		player[i].m_animTime = 0;
		player[i].m_move_flg = false;
		animTime[i] = 0;
		anim[i] = 0;

	}

	// プレイヤーの初期向き
	player[0].m_turn_flg = true;
	player[1].m_turn_flg = false;

	// 画像ハンドル
	player[0].m_hndl[0] = LoadGraph(NORMAL1);
	player[0].m_hndl[1] = LoadGraph(MOVE1);
	player[1].m_hndl[0] = LoadGraph(NORMAL2);
	player[1].m_hndl[1] = LoadGraph(MOVE2);


 	for (int i = 0; i < MAX_MEAT; i++)
	{
		meat[i].Init(i);
	}
}

int meatNum_Now[2];
void Player::Step() {

	meatNum_Now[0] = 0;
	meatNum_Now[1] = 0;
	//座標の保存
	for (int i = 0; i < 2; i++)
	{
		player[i].m_savePos = player[i].m_pos;
	}

	// 1プレイヤー操作
	player[0].m_move_flg = false;
	if (CheckHitKey(KEY_INPUT_D) != 0) {	// 右移動
		player[0].m_speed.x += SPEED;
		player[0].m_turn_flg = true;
		player[0].m_move_flg = true;
	}
	if (CheckHitKey(KEY_INPUT_A) != 0) {	// 左
		player[0].m_speed.x -= SPEED;
		player[0].m_turn_flg = false;
		player[0].m_move_flg = true;
	}
	if (CheckHitKey(KEY_INPUT_W) != 0)// 上
	{		
		player[0].m_speed.y -= SPEED;
		player[0].m_up_flg = true;
		player[0].m_move_flg = true;
	}
	if (CheckHitKey(KEY_INPUT_S) != 0)		// 下
	{
		player[0].m_speed.y += SPEED;
		player[0].m_up_flg = false;
		player[0].m_move_flg = true;
	}

	// 2プレイヤー操作
	player[1].m_move_flg = false;
	if (CheckHitKey(KEY_INPUT_RIGHT) != 0) { // 右移動
		player[1].m_speed.x += SPEED;
		player[1].m_turn_flg = true;
		player[1].m_move_flg = true;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) != 0) {	 // 左
		player[1].m_speed.x -= SPEED;
		player[1].m_turn_flg = false;
		player[1].m_move_flg = true;
	}
	if (CheckHitKey(KEY_INPUT_UP) != 0)		 // 上
	{
		player[1].m_speed.y -= SPEED;
		player[1].m_up_flg = true;
		player[1].m_move_flg = true;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) != 0)	 // 下
	{
		player[1].m_speed.y += SPEED;
		player[1].m_up_flg = false;
		player[1].m_move_flg = true;
	}

	// プレイヤーの座標更新
	for (int i = 0; i < MAX_PLAYER; i++) {
		player[i].m_savePos.x += player[i].m_speed.x;
		player[i].m_savePos.y += player[i].m_speed.y;
	}

	// プレイヤー加速度 最大値,最小値の設定
	for (int i = 0; i < MAX_PLAYER; i++) {
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

	// プレイヤー加速度減少
	for (int i = 0; i < MAX_PLAYER; i++) {
		player[i].m_speed.x -= player[i].m_speed.x / 32;
		player[i].m_speed.y -= player[i].m_speed.y / 32;
	}

	// プレイヤーがキルされたとき
	for (int i = 0; i < MAX_PLAYER; i++) {
		if (player[i].m_living_flg != true) {
			player[i].m_savePos = player[i].m_statepos;
			player[i].m_living_flg = true;
		}
	}

	//当たり判定を取る
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (CheckWallCollision(
			player[i].m_savePos, 40, 40))
		{
			player[i].m_savePos = player[i].m_pos;
			player[i].m_speed.x = 0.0f;
			player[i].m_speed.y = 0.0f;
		}
	}

	//座標の反映
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		player[i].m_pos = player[i].m_savePos;
	}

	// プレイヤー座標(画面外いかないようにする)
	for (int i = 0; i < MAX_PLAYER; i++) {
		if (player[i].m_pos.x < 0) {
			player[i].m_pos.x = 0.0f;
		}
		if (player[i].m_pos.x > 1240.0f) {
			player[i].m_pos.x = 1240.0f;
		}
		if (player[i].m_pos.y < 0) {
			player[i].m_pos.y = 0.0f;
		}
		if (player[i].m_pos.y > 680.0f) {
			player[i].m_pos.y = 680.0f;
		}
	}

	/////////////////////////肉
	// 運んでいる肉表示
	for (int i = 0; i < MAX_MEAT; i++) 
	{
		meat[i].Step(i);
	}
	////////////////////////////////
}

void Player::Draw() 
{
	SetFontSize(40);
	DrawFormatString(60, 60, GetColor(255, 255, 255), "%d", player[0].m_goal_meat);
	DrawFormatString(SCREEN_SIZE_X-100, SCREEN_SIZE_Y-100, GetColor(255, 255, 255), "%d", player[1].m_goal_meat);
	SetFontSize(20);

	/////////////////////////肉
// 運んでいる肉表示
	for (int i = 0; i < MAX_MEAT; i++)
	{
		meat[i].Draw();
	}
	////////////////////////////////

	Effect::Draw();

	// プレイヤー表示
	if (player[0].m_living_flg == true) {
		if (player[0].m_move_flg == false) {
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
		else {
			if (anim[0] == 0) {
				DrawRectGraphF(player[0].m_pos.x, player[0].m_pos.y, 0, 0, 40, 40, player[0].m_hndl[1], true, player[0].m_turn_flg);
			}
			else if (anim[0] == 1) {
				DrawRectGraphF(player[0].m_pos.x, player[0].m_pos.y, 0, 40, 40, 40, player[0].m_hndl[1], true, player[0].m_turn_flg);
			}
			else if (anim[0] == 2) {
				DrawRectGraphF(player[0].m_pos.x, player[0].m_pos.y, 40, 0, 40, 40, player[0].m_hndl[1], true, player[0].m_turn_flg);
			}
			else if (anim[0] == 3) {
				DrawRectGraphF(player[0].m_pos.x, player[0].m_pos.y, 40, 40, 40, 40, player[0].m_hndl[1], true, player[0].m_turn_flg);
			}
		}
	}

	// プレイヤー2表示
	if (player[1].m_living_flg == true) {
		if (player[1].m_move_flg == false) {
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
		else {
			if (anim[1] == 0) {
				DrawRectGraphF(player[1].m_pos.x, player[1].m_pos.y, 0, 0, 40, 40, player[1].m_hndl[1], true, player[1].m_turn_flg);
			}
			else if (anim[1] == 1) {
				DrawRectGraphF(player[1].m_pos.x, player[1].m_pos.y, 0, 40, 40, 40, player[1].m_hndl[1], true, player[1].m_turn_flg);
			}
			else if (anim[1] == 2) {
				DrawRectGraphF(player[1].m_pos.x, player[1].m_pos.y, 40, 0, 40, 40, player[1].m_hndl[1], true, player[1].m_turn_flg);
			}
			else if (anim[1] == 3) {
				DrawRectGraphF(player[1].m_pos.x, player[1].m_pos.y, 40, 40, 40, 40, player[1].m_hndl[1], true, player[1].m_turn_flg);
			}
		}
	}

	// プレイヤーアニメーション
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
}

//勝者
enum WINNER
{
	PLAYER1,
	PLAYER2,
	DRAW,
};

void Player::Fin() {
	for (int i = 0; i < MAX_PLAYER; i++) 
	{
		for (int j = 0; j < 2; j++) {

			DeleteGraph(player[i].m_hndl[j]);
		}

	}

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		meat[i].Fin();
	}

	if (player[0].m_goal_meat > player[1].m_goal_meat)
	{
		winner = PLAYER1;
	}
	else if (player[0].m_goal_meat < player[1].m_goal_meat)
	{
		winner = PLAYER2;
	}
	else
	{
		winner = DRAW;
	}
}


VECTOR Player::Getpos() { return m_pos; };

void Player::Setpos(VECTOR pos,int n) {
	player[n].m_pos = pos;
}


float Player::GetXpos() { return m_pos.x; };

void Player::SetXpos(float x,int n) {
	player[n].m_pos.x = x;
}


float Player::GetYpos() { return m_pos.y; };

void Player::SetYpos(float y,int n) {
	player[n].m_pos.y = y;
}


VECTOR Player::GetStatepos() { return m_statepos; };

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


//////////////////肉

const int POP_TIME = 3;

void Meat::Init(int meatNum)
{
	isUse = false;
	isGet = false;

	m_carry_speed = MEAT_MAX_SPEED;
	m_meathndl = LoadGraph(MEAT);
	m_carry_pos = DEFAULT_VECTOR;
	m_carry_pos = meatDefaultPos[meatNum];

	if (m_carry_pos.x != 0)
	{
		isUse = true;
	}

	isGet = false;
	getPlayer = -1;

	popTime = POP_TIME;
}
void Meat::Step(int meatNum)
{
	if(isUse)
	{
		//肉の獲得
		GetMeat();
		
		if(isGet)
		{
			//移動処理
			Move(meatNum);
		}
	}
	else if (meatNum < meatMaxNum)
	{
		//再出現
		PopMeat(meatNum);
	}
}

void Meat::Draw()
{
	if (isUse) 
	{
		DrawRotaGraphF(m_carry_pos.x,m_carry_pos.y,1.5f, 0.0f,m_meathndl, true);
	}

}
void Meat::Fin()
{
	DeleteGraph(m_meathndl);

}

//=====================================================================================

//肉の取得
void Meat::GetMeat()
{
	for(int i=0;i<MAX_PLAYER;i++)
	{
		float dis = GetDistance(player[i].GetXpos(), player[i].GetYpos(), m_carry_pos.x, m_carry_pos.y);
		if (dis <= 30 && getPlayer != i)
		{
			getPlayer = i;
			isGet = true;
			player[i].SetCarrymeat(player[i].GetCarrymeat(i) + 1, i);
			Sound::Se::Play(SE_ITEM_GET);
		}
	}		
}

//移動
float meatX[2], meatY[2];	//前の肉の座標保存用
void Meat::Move(int meatNum)
{
	//最初の肉はPlayerに依存
	if (meatNum_Now[getPlayer] == 0)
	{
		//一定距離に入っていなかったら
		if (GetDistance(
			player[getPlayer].GetXpos() + 20, player[getPlayer].GetYpos() + 45,
			m_carry_pos.x, m_carry_pos.y) >= 20)
		{
			//Playerに向かって進行
			m_carry_pos.x += GetMoving(m_carry_pos.x, m_carry_pos.y,
				player[getPlayer].GetXpos() + 20, player[getPlayer].GetYpos() + 45,
				'x', m_carry_speed);

			m_carry_pos.y += GetMoving(m_carry_pos.x, m_carry_pos.y,
				player[getPlayer].GetXpos() + 20, player[getPlayer].GetYpos() + 45,
				'y', m_carry_speed);
		}
	}
	//以降は前の肉に依存
	else
	{
		//一定距離に入っていなかったら
		if (GetDistance(
			meatX[getPlayer],meatY[getPlayer],
			m_carry_pos.x,m_carry_pos.y) >= 30)
		{
			//前の肉に向かって進行
			m_carry_pos.x += GetMoving(m_carry_pos.x, m_carry_pos.y,
				meatX[getPlayer], meatY[getPlayer],
				'x', m_carry_speed);

			m_carry_pos.y += GetMoving(m_carry_pos.x, m_carry_pos.y,
				meatX[getPlayer], meatY[getPlayer],
				'y', m_carry_speed);
		}
	}

	//座標の記録
	meatX[getPlayer] = m_carry_pos.x;
	meatY[getPlayer] = m_carry_pos.y;

	//次の肉へ
	meatNum_Now[getPlayer]++;

	AreaInMeat();
}

//肉のポイント化
VECTOR popPos = {};
void Meat::AreaInMeat()
{
	//自陣の座標を取得
	popPos = player[getPlayer].GetStatepos();
	if (GetDistance(
		popPos.x, popPos.y,
		m_carry_pos.x, m_carry_pos.y) <= 70)
	{
		//フラグ管理
		isUse = false;
		isGet = false;

		//ポイント加算
		player[getPlayer].AddGoalmeat();
		Sound::Se::Play(SE_AREA);

		popTime = POP_TIME;

		Effect::Play(EFFECT_TYPE_GET, m_carry_pos.x, m_carry_pos.y - 20);
	}
}

//再出現
void Meat::PopMeat(int meatNum)
{
	popTime -= 1.0f / FRAME_RATE;
	if (popTime <= 0)
	{
		m_carry_pos = meatDefaultPos[meatNum];
		isUse = true;
		getPlayer = -1;
	}
}