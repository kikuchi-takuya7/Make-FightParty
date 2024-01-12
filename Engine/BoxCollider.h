#pragma once
#include "Collider.h"


//-----------------------------------------------------------
//���^�̓����蔻��
//-----------------------------------------------------------
class BoxCollider :	public Collider
{
	//Collider�N���X��private�����o�ɃA�N�Z�X�ł���悤�ɂ���
	friend class Collider;

public:

	/// <summary>
	/// �R���X�g���N�^�i�����蔻��̍쐬�j
	/// </summary>
	/// <param name="basePos">�����蔻��̒��S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j</param>
	/// <param name="size">�����蔻��̃T�C�Y�i���A�����A���s���j</param>
	/// <param name="rotate">center�����]������p�x</param>
	BoxCollider(XMFLOAT3 basePos, XMFLOAT3 size, XMFLOAT3 rotate);

private:
	//�ڐG����
	//�����Ftarget	����̓����蔻��
	//�ߒl�F�ڐG���Ă��true
	bool IsHit(Collider* target) override;

	
};

