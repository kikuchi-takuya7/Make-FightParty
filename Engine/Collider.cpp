#include "BoxCollider.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "Model.h"
#include "Transform.h"
#include "Global.h"

//コンストラクタ
Collider::Collider():
	pGameObject_(nullptr)
{
}

//デストラクタ
Collider::~Collider()
{
}

//箱型同士の衝突判定
//引数：boxA	１つ目の箱型判定
//引数：boxB	２つ目の箱型判定
//戻値：接触していればtrue
bool Collider::IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB)
{

	// 各方向ベクトルの確保　標準化された方向ベクトルと、それに長さをかけて本来の長さに戻したベクトル
    //（N***:標準化方向ベクトル）
	XMVECTOR NAe1 = boxA->GetDirect(VEC_X), Ae1 = NAe1 * boxA->GetLen_W(VEC_X);
	XMVECTOR NAe2 = boxA->GetDirect(VEC_Y), Ae2 = NAe2 * boxA->GetLen_W(VEC_Y);
	XMVECTOR NAe3 = boxA->GetDirect(VEC_Z), Ae3 = NAe3 * boxA->GetLen_W(VEC_Z);
	XMVECTOR NBe1 = boxB->GetDirect(VEC_X), Be1 = NBe1 * boxB->GetLen_W(VEC_X);
	XMVECTOR NBe2 = boxB->GetDirect(VEC_Y), Be2 = NBe2 * boxB->GetLen_W(VEC_Y);
	XMVECTOR NBe3 = boxB->GetDirect(VEC_Z), Be3 = NBe3 * boxB->GetLen_W(VEC_Z);
	XMVECTOR Interval = boxA->GetPos_W() - boxB->GetPos_W(); //二つの箱の中心点間の距離を求める準備

	// 分離軸 : Ae1 箱Aの方向ベクトルと分離軸との内積を2つ足すと半径分の分離軸上の長さを求められて、それの合計がLより長いならぶつかってる可能性あり
	float rA = Length(Ae1);
	float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = fabs(Length(XMVector3Dot(Interval, NAe1)));
	if (L > rA + rB)
		return false; // 衝突していない

	// 分離軸 : Ae2
	rA = Length(Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, NAe2)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Ae3
	rA = Length(Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, NAe3)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = Length(Be1);
	L = fabs(Length(XMVector3Dot(Interval, NBe1)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = Length(Be2);
	L = fabs(Length(XMVector3Dot(Interval, NBe2)));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = Length(Be3);
	L = fabs(Length(XMVector3Dot(Interval, NBe3)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C11
	XMVECTOR Cross;
	Cross = XMVector3Cross(NAe1, NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C12
	Cross = XMVector3Cross(NAe1, NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C13
	Cross = XMVector3Cross(NAe1, NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C21
	Cross = XMVector3Cross(NAe2, NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C22
	Cross = XMVector3Cross(NAe2, NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C23
	Cross = XMVector3Cross(NAe2, NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C31
	Cross = XMVector3Cross(NAe3, NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C32
	Cross = XMVector3Cross(NAe3, NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// 分離軸 : C33
	Cross = XMVector3Cross(NAe3, NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}

//箱型と球体の衝突判定
//引数：box	箱型判定
//引数：sphere	２つ目の箱型判定
//戻値：接触していればtrue
bool Collider::IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere)
{
	/*XMFLOAT3 circlePos = Float3Add(sphere->pGameObject_->GetWorldPosition(), sphere->CalclationCenter());
	XMFLOAT3 boxPos = Float3Add(box->pGameObject_->GetWorldPosition(), box->CalclationCenter());



	if (circlePos.x > boxPos.x - box->size_.x - sphere->size_.x &&
		circlePos.x < boxPos.x + box->size_.x + sphere->size_.x &&
		circlePos.y > boxPos.y - box->size_.y - sphere->size_.x &&
		circlePos.y < boxPos.y + box->size_.y + sphere->size_.x &&
		circlePos.z > boxPos.z - box->size_.z - sphere->size_.x &&
		circlePos.z < boxPos.z + box->size_.z + sphere->size_.x )
	{
		return true;
	}*/

	return false;
}

//球体同士の衝突判定
//引数：circleA	１つ目の球体判定
//引数：circleB	２つ目の球体判定
//戻値：接触していればtrue
bool Collider::IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB)
{
	/*XMFLOAT3 centerA = circleA->CalclationCenter();
	XMFLOAT3 positionA = circleA->pGameObject_->GetWorldPosition();
	XMFLOAT3 centerB = circleB->CalclationCenter();
	XMFLOAT3 positionB = circleB->pGameObject_->GetWorldPosition();

	XMVECTOR v = (XMLoadFloat3(&centerA) + XMLoadFloat3(&positionA))
		- (XMLoadFloat3(&centerB) + XMLoadFloat3(&positionB));

	if (XMVector3Length(v).m128_f32[0] <= circleA->size_.x + circleB->size_.x)
	{
		return true;
	}*/

	return false;
}

// 分離軸に投影された軸成分から投影線分長を算出
float Collider::LenSegOnSeparateAxis(XMVECTOR* Sep, XMVECTOR* e1, XMVECTOR* e2, XMVECTOR* e3)
{
	// 3つの内積の絶対値の和で投影線分長を計算
    // 分離軸Sepは標準化されていること
	float r1 = fabs(Length(XMVector3Dot(*Sep, *e1)));
	float r2 = fabs(Length(XMVector3Dot(*Sep, *e2)));
	float r3 = e3 ? (fabs(Length(XMVector3Dot(*Sep, *e3)))) : 0;
	return r1 + r2 + r3;
}

//テスト表示用の枠を描画
//引数：position	オブジェクトの位置
void Collider::Draw(XMFLOAT3 position)
{
	Transform transform;

	transform.position_ = VectorToFloat3(center_);

	transform.Calclation();
	Model::SetTransform(hDebugModel_, transform);
	Model::Draw(hDebugModel_);
}

void Collider::SetCenter(XMFLOAT3 center)
{
	center_ = XMLoadFloat3(&center);
}

void Collider::SetSize(XMFLOAT3 size)
{
	//各軸方向ベクトルの長さをsizeから確保
	length_[VEC_X] = size.x;
	length_[VEC_Y] = size.y;
	length_[VEC_Z] = size.z;
}

void Collider::SetRotate(XMFLOAT3 rotate)
{
	//rotateから各軸ベクトルを取得
	directionNormalVec_[VEC_X] = XMVector3TransformCoord(center_, XMMatrixRotationX(XMConvertToRadians(rotate.x)));
	directionNormalVec_[VEC_Y] = XMVector3TransformCoord(center_, XMMatrixRotationX(XMConvertToRadians(rotate.y)));
	directionNormalVec_[VEC_Z] = XMVector3TransformCoord(center_, XMMatrixRotationX(XMConvertToRadians(rotate.z)));
}
