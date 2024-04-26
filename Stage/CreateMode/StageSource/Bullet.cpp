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


	//AutoCannonを親とするとずっと親の回転の影響受けちゃうから、発射された時点でのワールド座標だけを使いたい.それかベクトルで平行移動させちゃう
	
	

}

void Bullet::Update()
{
	
	//発射時の回転だけ覚えておいてベクトルでの移動->毎フレーム回転行列がかけられてグルグル回った

	
	XMMATRIX moveMat = XMMatrixTranslation(ZERO, ZERO, bulletSpeed_);
	vec_ = XMVector3TransformCoord(vec_, moveMat);

	transform_.position_ = VectorToFloat3(vec_);
	
	//transform_.position_.z += bulletSpeed_;



	moveLen_ += bulletSpeed_;

	//射程距離を超えたら
	if (moveLen_ >= BULLET_RANGE) {
		KillMe();
	}

}

void Bullet::Draw()
{
	
	//当たり判定もちゃんとbulletTransと同じようにする
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

void Bullet::SetStartRot(float rotY) 
{

	startRotateY_ = rotY;

	XMVECTOR myVec = XMLoadFloat3(&transform_.position_);
	XMMATRIX moveMat = XMMatrixTranslation(ZERO, ZERO, bulletSpeed_);
	XMMATRIX rotMat = XMMatrixRotationY(rotY);
	XMMATRIX mat = moveMat * rotMat;

	vec_ = XMVector3TransformCoord(myVec, mat);
}