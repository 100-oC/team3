#pragma once

const int TIME_LIMIT = 60;	//1�Q�[���̐�������(�b)
const char TIME_IMAGE_PATH[255] = "data/play/number_44�~64.png";	//�摜�p�X

class TimeLimit
{
private:
	int imageHandle[10];	//�摜�n���h��

	float timeCount;	//���Ԍv��
	int currentTime;	//���݂̎���

	bool start;

public:
	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`��
	void Draw(int type=0);

	//�I������
	void Fin();

	bool GetStart() { return start; }
};

//extern int currentTime;	//���݂̎���