#include "VFXData.h"

namespace HitEffect {
	std::string FILENAME = "VFX/cloudA.png";			//�摜�t�@�C����
	XMFLOAT3 POSITIONRND = XMFLOAT3(0.5f, 0.5f, 0.5f);	//�ʒu�̌덷
	XMFLOAT3 DIRECTIONRND = XMFLOAT3(90, 90, 90);		//�ړ������̌덷�i�e���̊p�x�j
	float	 SPEED = 0.2f;			//1�t���[���̑��x
	float	 SPEEDRND = ZERO;		//���x�덷�i0�`1�j
	float	 ACCEL = 1.0f;			//�����x
	float	 GRAVITY = 0.0f;		//�d��
	XMFLOAT4 COLOR = XMFLOAT4(1, 1, ZERO, 1);					//�F�iRGBA 0�`1�j
	XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, -0.03f, ZERO, -0.02f);	//�F�̕ω���
	XMFLOAT3 ROTATE = ZERO_FLOAT3;		//�e���ł̊p�x
	XMFLOAT3 ROTATERND = ZERO_FLOAT3;	//�p�x�덷
	XMFLOAT3 SPIN = ZERO_FLOAT3;		//��]���x
	XMFLOAT2 SIZE = XMFLOAT2(0.3, 0.3f);			//�T�C�Y
	XMFLOAT2 SIZERND = XMFLOAT2(0.4, 0.4f);			//�T�C�Y�덷�i0�`1�j
	XMFLOAT2 SCALE = XMFLOAT2(0.9f, 0.9f);			//1�t���[���̊g�嗦
	DWORD	 LIFETIME = 15;		//�p�[�e�B�N���̎����i�t���[�����j
	DWORD	 DELAY = ZERO;		//���t���[�������Ƀp�[�e�B�N���𔭐������邩
	DWORD	 NUMBER = 40;		//1�x�ɏo���p�[�e�B�N����
	bool	 ISBILLBOARD = true;		//�r���{�[�h���ǂ���
}

namespace DieEffect {
	namespace Explosion {
		std::string FILENAME = "VFX/cloudA.png";				//�摜�t�@�C����	
		XMFLOAT3 POSITIONRND = ZERO_FLOAT3;						//�ʒu�̌덷
		XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1.0f, ZERO);		//�ړ�����
		XMFLOAT3 DIRECTIONRND = XMFLOAT3(90, 90, 90);			//�ړ������̌덷�i�e���̊p�x�j
		float	 SPEED = 0.1f;			//1�t���[���̑��x
		float	 SPEEDRND = 0.8f;		//���x�덷�i0�`1�j
		float	 ACCEL = 1.0f;			//�����x
		float	 GRAVITY = 0.0f;		//�d��
		XMFLOAT4 COLOR = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);					//�F�iRGBA 0�`1�j
		XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, -1.0 / 20, ZERO, -1.0 / 20);	//�F�̕ω���
		XMFLOAT3 ROTATE = ZERO_FLOAT3;			//�e���ł̊p�x
		XMFLOAT3 ROTATERND = ZERO_FLOAT3;		//�p�x�덷
		XMFLOAT3 SPIN = ZERO_FLOAT3;			//��]���x
		XMFLOAT2 SIZE = XMFLOAT2(1.2f, 1.2f);			//�T�C�Y
		XMFLOAT2 SIZERND = XMFLOAT2(0.4, 0.4f);			//�T�C�Y�덷�i0�`1�j
		XMFLOAT2 SCALE = XMFLOAT2(1.05f, 1.05f);		//1�t���[���̊g�嗦
		DWORD	 LIFETIME = 30;		//�p�[�e�B�N���̎����i�t���[�����j
		DWORD	 DELAY = ZERO;		//���t���[�������Ƀp�[�e�B�N���𔭐������邩
		DWORD	 NUMBER = 80;		//1�x�ɏo���p�[�e�B�N����
		bool	 ISBILLBOARD = true;		//�r���{�[�h���ǂ���
	}
	namespace FireSpark {
		std::string FILENAME = "VFX/cloudA.png";			//�摜�t�@�C����
		XMFLOAT3 POSITIONRND = XMFLOAT3(0.5f, ZERO, 0.5f);	//�ʒu�̌덷
		XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1, ZERO);		//�ړ�����
		XMFLOAT3 DIRECTIONRND = XMFLOAT3(90, 90, 90);		//�ړ������̌덷�i�e���̊p�x�j
		float	 SPEED = 0.25f;			//1�t���[���̑��x
		float	 SPEEDRND = 1.0f;		//���x�덷�i0�`1�j
		float	 ACCEL = 0.93f;			//�����x
		float	 GRAVITY = 0.003f;		//�d��
		XMFLOAT4 COLOR = XMFLOAT4(1, 1, 0.1f, 1);					//�F�iRGBA 0�`1�j
		XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, ZERO, ZERO, ZERO);		//�F�̕ω���
		XMFLOAT3 ROTATE = ZERO_FLOAT3;		//�e���ł̊p�x
		XMFLOAT3 ROTATERND = ZERO_FLOAT3;	//�p�x�덷
		XMFLOAT3 SPIN = ZERO_FLOAT3;		//��]���x
		XMFLOAT2 SIZE = XMFLOAT2(0.1f, 0.1f);				//�T�C�Y
		XMFLOAT2 SIZERND = XMFLOAT2(0.4f, 0.4f);			//�T�C�Y�덷�i0�`1�j
		XMFLOAT2 SCALE = XMFLOAT2(0.99f, 0.99f);			//1�t���[���̊g�嗦
		DWORD	 LIFETIME = 100;		//�p�[�e�B�N���̎����i�t���[�����j
		DWORD	 DELAY = ZERO;			//���t���[�������Ƀp�[�e�B�N���𔭐������邩
		DWORD	 NUMBER = 80;			//1�x�ɏo���p�[�e�B�N����
		bool	 ISBILLBOARD = true;			//�r���{�[�h���ǂ���
	}
	
}

namespace VictoryEffect {
	namespace Fire {
		std::string FILENAME = "VFX/cloudA.png";			//�摜�t�@�C����
		XMFLOAT3 POSITIONRND = XMFLOAT3(0.1f, 0, 0.1f);		//�ʒu�̌덷
		XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1, ZERO);		//�ړ�����
		XMFLOAT3 DIRECTIONRND = ZERO_FLOAT3;		//�ړ������̌덷�i�e���̊p�x�j
		float	 SPEED = 0.01f;			//1�t���[���̑��x
		float	 SPEEDRND = ZERO;		//���x�덷�i0�`1�j
		float	 ACCEL = 1.0f;			//�����x
		float	 GRAVITY = -0.002f;		//�d��
		XMFLOAT4 COLOR = XMFLOAT4(1, 1, ZERO, 1);					//�F�iRGBA 0�`1�j
		XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, -0.03f, ZERO, -0.02f);		//�F�̕ω���
		XMFLOAT3 ROTATE = ZERO_FLOAT3;		//�e���ł̊p�x
		XMFLOAT3 ROTATERND = ZERO_FLOAT3;	//�p�x�덷
		XMFLOAT3 SPIN = ZERO_FLOAT3;		//��]���x
		XMFLOAT2 SIZE = XMFLOAT2(1.5f, 1.5f);				//�T�C�Y
		XMFLOAT2 SIZERND = XMFLOAT2(0.4f, 0.4f);			//�T�C�Y�덷�i0�`1�j
		XMFLOAT2 SCALE = XMFLOAT2(1.01f, 1.01f);			//1�t���[���̊g�嗦
		DWORD	 LIFETIME = 60;		//�p�[�e�B�N���̎����i�t���[�����j
		DWORD	 DELAY = ZERO;			//���t���[�������Ƀp�[�e�B�N���𔭐������邩
		DWORD	 NUMBER = 1;			//1�x�ɏo���p�[�e�B�N����
		bool	 ISBILLBOARD = true;			//�r���{�[�h���ǂ���
	}
	namespace FireSpark {
		std::string FILENAME = "VFX/cloudA.png";			//�摜�t�@�C����
		XMFLOAT3 POSITIONRND = XMFLOAT3(0.8f, ZERO, 0.8f);		//�ʒu�̌덷
		XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1, ZERO);		//�ړ�����
		XMFLOAT3 DIRECTIONRND = XMFLOAT3(10, 10, 10);		//�ړ������̌덷�i�e���̊p�x�j
		float	 SPEED = 0.1f;			//1�t���[���̑��x
		float	 SPEEDRND = ZERO;		//���x�덷�i0�`1�j
		float	 ACCEL = 1.0f;			//�����x
		float	 GRAVITY = ZERO;		//�d��
		XMFLOAT4 COLOR = XMFLOAT4(1, 1, ZERO, 1);					//�F�iRGBA 0�`1�j
		XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, -0.03f, ZERO, -0.02f);		//�F�̕ω���
		XMFLOAT3 ROTATE = ZERO_FLOAT3;		//�e���ł̊p�x
		XMFLOAT3 ROTATERND = ZERO_FLOAT3;	//�p�x�덷
		XMFLOAT3 SPIN = ZERO_FLOAT3;		//��]���x
		XMFLOAT2 SIZE = XMFLOAT2(0.2f, 0.2f);				//�T�C�Y
		XMFLOAT2 SIZERND = XMFLOAT2(0.4f, 0.4f);			//�T�C�Y�덷�i0�`1�j
		XMFLOAT2 SCALE = XMFLOAT2(0.95, 0.95);;			//1�t���[���̊g�嗦
		DWORD	 LIFETIME = 120;		//�p�[�e�B�N���̎����i�t���[�����j
		DWORD	 DELAY = ZERO;			//���t���[�������Ƀp�[�e�B�N���𔭐������邩
		DWORD	 NUMBER = 3;			//1�x�ɏo���p�[�e�B�N����
		bool	 ISBILLBOARD = true;			//�r���{�[�h���ǂ���
	}
}

namespace FiringEffect {
	std::string FILENAME = "VFX/cloudA.png";			//�摜�t�@�C����
	XMFLOAT3 POSITIONRND = XMFLOAT3(0.1f, ZERO, 0.1f);		//�ʒu�̌덷
	XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1, ZERO);		//�ړ�����
	XMFLOAT3 DIRECTIONRND = XMFLOAT3(ZERO, ZERO, ZERO);		//�ړ������̌덷�i�e���̊p�x�j
	float	 SPEED = 0.1f;			//1�t���[���̑��x
	float	 SPEEDRND = ZERO;		//���x�덷�i0�`1�j
	float	 ACCEL = 0.98f;			//�����x
	float	 GRAVITY = ZERO;		//�d��
	XMFLOAT4 COLOR = XMFLOAT4(1, 1, 1, 0.2);					//�F�iRGBA 0�`1�j
	XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, ZERO, ZERO, -0.002f);		//�F�̕ω���
	XMFLOAT3 ROTATE = ZERO_FLOAT3;		//�e���ł̊p�x
	XMFLOAT3 ROTATERND = ZERO_FLOAT3;	//�p�x�덷
	XMFLOAT3 SPIN = XMFLOAT3(ZERO, ZERO, 0.1f);		//��]���x
	XMFLOAT2 SIZE = XMFLOAT2(2, 2);				//�T�C�Y
	XMFLOAT2 SIZERND = XMFLOAT2(0.4f, 0.4f);			//�T�C�Y�덷�i0�`1�j
	XMFLOAT2 SCALE = XMFLOAT2(1.01f, 1.01f);;			//1�t���[���̊g�嗦
	DWORD	 LIFETIME = 30;		//�p�[�e�B�N���̎����i�t���[�����j
	DWORD	 DELAY = ZERO;			//���t���[�������Ƀp�[�e�B�N���𔭐������邩
	DWORD	 NUMBER = 2;			//1�x�ɏo���p�[�e�B�N����
	bool	 ISBILLBOARD = true;			//�r���{�[�h���ǂ���
}