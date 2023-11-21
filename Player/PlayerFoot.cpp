#include "PlayerFoot.h"
#include "../Engine/Model.h"
#include <cmath>

//�R���X�g���N�^
PlayerFoot::PlayerFoot(GameObject* parent)
    :GameObject(parent, "PlayerFoot"), hModel_{-1,-1}
{
}

//�f�X�g���N�^
PlayerFoot::~PlayerFoot()
{
}

//������
void PlayerFoot::Initialize()
{
    //���f���f�[�^�̃��[�h
    std::string fileName[NUM] = {
        "PlayerFbx/FootLegs.fbx",
        "PlayerFbx/ThighLegs.fbx"
    };
    for (int i = 0; i < NUM; i++) {
        hModel_[i] = Model::Load(fileName[i]);
        assert(hModel_[i] >= 0);
    }
    
}

//�X�V
void PlayerFoot::Update()
{
    //�ڕW�n�_�i�����ׂ������j
    XMVECTOR goal = { -5,0,0,0 };
    
    //���f���̒���
    float xLen = 4.0f;

    //�S�[���̃x�N�g���̒���
    float yLength = Length(goal);

    //���f���ƖڕW�n�_���Ȃ��Ζʁi�O�����̒藝�j
    float slope = std::hypot(xLen, yLength);

    //�ڕW�ʒu�����[�J�����W��( ��������Ȃ�)
     
    
    //���[�J�����W����O�p���p���ĐF�X�v�Z����

    float cosZ = std::cos(xLen);


}

//�`��
void PlayerFoot::Draw()
{
    Model::SetTransform(hModel_[0], transform_);
    Model::Draw(hModel_[0]);
}

//�J��
void PlayerFoot::Release()
{
}