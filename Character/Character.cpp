#include "Character.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"
#include "../Stage/CreateMode/StageSource/Bullet.h"
#include "../Stage/CreateMode/StageSource/Needle.h"
#include "../Stage/CreateMode/StageSource/StageSourceBase.h"
#include "../UI/PlayerUI.h"
#include "CharacterState/CharacterStateManager.h"

namespace {
	const int CHARACTER_HP = 100;
	const int CHARACTER_ATTACK_POWER = 100;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

//�R���X�g���N�^
Character::Character(GameObject* parent,std::string name)
	:GameObject(parent, name), hModel_(-1),status_(Status(CHARACTER_HP, CHARACTER_ATTACK_POWER, false, ZERO, ZERO, ZERO, "NONE")),
	pState_(new CharacterStateManager(this)), pBodyCollision_(nullptr), pAttackCollision_(nullptr), startPos_(ZERO_FLOAT3), stopDraw_(false)
	,pPlayerUI_(Instantiate<PlayerUI>(this))
{
}

//�f�X�g���N�^
Character::~Character()
{
}

//������
void Character::Initialize()
{
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, ZERO_FLOAT3);

	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("PlayerFbx/player.fbx");
	assert(hModel_ >= 0);

	//status_ = { CHARACTER_HP,CHARACTER_ATTACK_POWER, false ,ZERO,ZERO,ZERO,"NONE" };
	pPlayerUI_->SetMaxHp(status_.hp, status_.hp);

	ChildInitialize();
}

//�X�V
void Character::Update()
{
	//�����Ăق����Ȃ��Ƃ�
	if (IsEntered() == false) {
		return;
	}

	//������ʒu��prevPos�ɒu���Ă���
	prevPos_ = transform_.position_;

	

	pState_->Update();

	

	//�m�b�N�o�b�N���͈ړ��̏��������Ȃ�
	if (pState_->characterState_ != pState_->pCharacterStateList_.at(KNOCKBACK) && pState_->characterState_ != pState_->pCharacterStateList_.at(ATTACK)) {
		ChildUpdate();
	}


}

//�`��
void Character::Draw()
{

	if (stopDraw_ == true)
		return;

	ChildDraw();
}

//�J��
void Character::Release()
{
	ChildRelease();

	SAFE_DELETE(pState_);

	//�������ȊO�ACollision�͏����Ă���̂ł�����DELETE����B�����s���ɏ����ƃG���[�ɂȂ�
	//�Ă�����nullptr����Ă�͂��Ȃ̂ɂȂ���O���o��̂�
	
	//�ň�����state�̏�Ԃɂ����delete���邩���Ȃ��������߂�B
	//pAttackCollision_ = nullptr;

	/*SAFE_DELETE(pAttackCollision_);
	SAFE_DELETE(pBodyCollision_);*/
	
}

void Character::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	
	if (status_.dead) {
		return;
	}

	//�ǂɂԂ�������O�ɂ������W�ɖ߂�
	if (myType == COLLIDER_BODY && targetType == COLLIDER_BROCK) {
		SetPosition(prevPos_);
	}

	//�m�b�N�o�b�N���͓����蔻��𖳂���
	if (pState_->pCharacterStateList_.at(KNOCKBACK) == pState_->characterState_)
		return;

	//���ɓ����������̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_BULLET) {

		HitDamage(static_cast<Bullet*>(pTarget)->GetAttackPower());

		SetTargetRotate(pTarget->GetRotate());

		pState_->ChangeState(KNOCKBACK);

	}

	//�g�Q�ɓ����������̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_OBSTRYCTION) {
		HitDamage(static_cast<Needle*>(pTarget)->GetNeedlePower());
	}

	ChildOnCollision(pTarget, myType, targetType);
}

bool Character::HitDamage(int damage)
{
	status_.hp -= damage;

	pPlayerUI_->SetNowHp(status_.hp);

	//HP��0�ɂȂ�����
	if (status_.hp <= 0) {
		status_.dead = true;
	}

	return status_.dead;
}

void Character::StopDraw()
{
	stopDraw_ = true;
	pPlayerUI_->StopDraw();
}

void Character::StartDraw()
{
	stopDraw_ = false;
	pPlayerUI_->StartDraw();
}

void Character::StopDrawUI()
{
	pPlayerUI_->StopDraw();
}

void Character::Dead()
{
	status_.dead = true;
}



void Character::MoveCharacter()
{
}

void Character::ResetStatus()
{
	EraseCollider(COLLIDER_ATTACK);
	EraseCollider(COLLIDER_BODY);

	//�J�n�n�_�Ɉړ�����
	SetPosition(startPos_);

	//addcollider�����珟��ɊJ������邩���
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	status_.hp = CHARACTER_HP;
	status_.dead = false;
	status_.killPoint = ZERO;
	status_.trapKillPoint = ZERO;

	pPlayerUI_->SetMaxHp(status_.hp, CHARACTER_HP);

	TellStatus();

	ChangeState(IDLE);
}

void Character::ChangeState(CharacterStateList nextState)
{
	pState_->ChangeState(nextState);
}

void Character::SetUIPos(XMFLOAT3 pos)
{
	pPlayerUI_->SetPlayerUIPos(pos);
}

void Character::SetCharacterName(std::string name)
{
	status_.playerName = name;
	pPlayerUI_->SetPlayerName(name);
}


