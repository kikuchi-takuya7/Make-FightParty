#include "CharacterStateManager.h"
#include "../Character.h"

//各static変数を初期化する。staticだからグローバルな位置で最初に初期化しないとダメ
//CharacterAttackState* CharacterStateManager::CharacterAttackState_ = new CharacterAttackState;
//CharacterDieState* CharacterStateManager::CharacterDieState_ = new CharacterDieState;
//CharacterIdleState* CharacterStateManager::CharacterIdleState_ = new CharacterIdleState;
//CharacterJumpState* CharacterStateManager::CharacterJumpState_ = new CharacterJumpState;
//CharacterRunState* CharacterStateManager::CharacterRunState_ = new CharacterRunState;

//CharacterState* CharacterStateManager::CharacterState_ = CharacterIdleState_;

CharacterStateManager::CharacterStateManager(Character* character):CharacterState(character)
{

	pCharacterStateList_.emplace_back(new CharacterIdleState(character));
	pCharacterStateList_.emplace_back(new CharacterAttackState(character));
	pCharacterStateList_.emplace_back(new CharacterJumpState(character));
	pCharacterStateList_.emplace_back(new CharacterKnockBackState(character));
	pCharacterStateList_.emplace_back(new CharacterRunState(character));
	pCharacterStateList_.emplace_back(new CharacterDieState(character));	

	characterState_ = pCharacterStateList_.at(IDLE);
}

CharacterStateManager::~CharacterStateManager()
{
	
	
	for (int i = 0; i < STATE_NUM; i++) {
		SAFE_DELETE(pCharacterStateList_.at(i));
	}

	//子の中身はnewしてたわけじゃ無いからdeleteする必要はない
	//SAFE_DELETE(characterState_);

	pCharacterStateList_.clear();
}

void CharacterStateManager::Update()
{
	

	characterState_->Update();

	//ノックバックが終わってから死ぬ処理.
	if (pCharacter_->GetStatus().dead && characterState_ != pCharacterStateList_.at(KNOCKBACK)) {
		ChangeState(DIE);
	}

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
