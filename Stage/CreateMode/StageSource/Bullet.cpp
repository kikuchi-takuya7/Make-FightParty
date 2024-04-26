#include "Bullet.h"
#include "../../../Engine/Model.h"

namespace {

	const float BULLET_RANGE = 30.0f;
	const int DEFAULT_ATTACK_POWER = 10;
	const float DEFAULT_BULLET_SPEED = 0.4f;
	const float DEFAULT_BULLET_SIZE = 0.3f;
}

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), moveLen_(ZERO),attackPower_(DEFAULT_ATTACK_POWER),bulletSpeed_(DEFAULT_BULLET_SPEED), collider_(nullptr)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	bulletModel_ = Model::Load("Others/Bullet.fbx");
	assert(bulletModel_ >= ZERO);

	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(GetParent()->GetRotate().y));

	transform_.matRotate_ = XMMatrixIdentity();

	startRotateY_ = GetParent()->GetRotate().y;

	//AutoCannon��e�Ƃ���Ƃ����Ɛe�̉�]�̉e���󂯂��Ⴄ����A���˂��ꂽ���_�ł̃��[���h���W�������g������.���ꂩ�x�N�g���ŕ��s�ړ��������Ⴄ

}

void Bullet::Update()
{
	
	//���ˎ��̉�]�����o���Ă����ăx�N�g���ł̈ړ�->���t���[����]�s�񂪂������ăO���O�������

	/*XMVECTOR myVec = XMLoadFloat3(&transform_.position_);
	XMMATRIX moveMat = XMMatrixTranslation(ZERO, ZERO, bulletSpeed_);
	XMMATRIX rotMat = XMMatrixRotationY(startRotateY_);
	XMMATRIX mat = rotMat * moveMat;

	XMVECTOR vec = XMVector3TransformCoord(myVec, mat);

	transform_.position_ = VectorToFloat3(vec);*/
	
	transform_.position_.z += bulletSpeed_;

	//�˒������𒴂�����
	if (moveLen_ >= BULLET_RANGE) {
		KillMe();
	}

}

void Bullet::Draw()
{
	
	//�����蔻���������bulletTrans�Ɠ����悤�ɂ���
	//transform_ = bulletTrans_;

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

void Bullet::SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed)
{
	collider_ = collider;
	AddCollider(collider_, type);
	attackPower_ = attackPower;
	bulletSpeed_ = speed;
}


