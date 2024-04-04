#include "Character.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"
#include "../Engine/Audio.h"
#include "../Stage/CreateMode/StageSource/Bullet.h"
#include "../Stage/CreateMode/StageSource/Needle.h"
#include "../Stage/CreateMode/StageSource/StageSourceBase.h"
#include "../UI/PlayerUI.h"
#include "CharacterState/CharacterStateManager.h"
#include "../Engine/VFX.h"

namespace {
	const int CHARACTER_HP = 100;
	const int CHARACTER_ATTACK_POWER = 25;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(0.9, 2, 0.9);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1.5, 0.5, 3);

	const int PLAYER_MAX_NUM = 4;
}

//�R���X�g���N�^
Character::Character(GameObject* parent,std::string name)
	:GameObject(parent, name), hModel_(-1),status_(Status(CHARACTER_HP, CHARACTER_ATTACK_POWER, false, ZERO, ZERO, ZERO, "NONE")),
	pState_(nullptr), pBodyCollision_(nullptr), pAttackCollision_(nullptr), startPos_(ZERO_FLOAT3), stopDraw_(false), hSoundEffect_{-1,-1}
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
	std::string fileName = "PlayerFbx/player" + std::to_string(GetObjectID()) + ".fbx";
	hModel_ = Model::Load(fileName);
	assert(hModel_ >= ZERO);

	pState_ = new CharacterStateManager(this, hModel_);

	pPlayerUI_->SetMaxHp(status_.hp, status_.hp);


	//�����f�[�^�̃��[�h
	std::string str[SE_NUM] = { "Damage","Dead", };

	for (int i = ZERO; i < SE_NUM; i++) {

		std::string dir = "Audio/SE/";
		std::string extention = ".wav";

		std::string fileName = dir + str[i] + extention;

		hSoundEffect_[i] = Audio::Load(fileName,false,PLAYER_MAX_NUM);
		assert(hSoundEffect_[i] >= ZERO);

		Audio::Stop(hSoundEffect_[i]);
	}
	
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
	if (pState_->characterState_ != pState_->pCharacterStateList_.at(KNOCKBACK) && pState_->characterState_ != pState_->pCharacterStateList_.at(ATTACK) && status_.dead == false) {
		ChildUpdate();
	}


}

//�`��
void Character::Draw()
{

	if (IsVisibled())
		return;

	ChildDraw();
}

//�J��
void Character::Release()
{
	ChildRelease();

	//�������ȊO�ACollision�͏����Ă���̂ł�����DELETE����B

	//�R���W������colliderList����O���Ă�Ƃ��͎����J������Ȃ��̂ŁA����̏����̎��̂ݎ����ŊJ������
	if (pState_->characterState_ != pState_->pCharacterStateList_.at(ATTACK)) {

		SAFE_DELETE(pAttackCollision_);
	}
	else if (pState_->characterState_ == pState_->pCharacterStateList_.at(DIE)) {
		SAFE_DELETE(pAttackCollision_);
		SAFE_DELETE(pBodyCollision_);
	}

	SAFE_DELETE(pState_);

	
	
}

// �ʂ�collider�ɏՓ˂����Ƃ��ɌĂ΂��֐�
void Character::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//����ł����画�肵�Ȃ��l��
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

	//�U���ɓ��������Ƃ��̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		//�G�̕����Ɍ����Ȃ���
		SetTargetRotate(pTarget->GetRotate());
		pState_->ChangeState(KNOCKBACK);

		//�U����H������̂�Enemy�̏ꍇ�A���m���ő_�����U�����Ă�������ɕς���
		ChangeTarget(pTarget);

		//���̍U���ł��ꂽ��A����̃L���|�C���g�𑝂₷
		if (HitDamage(((Character*)pTarget)->GetStatus().attackPower)) {
			Status status = ((Character*)pTarget)->GetStatus();
			status.killPoint++;
			((Character*)pTarget)->SetStatus(status);
			((Character*)pTarget)->TellStatus();
			DieEffect();
		}
		else {
			HitEffect();
		}
	}
}

// �U���ɓ�����������HP�����炷�֐�
// �����F�H������_���[�W��
// �߂�l�F���̃_���[�W�Ŏ��S������true
bool Character::HitDamage(int damage)
{
	status_.hp -= damage;
	pPlayerUI_->SetNowHp(status_.hp);

	//HP��0�ɂȂ�����
	if (status_.hp <= 0) {
		status_.dead = true;
		Audio::Play(hSoundEffect_[DEAD]);
		return status_.dead;
	}

	Audio::Play(hSoundEffect_[HIT]);
	return status_.dead;
}

// �X�e�[�^�X���Q�[���J�n���Ƀ��Z�b�g����֐��iwinPoint�͂��̂܂܁j
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

//�`����~�߂�
void Character::StopDraw()
{
	Visible();
	pPlayerUI_->StopDraw();
}

//�`���������
void Character::StartDraw()
{
	Invisible();
	pPlayerUI_->StartDraw();
}

//UI�̕`����~�߂�
void Character::StopDrawUI()
{
	pPlayerUI_->StopDraw();
}

//�X�e�[�^�X��dead��true�ɂ���i���g�p�j
void Character::Dead()
{
	status_.dead = true;
}


// ���݂�state��ς���
// �����F����state
void Character::ChangeState(CharacterStateList nextState)
{
	pState_->ChangeState(nextState);
}

//�v���C���[UI�̏ꏊ���Z�b�g����
void Character::SetUIPos(XMFLOAT3 pos)
{
	pPlayerUI_->SetPlayerUIPos(pos);
}

//�L�����N�^�[�̖��O���Z�b�g����
void Character::SetCharacterName(std::string name)
{
	status_.playerName = name;
	pPlayerUI_->SetPlayerName(name);
}

//�U����H��������̃G�t�F�N�g
void Character::HitEffect()
{

	//�΂̕�
	EmitterData data;
	data.textureFileName = "VFX/cloudA.png";
	data.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + 1.5f, transform_.position_.z);
	data.delay = 0;
	data.speedRnd = 0.0;
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.color = XMFLOAT4(1, 1, 0, 1);
	data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
	data.number = 40;
	data.positionRnd = XMFLOAT3(0.5, 0.5, 0.5);
	data.direction = targetRot_;
	data.directionRnd = XMFLOAT3(90, 90, 90);
	data.size = XMFLOAT2(0.3, 0.3);
	data.scale = XMFLOAT2(0.9, 0.9);
	data.lifeTime = 15;
	data.speed = 0.2f;
	VFX::Start(data);
}

//���񂾎��ɂł�G�t�F�N�g
void Character::DieEffect()
{
	EmitterData data;

	//���i�����{�́j
	data.textureFileName = "VFX/cloudA.png";
	data.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + 1.5f, transform_.position_.z);
	data.delay = 0;
	data.number = 80;
	data.lifeTime = 30;
	data.direction = XMFLOAT3(0, 1, 0);
	data.directionRnd = XMFLOAT3(90, 90, 90);
	data.speed = 0.1f;
	data.speedRnd = 0.8;
	data.size = XMFLOAT2(1.2, 1.2);
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.05, 1.05);
	data.color = XMFLOAT4(1, 1, 0.1, 1);
	data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
	VFX::Start(data);

	//�΂̕�
	data.delay = 0;
	data.number = 80;
	data.lifeTime = 100;
	data.positionRnd = XMFLOAT3(0.5, 0, 0.5);
	data.direction = XMFLOAT3(0, 1, 0);
	data.directionRnd = XMFLOAT3(90, 90, 90);
	data.speed = 0.25f;
	data.speedRnd = 1;
	data.accel = 0.93;
	data.size = XMFLOAT2(0.1, 0.1);
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(0.99, 0.99);
	data.color = XMFLOAT4(1, 1, 0.1, 1);
	data.deltaColor = XMFLOAT4(0, 0, 0, 0);
	data.gravity = 0.003f;
	VFX::Start(data);

}


