#include "CharacterAI.h"
#include "NavigationAI.h"
#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/CharacterState/CharacterState.h"
#include "../Engine/Text.h"

namespace {
	//表示する現在のAIの状態
	XMFLOAT3 TEXT_POS = { -70,50,ZERO };
	std::string text[TEXT_NUM] = { ":Randam",":No1",":Counter"};
}

CharacterAI::CharacterAI(GameObject* parent)
	:AI(parent, "CharacterAI"), pNavigationAI_(nullptr), pMetaAI_(nullptr), pEnemy_(nullptr),pText_(new Text)
{
}

CharacterAI::CharacterAI(GameObject* parent, Enemy* enemy, NavigationAI* naviAI)
	:AI(parent, "CharacterAI"), pNavigationAI_(naviAI), pMetaAI_(nullptr), pEnemy_(enemy), pText_(new Text)
{
}

CharacterAI::~CharacterAI()
{
}

void CharacterAI::Initialize()
{
	//pEnemy_->GetStatus().playerName;
	pText_->Initialize();
}

void CharacterAI::Draw()
{
	std::string str = pEnemy_->GetStatus().playerName + text[target_.mode];
	int tmp = pEnemy_->GetObjectID();

	pText_->Draw(TEXT_POS.x, TEXT_POS.y * tmp, str.c_str());
}

void CharacterAI::Release()
{

}

// 狙うべき敵をMetaAIに聞く関数
void CharacterAI::AskTarget()
{
	//狙う敵のIDを決めてもらう
	target_ = pMetaAI_->Targeting(pEnemy_->GetObjectID());
}

// MetaAIに情報を伝える関数
void CharacterAI::TellStatus()
{
	pMetaAI_->ChangeStatus(pEnemy_->GetObjectID(), pEnemy_->GetStatus());
	pMetaAI_->DecidedWinner();
}


// NavigationAIに行くべき場所を聞き、移動する関数
void CharacterAI::MoveEnemy()
{

	//NavigationAIに向かうべき方向を聞く
	XMFLOAT3 fMove = pNavigationAI_->Astar(pEnemy_->GetObjectID(), target_.ID);

	pEnemy_->SetPosition(Float3Add(pEnemy_->GetPosition(), fMove));

	if (fMove == ZERO_FLOAT3) {
		pEnemy_->ChangeState(IDLE);
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

		pEnemy_->ChangeState(RUN);

	}
}

// 攻撃するかどうかを指示する関数
void CharacterAI::IsAttack()
{
	//狙おうとしてる敵が死んでたら、ターゲットを変える
	if (pMetaAI_->GetCharacterStatus(target_.ID).dead) {
		AskTarget();
	}

	float distance = pNavigationAI_->Distance(pEnemy_->GetObjectID(), target_.ID);
	
	if (distance <= 2.0f) {
		pEnemy_->ChangeState(ATTACK);
	}
}

// クリエイトモードで選択したオブジェクトを移動させる関数
// 戻り値：動かした後のTransform
Transform CharacterAI::MoveSelectObject()
{
	//ステージ内のどこかにランダムで置く
	Transform objTrans;
	objTrans.position_.x = rand() % 29;
	objTrans.position_.z = rand() % 29;

	objTrans.rotate_.y = rand() % 4 * 90;

	return objTrans;
}

