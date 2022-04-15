#include <DxLib.h>
#include <memory>
#include <chrono>
#include "Common/Vector2.h"

// ���܂�����ꂩ���邩��R�[�h�͂����܂ŋC�ɂ������菑����


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	Vector2 screenSize{ 640, 480 };
	SetWindowText("�v���g�^�C�v");
	ChangeWindowMode(true);
	SetGraphMode(screenSize.x_, screenSize.y_, 32);
	if (DxLib_Init()) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	Vector2Dbl pPos = { 20,20 }; // �v���C���[�̍��W
	Vector2Dbl ePos1 = { 300,300 }; // �G�l�~�[�̍��W
	double pSpeed = 150; // �v���C���[�̃X�s�[�h
	double eSpeed = 130; // �G�l�~�[�̃X�s�[�h
	int rot = 20; // �v���C���[�ƓG�̔��a
	double eTime = 0; // �G�l�~�[�������]������܂Ŏ���
	int erot = 0; // �����]��
	bool hit = false; // �v���C���[�ƃG�l�~�[�̓����蔻��
	bool App = true; // �G�l�~�[�̏o���Ə�����
	double AppTime = 0; // �G�l�~�[���o�����Ă����鎞��

	// �f���^�^�C���̎擾
	std::chrono::system_clock::time_point nowTime, oldTime;
	nowTime = std::chrono::system_clock::now();

	while (ProcessMessage() == 0)
	{
		// �f���^�^�C��
		double delta = 0.0;
		oldTime = nowTime;
		nowTime = std::chrono::system_clock::now();
		auto elTime = nowTime - oldTime;

		auto msec = std::chrono::duration_cast<std::chrono::microseconds>(elTime).count();
		delta = msec / 1000000.0;

		char keystate[256];
		GetHitKeyStateAll(keystate);
		// �v���C���[�̈ړ�
		if (keystate[KEY_INPUT_LEFT] && 0 < pPos.x_)
		{
			pPos.x_ -= pSpeed * delta;
		}
		if (keystate[KEY_INPUT_RIGHT] && screenSize.x_ > pPos.x_)
		{
			pPos.x_ += pSpeed * delta;
		}
		if (keystate[KEY_INPUT_UP] && 0 < pPos.y_)
		{
			pPos.y_ -= pSpeed * delta;
		}
		if (keystate[KEY_INPUT_DOWN] && screenSize.y_ > pPos.y_)
		{
			pPos.y_ += pSpeed * delta;
		}
		// �G�l�~�[�̈ړ�


		if (App)
		{
			if (AppTime <= 2)
			{
				AppTime += delta;
			}
			else
			{
				AppTime = 0;
				App = false;
			}
		}
		else
		{
			if (AppTime <= 5)
			{
				AppTime += delta;
			}
			else
			{
				AppTime = 0;
				App = true;
			}
		}

		// �����蔻��
		// �~�Ɖ~�̓����蔻��
		auto dx = pPos.x_ - ePos1.x_;
		auto dy = pPos.y_ - ePos1.y_;
		auto dr = dx * dx + dy * dy;
		auto dl = (rot + rot) * (rot + rot);

		if (dr < dl)
		{
			hit = true;
		}
		else
		{
			hit = false;
		}
		ClearDrawScreen();
		if (hit)
		{
			DrawCircle(static_cast<int>(pPos.x_), static_cast<int>(pPos.y_), rot, 0xff00ff, true);
		}
		else
		{
			DrawCircle(static_cast<int>(pPos.x_), static_cast<int>(pPos.y_), rot, 0x0000ff, true);
		}
		if (App)
		{
			DrawCircle(static_cast<int>(ePos1.x_), static_cast<int>(ePos1.y_), rot, 0xff0000, true);
		}

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}