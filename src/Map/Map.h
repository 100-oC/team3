#pragma once

const int MAPCHIP_SIZE = 50;	// �}�b�v�`�b�v1���̃T�C�Y
const int MAPCHIP_MAX_NUM = 5;	// �}�b�v�`�b�v�̌�
const int MAPCHIP_NUM_X = 2;	// �}�b�v�`�b�vX�̌�
const int MAPCHIP_NUM_Y = 3;	// �}�b�v�`�b�vY�̌�

const int MAP_NUM_X = 30;	//X�̕\����
const int MAP_NUM_Y = 18;	//Y�̕\����

const int MAP_AMX_NUM = 3;	//�}�b�v�̐�

enum MAP_CHIP
{
	MAP_AREA1P,
	MAP_GROUND,
	MAP_AREA2P,
	MAP_LEAF,
	MAP_RIVER,
};

// �}�b�v�N���X
class Map
{
private:
	//�}�b�v�`�b�v�̃n���h��
	int imgHandle[MAPCHIP_MAX_NUM];

	//�}�b�v�`�b�v�̐�
	static int mapNumX;
	static int mapNumY;

	//��̉摜�n���h��	int skyHandle;

	// �t�@�C������̃}�b�v�f�[�^
	int mapChipData2[MAP_NUM_Y][MAP_NUM_X];
	
	int mapCollisionData[MAP_NUM_Y][MAP_NUM_X];

	//�w�i�̉摜�n���h��
	int backHandle[2][15];
	//�O�i�̉摜�n���h��
	int frontHandle;


public:

	Map();

	static int GetMapNumX();
	static int GetMapNumY();

	// ������
	void Init(int mapNum);

	void Step();

	// �`��F�w�i��0,�@�v���C���[��艺��1,�@player���と2
	void Draw(int type);
	

	// �t�@�C������̓ǂݍ���
	void ReadFile(int Map);

	void Fin();

	void SetCollision(int Map);

	//�S�Ă̍��W�̐��݂̐e
	void AllPosInit();
};

extern Map mapData;
extern int mapChipData[MAP_NUM_Y][MAP_NUM_X];

void CheckWallCollision(float& x, float& y, float w, float h, bool side,bool up);
bool CheckWallCollision(VECTOR plPos, float w, float h);
