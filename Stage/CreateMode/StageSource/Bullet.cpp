#include "Bullet.h"
#include "../../../Engine/Model.h"

namespace {

	const float BULLET_RANGE = 30.0f;
	const float DEFAULT_BULLET_SPEED = 0.4f;
	const float DEFAULT_BULLET_SIZE = 0.3f;
}

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), moveLen_(ZERO),bulletSpeed_(DEFAULT_BULLET_SPEED),pCannon_(nullptr)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	bulletModel_ = Model::Load("Others/Bullet.fbx");
	assert(bulletModel_ >= ZERO);


}

void Bullet::Update()
{

	//�����̈ʒu�����C�̕����ւ̑O�x�N�g���𑫂�
	XMVECTOR myVec = XMLoadFloat3(&transform_.position_);
	myVec = forwardVec_ + myVec;
	transform_.position_ = VectorToFloat3(myVec);
	
	//���ˋ�����ۑ�
	moveLen_ += bulletSpeed_;

	//�˒������𒴂�����
	if (moveLen_ >= BULLET_RANGE) {
		KillMe();
	}

}

void Bullet::Draw()
{
	Model::SetTransform(bulletModel_, transform_);
	Model::Draw(bulletModel_);

#ifdef _DEBUG
	CollisionDraw();
#endif
}

void Bullet::Release()
{
}

void Bullet::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//�u���b�N�ɓ���������A���ꂪ�����łȂ���� ���������u���b�N�Ƒ�C�̋����������Ă���ĂȂ��B�����蔻��̖�肩
	if (targetType == COLLIDER_BROCK && pTarget != pCannon_) {
		KillMe();
	}

}

/// <summary>
/// ��C�̏����Z�b�g
/// </summary>
/// <param name="collider">���̓����蔻��</param>
/// <param name="type">�R���C�_�[�̃^�C�v</param>
/// <param name="attackPower">��C�̍U����</param>
/// <param name="speed">���̃X�s�[�h</param>
/// <param name="rotY">���𔭎˂������̑�C�̊p�x</param>
/// <param name="cannon">���̋ʂ𐶐�������C�̃|�C���^</param>
void Bullet::SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed, float rotY,StageSourceBase* cannon)
{
	//�����蔻���ǉ�
	AddCollider(collider, type);

	//���낢��ȏ����Z�b�g
	attackPower_ = attackPower;
	bulletSpeed_ = speed;
	pCannon_ = cannon;
	transform_.rotate_.y = rotY;

	//�O�x�N�g������i�ޕ����ւ̒P�ʃx�N�g�����v�Z
	XMVECTOR myVec = XMVectorSet(ZERO, ZERO, 1, ZERO);
	XMMATRIX rotMat = XMMatrixRotationY(XMConvertToRadians(rotY));

	//�����i�ޕ����̃x�N�g�����擾
	forwardVec_ = XMVector3Normalize(XMVector3TransformCoord(myVec, rotMat));
	forwardVec_ *= bulletSpeed_;
}
