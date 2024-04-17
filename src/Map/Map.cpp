#include<DxLib.h>
#include"Map.h"
#include"../MovePlayer/MovePlayer.h"
#include"../Collision/Collision.h"

int Map::mapNumX;
int Map::mapNumY;

//当たり判定の配置データ	1=地面,　2=左の壁,　3=右の壁
int** mapCollisionData;
// ファイルからのマップデータ
int** mapChipData;

int mapPlx;
int mapPly;

//マップチップのファイルパス
char map[MAP_AMX_NUM][255] = {
	"data/map/.csv",
};
char colli[MAP_AMX_NUM][255] = {
	"data/map/.csv",
};

//マップチップイメージパス
#define MAP_CHIP_IMG_PATH	"data/map/mapchip1_50×50_41.png"

Map::Map()
{
	mapChipData = 0;
	mapChipData2 = 0;
	mapNumX = 0;
	mapNumY = 0;
	skyHandle = 0;
	// コンストラクタの処理
	for (int i = 0; i < mapChipMaxNum; i++) {
		imgHandle[i] = -1;
	}
	
	for (int i = 0; i < 2; i++)
	{
		for (int n = 0; n < 15; n++)
		{
			backHandle[i][n] = -1;
		}
	}

	frontHandle = -1;

}


void Map::Init(int mapNum)
{
	//マップチップの読み込み
	LoadDivGraph(MAP_CHIP_IMG_PATH, 41, 6, 7, MAPCHIP_SIZE, MAPCHIP_SIZE, imgHandle);

	ReadFile(mapNum);
	SetCollision(mapNum);
}

void Map::Step()
{
}

void Map::Draw(int type) 
{
	switch (type)
	{
	case 0:
		//空の描画
		DrawGraph(0, 0, skyHandle, true);

		break;

	case 1:	//プレイヤーの下に描画

		for (int y = 0; y < mapNumY; y++)
		{
			for (int x = 0; x < mapNumX; x++)
			{
				// ブロックを描画
				int mapchipType = mapChipData[y][x];

				if (mapChipData[y][x] != -1)
				{
					DrawGraph(x * MAPCHIP_SIZE,
						y * MAPCHIP_SIZE,
						imgHandle[mapchipType], true);
				}
			}
		}

		break;

	case 2:	//プレイヤーの上に描画

		for (int y = 0; y < mapNumY; y++)
		{
			for (int x = 0; x < mapNumX; x++)
			{
				// ブロックを描画
				int mapchipType = mapChipData2[y][x];

				if (mapChipData2[y][x] != -1)
				{
					DrawGraph(x * MAPCHIP_SIZE,
						y * MAPCHIP_SIZE,
						imgHandle[mapchipType], true);
				}
			}
		}

		break;

	default:
		break;
	}
}

// ファイルからの読み込み
void Map::ReadFile(int Map)
{
	FILE* fp;
	fopen_s(&fp, map[Map], "r");

	if (fp != NULL)
	{
		mapNumX = 0;
		mapNumY = 0;

		//csvに入っている行数情報を取得
		fscanf_s(fp, "%d", &mapNumX);
		fgetc(fp);
		fscanf_s(fp, "%d", &mapNumY);
		fgetc(fp);

		//Yのメモリ確保
		mapChipData = new int* [mapNumY];
		mapChipData2 = new int* [mapNumY];

		mapCollisionData = new int* [mapNumY];

		for (int i = 0; i < mapNumY; i++)
		{
			//Xのメモリ確保
			mapChipData[i] = new int[mapNumX];
			mapChipData2[i] = new int[mapNumX];

			mapCollisionData[i] = new int[mapNumX];
		}

		int mapIndexX = 0;
		int mapIndexY = 0;

		//レイヤー１読み込み
		while (true)
		{
			// 数値部分を読み込む
			fscanf_s(fp, "%d", &mapChipData[mapIndexY][mapIndexX]);
			mapIndexX++;

			// 「,」を飛ばすために読み込みを実行
			char c = fgetc(fp);

			// EOFの場合は読み込み終了
			if (c == EOF)
			{
				break;
			}
			if (c == 'a')
			{
				break;
			}
			// 改行コードの場合は保存先を変更する
			else if (c == '\n')
			{
				mapIndexY++;
				mapIndexX = 0;
			}
		}

		mapIndexX = 0;
		mapIndexY = 0;

		//レイヤー２読み込み
		while (true)
		{
			// 数値部分を読み込む
			fscanf_s(fp, "%d", &mapChipData2[mapIndexY][mapIndexX]);
			mapIndexX++;

			// 「,」を飛ばすために読み込みを実行
			char c = fgetc(fp);

			// EOFの場合は読み込み終了
			if (c == EOF)
			{
				break;
			}
			// 改行コードの場合は保存先を変更する
			else if (c == '\n')
			{
				mapIndexY++;
				mapIndexX = 0;
			}
		}
		fclose(fp);
	}
}

//マップ後処理
void Map::Fin()
{
	//メモリの開放
	//先にXを削除
	for (int i = 0; i < mapNumY; i++)
	{
		delete[] mapChipData[i];
		mapChipData[i] = 0;
	}
	//Yを解放
	delete[] mapChipData;
	mapChipData = 0;
}

//当たり判定の読み込み
void Map::SetCollision(int Map)
{
	FILE* fp1;
	fopen_s(&fp1, colli[Map], "r");

	if (fp1 != NULL)
	{
		int mapIndexX = 0;
		int mapIndexY = 0;

		while (true)
		{
			// 数値部分を読み込む
			fscanf_s(fp1, "%d", &mapCollisionData[mapIndexY][mapIndexX]);
			mapIndexX++;

			// 「,」を飛ばすために読み込みを実行
			char c = fgetc(fp1);

			// EOFの場合は読み込み終了
			if (c == EOF)
			{
				break;
			}
			// 改行コードの場合は保存先を変更する
			else if (c == '\n')
			{
				mapIndexY++;
				mapIndexX = 0;
			}
		}

		fclose(fp1);
	}
}

//====================================================================================================

//壁の当たり判定：当たり判定を取りたいやつの座標と横幅、縦幅
void CheckWallCollision
(float& x, float& y, float w, float h)
{
	float mapX = 0;
	float mapY = 0;

	for (int indexY = 0; indexY < Map::GetMapNumY(); indexY++)
	{
		for (int indexX = 0; indexX < Map::GetMapNumX(); indexX++)
		{
			//マップの変数を作る
			mapX = (float)indexX * MAPCHIP_SIZE;
			mapY = (float)indexY * MAPCHIP_SIZE;

			if (Collision::Rect(mapX, mapY, (float)MAPCHIP_SIZE, (float)MAPCHIP_SIZE,
				x - w / 2, y - h / 2, w, h))
			{

			}
		}
	}
}

int Map::GetMapNumX()
{
	return mapNumX;
}

int Map::GetMapNumY() 
{ 
	return mapNumY; 
}

//====================================================================================================

//全ての座標の生みの親
void AllPosInit()
{
	/*====================================================
　	当たり判定を格納した変数からスポーン位置を取る
	======================================================*/

	for (int indexY = 0; indexY < Map::GetMapNumY(); indexY++)
	{
		for (int indexX = 0; indexX < Map::GetMapNumX(); indexX++)
		{
			
			switch (mapCollisionData[indexY][indexX])
			{

			//10に何かある
			case 10: {

				//使い方
				/*Goal::SetPosX((float)indexX * MAPCHIP_SIZE + GOAL_SIZE_X / 2);
				Goal::SetPosY((float)indexY * MAPCHIP_SIZE - GOAL_SIZE_Y);*/

				break; }

			default:
				break;
			} 
		}
	}
}