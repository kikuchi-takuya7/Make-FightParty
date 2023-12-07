#include "PlayerFoot.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include <cmath>

//���f���̒���
const float MODELLENGTH = 4.0f;

//�R���X�g���N�^
PlayerFoot::PlayerFoot(GameObject* parent)
    :GameObject(parent, "PlayerFoot"), hModel_{-1,-1},hBallModel_(-1)
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

    hBallModel_ = Model::Load("EditorUIFbx/Ball.fbx");
    assert(hBallModel_ >= 0);
    
    /*transform_.position_.x = 4.0f;
    transform_.position_.y = 1.0f;
    transform_.position_.z = 5.0f;*/

    footRootTrans_ = transform_;

    //���f�����{�̈ʒu
    footRootTrans_.position_.x += 0.0f;
    footRootTrans_.position_.y += 0.0f;
    footRootTrans_.position_.z += 0.0f;

    //���f���̐�[��position
    footTipTrans_ = footRootTrans_;
    
    //���f���̒�����4�ɂ��Ă邩��
    footTipTrans_.position_.x += MODELLENGTH;

    goalValue_ = { 0,0,0 };
    prevFootTipPos_ = { 0,0,0 };

    prevCosY_ = 0;
    prevCosZ_ = 0;
    
}

//�X�V
void PlayerFoot::Update()
{

    //�@�܂�y���ŉ�]�����ĉ��������킹��
    //�A����z�����g���ďc�����킹��
    //�B�Ō��x���ŉ�]������H���f�����������ɂ���x���ɍ����悤�Ɋw�Z�Ŏ������Ă��r�͂�������Ă邩�瑫���S���r�ł����񂶂��

    //���f��.position�Ń��f���̉�]���鍪�{���w���āA�����x�i�����̒����j�𑫂��������[position�Ƃ���B�i���s�ړ��s��ŉ��ړ������Ă���p�x�̉�]�s���������΂������ȁj
    //�p�x���o�����烂�f��.rotate�ŉ�]�����āA


    //���[�J�����W����O�p���p���ĐF�X�v�Z����
    //x���ɉ�]�����Ă���y���ɉ�]�����悤�̊����i�Z�K�̃T�C�g�ʂ�ɏ����Ă邩��x�����ۂ����ǈႤ��������j
  

    //�ڕW�n�_(�����ׂ������ŁA�ŏI�I�Ȑ�[�̈ʒu)
    XMVECTOR goal = XMLoadFloat3(&goalValue_);

    /*if (goalValue_ == prevFootTipPos_) {
        return;
    }*/

#if 1

    //��]��-�ɂ��s���悤�ɂ���
    XMFLOAT3 checkGoal;
    XMStoreFloat3(&checkGoal, goal);

    //���݂̃x�N�g���i��[�j
    XMFLOAT3 tmpFloat = footTipTrans_.position_;
    tmpFloat.y = 0;
    
    //��[�̈ʒu�̃x�N�g��
    XMVECTOR nowFootTipPos = XMLoadFloat3(&tmpFloat);

    //Y����]�����邽�߂̕ϐ�
    XMVECTOR goalTmp = goal;
    goalTmp = XMVectorSetY(goal, 0);

    XMVECTOR goalN = XMVector3Normalize(goalTmp);
    XMVECTOR nowFootTipPosN = XMVector3Normalize(nowFootTipPos);
    XMVECTOR dot = XMVector3Dot(goalN, nowFootTipPosN); //���ς����߂�
    float dotLen = XMVectorGetX(dot);

    //�����y����]�̊p�x
    float cos = acos(dotLen);

    float yaw = cos;

    //���{����񂷂��獪������]������
    cos = -XMConvertToDegrees(cos);////////////////////////�Ȃ���y���̉�]���t���������炱���}�C�i�X�ɂ��Ă�B����cos�̎d�l�H

    //cos���}�C�i�X�ɂȂ�悤��
    if (checkGoal.z <= 0) {
        cos *= -1;
    }

    prevCosY_ += cos;
    

    footRootTrans_.rotate_.y = cos;
    

    ///////////////��������c����]///////////////////////
    //y����]�����Ă���z����]

    tmpFloat = footTipTrans_.position_;
    tmpFloat.z = 0;

    nowFootTipPos = XMLoadFloat3(&tmpFloat);

    //z����]�����邽�߂̕ϐ�
    goalTmp = goal;
    goalTmp = XMVectorSetZ(goal, 0);
    //goalTmp = XMVectorSetX(goal, 0);

    goalN = XMVector3Normalize(goalTmp);
    nowFootTipPosN = XMVector3Normalize(nowFootTipPos);
    dot = XMVector3Dot(goalN, nowFootTipPosN); //���ς����߂�
    dotLen = XMVectorGetX(dot);

    //�����z����]�̊p�x
    cos = acos(dotLen);

    float pitch = cos;

    cos = XMConvertToDegrees(cos);

    if (checkGoal.y <= 0) {
        cos *= -1;
    }

    prevCosZ_ += cos;

    //���{����񂷂��獪������]������
    footRootTrans_.rotate_.z = cos;


    ////����ȍs�񂪂��������ǂ܂��g���K�v�͂Ȃ������B
    //XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, 0);

    //nowFootTipPos = XMLoadFloat3(&footTipTrans_.position_);
    //nowFootTipPos = XMVector3Transform(nowFootTipPos, rotMatrix);
    //
    ////�s���K�p�����x�N�g����footTrans�ɓ����BfootRoot�̈ʒu���烂�f���̒������p�x�����ĐL�΂����ʒu�ɂ���͂��B�����Ă��ꂪ�S�[���̈ʒu�̂͂�
    //XMStoreFloat3(&footTipTrans_.position_, nowFootTipPos);

    prevFootTipPos_ = goalValue_;

#else

    //��]��-�ɂ��s���悤�ɂ���
    XMFLOAT3 checkGoal;
    XMStoreFloat3(&checkGoal, goal);

    //���݂̃x�N�g���i��[�j
    XMFLOAT3 tmpFloat = footTipTrans_.position_;
    tmpFloat.y = 0;
    XMVECTOR nowPosXZ = XMLoadFloat3(&tmpFloat);

    //Y�̒l�𖳂�����xz���W�ƍl�����ϐ�
    XMVECTOR goalTmp = goal;
    goalTmp = XMVectorSetY(goal, 0);

    //z�i�T�C�g�ł�y�j�̒��������߂�
    XMVECTOR LengthTmp = goalTmp - nowPosXZ;
    float zLength = Length(LengthTmp);

    tmpFloat = footTipTrans_.position_;
    tmpFloat.z = 0;
    XMVECTOR nowPosXY = XMLoadFloat3(&tmpFloat);

    //Z�̒l�𖳂�����xy���W�ƍl�����ϐ�
    goalTmp = goal;
    goalTmp = XMVectorSetZ(goal, 0);

    //y�i�T�C�g�ł�z�j�̒��������߂�
    LengthTmp = goalTmp - nowPosXY;
    float yLength = Length(LengthTmp);

    //xz���W���猩�����̖ڕW�n�_�܂ł̎Ε�(����)
    float hypotZ = sqrt(pow(MODELLENGTH, 2) + pow(zLength, 2));

    //xy���W���猩�����̎Ε�(����)
    float hypotY = sqrt(pow(MODELLENGTH, 2) + pow(zLength, 2) + pow(yLength, 2));

    //�R�T�C����y�i�T�C�g�ł�z�j
    float cosY = MODELLENGTH / hypotZ;
    float sinY = zLength / hypotZ;
    //�R�T�C����z�i�T�C�g�ł�y�j
    float cosZ = hypotZ / hypotY;
    float sinZ = yLength / hypotY;

    XMVECTOR nowFootTipPos = XMLoadFloat3(&tmpFloat);

    //y���ŉ�]�����]�s������

    XMMATRIX rotY = { cosY,  0,   -sinY, 0,
                      0,     1,    0,    0,
                      sinY,  0,    cosY, 0,
                      0,     0,    0,    1 };

    //�x�N�g���ɉ�]�s�񂩂��Ă����̃x�N�g������]���邾���ō����̉�]���͂킩��Ȃ��B�ł�2�{�[��IK�̎��ɑ����K�v�ɂȂ邩��厖
    nowFootTipPos = XMVector3Transform(nowFootTipPos, rotY);

    XMMATRIX rotY = { cosY,  0,   -sinY, 0,
                      0,     1,    0,    0,
                      sinY,  0,    cosY, 0,
                      0,     0,    0,    1 };



#endif

}

//�`��
void PlayerFoot::Draw()
{
    Model::SetTransform(hModel_[TIP], footRootTrans_);
    Model::Draw(hModel_[TIP]);

    Transform ballTrans;
    ballTrans.position_ = goalValue_;
    Model::SetTransform(hBallModel_, ballTrans);
    Model::Draw(hBallModel_);
}

//�J��
void PlayerFoot::Release()
{
}

void PlayerFoot::Imgui_Window()
{

    ImGui::SetNextWindowPos(ImVec2(875, 400), ImGuiCond_Once);//, ImGuiCond_FirstUseEver�����t����Ə��߂Ď��s�����Ƃ��������̑傫���ɐݒ肳��āB����ȍ~��imgui.ini�ɕۑ������
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Once);//ImGuiCond_Once��t����ƌĂяo���Ƃ��������̑傫���ɂȂ�

    ImGui::Begin("DataWindow");
    if (ImGui::CollapsingHeader("MapEditor"))
    {
        if (ImGui::Button("reset")) {
            goalValue_.x = 0;
            goalValue_.y = 0;
            goalValue_.z = 0;
            goalValue_.x = 0;
        }

        Setting_Float3(goalValue_, -10, 10, "goal");
        ImGui::SliderFloat("rotate_x", &footRootTrans_.rotate_.x, 0, 360);
        
        std::string str = std::to_string(footRootTrans_.rotate_.x);
        ImGui::Text(str.c_str());

        str = std::to_string(footRootTrans_.rotate_.y);
        ImGui::Text(str.c_str());

        str = std::to_string(footRootTrans_.rotate_.z);
        ImGui::Text(str.c_str());
    }

    //if (ImGui::TreeNode("Object")) {//Object�̃c���[���N���b�N�����


    //    ImGui::TreePop();
    //}

    ImGui::End();
}
