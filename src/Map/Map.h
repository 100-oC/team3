#pragma once

const int MAPCHIP_SIZE = 50;	// マップチップ1枚のサイズ
const int MAPCHIP_MAX_NUM = 4;	// マップチップの個数
const int MAPCHIP_NUM_X = 2;	// マップチップXの個数
const int MAPCHIP_NUM_Y = 2;	// マップチップYの個数

const int MAP_NUM_X = 16;	//Xの表示数
const int MAP_NUM_Y = 20;	//Yの表示数

//マップチップの数
const int mapChipMaxNum = 41;

const int MAP_AMX_NUM = 3;	//マップの数

// マップクラス
class Map
{
private:
	//マップチップのハンドル
	int imgHandle[mapChipMaxNum];

	//マップチップの数
	static int mapNumX;
	static int mapNumY;

	//空の画像ハンドル	int skyHandle;

	// ファイルからのマップデータ
	int mapChipData[MAP_NUM_Y][MAP_NUM_X];
	int mapChipData2[MAP_NUM_Y][MAP_NUM_X];
	
	int mapCollisionData[MAP_NUM_Y][MAP_NUM_X];

	//背景の画像ハンドル
	int backHandle[2][15];
	//前景の画像ハンドル
	int frontHandle;


public:

	Map();

	static int GetMapNumX();
	static int GetMapNumY();

	// 初期化
	void Init(int mapNum);

	void Step();

	// 描画：背景→0,　プライヤーより下→1,　playerより上→2
	void Draw(int type);
	

	// ファイルからの読み込み
	void ReadFile(int Map);

	void Fin();

	void SetCollision(int Map);

	//全ての座標の生みの親
	void AllPosInit();
};

extern Map mapData;

