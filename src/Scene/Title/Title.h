#pragma once

enum TITLE_IMAGE
{
	TITLE_GROUND,
	TITLE_MEAT1,
	TITLE_MEAT2,
	TITLE_TITLE,
	TITLE_PLAYER,
	TITLE_MANUSL,
	TITLE_START,

	TITLE_MAX_NUM,
};

const char TITLE_IMAGE_PATH[TITLE_MAX_NUM][255]
{
	"data/title/background.png",
	"data/title/meat1.png",
	"data/title/meat2.png",
	"data/title/title.png",
	"data/title/player.png",
	"data/title/manual.png",
	"data/title/start.png",
};

class Title
{
private:

	int hndl[TITLE_MAX_NUM];

	int x[TITLE_MAX_NUM];
	int y[TITLE_MAX_NUM];

	int fade[TITLE_MAX_NUM];
	float size[TITLE_MAX_NUM];

	bool lighting;
	int progress;
	
	//背景のフェードイン
	void GroundFadeIn();
	//画面作り
	void MakeTitle();
	//入力待ち
	void StartGame();

	//タイトル完成
	void MakeFinish();

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
