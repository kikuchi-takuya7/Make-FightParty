#include "Bullet.h"
#include "../../../Engine/Model.h"

namespace {

	const float BULLET_RANGE = 30.0f;
}

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), moveLen_(ZERO),attackPower_(10),bulletSpeed_(0.4f), collider_(nullptr)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Others/Bullet.fbx");
	assert(hModel_ >= 0);

	transform_.rotate_.y = GetParent()->GetRotate().y;
	
}

void Bullet::Update()
{
	moveLen_ += bulletSpeed_;

	if (moveLen_ >= BULLET_RANGE) {
		KillMe();
	}

	int rotate = abs(GetParent()->GetRotate().y);

	bulletPos_.z += bulletSpeed_;

	if (rotate == 0) {
		transform_.position_.z += bulletSpeed_;
	}
	if (rotate == 90) {
		transform_.position_.z += bulletSpeed_;
	}
	if (rotate == 180) {
		transform_.position_.z -= bulletSpeed_;
	}
	if (rotate == 270) {
		transform_.position_.z -= bulletSpeed_;
	}

	/*rotate = rotate % 360;
	
	if (rotate == 360) {
		transform_.position_.z += bulletSpeed_;
	}
	if (rotate == 270) {
		transform_.position_.x += bulletSpeed_;
	}
	if (rotate == 180) {
		transform_.position_.z -= bulletSpeed_;
	}
	if (rotate == 90) {
		transform_.position_.x -= bulletSpeed_;
	}*/

}

void Bullet::Draw()
{
	Transform bulletTrans = transform_;
	bulletTrans.position_ = bulletPos_;

	Model::SetTransform(hModel_, bulletTrans);
	Model::Draw(hModel_);

	CollisionDraw();
}

void Bullet::Release()
{
}

void Bullet::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	if (targetType == COLLIDER_BROCK && pTarget != this->GetParent()) {
		KillMe();
	}

	if (targetType == COLLIDER_BODY) {
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

