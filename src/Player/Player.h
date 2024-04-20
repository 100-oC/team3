#pragma once

#define PATH1 "data/play/normal1_40.png"

const int MAX_PLAYER = 2;	// プレイヤーの最大数

class Player {
private:
	VECTOR m_pos = { 0.0f,0.0f };		// 座標
	VECTOR m_statepos = { 0.0f,0.0f };	// 初期地点(リスポーン地点座標)
	VECTOR m_speed = { 0.0f ,0.0f };	// 移動速度
	int m_hndl;							// 画像ハンドル
	bool m_living_flg = true;			// 生存しているかフラグ(trueで生存)

public:
	void Init();
	void Step();
	void Draw();


	VECTOR GetStatePos(int n);						// リスポーン地点取得
	void SetStatepos(VECTOR statepos, int n);		// リスポーン地点設定

};