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
	
	//回転行列をかけ続けるとその大砲の座標を外周として座標0,0の所を中心にぐるぐる回った。
	//最初だけベクトルに回転行列をかけると
	XMMATRIX moveMat = XMMatrixTranslation(ZERO, ZERO, bulletSpeed_);
	XMMATRIX rotMat = XMMatrixRotationY(startRotateY_);
	XMMATRIX mat = moveMat * (rotMat * GetWorldMatrix());

	XMVECTOR myVec = XMLoadFloat3(&transform_.position_);

	myVec = XMVector3TransformCoord(myVec, mat);
	transform_.position_ = VectorToFloat3(myVec);
	

	

	//bulletTrans_.position_.z += bulletSpeed_;

	//transform_.position_.z += bulletSpeed_;
	moveLen_ += bulletSpeed_;

	//射程距離を超えたら
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
	//ブロックに当たったら、それが自分でなければ
	if (targetType == COLLIDER_BROCK && pTarget != this->GetParent()) {
		KillMe();
	}

}

/// <summary>
/// 大砲の情報をセット
/// </summary>
/// <param name="collider">球の当たり判定</param>
/// <param name="type">コライダーのタイプ</param>
/// <param name="attackPower">大砲の攻撃力</param>
/// <param name="speed">球のスピード</param>
void Bullet::SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed)
{
	collider_ = collider;
	AddCollider(collider_, type);
	attackPower_ = attackPower;
	bulletSpeed_ = speed;
}

/// <summary>
/// 自動追従砲台用の情報をセット 未使用
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