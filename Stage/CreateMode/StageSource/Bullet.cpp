#include "Bullet.h"
#include "../../../Engine/Model.h"

namespace {

	const float BULLET_RANGE = 30.0f;
	const float DEFAULT_BULLET_SPEED = 0.4f;
	const float DEFAULT_BULLET_SIZE = 0.3f;
}

Bullet::Bullet(GameObject* parent)
	:StageSourceBase(parent, "Bullet"), moveLen_(ZERO),bulletSpeed_(DEFAULT_BULLET_SPEED), collider_(nullptr)
{
}

Bullet::~Bullet()
{
}

void Bullet::ChildInitialize()
{
	bulletModel_ = Model::Load("Others/Bullet.fbx");
	assert(bulletModel_ >= ZERO);

	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(GetParent()->GetRotate().y));

	//transform_.matRotate_ = XMMatrixIdentity();


	//AutoCannon��e�Ƃ���Ƃ����Ɛe�̉�]�̉e���󂯂��Ⴄ����A���˂��ꂽ���_�ł̃��[���h���W�������g������.���ꂩ�x�N�g���ŕ��s�ړ��������Ⴄ
	
	

}

void Bullet::ChildUpdate()
{
	
	//���ˎ��̉�]�����o���Ă����ăx�N�g���ł̈ړ�->���t���[����]�s�񂪂������ăO���O�������

	
	XMMATRIX moveMat = XMMatrixTranslation(ZERO, ZERO, bulletSpeed_);
	vec_ = XMVector3TransformCoord(vec_, moveMat);

	transform_.position_ = VectorToFloat3(vec_);
	
	//transform_.position_.z += bulletSpeed_;



	moveLen_ += bulletSpeed_;

	//�˒������𒴂�����
	if (moveLen_ >= BULLET_RANGE) {
		KillMe();
	}

}

void Bullet::ChildDraw()
{
	
	//�����蔻���������bulletTrans�Ɠ����悤�ɂ���
	//transform_ = bulletTrans_;

	Model::SetTransform(bulletModel_, transform_);
	Model::Draw(bulletModel_);

#ifdef _DEBUG
	CollisionDraw();
#endif
}

void Bullet::ChildRelease()
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

void Bullet::SetStartRot(float rotY) 
{

	startRotateY_ = rotY;

	XMVECTOR myVec = XMLoadFloat3(&transform_.position_);
	XMMATRIX rotMat = XMMatrixRotationY(rotY);
	XMMATRIX mat = rotMat;

	vec_ = XMVector3TransformCoord(myVec, mat);
}