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
	
	//�w�i�̃t�F�[�h�C��
	void GroundFadeIn();
	//��ʍ��
	void MakeTitle();
	//���͑҂�
	void StartGame();

	//�^�C�g������
	void MakeFinish();

public:
	//������
	void Init();
	//�ʏ폈��
	void Step();
	//�`�揈��
	void Draw();
	//�I������
	void Fin();
};
