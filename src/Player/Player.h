#pragma once

#include "../Item/Meat/Meat.h"

#define NORMAL1 "data/play/normal1_40.png"
#define NORMAL2 "data/play/normal2_40.png"
#define MOVE1	"data/play/move1_40.png"
#define MOVE2	"data/play/move2_40.png"

#define MEAT	"data/play/meat_14.png"

const int MAX_PLAYER = 2;								// プレイヤーの最大数
const float SPEED = 0.5f;								// プレイヤーの速度
const float MAX_SPEED = 3.5f;							// プレイヤーの最大速度
const float MEAT_MAX_SPEED = MAX_SPEED+1.5f;						// 肉の最大速度

class Player {
private:
	VECTOR m_pos = { 0.0f,0.0f };						// 座標
	VECTOR m_savePos = { 0.0f,0.0f };					// 一時保存用座標
	VECTOR m_statepos = { 0.0f,0.0f };					// 初期地点(リスポーン地点座標)
	VECTOR m_speed = { 0.0f ,0.0f };					// 移動速度

	int m_hndl[2];										// 画像ハンドル

	bool m_living_flg = true;							// 生存しているかフラグ(trueで生存)
	bool m_turn_flg = false;							// プレイヤーの向き変更
	bool m_move_flg = false;							// プレイヤーが動いているか
	int m_carry_meat = 0;								// 現在運んでいる肉の数
	int m_goal_meat = 0;								// 現在自分のリス地に運んた肉の数

	bool m_up_flg = false;							// プレイヤーの上下

	int m_animTime = 0;									// アニメの変更時間
	int m_anim = 0;										// 現在のアニメ


	//////////////////肉
	//int m_meathndl;										// 運ぶ肉のハンドル

	//VECTOR m_carry_pos[MAX_MEAT] = {0.0f,0.0f};			// 現在運んでいる肉の座標
	//float m_carry_speed= MEAT_MAX_SPEED;				// 現在運んでいる肉の速度

	//////////////////


public:
	void Init();
	void Step();
	void Draw();
	void Fin();


	VECTOR Getpos();								// 座標取得
	void Setpos(VECTOR pos, int n);						// 座標設定	(nは配列の要素)

	float GetXpos();								// X座標取得
	void SetXpos(float x, int n);						// X座標設定

	float GetYpos();								// Y座標取得
	void SetYpos(float y, int n);						// Y座標設定

	VECTOR GetStatepos();							// リスポーン地点取得
	void SetStatepos(VECTOR statepos, int n);			// リスポーン地点設定

	int GetCarrymeat(int n);							// 現在運んでいる肉の数取得
	void SetCarrymeat(int carrymeat, int n);			// 現在運んでいる肉の数設定

	int GetGoalmeat(int n);								// 現在自分のリス地に運んた肉の数取得
	void SetGoalmeat(int goalmeat, int n);				// 現在自分のリス地に運んた肉の数設定
	void AddGoalmeat(int add = 1) { m_goal_meat += add; }

};

//肉
class Meat {
private:
	int m_meathndl;										// 運ぶ肉のハンドル

	VECTOR m_carry_pos = { 0.0f,0.0f };					// 現在運んでいる肉の座標
	float m_carry_speed = MEAT_MAX_SPEED;				// 現在運んでいる肉の速度

	bool isUse = false;	//表示フラグ
	bool isGet = false;	//入手フラグ

	int getPlayer = -1;	//入手したPlayerの記録

	float popTime = 0.0f;

	void GetMeat();	//肉の取得
	void Move(int meatNum);	//移動
	void AreaInMeat();	//肉のポイント化
	void PopMeat(int meatNum);	//再出現

public:
	void Init(int meatNum);
	void Step(int meatNum);
	void Draw();
	void Fin();
};