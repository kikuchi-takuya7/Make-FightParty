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
    
    //�r�̒������]���ɉ��Ɉړ������悤�ˁB���ꂪ���R�ɓ��������[�̈ʒu
    /*transform_.position_.x = 4.0f;
    transform_.position_.y = 1.0f;
    transform_.position_.z = 5.0f;*/

    footTrans_ = transform_;

    //�r�̒������]���ɉ��Ɉړ������悤�ˁB���ꂪ���R�ɓ��������[�̈ʒu
    footTrans_.position_.x = 4.0f;
    footTrans_.position_.y = 1.0f;
    footTrans_.position_.z = 5.0f;

    //���f���̍�����position
    footRoot_ = footTrans_;
    
    footRoot_.position_.x += -4.0f;

    
}

//�X�V
void PlayerFoot::Update()
{

    //�@�܂�y���ŉ�]�����ĉ��������킹��
    //�A����z�����g���ďc�����킹��
    //�B�Ō��x���ŉ�]������H���f�����������ɂ���x���ɍ����悤�Ɋw�Z�Ŏ������Ă��r�͂�������Ă邩�瑫���S���r�ł����񂶂��

    //���f��.position�Ń��f���̉�]���鍪�{���w���āA�����x�i�����̒����j�𑫂��������[position�Ƃ���B�i���s�ړ��s��ŉ��ړ������Ă���p�x�̉�]�s���������΂������ȁj
    //�p�x���o�����烂�f��.rotate�ŉ�]�����āA

    //�ڕW�n�_�i�����ׂ������j
    XMVECTOR goal = { 5,5,5,0 };

    //���݂̃x�N�g��
    XMFLOAT3 tmpFloat = footTrans_.position_;
    tmpFloat.y = 0;
    
    //��[�̈ʒu�̃x�N�g��
    XMVECTOR nowPos = XMLoadFloat3(&tmpFloat);


    //�ڕW�ʒu�����[�J�����W��( ��������Ȃ��H)
     
    
    //���[�J�����W����O�p���p���ĐF�X�v�Z����
    //x���ɉ�]�����Ă���y���ɉ�]�����悤�̊����i�Z�K�̃T�C�g�ʂ�ɏ����Ă邩��x�����ۂ����ǈႤ��������j

    //Y����]�����邽�߂̕ϐ�
    XMVECTOR goalTmp = goal;
    goalTmp = XMVectorSetY(goal, 0);

    XMVECTOR goalN = XMVector3Normalize(goalTmp);
    XMVECTOR nowPosN = XMVector3Normalize(nowPos);
    XMVECTOR dot = XMVector3Dot(goalN, nowPosN); //���ς����߂�
    float dotLen = XMVectorGetX(dot);

    //�����y����]�̊p�x
    float cos = acos(dotLen);
    
    XMMATRIX rotX = XMMatrixIdentity();

    rotX = XMMatrixRotationX(cos);   //X���ŉ�]�s��

    //rotX = XMMatrixRotationX(XMConvertToRadians(45));

    footRoot_.rotate_.y = XMConvertToDegrees(cos);

    //X����]�s���K�p
    /*nowPos = XMVector3TransformCoord(nowPos, rotX);
    XMStoreFloat3(&f, nowPos);*/


    ///////////////��������c����]////////////

    tmpFloat = footTrans_.position_;
    tmpFloat.z = 0;

    nowPos = XMLoadFloat3(&tmpFloat);

    //z����]�����邽�߂̕ϐ�
    goalTmp = goal;
    goalTmp = XMVectorSetZ(goal, 0);

    goalN = XMVector3Normalize(goalTmp);
    nowPosN = XMVector3Normalize(nowPos);
    dot = XMVector3Dot(goalN, nowPosN); //���ς����߂�
    dotLen = XMVectorGetX(dot);

    //�����z����]�̊p�x
    cos = acos(dotLen);

    footRoot_.rotate_.z = XMConvertToDegrees(cos);

    //�����footRoot��rotate�̓S�[���̌����Ɍ��������Ă����z��B�������낤����
    //footRoot.rotate���̉�]�s������������Ƃɕ��s�ړ��s��

    //footRoot.rotate�̕�������]
    XMMATRIX rotZ,rotY;
    rotY = XMMatrixRotationY(XMConvertToRadians(footRoot_.rotate_.y));
    rotZ = XMMatrixRotationZ(XMConvertToRadians(footRoot_.rotate_.z));

    XMMATRIX rotMatrix = rotY * rotZ;

     //�r�̒������������s�ړ�������
    XMMATRIX moveLen = XMMatrixTranslation(4, 0, 0);

    //�x�N�g���ɂ��čs���K�p������B���f���̒������������Ă邩�烂�f���̍�����position���x�N�g����
    tmpFloat = footRoot_.position_;

    nowPos = XMLoadFloat3(&tmpFloat);
    nowPos = XMVector3TransformCoord(nowPos, rotMatrix * moveLen);

    //�s���K�p�����x�N�g����footTrans�ɓ����BfootRoot�̈ʒu���烂�f���̒������p�x�����ĐL�΂����ʒu�ɂ���͂�
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
