#pragma once

const int MAPCHIP_SIZE = 50;	// �}�b�v�`�b�v1���̃T�C�Y

//�}�b�v�`�b�v�̐�
const int mapChipMaxNum = 41;

const int MAP_AMX_NUM = 3;	//�}�b�v�̐�

// �}�b�v�N���X
class Map
{
private:
	//�}�b�v�`�b�v�̃n���h��
	int imgHandle[mapChipMaxNum];

	//�}�b�v�`�b�v�̐�
	static int mapNumX;
	static int mapNumY;

	//��̉摜�n���h��
	int skyHandle;

	// �t�@�C������̃}�b�v�f�[�^
	int** mapChipData2;

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

	// �`��
	void Draw(int type);
	

	// �t�@�C������̓ǂݍ���
	void ReadFile(int Map);

	void Fin();

	void SetCollision(int Map);
	
};

// �t�@�C������̃}�b�v�f�[�^
extern int** mapChipData;
//�����蔻��̔z�u�f�[�^	1=�n��,�@2=���̕�,�@3=�E�̕�
extern int** mapCollisionData;
extern Map mapData;

//�S�Ă̍��W�̐��݂̐e
void AllPosInit();