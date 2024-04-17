#pragma once

const int MAPCHIP_SIZE = 50;	// マップチップ1枚のサイズ

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

	//空の画像ハンドル
	int skyHandle;

	// ファイルからのマップデータ
	int** mapChipData2;

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

	// 描画
	void Draw(int type);
	

	// ファイルからの読み込み
	void ReadFile(int Map);

	void Fin();

	void SetCollision(int Map);
	
};

// ファイルからのマップデータ
extern int** mapChipData;
//当たり判定の配置データ	1=地面,　2=左の壁,　3=右の壁
extern int** mapCollisionData;
extern Map mapData;

//全ての座標の生みの親
void AllPosInit();