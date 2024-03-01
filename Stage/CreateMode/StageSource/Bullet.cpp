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
	bulletModel_ = Model::Load("Others/Bullet.fbx");
	assert(bulletModel_ >= 0);

	//Initializeを呼び出してからSetSizeしてるから真ん中に出る謎の球体はでかい。つまり

	transform_.rotate_.y = GetParent()->GetRotate().y;
}

void Bullet::Update()
{
	moveLen_ += bulletSpeed_;

	if (moveLen_ >= BULLET_RANGE) {
		KillMe();
	}

	int rotate = GetParent()->GetRotate().y;


	//transform_.positionでコリジョンの動きで、bulletPosでモデルの動き
	//collisionはrotateを考慮してないので、別々に作る必要がある

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

	//親の位置（大砲）に移動させて、移動させる。親のTransformから見てzに移動させてもモデル自体はそう動くけどcollisionはワールドでのz方向に行ってしまう
	Transform bulletTrans;
	bulletTrans.scale_ = transform_.scale_;
	bulletTrans.position_ = Float3Add(transform_.position_,GetParent()->GetPosition());

	Model::SetTransform(bulletModel_, bulletTrans);
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


