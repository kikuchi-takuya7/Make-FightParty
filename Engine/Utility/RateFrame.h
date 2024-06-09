#pragma once
#include <cmath>
#include <DirectXMath.h>
#include <vector>
#include "../../Engine/GameObject.h"

using std::string;

//�ǂ̂悤�ɒl�𑝂₷���̎��
enum ADDTYPE {
	CONSTANT,		//�����ia�j
	ACCELERATION	//�����ia+a�j
};

/// <summary>
/// 0�`1�܂ł̒l���Ǘ�����N���X
/// </summary>
class RateFrame : public GameObject
{
public:

	//�R���X�g���N�^
	RateFrame(GameObject* parent);
	//�f�X�g���N�^
	~RateFrame();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �������
	/// </summary>
	void Release() override;

	/// <summary>
	/// ���[�g�����Z�b�g����
	/// </summary>
	void Reset();


	///////////////////////�A�N�Z�X�֐�///////////////////////

	/// <summary>
	/// ���`��Ԃ���ׂ̒l���Z�b�g����
	/// </summary>
	/// <param name="rate">1�t���[�����ɑ���������l(�O�`�P)</param>
	/// <param name="isUpdate">�l���X�V���邩�ۂ�</param>
	/// <param name="type">�l��ǉ�����p�^�[��</param>
	void SetData(float rate, bool isUpdate, ADDTYPE type);

	/// <summary>
	/// 1�t���[�����ɑ���������l(�O�`�P)���Z�b�g����
	/// </summary>
	/// <param name="rate">�ǂ̂��炢���������邩</param>
	void SetRate(float rate);

	/// <summary>
	/// �X�V���邩�ǂ����̃t���O��ݒ肷��
	/// </summary>
	/// <param name="isUpdate">�X�V���邩�ۂ�</param>
	void SetFlag(bool isUpdate);

	/// <summary>
	/// �w�肵���f�[�^�̌��݂̃t���[�����l��
	/// </summary>
	float GetNowFrame();

private:

	//1�t���[���ӂ�̑����l
	float rate_;

	//���Z�b�g�p��rate_�l
	float startRate_;

	//���݂̃t���[��
	float frame_;

	//�l���X�V���邩
	bool isUpdate_;

	//�l�𑝂₷�p�^�[��
	ADDTYPE type_;

};

