#pragma once
#include <cmath>
#include <DirectXMath.h>
#include <vector>
#include <map>
#include <string>

using std::string;
using std::map;

/// <summary>
/// �t���[�����̃f�[�^
/// </summary>
struct RateData {

	//1�t���[���ӂ�̑����l
	float rate;

	//���݂̃t���[��
	float flame;

	//�l���X�V���邩
	bool isUpdate;

	RateData() {
		rate = 0.0f;
		flame = 0.0f;
		isUpdate = false;
	}

	RateData(int r , bool is) {
		rate = r;
		flame = 0.0f;
		isUpdate = is;
	}

};

namespace LinearInterpolation
{
	//���`��Ԃ��邽�߂̏���ۑ�
	map<string, RateData> mp;

	/// <summary>
	/// ���`��Ԃ���ׂ̒l���Z�b�g����
	/// </summary>
	/// <param name="s">�ۑ��������f�[�^�̖��O</param>
	/// <param name="rate">1�t���[�����ɑ���������l(�O�`�P)</param>
	/// <param name="isUpdate">�l���X�V���邩�ۂ�</param>
	void SetData(string s, float rate, bool isUpdate) { mp.insert(std::make_pair(s, RateData(rate, isUpdate))); }

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �������
	/// </summary>
	/// <param name="s">���������</param>
	void Release(string s);

};

