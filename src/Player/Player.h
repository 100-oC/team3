#pragma once

#include "../Item/Meat/Meat.h"

#define NORMAL1 "data/play/normal1_40.png"
#define NORMAL2 "data/play/normal2_40.png"
#define MOVE1	"data/play/move1_40.png"
#define MOVE2	"data/play/move2_40.png"

#define MEAT	"data/play/meat_14.png"

const int MAX_PLAYER = 2;							// プレイヤーの最大数
const float SPEED = 0.25f;							// プレイヤーの速度
const float MAX_SPEED = 5.0f;						// プレイヤーの最大速度

class Player {
private:
	VECTOR m_pos = { 0.0f,0.0f };					// 座標
	VECTOR m_savePos = { 0.0f,0.0f };				// 一時保存用座標
	VECTOR m_statepos = { 0.0f,0.0f };				// 初期地点(リスポーン地点座標)
	VECTOR m_speed = { 0.0f ,0.0f };				// 移動速度

	int m_hndl[2];									// 画像ハンドル
	int m_meathndl;									// 運ぶ肉のハンドル

	bool m_living_flg = true;						// 生存しているかフラグ(trueで生存)
	bool m_turn_flg = false;						// プレイヤーの向き変更
	bool m_move_flg = false;						// プレイヤーが動いているか

	bool m_up_flg = false;						// プレイヤーの上下
	int m_carry_meat = 0;							// 現在運んでいる肉の数
	VECTOR m_carry_pos[MAX_MEAT] = {0.0f,0.0f};		// 現在運んでいる肉の座標
	float m_carry_speed = 1.0f;						// 現在運んでいる肉の速度
	int m_goal_meat = 0;							// 現在自分のリス地に運んた肉の数

	int m_animTime = 0;								// アニメの変更時間
	int m_anim = 0;									// 現在のアニメ

public:
	void Init();
	void Step();
	void Draw();
	void Fin();


	VECTOR Getpos(int n);							// 座標取得
	void Setpos(VECTOR pos, int n);					// 座標設定	(nは配列の要素)

	float GetXpos(int n);							// X座標取得
	void SetXpos(float x, int n);					// X座標設定

	float GetYpos(int n);							// Y座標取得
	void SetYpos(float y, int n);					// Y座標設定

	VECTOR GetStatepos(int n);						// リスポーン地点取得
	void SetStatepos(VECTOR statepos, int n);		// リスポーン地点設定

	int GetCarrymeat(int n);						// 現在運んでいる肉の数取得
	void SetCarrymeat(int carrymeat, int n);		// 現在運んでいる肉の数設定

	int GetGoalmeat(int n);							// 現在自分のリス地に運んた肉の数取得
	void SetGoalmeat(int goalmeat, int n);			// 現在自分のリス地に運んた肉の数設定

};