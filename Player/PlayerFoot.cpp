#include "PlayerFoot.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include <cmath>

//���f���̒���
const float MODELLENGTH = 4.0f;

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
    
    /*transform_.position_.x = 4.0f;
    transform_.position_.y = 1.0f;
    transform_.position_.z = 5.0f;*/

    footRoot_ = transform_;

    //���f�����{�̈ʒu
    footRoot_.position_.x += 0.0f;
    footRoot_.position_.y += 0.0f;
    footRoot_.position_.z += 0.0f;

    //���f���̐�[��position
    footTrans_ = footRoot_;
    
    //���f���̒�����4�ɂ��Ă邩��
    footTrans_.position_.x += MODELLENGTH;

    
}

//�X�V
void PlayerFoot::Update()
{

    //�@�܂�y���ŉ�]�����ĉ��������킹��
    //�A����z�����g���ďc�����킹��
    //�B�Ō��x���ŉ�]������H���f�����������ɂ���x���ɍ����悤�Ɋw�Z�Ŏ������Ă��r�͂�������Ă邩�瑫���S���r�ł����񂶂��

    //���f��.position�Ń��f���̉�]���鍪�{���w���āA�����x�i�����̒����j�𑫂��������[position�Ƃ���B�i���s�ړ��s��ŉ��ړ������Ă���p�x�̉�]�s���������΂������ȁj
    //�p�x���o�����烂�f��.rotate�ŉ�]�����āA

    //�ڕW�n�_(�����ׂ������ŁA�ŏI�I�Ȑ�[�̈ʒu)
    XMVECTOR goal = { 4,4,4,0 };

    //���݂̃x�N�g���i��[�j
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

    //���{����񂷂��獪������]������
    footRoot_.rotate_.y = XMConvertToDegrees(cos);

    ///////////////��������c����]////////////
    //y����]�����Ă���z����]

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

    //���{����񂷂��獪������]������
    footRoot_.rotate_.z = XMConvertToDegrees(cos);

    //�����footRoot��rotate�̓S�[���̌����Ɍ��������Ă����z��B
    //footRoot.rotate���̉�]�s������������Ƃɕ��s�ړ��s��

    //footRoot.rotate�̕�������]
    XMMATRIX rotZ,rotY;
    rotY = XMMatrixRotationY(XMConvertToRadians(footRoot_.rotate_.y));
    rotZ = XMMatrixRotationZ(XMConvertToRadians(footRoot_.rotate_.z));

    XMMATRIX rotMatrix = rotY * rotZ;

     //�r�̒������������s�ړ�������
    XMMATRIX moveLen = XMMatrixTranslation(MODELLENGTH, 0, 0);

    //�x�N�g���ɂ��čs���K�p������B���f���̍�����position���x�N�g����
    //���s�ړ�������K�v�Ȃ��Ȃ�܂��s�񂢂�Ȃ��H
    tmpFloat = footRoot_.position_;

    nowPos = XMLoadFloat3(&tmpFloat);
    nowPos = XMVector3TransformCoord(nowPos, rotMatrix);

    //�s���K�p�����x�N�g����footTrans�ɓ����BfootRoot�̈ʒu���烂�f���̒������p�x�����ĐL�΂����ʒu�ɂ���͂��B�����Ă��ꂪ�S�[���̈ʒu�̂͂�
    XMStoreFloat3(&footRoot_.position_, nowPos);

    //��[��Transform�����f���Ɖ�悤�ɉ�]������
    /*footRoot_.rotate_.y = footTrans_.rotate_.y;
    footRoot_.rotate_.z = footTrans_.rotate_.z;*/
}

//�`��
void PlayerFoot::Draw()
{
    Model::SetTransform(hModel_[0], footRoot_);
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
