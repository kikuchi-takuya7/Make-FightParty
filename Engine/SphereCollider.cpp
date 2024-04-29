#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Model.h"

//�R���X�g���N�^�i�����蔻��̍쐬�j
//�����Fcenter	�����蔻��̒��S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
//�����Fsize	�����蔻��̃T�C�Y(���a)
SphereCollider::SphereCollider(XMFLOAT3 center, float size)
{
	center_ = XMLoadFloat3(&center);
	length_[VEC_X] = size;
	type_ = COLLIDER_CIRCLE;

	size_.x = size;

	//�����[�X���͔���g�͕\�����Ȃ�
#ifdef _DEBUG
	//�e�X�g�\���p����g
	hDebugModel_ = Model::Load("DebugCollision/sphereCollider.fbx");
#endif
}

SphereCollider::~SphereCollider()
{
}

//�ڐG����
//�����Ftarget	����̓����蔻��
//�ߒl�F�ڐG���Ă��true
bool SphereCollider::IsHit(Collider* target)
{
	if (target->type_ == COLLIDER_BOX)
		return IsHitBoxVsCircle((BoxCollider*)target, this);
	else
		return IsHitCircleVsCircle((SphereCollider*)target, this);
}