#include "CharacterStateManager.h"
#include "../Character.h"

//�estatic�ϐ�������������Bstatic������O���[�o���Ȉʒu�ōŏ��ɏ��������Ȃ��ƃ_��
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

	//�q�̒��g��new���Ă��킯���ᖳ������delete����K�v�͂Ȃ�
	//SAFE_DELETE(characterState_);

	pCharacterStateList_.clear();
}

void CharacterStateManager::Update()
{
	

	characterState_->Update();

	//�m�b�N�o�b�N���I����Ă��玀�ʏ���.
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

	//��Ԃ�ύX���āA���̏�Ԃ̏������������s��
	characterState_->Leave();
	characterState_ = pCharacterStateList_.at(nextState);
	characterState_->Enter();
	
	
}
