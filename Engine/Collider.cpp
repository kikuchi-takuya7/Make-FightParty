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

	//ワールド座標から見た座標で当たり判定する。ローカル座標でやっちゃだめ
	XMFLOAT3 boxPosA = Float3Add(boxA->pGameObject_->GetWorldPosition(), boxA->CalclationCenter());
	XMFLOAT3 boxPosB = Float3Add(boxB->pGameObject_->GetWorldPosition(), boxB->CalclationCenter());

	//XMFLOAT3 boxSizeA = Float3Add(boxA->pGameObject_->GetWorldPosition(), boxA->CalclationCenter());

	if ((boxPosA.x + boxA->size_.x / 2) > (boxPosB.x - boxB->size_.x / 2) &&
		(boxPosA.x - boxA->size_.x / 2) < (boxPosB.x + boxB->size_.x / 2) &&
		(boxPosA.y + boxA->size_.y / 2) > (boxPosB.y - boxB->size_.y / 2) &&
		(boxPosA.y - boxA->size_.y / 2) < (boxPosB.y + boxB->size_.y / 2) &&
		(boxPosA.z + boxA->size_.z / 2) > (boxPosB.z - boxB->size_.z / 2) &&
		(boxPosA.z - boxA->size_.z / 2) < (boxPosB.z + boxB->size_.z / 2))
	{
		return true;
	}
	return false;
}

//箱型と球体の衝突判定
//引数：box	箱型判定
//引数：sphere	２つ目の箱型判定
//戻値：接触していればtrue
bool Collider::IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere)
{
	XMFLOAT3 circlePos = Float3Add(sphere->pGameObject_->GetWorldPosition(), sphere->CalclationCenter());
	XMFLOAT3 boxPos = Float3Add(box->pGameObject_->GetWorldPosition(), box->CalclationCenter());



	if (circlePos.x > boxPos.x - box->size_.x - sphere->size_.x &&
		circlePos.x < boxPos.x + box->size_.x + sphere->size_.x &&
		circlePos.y > boxPos.y - box->size_.y - sphere->size_.x &&
		circlePos.y < boxPos.y + box->size_.y + sphere->size_.x &&
		circlePos.z > boxPos.z - box->size_.z - sphere->size_.x &&
		circlePos.z < boxPos.z + box->size_.z + sphere->size_.x )
	{
		return true;
	}

	return false;
}

//球体同士の衝突判定
//引数：circleA	１つ目の球体判定
//引数：circleB	２つ目の球体判定
//戻値：接触していればtrue
bool Collider::IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB)
{
	XMFLOAT3 centerA = circleA->CalclationCenter();
	XMFLOAT3 positionA = circleA->pGameObject_->GetWorldPosition();
	XMFLOAT3 centerB = circleB->CalclationCenter();
	XMFLOAT3 positionB = circleB->pGameObject_->GetWorldPosition();

	XMVECTOR v = (XMLoadFloat3(&centerA) + XMLoadFloat3(&positionA))
		- (XMLoadFloat3(&centerB) + XMLoadFloat3(&positionB));

	if (XMVector3Length(v).m128_f32[0] <= circleA->size_.x + circleB->size_.x)
	{
		return true;
	}

	return false;
}

XMFLOAT3 Collider::CalclationCenter()
{

	//回転行列
	XMMATRIX rotateX, rotateY, rotateZ, rotMatrix;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	rotMatrix = rotateZ * rotateX * rotateY;

	//centerを回転させて返す
	XMVECTOR centerVec = XMLoadFloat3(&center_);

	centerVec = XMVector3TransformCoord(centerVec, rotMatrix);

	return VectorToFloat3(centerVec);
}

XMFLOAT3 Collider::CalclationSize()
{
	//球体だった場合しないように
	if (type_ == COLLIDER_CIRCLE)
		return XMFLOAT3(1,1,1);

	//回転行列
	XMMATRIX rotateX, rotateY, rotateZ, rotMatrix;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	rotMatrix = rotateZ * rotateX * rotateY;

	//Sizeを回転させて返す
	XMVECTOR sizeVec = XMLoadFloat3(&size_);

	sizeVec = XMVector3TransformCoord(sizeVec, rotMatrix);

	return VectorToFloat3(sizeVec);
}

//テスト表示用の枠を描画
//引数：position	オブジェクトの位置
void Collider::Draw(XMFLOAT3 position)
{
	Transform transform;
	XMFLOAT3 center = CalclationCenter();
	XMFLOAT3 size = CalclationSize();
	transform.position_ = XMFLOAT3(position.x + center.x, position.y + center.y, position.z + center.z);
	transform.scale_ = size;
	transform.Calclation();
	Model::SetTransform(hDebugModel_, transform);
	Model::Draw(hDebugModel_);
}
