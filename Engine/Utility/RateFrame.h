#pragma once
#include <cmath>
#include <DirectXMath.h>
#include <vector>
#include <map>
#include <string>

using std::string;
using std::map;

/// <summary>
/// ���`�⊮�p�̒l�����Ǘ�����N���X
/// </summary>
namespace RateFrame
{

	/// <summary>
	/// �t���[�����̃f�[�^
	/// </summary>
	struct RateData {

		//1�t���[���ӂ�̑����l
		float rate;

		//���݂̃t���[��
		float frame;

		//�l���X�V���邩
		bool isUpdate;

		RateData() {
			rate = 0.0f;
			frame = 0.0f;
			isUpdate = false;
		}

		RateData(int r, bool is) {
			rate = r;
			frame = 0.0f;
			isUpdate = is;
		}

	};

	//���`��Ԃ��邽�߂̏���ۑ�
	extern map<string, RateData> data;

	/// <summary>
	/// ���`��Ԃ���ׂ̒l���Z�b�g����
	/// </summary>
	/// <param name="s">�ۑ��������f�[�^�̖��O</param>
	/// <param name="rate">1�t���[�����ɑ���������l(�O�`�P)</param>
	/// <param name="isUpdate">�l���X�V���邩�ۂ�</param>
	void SetData(string s, float rate, bool isUpdate);

	/// <summary>
	/// �X�V���邩�ǂ�����ݒ肷��
	/// </summary>
	/// <param name="s">�ύX�������f�[�^�̖��O</param>
	/// <param name="isUpdate">�X�V���邩�ۂ�</param>
	void SetFlag(string s, bool isUpdate);

	/// <summary>
	/// �w�肵���f�[�^�̌��݂̃t���[�����l��
	/// </summary>
	/// <param name="s">�~�����t���[�����i�[���Ă�f�[�^�̖��O</param>
	float GetNowFrame(string s);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �ʂ̉������
	/// </summary>
	/// <param name="s">���������data</param>
	void Release(string s);

	/// <summary>
	/// �������
	/// </summary>
	void Release();

};

