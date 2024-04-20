#pragma once

enum TITLE_IMAGE
{
	TITLE_BACKGROUND,
	TITLE_TITLE,
	TITLE_MEAT1,
	TITLE_MEAT2,
	TITLE_PLAYER,
	TITLE_MANUSL,

	TITLE_MAX_NUM,
};

const char TITLE_IMAGE_PATH[TITLE_MAX_NUM][255]
{
	"data/title/background.png",
	"data/title/title.png",
	"data/title/meat1.png",
	"data/title/meat2.png",
	"data/title/player.png",
	"data/title/manual.png",
};

class Title
{
private:

	int hndl[TITLE_MAX_NUM];

	int x[TITLE_MAX_NUM];
	int y[TITLE_MAX_NUM];

	int fade[TITLE_MAX_NUM];

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
