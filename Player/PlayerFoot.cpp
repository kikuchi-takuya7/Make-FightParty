#include "PlayerFoot.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
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
    
    footTrans_ = transform_;

}

//�X�V
void PlayerFoot::Update()
{
    static int tmp = 0;

    if (Input::IsKey(DIK_Z)) {
        tmp += 1;
    }

    //�ڕW�n�_�i�����ׂ������j
    XMVECTOR goal = { 3,5,5,0 };

    //���f���̒��S���[�ɂ��Ă邩��Ƃ肠��������ŁB
    XMFLOAT3 f = footTrans_.position_;
    XMVECTOR nowPos = XMLoadFloat3(&f);

    //���f���̒���
    //float xLen = 4.0f;

    //�S�[���̃x�N�g���̒���
    //float yLength = Length(goal);

    //���f���ƖڕW�n�_���Ȃ��Ζʁi�O�����̒藝�j
    //float slope = std::hypot(xLen, yLength);

    //�ڕW�ʒu�����[�J�����W��( ��������Ȃ�)
     
    
    //���[�J�����W����O�p���p���ĐF�X�v�Z����
    //x���ɉ�]�����Ă���y���ɉ�]�����悤�̊����i�Z�K�̃T�C�g�ʂ�ɏ����Ă邩��x�����ۂ����ǈႤ��������j


    //�x�N�g��������Ȃ����B�I�_�����w�肵�ĂȂ�����n�_���w�肷��ׂ��H��̍��W�����Ńx�N�g�����Ă̂��������Șb�ȋC�����Ă���
    XMVECTOR goalN = XMVector3Normalize(goal);
    XMVECTOR nowPosN = XMVector3Normalize(nowPos);
    XMVECTOR dot = XMVector3Dot(goalN, nowPosN); //���ς����߂�
    float dotLen = XMVectorGetX(dot);

    //�����x����]�̊p�x
    float cosZ = acos(dotLen);
    
    XMMATRIX rotX = XMMatrixIdentity();

    //rotX = XMMatrixRotationX(cosZ);   //X���ŉ�]�s��

    rotX = XMMatrixRotationX(XMConvertToRadians(45));

    footTrans_.rotate_.x = XMConvertToDegrees(cosZ);

    //X����]�s���K�p
    /*nowPos = XMVector3TransformCoord(nowPos, rotX);
    XMStoreFloat3(&footTrans_.position_, nowPos);*/

}

//�`��
void PlayerFoot::Draw()
{
    Model::SetTransform(hModel_[0], footTrans_);
    Model::Draw(hModel_[0]);
}

//�J��
void PlayerFoot::Release()
{
}