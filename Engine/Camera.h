#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//�J����
//-----------------------------------------------------------
namespace Camera
{
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize();

	//�X�V�i�r���[�s��쐬�j
	void Update();

	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(XMVECTOR position);
	void SetPosition(XMFLOAT3 position);

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(XMVECTOR target);
	void SetTarget(XMFLOAT3 target);

	//�ʒu���擾
	XMFLOAT3 GetPosition();

	//�œ_���擾
	XMFLOAT3 GetTarget();

	//�ʒu���擾
	XMVECTOR GetPositionVector();

	//�œ_���擾
	XMVECTOR GetTargetVector();
	
	//�r���[�s����擾
	XMMATRIX GetViewMatrix();

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix();

	//�r���{�[�h�p��]�s����擾
	XMMATRIX GetBillboardMatrix();

	/// <summary>
	/// 3�������W���Q�������W�ɕϊ�����
	/// </summary>
	/// <param name="pos3d">3D���W</param>
	/// <returns>2D���W</returns>
	XMFLOAT3 GetScreenPosition(XMFLOAT3 pos3d);

	/// <summary>
	/// MoveCam�̕ϐ���������������
	/// </summary>
	void MoveCamEnter();

	/// <summary>
	/// �J���������炩�Ɉړ�������
	/// </summary>
	/// <param name="lastPos">�ŏI�I�ȃJ�����|�W�V����</param>
	/// <param name="lastTar">�ŏI�I�ȃJ�����^�[�Q�b�g</param>
	/// <param name="moveRate">�ǂ̂��炢���炩�Ɉړ������邩(�ő�1.0f)</param>
	/// <returns>�ړ����I�������true</returns>
	bool MoveCam(XMFLOAT3 lastPos, XMFLOAT3 lastTar, float moveRate);

	float GetRateValue(float begin, float end, float rate);

};