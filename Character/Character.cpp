#include "Character.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"
#include "../Stage/CreateMode/StageSource/Bullet.h"
#include "../Stage/CreateMode/StageSource/StageSourceBase.h"

namespace {
	const int CHARACTER_HP = 100;
	const int CHARACTER_ATTACK_POWER = 20;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

//�R���X�g���N�^
Character::Character(GameObject* parent,std::string name)
	:GameObject(parent, name), hModel_(-1),pBodyCollision_(nullptr),pAttackCollision_(nullptr), startPos_(ZERO_FLOAT3),stopDraw_(false)
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

	status_ = { CHARACTER_HP,CHARACTER_ATTACK_POWER, 0, false };



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

	


	ChildUpdate();


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

	//�������ȊO�ACollision�͏����Ă���̂ł�����DELETE����B�����s���ɏ����ƃG���[�ɂȂ�
	//�Ă�����nullptr����Ă�͂��Ȃ̂ɂȂ���O���o��̂�
	SAFE_DELETE(pAttackCollision_);
	SAFE_DELETE(pBodyCollision_);
	
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

	if (myType == COLLIDER_BODY && targetType == COLLIDER_BULLET) {

		//HitDamage(static_cast<Bullet*>(pTarget)->GetAttackPower());

	}

	ChildOnCollision(pTarget, myType, targetType);
}

void Character::HitDamage(int damage)
{
	status_.hp -= damage;

	//HP��0�ɂȂ�����
	if (status_.hp <= 0) {
		status_.dead = true;
	}
}

void Character::StopDraw()
{
	stopDraw_ = true;
}

void Character::StartDraw()
{
	stopDraw_ = false;
}

void Character::Dead()
{
	status_.dead = true;
}

void Character::KnockBackEnter(float distance)
{
	//�F�X������
	knockBackRate_ = 0.0f;


	//�G�̌����Ă�����ɉ�]�����邽�߉�]���t�ɂ���
	targetRot_.y = targetRot_.y - 180;
	this->SetRotateY(targetRot_.y);


	//�v���C���[�̌��݂̈ʒu���x�N�g���^�ɕϊ�
	XMFLOAT3 floatPos = this->GetPosition();
	XMVECTOR pos = XMLoadFloat3(&floatPos);

	//�ŏ��ɍŏI�I�Ȉʒu���m�F���Ă���
	XMVECTOR move = { ZERO, ZERO, distance, ZERO };

	//�ړ��x�N�g����ό` (�G�Ɠ��������ɉ�]) ������
	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(targetRot_.y));
	move = XMVector3TransformCoord(move, rotY);

	//�v���C���[��G�Ɣ��Ε����Ɉړ�������
	pos -= move;

	lastPoint_ = VectorToFloat3(pos);

	if (lastPoint_.x <= 0.5) {
		lastPoint_.x = 0;
	}
	if (lastPoint_.x >= 28.5) {
		lastPoint_.x = 28.5;
	}
	if (lastPoint_.z <= 0.5) {
		lastPoint_.z = 0.5;
	}
	if (lastPoint_.z >= 28.5) {
		lastPoint_.z = 28.5;
	}

}

void Character::KnockBackUpdate(float knockBackSpeed)
{

	//�G�̌����Ă���������~����.�ł����Enter�̎��_�Ŕ�΂������W������Ă����āA�����ɒ������瓮������Ċ����ɂ������B�ɋ}�t����

	//�v���C���[�̌��݂̈ʒu���x�N�g���^�ɕϊ�
	XMFLOAT3 playerPos = GetPosition();

	RateMovePosition(playerPos, lastPoint_, knockBackSpeed);

	SetPosition(playerPos);

}

float Character::GetRateValue(float begin, float end, float rate)
{
	return (end - begin) * rate + begin;
}


