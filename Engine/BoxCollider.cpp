#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Model.h"


//�R���X�g���N�^�i�����蔻��̍쐬�j
//�����Fcenter	�����蔻��̒��S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
//�����Fsize	�����蔻��̃T�C�Y
//�����Frotate	�����蔻�����]������p�x�i�܂�����ĂȂ��j
BoxCollider::BoxCollider(XMFLOAT3 center, XMFLOAT3 size, XMFLOAT3 rotate)
{
	center_ = XMLoadFloat3(&center);

	//rotate����e���x�N�g�����擾
	directionVec_[VEC_X] = XMVector3TransformCoord(center_, XMMatrixRotationX(XMConvertToRadians(rotate.x)));
	directionVec_[VEC_Y] = XMVector3TransformCoord(center_, XMMatrixRotationX(XMConvertToRadians(rotate.y)));
	directionVec_[VEC_Z] = XMVector3TransformCoord(center_, XMMatrixRotationX(XMConvertToRadians(rotate.z)));

	//�e�������x�N�g���̒�����size����m��
	length_[VEC_X] = size.x;
	length_[VEC_Y] = size.y;
	length_[VEC_Z] = size.z;

	type_ = COLLIDER_BOX;

	//�����[�X���͔���g�͕\�����Ȃ�
#ifdef _DEBUG
	//�e�X�g�\���p����g
	hDebugModel_ = Model::Load("DebugCollision/boxCollider.fbx");
#endif
}

BoxCollider::~BoxCollider()
{
}

//�ڐG����
//�����Ftarget	����̓����蔻��
//�ߒl�F�ڐG���Ă��true
bool BoxCollider::IsHit(Collider* target)
{
	if (target->type_ == COLLIDER_BOX)
		return IsHitBoxVsBox((BoxCollider*)target, this);
	else
		return IsHitBoxVsCircle(this, (SphereCollider*)target);
}