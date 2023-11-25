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
        "PlayerFbx/HandArms.fbx",
        "PlayerFbx/ThighLegs.fbx"
    };
    for (int i = 0; i < NUM; i++) {
        hModel_[i] = Model::Load(fileName[i]);
        assert(hModel_[i] >= 0);
    }
    
    footTrans_ = transform_;
    //footTrans_.rotate_.x = 90.0f;
}

//�X�V
void PlayerFoot::Update()
{
    static int tmp = 0;

    if (Input::IsKey(DIK_Z)) {
        tmp += 1;
    }

    //�ڕW�n�_�i�����ׂ������j
    XMVECTOR goal = { 5,5,5,0 };


    //�@�܂�y���ŉ�]�����ĉ��������킹��
    //�A����z�����g���ďc�����킹��
    //�B�Ō��x���ŉ�]������H���f�����������ɂ���x���ɍ����悤�Ɋw�Z�Ŏ������Ă��r�͂�������Ă邩�瑫���S���r�ł����񂶂��

    //rotate�ŉ�]�����Ă�����͂����܂�position���ɉ�]�����ĂāAposition�͎w�肵���ʒu����ς���ĂȂ�����rotate�ŉ�]�������Ƃ��Ă�����position���ς���ĂȂ����炻�̎��������B

    //
    footTrans_.position_.x = 10.0f;
    footTrans_.position_.y = 1.0f;
    footTrans_.position_.z = 5.0f;
    XMFLOAT3 f = footTrans_.position_;
    f.y = 0;
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

    //Y����]�����邽�߂̕ϐ�
    XMVECTOR goalY = goal;
    goalY = XMVectorSetY(goal, 0);

    XMVECTOR goalN = XMVector3Normalize(goalY);
    XMVECTOR nowPosN = XMVector3Normalize(nowPos);
    XMVECTOR dot = XMVector3Dot(goalN, nowPosN); //���ς����߂�
    float dotLen = XMVectorGetX(dot);

    //�T�C�g�Ɠ����悤�ɂ���Ă݂�
    //XMVECTOR cosSZ = nowPos / (nowPos * nowPos) + (goal * goal);

    //�����x����]�̊p�x
    float cosZ = acos(dotLen);
    
    XMMATRIX rotX = XMMatrixIdentity();

    rotX = XMMatrixRotationX(cosZ);   //X���ŉ�]�s��

    //rotX = XMMatrixRotationX(XMConvertToRadians(45));

    //footTrans_.rotate_.x = XMConvertToDegrees(cosZ);

    //X����]�s���K�p
    nowPos = XMVector3TransformCoord(nowPos, rotX);
    XMStoreFloat3(&footTrans_.position_, nowPos);

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

void PlayerFoot::Imgui_Window()
{
    ImGui::Begin("DataWindow");
    if (ImGui::CollapsingHeader("MapEditor"))
    {
    }

    if (ImGui::TreeNode("Object")) {//Object�̃c���[���N���b�N�����


        ImGui::TreePop();
    }

    ImGui::End();
}
