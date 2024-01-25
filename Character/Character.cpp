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

}

//�J��
void Character::Release()
{

}

void Character::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//���������Ƃ��̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		
	}

	//�U���𓖂Ă����̏���
	if (myType == COLLIDER_ATTACK && targetType == COLLIDER_BODY)
	{
		((Character*)pTarget)->HitDamage(status_.attackPower);
	}
}

void Character::HitDamage(int damage)
{
	status_.hp -= damage;



}

