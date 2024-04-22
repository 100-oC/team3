#pragma once

const int TIME_LIMIT = 60;	//1ゲームの制限時間(秒)
const char TIME_IMAGE_PATH[255] = "data/play/number_44×64.png";	//画像パス

class TimeLimit
{
private:
	int imageHandle[10];	//画像ハンドル

	float timeCount;	//時間計測
	int currentTime;	//現在の時間

	bool start;

public:
	//初期化
	void Init();

	//通常処理
	void Step();

	//描画
	void Draw(int type=0);

	//終了処理
	void Fin();

	bool GetStart() { return start; }
};

//extern int currentTime;	//現在の時間