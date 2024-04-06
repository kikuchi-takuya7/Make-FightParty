#include "Character.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"
#include "../Engine/Audio.h"
#include "../Engine/VFX.h"
#include "../Stage/CreateMode/StageSource/Bullet.h"
#include "../Stage/CreateMode/StageSource/Needle.h"
#include "../Stage/CreateMode/StageSource/StageSourceBase.h"
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
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1.5, 0.5, 3);

	const int PLAYER_MAX_NUM = 4;
}

//namespace HitEffectData {
//	std::string FILENAME = "VFX/cloudA.png";			//�摜�t�@�C����
//	XMFLOAT3 POSITIONRND = XMFLOAT3(0.5f, 0.5f, 0.5f);	//�ʒu�̌덷
//	XMFLOAT3 DIRECTIONRND = XMFLOAT3(90, 90, 90);		//�ړ������̌덷�i�e���̊p�x�j
//	float	 SPEED = 0.2f;			//1�t���[���̑��x
//	float	 SPEEDRND = ZERO;		//���x�덷�i0�`1�j
//	float	 ACCEL = 1.0f;			//�����x
//	float	 GRAVITY = 0.0f;		//�d��
//	XMFLOAT4 COLOR = XMFLOAT4(1, 1, ZERO, 1);					//�F�iRGBA 0�`1�j
//	XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, -0.03f, ZERO, -0.02f);	//�F�̕ω���
//	XMFLOAT3 ROTATE = XMFLOAT3(ZERO, ZERO, ZERO);		//�e���ł̊p�x
//	XMFLOAT3 ROTATERND = XMFLOAT3(ZERO, ZERO, ZERO);	//�p�x�덷
//	XMFLOAT3 SPIN = XMFLOAT3(ZERO, ZERO, ZERO);			//��]���x
//	XMFLOAT2 SIZE = XMFLOAT2(0.3, 0.3f);			//�T�C�Y
//	XMFLOAT2 SIZERND = XMFLOAT2(0.4, 0.4f);			//�T�C�Y�덷�i0�`1�j
//	XMFLOAT2 SCALE = XMFLOAT2(0.9f, 0.9f);			//1�t���[���̊g�嗦
//	DWORD	 LIFETIME = 15;		//�p�[�e�B�N���̎����i�t���[�����j
//	DWORD	 DELAY = ZERO;		//���t���[�������Ƀp�[�e�B�N���𔭐������邩
//	DWORD	 NUMBER = 40;		//1�x�ɏo���p�[�e�B�N����
//	bool	 ISBILLBOARD;		//�r���{�[�h���ǂ���
//}
//
//namespace DieEffect {
//	namespace Explosion {
//		std::string FILENAME = "VFX/cloudA.png";				//�摜�t�@�C����	
//		XMFLOAT3 POSITIONRND = ZERO_FLOAT3;						//�ʒu�̌덷
//		XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1.0f, ZERO);		//�ړ�����
//		XMFLOAT3 DIRECTIONRND = XMFLOAT3(90, 90, 90);			//�ړ������̌덷�i�e���̊p�x�j
//		float	 SPEED = 0.1f;			//1�t���[���̑��x
//		float	 SPEEDRND = 0.8f;		//���x�덷�i0�`1�j
//		float	 ACCEL = 1.0f;			//�����x
//		float	 GRAVITY = 0.0f;		//�d��
//		XMFLOAT4 COLOR = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);					//�F�iRGBA 0�`1�j
//		XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, -1.0 / 20, ZERO, -1.0 / 20);	//�F�̕ω���
//		XMFLOAT3 ROTATE;		//�e���ł̊p�x
//		XMFLOAT3 ROTATERND;		//�p�x�덷
//		XMFLOAT3 SPIN;			//��]���x
//		XMFLOAT2 SIZE = XMFLOAT2(1.2f, 1.2f);			//�T�C�Y
//		XMFLOAT2 SIZERND = XMFLOAT2(0.4, 0.4f);			//�T�C�Y�덷�i0�`1�j
//		XMFLOAT2 SCALE = XMFLOAT2(1.05f, 1.05f);			//1�t���[���̊g�嗦
//		DWORD	 LIFETIME = 30;		//�p�[�e�B�N���̎����i�t���[�����j
//		DWORD	 DELAY = ZERO;		//���t���[�������Ƀp�[�e�B�N���𔭐������邩
//		DWORD	 NUMBER = 80;		//1�x�ɏo���p�[�e�B�N����
//		bool	 ISBILLBOARD;		//�r���{�[�h���ǂ���
//	}
//	namespace FireSpark {
//		std::string FILENAME = "VFX/cloudA.png";			//�摜�t�@�C����
//		XMFLOAT3 POSITIONRND = XMFLOAT3(0.5f, ZERO, 0.5f);	//�ʒu�̌덷
//		XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1, ZERO);		//�ړ�����
//		XMFLOAT3 DIRECTIONRND = XMFLOAT3(90, 90, 90);		//�ړ������̌덷�i�e���̊p�x�j
//		float	 SPEED = 0.25f;			//1�t���[���̑��x
//		float	 SPEEDRND = 1.0f;		//���x�덷�i0�`1�j
//		float	 ACCEL = 0.93f;			//�����x
//		float	 GRAVITY = 0.003f;		//�d��
//		XMFLOAT4 COLOR = XMFLOAT4(1, 1, 0.1f, 1);					//�F�iRGBA 0�`1�j
//		XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, ZERO, ZERO, ZERO);		//�F�̕ω���
//		XMFLOAT3 ROTATE;		//�e���ł̊p�x
//		XMFLOAT3 ROTATERND;		//�p�x�덷
//		XMFLOAT3 SPIN;			//��]���x
//		XMFLOAT2 SIZE = XMFLOAT2(0.1f, 0.1f);				//�T�C�Y
//		XMFLOAT2 SIZERND = XMFLOAT2(0.4f, 0.4f);			//�T�C�Y�덷�i0�`1�j
//		XMFLOAT2 SCALE = XMFLOAT2(0.99f, 0.99f);			//1�t���[���̊g�嗦
//		DWORD	 LIFETIME = 100;		//�p�[�e�B�N���̎����i�t���[�����j
//		DWORD	 DELAY = ZERO;			//���t���[�������Ƀp�[�e�B�N���𔭐������邩
//		DWORD	 NUMBER = 80;			//1�x�ɏo���p�[�e�B�N����
//		bool	 ISBILLBOARD;			//�r���{�[�h���ǂ���
//	}
//
//}

//�R���X�g���N�^
Character::Character(GameObject* parent,std::string name)
	:GameObject(parent, name), hModel_(-1),status_(Status(CHARACTER_HP, CHARACTER_ATTACK_POWER, false, ZERO, ZERO, ZERO, "NONE")),
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
	using namespace HitEffectData;

	//�΂̕�
	EmitterData data;
	data.textureFileName = FILENAME;
	data.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + 1.5f, transform_.position_.z);
	data.positionRnd = POSITIONRND;
	data.direction = targetRot_;
	data.directionRnd = DIRECTIONRND;
	data.speed = SPEED;
	data.speedRnd = SPEEDRND;
	data.color = COLOR;
	data.deltaColor = DELTACOLOR;
	data.size = HitEffectData::SIZE;
	data.sizeRnd = SIZERND;
	data.scale = SCALE;
	data.lifeTime = LIFETIME;
	data.delay = DELAY;
	data.number = NUMBER;

	
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
		data.direction = DIRECTION;
		data.directionRnd = DIRECTIONRND;
		data.speed = SPEED;
		data.speedRnd = SPEEDRND;
		data.color = COLOR;
		data.deltaColor = DELTACOLOR;
		data.size = Explosion::SIZE;
		data.sizeRnd = SIZERND;
		data.scale = SCALE;
		data.lifeTime = LIFETIME;
		data.delay = DELAY;
		data.number = NUMBER;

		VFX::Start(data);
	}
	

	//�΂̕�
	{
		using namespace FireSpark;

		data.positionRnd = POSITIONRND;
		data.direction = DIRECTION;
		data.directionRnd = DIRECTIONRND;
		data.speed = SPEED;
		data.speedRnd = SPEEDRND;
		data.accel = FireSpark::ACCEL;
		data.gravity = GRAVITY;
		data.color = COLOR;
		data.deltaColor = DELTACOLOR;
		data.size = FireSpark::SIZE;
		data.sizeRnd = SIZERND;
		data.scale = SCALE;
		data.lifeTime = LIFETIME;
		data.delay = DELAY;
		data.number = NUMBER;

		VFX::Start(data);
	}

}


