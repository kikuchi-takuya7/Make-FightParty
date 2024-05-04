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


}

void Bullet::Update()
{
	
#if 0 //常に回転行列をかけてる方

	//回転行列をかけ続けるとその大砲の座標を外周として座標0,0の所を中心にぐるぐる回った。
	//最初だけベクトルに回転行列をかけると
	XMMATRIX moveMat = XMMatrixTranslation(ZERO, ZERO, bulletSpeed_);
	XMMATRIX rotMat = XMMatrixRotationY(XMConvertToRadians(startRotateY_));
	XMMATRIX mat = moveMat;

	XMVECTOR myVec = XMVectorZero();

	myVec = XMVector3TransformCoord(myVec, mat);
	vec_ = vec_ + myVec; //平行移動行列をかけたベクトルと大砲の座標で回転させたベクトルを足すと大砲の周りからz方向に真っすぐ飛んだ。つまりvec_の時点で座標周りを回転してる？
	transform_.position_ = VectorToFloat3(vec_);
	
#else //最初に回転行列をかけただけの方

	XMVECTOR myVec = XMLoadFloat3(&transform_.position_);
	
	myVec = forwardVec_ + myVec;

	transform_.position_ = VectorToFloat3(myVec);

#endif
	

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
/// <param name="rotY">球を発射した時の大砲の角度</param>
void Bullet::SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed, float rotY)
{
	collider_ = collider;
	AddCollider(collider_, type);
	attackPower_ = attackPower;
	bulletSpeed_ = speed;

	transform_.rotate_.y = rotY;

	//前ベクトルから進む方向への単位ベクトルを計算
	XMVECTOR myVec = XMVectorSet(ZERO, ZERO, 1, ZERO);
	XMMATRIX rotMat = XMMatrixRotationY(XMConvertToRadians(rotY));

	//球が進む方向のベクトルを取得
	forwardVec_ = XMVector3Normalize(XMVector3TransformCoord(myVec, rotMat));
	forwardVec_ *= bulletSpeed_;
}
