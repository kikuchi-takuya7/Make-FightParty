#include "CharacterStateManager.h"
#include "../Character.h"

//各static変数を初期化する。staticだからグローバルな位置で最初に初期化しないとダメ
//CharacterAttackState* CharacterStateManager::CharacterAttackState_ = new CharacterAttackState;
//CharacterDieState* CharacterStateManager::CharacterDieState_ = new CharacterDieState;
//CharacterIdleState* CharacterStateManager::CharacterIdleState_ = new CharacterIdleState;
//CharacterJumpState* CharacterStateManager::CharacterJumpState_ = new CharacterJumpState;
//CharacterRunState* CharacterStateManager::CharacterRunState_ = new CharacterRunState;

//CharacterState* CharacterStateManager::CharacterState_ = CharacterIdleState_;

CharacterStateManager::CharacterStateManager()
{
	characterAttackState_ = new CharacterAttackState;
	characterDieState_ = new CharacterDieState;
	characterIdleState_ = new CharacterIdleState;
	characterJumpState_ = new CharacterJumpState;
	characterKnockBackState_ = new CharacterKnockBackState;
	characterRunState_ = new CharacterRunState;

	characterState_ = characterIdleState_;
}

void CharacterStateManager::Update(Character* character)
{

	//攻撃してる時に攻撃喰らった時に攻撃判定を消す用。それぞれのEnterに置いた方がいいかな
	if (characterState_ != characterAttackState_) {

		character->EraseCollider(COLLIDER_ATTACK);
	}

	//行動不能状態なら移動はしない
	if (characterState_ == characterKnockBackState_ || characterState_ == characterDieState_) {
		characterState_->Update(character);
		return;
	}

	//死ぬ処理
	if (character->GetStatus().dead) {
		ChangeState(DIE, character);
	}

	//移動キーが押されているなら
	if (Input::IsKey(DIK_A) || Input::IsKey(DIK_D)|| Input::IsKey(DIK_W) || Input::IsKey(DIK_S))
	{

		//Runstateで移動中なら速度早くして、他のstateなら移動速度遅くするとかが良い気がする
		MoveCharacter(character);
		//ChangeState(Character_RUN, Character);
	}

	characterState_->Update(character);

	

}

void CharacterStateManager::HandleInput(Character* character)
{
}

void CharacterStateManager::Enter(Character* character)
{
}

void CharacterStateManager::ChangeState(CharacterStatePattern nextState, Character* character)
{

	//状態を変更して、その状態の初期化処理を行う
	switch (nextState)
	{
	case ATTACK:
		characterState_ = characterAttackState_;
		break;

	case DIE:
		characterState_ = characterDieState_;
		break;

	case IDLE:
		characterState_ = characterIdleState_;
		break;

	case JUMP:
		characterState_ = characterJumpState_;
		break;

	case KNOCKBACK:
		characterState_ = characterKnockBackState_;
		break;

	case RUN:
		characterState_ = characterRunState_;
		break;

	default:
		return;
		break;
	}

	characterState_->Enter(character);
	
}

void CharacterStateManager::MoveCharacter(Character* character)
{
	XMFLOAT3 fMove = ZERO_FLOAT3;

	////ここの引数でプレイヤー数を指定する
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	XMFLOAT3 characterPos = character->GetPosition();

	//結局後で正規化してるからここの値は大きくても意味なし
	if (Input::IsKey(DIK_A) && characterPos.x >= 0.5)
	{
		fMove.x = -0.01f;
	}
	if (Input::IsKey(DIK_D) && characterPos.x <= 28.5)
	{
		fMove.x = 0.01f;
	}
	if (Input::IsKey(DIK_W) && characterPos.z <= 28.5)
	{
		fMove.z = 0.01f;
	}
	if (Input::IsKey(DIK_S) && characterPos.z >= 0.5)
	{
		fMove.z = -0.01f;
	}

	XMVECTOR vMove = XMLoadFloat3(&fMove);

	//斜めの移動でも早くならないように(必要か？)
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	//速度調整
	fMove.x *= 0.5;
	fMove.z *= 0.5;

	characterPos.x += fMove.x;
	characterPos.z += fMove.z;

	character->SetPosition(characterPos);

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

		character->SetRotateY(degree);

		character->SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));

	}
}
