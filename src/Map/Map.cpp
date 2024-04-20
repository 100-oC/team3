#include<DxLib.h>
#include"Map.h"
#include"../MovePlayer/MovePlayer.h"
#include"../Collision/Collision.h"

int Map::mapNumX;
int Map::mapNumY;

int mapPlx;
int mapPly;

//マップチップのファイルパス
char map[MAP_AMX_NUM][255] = {
	"data/map/map(仮).csv",
};
char colli[MAP_AMX_NUM][255] = {
	"data/map/mapCollsion(仮).csv",
};

//マップチップイメージパス
#define MAP_CHIP_IMG_PATH	"data/map/Map仮.png"

Map::Map()
{
	for (int y = 0; y < MAP_NUM_Y; y++)
	{
		for (int x = 0; x < MAP_NUM_X; x++)
		{
			mapChipData[y][x] = -1;
			mapChipData2[y][x] = -1;
			mapCollisionData[y][x] = -1;
		}
	}
	
	mapNumX = 0;
	mapNumY = 0;
	//skyHandle = 0;
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
	LoadDivGraph(MAP_CHIP_IMG_PATH, MAPCHIP_MAX_NUM, MAPCHIP_NUM_X, MAPCHIP_NUM_Y, MAPCHIP_SIZE, MAPCHIP_SIZE, imgHandle);

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
		//DrawGraph(0, 0, skyHandle, true);

		break;

	case 1:	//プレイヤーの下に描画

		for (int y = 0; y < MAP_NUM_Y; y++)
		{
			for (int x = 0; x < MAP_NUM_X; x++)
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
			/*if (c == 'a')
			{
				break;
			}*/
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
				//当たっていたら以下


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
void Map::AllPosInit()
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