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

#if 1 //�e���̕����x�N�g���͂ǂ�����Ď��

	//rotate����e���x�N�g�����擾
	XMVECTOR vec = XMVectorSet(1, ZERO, ZERO, ZERO);
	directionNormalVec_[VEC_X] = XMVector3Normalize(XMVector3TransformCoord(vec, XMMatrixRotationX(XMConvertToRadians(rotate.x))));
	vec = XMVectorSet(ZERO, 1, ZERO, ZERO);
	directionNormalVec_[VEC_Y] = XMVector3Normalize(XMVector3TransformCoord(vec, XMMatrixRotationY(XMConvertToRadians(rotate.y))));
	vec = XMVectorSet(ZERO, ZERO, 1, ZERO);
	directionNormalVec_[VEC_Z] = XMVector3Normalize(XMVector3TransformCoord(vec, XMMatrixRotationZ(XMConvertToRadians(rotate.z))));

#else

	//�l�p�`�e���̕����x�N�g���𐳋K�����Ċm��
	directionNormalVec_[VEC_X] = XMVector3Normalize(XMVector3TransformCoord(center_, XMMatrixRotationX(XMConvertToRadians(rotate.x))));
	directionNormalVec_[VEC_Y] = XMVector3Normalize(XMVector3TransformCoord(center_, XMMatrixRotationY(XMConvertToRadians(rotate.y))));
	directionNormalVec_[VEC_Z] = XMVector3Normalize(XMVector3TransformCoord(center_, XMMatrixRotationZ(XMConvertToRadians(rotate.z))));

#endif

	//�e�������x�N�g���̒�����size����m��
	length_[VEC_X] = size.x;
	length_[VEC_Y] = size.y;
	length_[VEC_Z] = size.z;

	//�`�掞�p�Ɏc��
	rotate_ = rotate;
	size_ = size;

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