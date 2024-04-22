#pragma once

enum RESULT_IMAGE
{
	RESULT_GROUND,
	RESULT_WINNER1P,
	RESULT_WINNER2P,
	RESULT_DRAW,

	RESULT_MAX_NUM,
};

const char RESULT_IMAGE_PATH[RESULT_MAX_NUM][255] =
{
	"data/result/background.png",
	"data/result/winner1P.png",
	"data/result/winner2P.png",
	"data/result/draw.png",
};

class Result
{
private:
	int hndl[RESULT_MAX_NUM];

public:
	//初期化
	void Init();
	//通常処理
	void Step();
	//描画処理
	void Draw();
	//終了処理
	void Fin();
};
