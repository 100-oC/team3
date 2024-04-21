#pragma once

enum RESULT_IMAGE
{
	RESULT_GROUND,
	RESULT_WINNER1P,
	RESULT_WINNER2P,

	RESULT_MAX_NUM,
};

const char RESULT_IMAGE_PATH[RESULT_MAX_NUM][255] =
{
	"data/result/background.png",
	"data/result/winner1P.png",
	"data/result/winner2P.png",
};

class Result
{
private:
	int hndl[RESULT_MAX_NUM];

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
