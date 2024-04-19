//�E�B���h�E��\������v���O�����i�ЂȌ`�j

#include "DxLib.h"	//DX���C�u�����̃C���N���[�h
#include "Player/Player.h"
#include "Input/Input.h"

// define
#define	SCREEN_SIZE_X	1280	// X�����̉�ʃT�C�Y���w��
#define	SCREEN_SIZE_Y	720		// Y�����̉�ʃT�C�Y���w��

// Win32�A�v���P�[�V������ WinMain�֐� ����n�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//�E�B���h�E�̖��O��ς���
	SetMainWindowText("÷İ");

	//�E�B���h�E�̏�Ԃ�ݒ肷��
	ChangeWindowMode(true);

	// ��ʃT�C�Y��ύX
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1) {
		return -1;
	}

	//�`�悷��X�N���[����ݒ肷��
	SetDrawScreen(DX_SCREEN_BACK);

	//-----------------------------------------
	//��ԍŏ��ɂP�񂾂���鏈���������ɏ���


	///*
	// �v���C���[���
	struct Player {
		VECTOR pos = { 0.0f,0.0f };		// ���W
		VECTOR statepos = { 0.0f,0.0f };// �����n�_(���X�|�[���n�_���W)
		VECTOR speed = { 0.0f ,0.0f };	// �ړ����x
		int hndl;						// �摜�n���h��
		bool living_flg = true;			// �������Ă��邩�t���O(true�Ő���)
	};
	Player player[2];

	// �����n�i���j
	player[0].statepos = { 0.0f,0.0f };
	player[1].statepos = { 1240.0f,680.0f };

	player[0].pos = player[0].statepos;
	player[1].pos = player[1].statepos;
	//*/

	//-----------------------------------------

	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			//�G�X�P�[�v�L�[�������ꂽ��I��
			break;
		}

		//��ʂɕ\�����ꂽ���̂�������
		ClearDrawScreen();

		//-----------------------------------------
		//��������Q�[���̖{�̂��������ƂɂȂ�
		//-----------------------------------------



		// �y�v���C���[�����z
		// 1�v���C���[����
		if (CheckHitKey(KEY_INPUT_D) != 0)	// �E�ړ�
			player[0].speed.x += 0.5f;
		if (CheckHitKey(KEY_INPUT_A) != 0)	// ��
			player[0].speed.x -= 0.5f;
		if (CheckHitKey(KEY_INPUT_W) != 0)	// ��
			player[0].speed.y -= 0.5f;
		if (CheckHitKey(KEY_INPUT_S) != 0)	// ��
			player[0].speed.y += 0.5f;

		// 2�v���C���[����
		if (CheckHitKey(KEY_INPUT_RIGHT) != 0)	// �E�ړ�
			player[1].speed.x += 0.5f;
		if (CheckHitKey(KEY_INPUT_LEFT) != 0)	// ��
			player[1].speed.x -= 0.5f;
		if (CheckHitKey(KEY_INPUT_UP) != 0)		// ��
			player[1].speed.y -= 0.5f;
		if (CheckHitKey(KEY_INPUT_DOWN) != 0)	// ��
			player[1].speed.y += 0.5f;

		// �v���C���[�̍��W�X�V
		for (int i = 0; i < 2; i++) {
			player[i].pos.x += player[i].speed.x;
			player[i].pos.y += player[i].speed.y;
		}

		// �v���C���[�����x �ő�l,�ŏ��l�̐ݒ�
		for (int i = 0; i < 2; i++) {
			if (player[i].speed.x > 5.0f) {
				player[i].speed.x = 5.0f;
			}
			else if (player[i].speed.x < -5.0f) {
				player[i].speed.x = -5.0f;
			}

			if (player[i].speed.y > 5.0f) {
				player[i].speed.y = 5.0f;
			}
			else if (player[i].speed.y < -5.0f) {
				player[i].speed.y = -5.0f;
			}
		}

		// �v���C���[�����x����
		for (int i = 0; i < 2; i++) {
			player[i].speed.x -= player[i].speed.x / 32;
			player[i].speed.y -= player[i].speed.y / 32;
		}

		// �v���C���[���L�����ꂽ�Ƃ�
		for (int i = 0; i < 2; i++) {
			if (player[i].living_flg != true) {
				player[i].pos = player[i].statepos;
				player[i].living_flg = true;
			}
		}


		// �v���C���[�`��(��)
		if (player[0].living_flg == true) {
			DrawBox(player[0].pos.x, player[0].pos.y,
				player[0].pos.x + 40.0f, player[0].pos.y + 40.0f, GetColor(0, 255, 0), true);
		}
		if (player[1].living_flg == true) {
			DrawBox(player[1].pos.x, player[1].pos.y,
				player[1].pos.x + 40.0f, player[1].pos.y + 40.0f, GetColor(155, 0, 255), true);
		}

		//-----------------------------------------
		//���[�v�̏I����
		//�t���b�v�֐�
		ScreenFlip();

	}

	//-----------------------------------------
	//�Ō�ɂP�񂾂���鏈���������ɏ���



	//-----------------------------------------
	//DX���C�u�����̌㏈��
	DxLib_End();

	return 0;
}

