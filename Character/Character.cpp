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
