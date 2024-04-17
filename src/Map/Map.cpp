#include<DxLib.h>
#include"Map.h"
#include"../MovePlayer/MovePlayer.h"
#include"../Collision/Collision.h"

int Map::mapNumX;
int Map::mapNumY;

//�����蔻��̔z�u�f�[�^	1=�n��,�@2=���̕�,�@3=�E�̕�
int** mapCollisionData;
// �t�@�C������̃}�b�v�f�[�^
int** mapChipData;

int mapPlx;
int mapPly;

//�}�b�v�`�b�v�̃t�@�C���p�X
char map[MAP_AMX_NUM][255] = {
	"data/map/.csv",
};
char colli[MAP_AMX_NUM][255] = {
	"data/map/.csv",
};

//�}�b�v�`�b�v�C���[�W�p�X
#define MAP_CHIP_IMG_PATH	"data/map/mapchip1_50�~50_41.png"

Map::Map()
{
	mapChipData = 0;
	mapChipData2 = 0;
	mapNumX = 0;
	mapNumY = 0;
	skyHandle = 0;
	// �R���X�g���N�^�̏���
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
	//�}�b�v�`�b�v�̓ǂݍ���
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
		//��̕`��
		DrawGraph(0, 0, skyHandle, true);

		break;

	case 1:	//�v���C���[�̉��ɕ`��

		for (int y = 0; y < mapNumY; y++)
		{
			for (int x = 0; x < mapNumX; x++)
			{
				// �u���b�N��`��
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

	case 2:	//�v���C���[�̏�ɕ`��

		for (int y = 0; y < mapNumY; y++)
		{
			for (int x = 0; x < mapNumX; x++)
			{
				// �u���b�N��`��
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

// �t�@�C������̓ǂݍ���
void Map::ReadFile(int Map)
{
	FILE* fp;
	fopen_s(&fp, map[Map], "r");

	if (fp != NULL)
	{
		mapNumX = 0;
		mapNumY = 0;

		//csv�ɓ����Ă���s�������擾
		fscanf_s(fp, "%d", &mapNumX);
		fgetc(fp);
		fscanf_s(fp, "%d", &mapNumY);
		fgetc(fp);

		//Y�̃������m��
		mapChipData = new int* [mapNumY];
		mapChipData2 = new int* [mapNumY];

		mapCollisionData = new int* [mapNumY];

		for (int i = 0; i < mapNumY; i++)
		{
			//X�̃������m��
			mapChipData[i] = new int[mapNumX];
			mapChipData2[i] = new int[mapNumX];

			mapCollisionData[i] = new int[mapNumX];
		}

		int mapIndexX = 0;
		int mapIndexY = 0;

		//���C���[�P�ǂݍ���
		while (true)
		{
			// ���l������ǂݍ���
			fscanf_s(fp, "%d", &mapChipData[mapIndexY][mapIndexX]);
			mapIndexX++;

			// �u,�v���΂����߂ɓǂݍ��݂����s
			char c = fgetc(fp);

			// EOF�̏ꍇ�͓ǂݍ��ݏI��
			if (c == EOF)
			{
				break;
			}
			if (c == 'a')
			{
				break;
			}
			// ���s�R�[�h�̏ꍇ�͕ۑ����ύX����
			else if (c == '\n')
			{
				mapIndexY++;
				mapIndexX = 0;
			}
		}

		mapIndexX = 0;
		mapIndexY = 0;

		//���C���[�Q�ǂݍ���
		while (true)
		{
			// ���l������ǂݍ���
			fscanf_s(fp, "%d", &mapChipData2[mapIndexY][mapIndexX]);
			mapIndexX++;

			// �u,�v���΂����߂ɓǂݍ��݂����s
			char c = fgetc(fp);

			// EOF�̏ꍇ�͓ǂݍ��ݏI��
			if (c == EOF)
			{
				break;
			}
			// ���s�R�[�h�̏ꍇ�͕ۑ����ύX����
			else if (c == '\n')
			{
				mapIndexY++;
				mapIndexX = 0;
			}
		}
		fclose(fp);
	}
}

//�}�b�v�㏈��
void Map::Fin()
{
	//�������̊J��
	//���X���폜
	for (int i = 0; i < mapNumY; i++)
	{
		delete[] mapChipData[i];
		mapChipData[i] = 0;
	}
	//Y�����
	delete[] mapChipData;
	mapChipData = 0;
}

//�����蔻��̓ǂݍ���
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
			// ���l������ǂݍ���
			fscanf_s(fp1, "%d", &mapCollisionData[mapIndexY][mapIndexX]);
			mapIndexX++;

			// �u,�v���΂����߂ɓǂݍ��݂����s
			char c = fgetc(fp1);

			// EOF�̏ꍇ�͓ǂݍ��ݏI��
			if (c == EOF)
			{
				break;
			}
			// ���s�R�[�h�̏ꍇ�͕ۑ����ύX����
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

//�ǂ̓����蔻��F�����蔻�����肽����̍��W�Ɖ����A�c��
void CheckWallCollision
(float& x, float& y, float w, float h)
{
	float mapX = 0;
	float mapY = 0;

	for (int indexY = 0; indexY < Map::GetMapNumY(); indexY++)
	{
		for (int indexX = 0; indexX < Map::GetMapNumX(); indexX++)
		{
			//�}�b�v�̕ϐ������
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

//�S�Ă̍��W�̐��݂̐e
void AllPosInit()
{
	/*====================================================
�@	�����蔻����i�[�����ϐ�����X�|�[���ʒu�����
	======================================================*/

	for (int indexY = 0; indexY < Map::GetMapNumY(); indexY++)
	{
		for (int indexX = 0; indexX < Map::GetMapNumX(); indexX++)
		{
			
			switch (mapCollisionData[indexY][indexX])
			{

			//10�ɉ�������
			case 10: {

				//�g����
				/*Goal::SetPosX((float)indexX * MAPCHIP_SIZE + GOAL_SIZE_X / 2);
				Goal::SetPosY((float)indexY * MAPCHIP_SIZE - GOAL_SIZE_Y);*/

				break; }

			default:
				break;
			} 
		}
	}
}