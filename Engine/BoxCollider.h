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
	//�R���X�g���N�^�i�����蔻��̍쐬�j
	//�����Fcenter	�����蔻��̒��S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
	//�����Fsize	�����蔻��̃T�C�Y�i���A�����A���s���j���a
	//�����Frotate	�����蔻�����]������p�x�i�܂�����ĂȂ��j
	BoxCollider(XMFLOAT3 center, XMFLOAT3 size, XMFLOAT3 rotate);

	~BoxCollider();

private:
	//�ڐG����
	//�����Ftarget	����̓����蔻��
	//�ߒl�F�ڐG���Ă��true
	bool IsHit(Collider* target) override;
};

