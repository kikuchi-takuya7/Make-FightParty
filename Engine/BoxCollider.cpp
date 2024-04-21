#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Model.h"


//コンストラクタ（当たり判定の作成）
//引数：center	当たり判定の中心位置（ゲームオブジェクトの原点から見た位置）
//引数：size	当たり判定のサイズ
//引数：rotate	当たり判定を回転させる角度（まだ回ってない）
BoxCollider::BoxCollider(XMFLOAT3 center, XMFLOAT3 size, XMFLOAT3 rotate)
{
	center_ = XMLoadFloat3(&center);

	//rotateから各軸ベクトルを取得
	directionVec_[VEC_X] = XMVector3TransformCoord(center_, XMMatrixRotationX(XMConvertToRadians(rotate.x)));
	directionVec_[VEC_Y] = XMVector3TransformCoord(center_, XMMatrixRotationX(XMConvertToRadians(rotate.y)));
	directionVec_[VEC_Z] = XMVector3TransformCoord(center_, XMMatrixRotationX(XMConvertToRadians(rotate.z)));

	//各軸方向ベクトルの長さをsizeから確保
	length_[VEC_X] = size.x;
	length_[VEC_Y] = size.y;
	length_[VEC_Z] = size.z;

	type_ = COLLIDER_BOX;

	//リリース時は判定枠は表示しない
#ifdef _DEBUG
	//テスト表示用判定枠
	hDebugModel_ = Model::Load("DebugCollision/boxCollider.fbx");
#endif
}

BoxCollider::~BoxCollider()
{
}

//接触判定
//引数：target	相手の当たり判定
//戻値：接触してればtrue
bool BoxCollider::IsHit(Collider* target)
{
	if (target->type_ == COLLIDER_BOX)
		return IsHitBoxVsBox((BoxCollider*)target, this);
	else
		return IsHitBoxVsCircle(this, (SphereCollider*)target);
}