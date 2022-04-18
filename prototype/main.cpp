#include <DxLib.h>
#include <memory>
#include <chrono>
//#include "Common/Geometry.h"
#include "Common/Vector2.h"

// ���܂�����ꂩ���邩��R�[�h�͂����܂ŋC�ɂ������菑����

//�J�v�Z��
struct Box {
	Vector2Dbl posA; //�[�_A
	Vector2Dbl posB; //�[�_B
	Box() : posA(0, 0), posB(0, 0) {}
	Box(const Vector2Dbl& a, const Vector2Dbl& b) :
		posA(a), posB(b) {}
	Box(float ax, float ay, float bx, float by) :
		posA(ax, ay), posB(bx, by) {}
};

// Box�`��
//void DrawBox(const Capsule& box, unsigned int color)
//{
//	auto v = box.posB - box.posA;
//
//	auto angle = atan2(v.x, v.y) - DX_PI_F / 2.0f;
//	//�Ȃ񂩌덷�����邽��1�𑫂��Ă���
//	auto w = cos(angle) * (20 + 1.0f);
//	auto h = sin(angle) * (20 + 1.0f);
//
//	DrawQuadrangle(
//		box.posA.x - w, box.posA.y - h,
//		box.posB.x - w, box.posB.y - h,
//		box.posB.x + w, box.posB.y + h,
//		box.posA.x + w, box.posA.y + h, color, true);
//}

//// �~�Ǝl�p�̓����蔻��
//bool IsHit(const Box& box, const Vector2Dbl& Pos, const int& rot)
//{
//	auto Tx = Pos.x_ - box.posA.x_;
//	auto Ty = Pos.y_ - box.posA.y_;
//	auto Lx = box.posB.x_ - box.posA.x_;
//	auto Ly = box.posB.y_ - box.posA.y_;
//	auto dot = Dot(Tx, Ty, Lx, Ly);
//	auto s = dot/
//}

// �~�Ɖ~�̓����蔻��
bool CircleHit(Vector2Dbl pPos, Vector2Dbl ePos, int rot)
{
	auto dx = pPos.x_ - ePos.x_;
	auto dy = pPos.y_ - ePos.y_;
	auto dr = dx * dx + dy * dy;
	auto dl = (rot + rot) * (rot + rot);
	if (dr < dl)
	{
		return true;
	}
	return false;
}

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

	srand(static_cast<unsigned int>(time(NULL)));
	
	Vector2Dbl pPos = { 20,20 }; // �v���C���[�̍��W
	Vector2Dbl ePos1 = { 300,300 }; // �G�l�~�[�̍��W
	//Capsule box(20,Vector2Dbl{ 20,100 }, Vector2Dbl{ 20,400 });
	double pSpeed = 150; // �v���C���[�̃X�s�[�h
	double eSpeed = 130; // �G�l�~�[�̃X�s�[�h
	int rot = 20; // �v���C���[�ƓG�̔��a
	double eTime = 0; // �G�l�~�[�������]������܂Ŏ���
	int erot = 1; // �����]��
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
		if (keystate[KEY_INPUT_LEFT] && 0 < pPos.x_ - rot)
		{
			pPos.x_ -= pSpeed * delta;
		}
		if (keystate[KEY_INPUT_RIGHT] && screenSize.x_ > pPos.x_ + rot)
		{
			pPos.x_ += pSpeed * delta;
		}
		if (keystate[KEY_INPUT_UP] && 0 < pPos.y_ - rot)
		{
			pPos.y_ -= pSpeed * delta;
		}
		if (keystate[KEY_INPUT_DOWN] && screenSize.y_ > pPos.y_ + rot)
		{
			pPos.y_ += pSpeed * delta;
		}
		// �G�l�~�[�̈ړ�
		if (eTime >= 1.5)
		{
			if (erot == 0)
			{
				erot = rand() % 3;
				erot += 1;
				eTime = 0;
			}
			if (erot == 1)
			{
				erot = rand() % 4;
				if (erot == 1)
				{
					int ran = rand() % 2;
					erot += (ran + 1);
				}
				eTime = 0;
			}
			if (erot == 2)
			{
				erot = rand() % 4;
				if (erot == 2)
				{
					int ran = rand() % 2;
					erot -= (ran + 1);
				}
				eTime = 0;
			}
			if (erot == 3)
			{
				erot = rand() % 3;
				eTime = 0;
			}
		}
		eTime += delta;

		if (erot == 0 && 0 < ePos1.x_ -rot)
		{
			ePos1.x_ -= eSpeed * delta;
		}
		if (erot == 1 && screenSize.x_ > ePos1.x_ + rot)
		{
			ePos1.x_ += eSpeed * delta;
		}
		if (erot == 2 && 0 < ePos1.y_ - rot)
		{
			ePos1.y_ -= eSpeed * delta;
		}
		if (erot == 3 && screenSize.y_ > ePos1.y_ + rot)
		{
			ePos1.y_ += eSpeed * delta;
		}


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

		hit = CircleHit(pPos, ePos1, rot);
		// �����蔻��
		ClearDrawScreen();
		//DrawBox(box, 0x00ff00);
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

