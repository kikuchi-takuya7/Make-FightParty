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

	transform_.rotate_.y = GetParent()->GetRotate().y;


}

void Bullet::Update()
{
	
	//��]�s�������������Ƃ��̑�C�̍��W���O���Ƃ��č��W0,0�̏��𒆐S�ɂ��邮�������B
	//�ŏ������x�N�g���ɉ�]�s����������
	XMMATRIX moveMat = XMMatrixTranslation(ZERO, ZERO, bulletSpeed_);
	XMMATRIX rotMat = XMMatrixRotationY(startRotateY_);
	XMMATRIX mat = moveMat * (rotMat * GetWorldMatrix());

	XMVECTOR myVec = XMLoadFloat3(&transform_.position_);

	myVec = XMVector3TransformCoord(myVec, mat);
	transform_.position_ = VectorToFloat3(myVec);
	

	

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
void Bullet::SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed)
{
	collider_ = collider;
	AddCollider(collider_, type);
	attackPower_ = attackPower;
	bulletSpeed_ = speed;
}

/// <summary>
/// �����Ǐ]�C��p�̏����Z�b�g ���g�p
/// </summary>
/// <param name="rotY"></param>
void Bullet::SetStartRot(float rotY) 
{

	startRotateY_ = rotY;

	XMVECTOR myVec = XMLoadFloat3(&transform_.position_);
	XMMATRIX rotMat = XMMatrixRotationY(rotY);
	XMMATRIX mat = rotMat;

	vec_ = XMVector3TransformCoord(myVec, mat);
}