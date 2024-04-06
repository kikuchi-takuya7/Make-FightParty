#pragma once
#include "../Engine/Direct3D.h"
#include "../Engine/Global.h"
#include<string>

namespace HitEffect {
	extern std::string FILENAME;	//�摜�t�@�C����
	extern XMFLOAT3 POSITIONRND;	//�ʒu�̌덷
	extern XMFLOAT3 DIRECTIONRND;	//�ړ������̌덷�i�e���̊p�x�j
	extern float	SPEED;			//1�t���[���̑��x
	extern float	SPEEDRND;		//���x�덷�i0�`1�j
	extern float	ACCEL;			//�����x
	extern float	GRAVITY;		//�d��
	extern XMFLOAT4 COLOR;			//�F�iRGBA 0�`1�j
	extern XMFLOAT4 DELTACOLOR;		//�F�̕ω���
	extern XMFLOAT3 ROTATE;			//�e���ł̊p�x
	extern XMFLOAT3 ROTATERND;		//�p�x�덷
	extern XMFLOAT3 SPIN;			//��]���x
	extern XMFLOAT2 SIZE;			//�T�C�Y
	extern XMFLOAT2 SIZERND;		//�T�C�Y�덷�i0�`1�j
	extern XMFLOAT2 SCALE;			//1�t���[���̊g�嗦
	extern DWORD	LIFETIME;		//�p�[�e�B�N���̎����i�t���[�����j
	extern DWORD	DELAY;			//���t���[�������Ƀp�[�e�B�N���𔭐������邩
	extern DWORD	NUMBER;			//1�x�ɏo���p�[�e�B�N����
	extern bool	 ISBILLBOARD;		//�r���{�[�h���ǂ���
}

namespace DieEffect {
	namespace Explosion {
		extern std::string FILENAME;	//�摜�t�@�C����
		extern XMFLOAT3 POSITIONRND;	//�ʒu�̌덷
		extern XMFLOAT3 DIRECTION;		//�ړ�����
		extern XMFLOAT3 DIRECTIONRND;	//�ړ������̌덷�i�e���̊p�x�j
		extern float	SPEED;			//1�t���[���̑��x
		extern float	SPEEDRND;		//���x�덷�i0�`1�j
		extern float	ACCEL;			//�����x
		extern float	GRAVITY;		//�d��
		extern XMFLOAT4 COLOR;			//�F�iRGBA 0�`1�j
		extern XMFLOAT4 DELTACOLOR;		//�F�̕ω���
		extern XMFLOAT3 ROTATE;			//�e���ł̊p�x
		extern XMFLOAT3 ROTATERND;		//�p�x�덷
		extern XMFLOAT3 SPIN;			//��]���x
		extern XMFLOAT2 SIZE;			//�T�C�Y
		extern XMFLOAT2 SIZERND;		//�T�C�Y�덷�i0�`1�j
		extern XMFLOAT2 SCALE;			//1�t���[���̊g�嗦
		extern DWORD	LIFETIME;		//�p�[�e�B�N���̎����i�t���[�����j
		extern DWORD	DELAY;			//���t���[�������Ƀp�[�e�B�N���𔭐������邩
		extern DWORD	NUMBER;			//1�x�ɏo���p�[�e�B�N����
		extern bool	 ISBILLBOARD;		//�r���{�[�h���ǂ���
	}
	namespace FireSpark {
		extern std::string FILENAME;	//�摜�t�@�C����
		extern XMFLOAT3 POSITIONRND;	//�ʒu�̌덷
		extern XMFLOAT3 DIRECTION;		//�ړ�����
		extern XMFLOAT3 DIRECTIONRND;	//�ړ������̌덷�i�e���̊p�x�j
		extern float	SPEED;			//1�t���[���̑��x
		extern float	SPEEDRND;		//���x�덷�i0�`1�j
		extern float	ACCEL;			//�����x
		extern float	GRAVITY;		//�d��
		extern XMFLOAT4 COLOR;			//�F�iRGBA 0�`1�j
		extern XMFLOAT4 DELTACOLOR;		//�F�̕ω���
		extern XMFLOAT3 ROTATE;			//�e���ł̊p�x
		extern XMFLOAT3 ROTATERND;		//�p�x�덷
		extern XMFLOAT3 SPIN;			//��]���x
		extern XMFLOAT2 SIZE;			//�T�C�Y
		extern XMFLOAT2 SIZERND;		//�T�C�Y�덷�i0�`1�j
		extern XMFLOAT2 SCALE;			//1�t���[���̊g�嗦
		extern DWORD	LIFETIME;		//�p�[�e�B�N���̎����i�t���[�����j
		extern DWORD	DELAY;			//���t���[�������Ƀp�[�e�B�N���𔭐������邩
		extern DWORD	NUMBER;			//1�x�ɏo���p�[�e�B�N����
		extern bool	 ISBILLBOARD;		//�r���{�[�h���ǂ���
	}

}

namespace VictoryEffect {
	namespace Fire {
		extern std::string FILENAME;	//�摜�t�@�C����
		extern XMFLOAT3 POSITIONRND;	//�ʒu�̌덷
		extern XMFLOAT3 DIRECTION;		//�ړ�����
		extern XMFLOAT3 DIRECTIONRND;	//�ړ������̌덷�i�e���̊p�x�j
		extern float	SPEED;			//1�t���[���̑��x
		extern float	SPEEDRND;		//���x�덷�i0�`1�j
		extern float	ACCEL;			//�����x
		extern float	GRAVITY;		//�d��
		extern XMFLOAT4 COLOR;			//�F�iRGBA 0�`1�j
		extern XMFLOAT4 DELTACOLOR;		//�F�̕ω���
		extern XMFLOAT3 ROTATE;			//�e���ł̊p�x
		extern XMFLOAT3 ROTATERND;		//�p�x�덷
		extern XMFLOAT3 SPIN;			//��]���x
		extern XMFLOAT2 SIZE;			//�T�C�Y
		extern XMFLOAT2 SIZERND;		//�T�C�Y�덷�i0�`1�j
		extern XMFLOAT2 SCALE;			//1�t���[���̊g�嗦
		extern DWORD	LIFETIME;		//�p�[�e�B�N���̎����i�t���[�����j
		extern DWORD	DELAY;			//���t���[�������Ƀp�[�e�B�N���𔭐������邩
		extern DWORD	NUMBER;			//1�x�ɏo���p�[�e�B�N����
		extern bool	 ISBILLBOARD;		//�r���{�[�h���ǂ���
	}
	namespace FireSpark {
		extern std::string FILENAME;	//�摜�t�@�C����
		extern XMFLOAT3 POSITIONRND;	//�ʒu�̌덷
		extern XMFLOAT3 DIRECTION;		//�ړ�����
		extern XMFLOAT3 DIRECTIONRND;	//�ړ������̌덷�i�e���̊p�x�j
		extern float	SPEED;			//1�t���[���̑��x
		extern float	SPEEDRND;		//���x�덷�i0�`1�j
		extern float	ACCEL;			//�����x
		extern float	GRAVITY;		//�d��
		extern XMFLOAT4 COLOR;			//�F�iRGBA 0�`1�j
		extern XMFLOAT4 DELTACOLOR;		//�F�̕ω���
		extern XMFLOAT3 ROTATE;			//�e���ł̊p�x
		extern XMFLOAT3 ROTATERND;		//�p�x�덷
		extern XMFLOAT3 SPIN;			//��]���x
		extern XMFLOAT2 SIZE;			//�T�C�Y
		extern XMFLOAT2 SIZERND;		//�T�C�Y�덷�i0�`1�j
		extern XMFLOAT2 SCALE;			//1�t���[���̊g�嗦
		extern DWORD	LIFETIME;		//�p�[�e�B�N���̎����i�t���[�����j
		extern DWORD	DELAY;			//���t���[�������Ƀp�[�e�B�N���𔭐������邩
		extern DWORD	NUMBER;			//1�x�ɏo���p�[�e�B�N����
		extern bool	 ISBILLBOARD;		//�r���{�[�h���ǂ���
	}

}