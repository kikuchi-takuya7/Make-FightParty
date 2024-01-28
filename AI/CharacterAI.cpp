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
	//最初に狙う敵のIDを決めてもらう
	pMetaAI_->Targeting(pEnemy_->GetObjectID());

}

void CharacterAI::Release()
{

}

//動かす
void CharacterAI::MoveEnemy()
{

	//NavigationAIに向かうべき方向を聞く
	XMFLOAT3 fMove = pNavigationAI_->Astar(pEnemy_->GetObjectID(), targetID_);

	pEnemy_->SetPosition(Float3Add(pEnemy_->GetPosition(), fMove));

	if (fMove == ZERO_FLOAT3) {
		pEnemy_->ChangeState(ENEMY_IDLE);
	}

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

		//pEnemy_->ChangeState(ENEMY_RUN);

	}

}

void CharacterAI::Attack()
{

}

void CharacterAI::IsAttack()
{
	float distance = pNavigationAI_->Distance(pEnemy_->GetObjectID(), targetID_);
	
	if (distance <= 2.5f) {
		//pEnemy_->ChangeState(ENEMY_ATTACK);
	}
}
