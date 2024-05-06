#include "Character.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"
#include "../Engine/Audio.h"
#include "../Engine/VFX.h"
#include "../Stage/CreateMode/StageSource/Bullet.h"
#include "../Stage/CreateMode/StageSource/Needle.h"
#include "../Stage/CreateMode/StageSource/StageSourceBase.h"
#include "../Stage/CreateMode/StageSource/Mud.h"
#include "../Stage/CreateMode/StageSource/RotateBlade.h"
#include "../UI/PlayerUI.h"
#include "CharacterState/CharacterStateManager.h"
#include "../VFXData/VFXData.h"

//��b�X�e�[�^�X��
namespace {
	const int CHARACTER_HP = 100;
	const int CHARACTER_ATTACK_POWER = 25;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(0.9, 2, 0.9);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1.5, 0.5, 3.0);

	const int PLAYER_MAX_NUM = 4;

	const float DEFAULT_MOVE_SPEED = 0.12f;
}

//�R���X�g���N�^
Character::Character(GameObject* parent,std::string name)
	:GameObject(parent, name), hModel_(-1),status_(Status(CHARACTER_HP, CHARACTER_ATTACK_POWER, DEFAULT_MOVE_SPEED, false, ZERO, ZERO, ZERO, "NONE")),
	pState_(nullptr), pBodyCollision_(nullptr), pAttackCollision_(nullptr), startPos_(ZERO_FLOAT3), hSoundEffect_{-1,-1}
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

	//�D�𓥂񂾎��̈ړ����x��߂��p
	status_.moveSpeed = DEFAULT_MOVE_SPEED;

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
	//��������Ȃ�
	if (IsEntered() == false) {
		return;
	}

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

	//������̍U���ɓ����������̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_BULLET) {

		HitDamage(static_cast<Bullet*>(pTarget)->GetBulletPower());
		SetTargetRotate(pTarget->GetRotate());
		pState_->ChangeState(KNOCKBACK);

	}

	//��]����n����̍U���ɓ����������̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_OBJ_ATTACK) {

		HitDamage(static_cast<RotateBlade*>(pTarget)->GetAttackPower());
		SetTargetRotate(pTarget->GetRotate());
		pState_->ChangeState(KNOCKBACK);

	}

	//�g�Q�ɓ����������̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_NEEDLE) {
		HitDamage(static_cast<Needle*>(pTarget)->GetNeedlePower());
	}

	//�D�ɓ����������̏��� 
	if (myType == COLLIDER_BODY && targetType == COLLIDER_MUD) {
		float deceleration = static_cast<Mud*>(pTarget)->GetDeceleration();
		status_.moveSpeed = DEFAULT_MOVE_SPEED * deceleration;
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
	if (status_.hp <= ZERO) {
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

	//�X�e�[�^�X��������
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
	using namespace HitEffect;

	//�΂̕�
	EmitterData data;
	data.textureFileName = FILENAME;
	data.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + 1.5f, transform_.position_.z);
	data.positionRnd = POSITIONRND;
	data.direction = targetRot_;
	data.directionRnd = DIRECTIONRND;
	data.speed = SPEED;
	data.speedRnd = SPEEDRND;
	data.accel = HitEffect::ACCEL;
	data.gravity = GRAVITY;
	data.color = COLOR;
	data.deltaColor = DELTACOLOR;
	data.rotate = ROTATE;
	data.rotateRnd = ROTATERND;
	data.spin = SPIN;
	data.size = HitEffect::SIZE;
	data.sizeRnd = SIZERND;
	data.scale = SCALE;
	data.lifeTime = LIFETIME;
	data.delay = DELAY;
	data.number = NUMBER;
	data.isBillBoard = ISBILLBOARD;
	
	VFX::Start(data);
}

//���񂾎��ɂł�G�t�F�N�g
void Character::DieEffect()
{

	using namespace DieEffect;

	EmitterData data;

	//���i�����{�́j
	{
		using namespace Explosion;

		data.textureFileName = FILENAME;
		data.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + 1.5f, transform_.position_.z);
		data.positionRnd = POSITIONRND;
		data.direction = targetRot_;
		data.directionRnd = DIRECTIONRND;
		data.speed = SPEED;
		data.speedRnd = SPEEDRND;
		data.accel = Explosion::ACCEL;
		data.gravity = GRAVITY;
		data.color = COLOR;
		data.deltaColor = DELTACOLOR;
		data.rotate = ROTATE;
		data.rotateRnd = ROTATERND;
		data.spin = SPIN;
		data.size = Explosion::SIZE;
		data.sizeRnd = SIZERND;
		data.scale = SCALE;
		data.lifeTime = LIFETIME;
		data.delay = DELAY;
		data.number = NUMBER;
		data.isBillBoard = ISBILLBOARD;

		VFX::Start(data);
	}
	

	//�΂̕�
	{
		using namespace FireSpark;

		data.positionRnd = POSITIONRND;
		data.direction = targetRot_;
		data.directionRnd = DIRECTIONRND;
		data.speed = SPEED;
		data.speedRnd = SPEEDRND;
		data.accel = FireSpark::ACCEL;
		data.gravity = GRAVITY;
		data.color = COLOR;
		data.deltaColor = DELTACOLOR;
		data.rotate = ROTATE;
		data.rotateRnd = ROTATERND;
		data.spin = SPIN;
		data.size = FireSpark::SIZE;
		data.sizeRnd = SIZERND;
		data.scale = SCALE;
		data.lifeTime = LIFETIME;
		data.delay = DELAY;
		data.number = NUMBER;
		data.isBillBoard = ISBILLBOARD;

		VFX::Start(data);
	}

}


