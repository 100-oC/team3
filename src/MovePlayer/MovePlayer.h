#pragma once

#define CIRCLE_PLAYER_SPD		(2)		//自機の速度
#define CIRCLE_PLAYER_SPD_FAST	(5)		//自機の速い速度

//キャラのジャンプの高さ
const float JUMP_HEIGHT = -15;
//キャラの移動スピード
const float PLAYER_SPEED = 1.5f;

// 重力加速度
const float GRAVITY = 1.0f;	

//ジャンプ用初期化
void MovePlayerInit();

//移動処理
void MovePlayer(float& x, float& y);

//ジャンプ処理
void JumpPlayer(float& x, float& y);

//地面の処理
void groundProcess(float& Zy);