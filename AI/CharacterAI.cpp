#include "CharacterAI.h"
#include "NavigationAI.h"
#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"

CharacterAI::CharacterAI() :pNavigationAI_(nullptr), pMetaAI_(nullptr), pEnemy_(nullptr)
{
}

CharacterAI::CharacterAI(Enemy* enemy, NavigationAI* naviAI) :pNavigationAI_(naviAI),pMetaAI_(nullptr), pEnemy_(enemy)
{
}

CharacterAI::~CharacterAI()
{
}

void CharacterAI::Initialize()
{
	//pNavigationAI_->Initialize();

	//pNavigationAI_->SetEnemyPos(pEnemy_->GetPosition());
	isStay_ = false;
	stayTime_ = 0;
}

void CharacterAI::Release()
{

}

//動かす
void CharacterAI::MoveEnemy()
{

	//一定時間止まる
	if (isStay_) {
		stayTime_++;
		if (stayTime_ <= 60) {
			return;
		}
	}

	//NavigationAIに向かうべき方向を聞く
	XMFLOAT3 fMove = pNavigationAI_->Astar();

	//目標地点に着いた場合、一定時間止まる.攻撃した時にも止まりたい
	if (fMove == ZERO_FLOAT3) {
		Stay();
	}

	pEnemy_->SetPosition(Float3Add(pEnemy_->GetPosition(), fMove));

	//向かう方向ベクトルを確認
	XMVECTOR vMove = XMLoadFloat3(&fMove);
	vMove = XMVector3Normalize(vMove);
	float length = Length(vMove);

	//動いているなら角度を求めて回転する
	if (length != ZERO) {

		XMVECTOR vFront = { 0,0,1,0 };
		vMove = XMVector3Normalize(vMove);

		//内積から角度を求める
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		//外積が-になる角度なら
		XMVECTOR vCross = XMVector3Cross(vFront, vMove);
		if (XMVectorGetY(vCross) < ZERO) {

			angle *= -1;
		}

		float degree = XMConvertToDegrees(angle);

		pEnemy_->SetRotateY(degree);

		pEnemy_->SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));

	}

}

void CharacterAI::Stay()
{
	isStay_ = true;//これ攻撃判定が広いせいで無限ループするときあり
	stayTime_ = 0;
}

void CharacterAI::Attack()
{
}
