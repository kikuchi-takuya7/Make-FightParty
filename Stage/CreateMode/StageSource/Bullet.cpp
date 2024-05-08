#include "Bullet.h"
#include "../../../Engine/Model.h"

namespace {

	const float BULLET_RANGE = 30.0f;
	const float DEFAULT_BULLET_SPEED = 0.4f;
	const float DEFAULT_BULLET_SIZE = 0.3f;
}

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), moveLen_(ZERO),bulletSpeed_(DEFAULT_BULLET_SPEED),pCannon_(nullptr)
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

	//自分の位置から大砲の方向への前ベクトルを足す
	XMVECTOR myVec = XMLoadFloat3(&transform_.position_);
	myVec = forwardVec_ + myVec;
	transform_.position_ = VectorToFloat3(myVec);
	
	//発射距離を保存
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
	//ブロックに当たったら、それが自分でなければ そもそもブロックと大砲の球が当たってくれてない。当たり判定の問題か
	if (targetType == COLLIDER_BROCK && pTarget != pCannon_) {
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
/// <param name="rotY">球を発射した時の大砲の角度</param>
/// <param name="cannon">この玉を生成した大砲のポインタ</param>
void Bullet::SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed, float rotY,StageSourceBase* cannon)
{
	//当たり判定を追加
	AddCollider(collider, type);

	//いろいろな情報をセット
	attackPower_ = attackPower;
	bulletSpeed_ = speed;
	pCannon_ = cannon;
	transform_.rotate_.y = rotY;

	//前ベクトルから進む方向への単位ベクトルを計算
	XMVECTOR myVec = XMVectorSet(ZERO, ZERO, 1, ZERO);
	XMMATRIX rotMat = XMMatrixRotationY(XMConvertToRadians(rotY));

	//球が進む方向のベクトルを取得
	forwardVec_ = XMVector3Normalize(XMVector3TransformCoord(myVec, rotMat));
	forwardVec_ *= bulletSpeed_;
}
