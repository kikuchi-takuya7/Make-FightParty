#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),hModel_(-1)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("PlayerFbx/Body.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void Player::Update()
{
    pState_->Update(this);
    

}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}

//��Ԃ�ύX
void Player::ChangeState(PlayerState nextState)
{
}
