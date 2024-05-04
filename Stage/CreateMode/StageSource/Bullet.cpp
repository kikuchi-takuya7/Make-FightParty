#include "Bullet.h"
#include "../../../Engine/Model.h"

namespace {

	const float BULLET_RANGE = 30.0f;
	const float DEFAULT_BULLET_SPEED = 0.4f;
	const float DEFAULT_BULLET_SIZE = 0.3f;
}

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), moveLen_(ZERO),bulletSpeed_(DEFAULT_BULLET_SPEED),startRotateY_(ZERO), collider_(nullptr)
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
	
#if 0 //��ɉ�]�s��������Ă��

	//��]�s�������������Ƃ��̑�C�̍��W���O���Ƃ��č��W0,0�̏��𒆐S�ɂ��邮�������B
	//�ŏ������x�N�g���ɉ�]�s����������
	XMMATRIX moveMat = XMMatrixTranslation(ZERO, ZERO, bulletSpeed_);
	XMMATRIX rotMat = XMMatrixRotationY(XMConvertToRadians(startRotateY_));
	XMMATRIX mat = moveMat;

	XMVECTOR myVec = XMVectorZero();

	myVec = XMVector3TransformCoord(myVec, mat);
	vec_ = vec_ + myVec; //���s�ړ��s����������x�N�g���Ƒ�C�̍��W�ŉ�]�������x�N�g���𑫂��Ƒ�C�̎��肩��z�����ɐ^��������񂾁B�܂�vec_�̎��_�ō��W�������]���Ă�H
	transform_.position_ = VectorToFloat3(vec_);
	
#else //�ŏ��ɉ�]�s��������������̕�

	XMVECTOR myVec = XMLoadFloat3(&transform_.position_);
	
	myVec = forwardVec_ + myVec;

	transform_.position_ = VectorToFloat3(myVec);

#endif
	

	//bulletTrans_.position_.z += bulletSpeed_;

	//transform_.position_.z += bulletSpeed_;
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
	//�u���b�N�ɓ���������A���ꂪ�����łȂ����
	if (targetType == COLLIDER_BROCK && pTarget != this->GetParent()) {
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
void Bullet::SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed, float rotY)
{
	collider_ = collider;
	AddCollider(collider_, type);
	attackPower_ = attackPower;
	bulletSpeed_ = speed;

	transform_.rotate_.y = rotY;

	//�O�x�N�g������i�ޕ����ւ̒P�ʃx�N�g�����v�Z
	XMVECTOR myVec = XMVectorSet(ZERO, ZERO, 1, ZERO);
	XMMATRIX rotMat = XMMatrixRotationY(XMConvertToRadians(rotY));

	//�����i�ޕ����̃x�N�g�����擾
	forwardVec_ = XMVector3Normalize(XMVector3TransformCoord(myVec, rotMat));
	forwardVec_ *= bulletSpeed_;
}
