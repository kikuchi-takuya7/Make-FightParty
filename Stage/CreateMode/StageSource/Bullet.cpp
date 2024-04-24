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

	//Initializeを呼び出してからSetSizeしてるから真ん中に出る謎の球体はでかい。つまり

	transform_.rotate_.y = GetParent()->GetRotate().y;
}

void Bullet::Update()
{
	transform_.position_.z += bulletSpeed_;

	//射程距離を超えたら
	if (transform_.position_.z >= BULLET_RANGE) {
		KillMe();
	}

#if 0//colliderクラスを改良したため、transformを変えたらそのまま反映してくれるようになった

	//transform_.positionでコリジョンの動きで、bulletPosでモデルの動き
	//collisionはrotateを考慮してないので、別々に作る必要がある

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

#else//別の方法


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
	//ブロックに当たったら、それが自分でなければ
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


