#include "CharacterStateManager.h"
#include "../Character.h"

//各static変数を初期化する。staticだからグローバルな位置で最初に初期化しないとダメ
//CharacterAttackState* CharacterStateManager::CharacterAttackState_ = new CharacterAttackState;
//CharacterDieState* CharacterStateManager::CharacterDieState_ = new CharacterDieState;
//CharacterIdleState* CharacterStateManager::CharacterIdleState_ = new CharacterIdleState;
//CharacterJumpState* CharacterStateManager::CharacterJumpState_ = new CharacterJumpState;
//CharacterRunState* CharacterStateManager::CharacterRunState_ = new CharacterRunState;

//CharacterState* CharacterStateManager::CharacterState_ = CharacterIdleState_;

CharacterStateManager::CharacterStateManager(Character* character, int model):CharacterState(character, model)
{

	pCharacterStateList_.emplace_back(new CharacterIdleState(character, model));
	pCharacterStateList_.emplace_back(new CharacterAttackState(character, model));
	pCharacterStateList_.emplace_back(new CharacterJumpState(character, model));
	pCharacterStateList_.emplace_back(new CharacterKnockBackState(character, model));
	pCharacterStateList_.emplace_back(new CharacterRunState(character, model));
	pCharacterStateList_.emplace_back(new CharacterDieState(character, model));

	characterState_ = pCharacterStateList_.at(IDLE);
	characterState_->Enter();
}

CharacterStateManager::~CharacterStateManager()
{
	
	
	for (int i = 0; i < STATE_NUM; i++) {
		SAFE_DELETE(pCharacterStateList_.at(i));
	}

	//この中身はnewしてたわけじゃ無いからdeleteする必要はない
	//SAFE_DELETE(characterState_);

	pCharacterStateList_.clear();
}

void CharacterStateManager::Update()
{

	//死ぬ処理.
	if (pCharacter_->GetStatus().dead) {
		ChangeState(DIE);
	}

	characterState_->Update();

	

}

void CharacterStateManager::HandleInput()
{
}

void CharacterStateManager::Enter()
{
}

void CharacterStateManager::Leave()
{
}

void CharacterStateManager::ChangeState(CharacterStateList nextState)
{

	//状態を変更して、その状態の初期化処理を行う
	characterState_->Leave();
	characterState_ = pCharacterStateList_.at(nextState);
	characterState_->Enter();
	
	
}
