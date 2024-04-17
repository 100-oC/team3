#include"MovePlayer.h"
#include"DxLib.h"
#include"../input/input.h"

//ジャンプボタンが機能する時間
float JumpFrgCount;

//重力の加算
float Yspeed;	

//ジャンプの回数
int jumpCount;
//ジャンプフラグ
bool jump;

//ジャンプ用初期化
void MovePlayerInit()
{
	JumpFrgCount = 0.0f;
	Yspeed = 0.0f;
	jumpCount = 0;
	jump = false;
}

//移動処理
void MovePlayer(float &x, float &y)
{
	//座標を保存
	float playerZx = x;
	//座標の保存
	float playerZy = y;

	//加速を戻す
	float speed = CIRCLE_PLAYER_SPD_FAST * PLAYER_SPEED;

	//右移動操作
	if (Input::Key::Keep(KEY_INPUT_RIGHT) || Input::Key::Keep(KEY_INPUT_D))
	{
		playerZx += speed;
	}
	//左移動操作
	else if (Input::Key::Keep(KEY_INPUT_LEFT) || Input::Key::Keep(KEY_INPUT_A))
	{
		playerZx -= speed;
	}

	//上移動操作
	else if (Input::Key::Keep(KEY_INPUT_UP) || Input::Key::Keep(KEY_INPUT_W))
	{
		playerZy -= speed;
	}

	//下移動操作
	else if (Input::Key::Keep(KEY_INPUT_DOWN) || Input::Key::Keep(KEY_INPUT_S))
	{
		playerZy += speed;
	}

	//座標の決定
	x = playerZx;
	y = playerZy;
}

//ジャンプ
void JumpPlayer(float& x, float& y)
{
	//座標を保存
	float playerZx = x;
	//座標の保存
	float playerZy = y;

	Yspeed += GRAVITY;

	//押した瞬間にジャンプ回数を加算
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		jumpCount++;
	}

	//ジャンプ処理
	if (!jump)
	{
		if (Input::Key::Keep(KEY_INPUT_SPACE))
		{
			//この時間内だけジャンプできる
			if (JumpFrgCount <= 0.15f)
			{
				//ジャンプ時間プラス
				JumpFrgCount += 1.0f / 60;
				//ジャンプ処理
				Yspeed = JUMP_HEIGHT;
			}
		}
		//離したら時間をリセット
		else
		{
			JumpFrgCount = 0.0f;
		}
	}

	//ジャンプ回数が最高になるとjumpをtrueにして以降ジャンプさせない
	if (jumpCount >= 1)
	{
		jump = true;
	}

	//重力の加算
	playerZy += Yspeed;
		
	//床判定（現在は画面下部）
	if (playerZy >= 480.0f)
	{
		//床の処理
		groundProcess(playerZy);
	}

	//座標を確定
	y = playerZy;
}

//地面の処理
void groundProcess(float& Zy)
{
	//固定
	Zy = 480.0f;

	//プレイヤーにかかる重力をリセット
	Yspeed = 0.0f;

	//ジャンプできるようにする
	jump = false;

	//ジャンプした回数のリセット
	jumpCount = 0;
}