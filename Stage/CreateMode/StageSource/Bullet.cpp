#include "Bullet.h"
#include "../../../Engine/Model.h"

namespace {

	const float BULLET_RANGE = 30.0f;
	const int DEFAULT_ATTACK_POWER = 10;
	const float DEFAULT_BULLET_SPEED = 0.4f;
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

	//Initialize���Ăяo���Ă���SetSize���Ă邩��^�񒆂ɏo���̋��̂͂ł����B�܂�

	transform_.rotate_.y = GetParent()->GetRotate().y;
}

void Bullet::Update()
{
	transform_.position_.z += bulletSpeed_;

	//�˒������𒴂�����
	if (transform_.position_.z >= BULLET_RANGE) {
		KillMe();
	}

#if 0//collider�N���X�����ǂ������߁Atransform��ς����炻�̂܂ܔ��f���Ă����悤�ɂȂ���

	//transform_.position�ŃR���W�����̓����ŁAbulletPos�Ń��f���̓���
	//collision��rotate���l�����ĂȂ��̂ŁA�ʁX�ɍ��K�v������

	int rotate = GetParent()->GetRotate().y;

	bulletPos_.z += bulletSpeed_;

	if (rotate == 0) {
		transform_.position_.z += bulletSpeed_;
	}
	if (rotate == 90) {
		transform_.position_.x += bulletSpeed_;
	}
	if (rotate == 180) {
		transform_.position_.z -= bulletSpeed_;
	}
	if (rotate == 270) {
		transform_.position_.x -= bulletSpeed_;
	}

#else//�ʂ̕��@


#endif

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

void Bullet::SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed)
{
	collider_ = collider;
	AddCollider(collider_, type);
	attackPower_ = attackPower;
	bulletSpeed_ = speed;
}


