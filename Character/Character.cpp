#include "Character.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"


//�R���X�g���N�^
Character::Character(GameObject* parent,std::string name)
	:GameObject(parent, name), hModel_(-1),pBodyCollision_(nullptr),pAttackCollision_(nullptr)
{
}

//�f�X�g���N�^
Character::~Character()
{
}

//������
void Character::Initialize()
{

	ChildInitialize();
}

//�X�V
void Character::Update()
{

	//����ł鎞�Ƃ��A�b�v�f�[�g�������Ȃ��Ƃ��ɂ����Ŏ~�߂��Ⴆ�΂���

	ChildUpdate();
}

//�`��
void Character::Draw()
{
	ChildDraw();
}

//�J��
void Character::Release()
{
	ChildRelease();
}

void Character::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
}

void Character::HitDamage(int damage)
{
	status_.hp -= damage;



}

void Character::SetAttackCollider()
{
	AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK);
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

	if (lastPoint_.x <= 0) {
		lastPoint_.x = 0;
	}
	if (lastPoint_.x >= 29) {
		lastPoint_.x = 29;
	}
	if (lastPoint_.z <= 0) {
		lastPoint_.z = 0;
	}
	if (lastPoint_.z >= 29) {
		lastPoint_.z = 29;
	}

	//player->SetPosition(VectorToFloat3(pos));
}

void Character::KnockBackUpdate(int rigidityFlame)
{

	//�G�̌����Ă���������~����.�ł����Enter�̎��_�Ŕ�΂������W������Ă����āA�����ɒ������瓮������Ċ����ɂ������B�ɋ}�t����

	//�v���C���[�̌��݂̈ʒu���x�N�g���^�ɕϊ�
	XMFLOAT3 playerPos = this->GetPosition();

	//���[�g�łʂ�ʂ铮���悤��
	if (knockBackRate_ < 1.0f) {
		knockBackRate_ += 0.05f;

		// �ςȐ����Ŏ~�܂�Ȃ��悤��
		if (knockBackRate_ > 1.0f)
			knockBackRate_ = 1.0f;

		playerPos.x = GetRateValue(playerPos.x, lastPoint_.x, knockBackRate_);
		playerPos.z = GetRateValue(playerPos.z, lastPoint_.z, knockBackRate_);

		this->SetPosition(playerPos);

	}
}

float Character::GetRateValue(float begin, float end, float rate)
{
	return (end - begin) * rate + begin;
}


