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

    footRoot_ = transform_;

    //���f�����{�̈ʒu
    footRoot_.position_.x += 0.0f;
    footRoot_.position_.y += 0.0f;
    footRoot_.position_.z += 0.0f;

    //���f���̐�[��position
    footTrans_ = footRoot_;
    
    //���f���̒�����4�ɂ��Ă邩��
    footTrans_.position_.x += MODELLENGTH;

    goalValue_ = { 0,0,0 };

    footVec_ = XMVectorSetX(footVec_, 1);
    
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


    //�{����x���W���ړ������Ă�y�����������Ȃ��͂��Ȃ̂�z���������Ă�B�Ȃ�

    //�ڕW�n�_(�����ׂ������ŁA�ŏI�I�Ȑ�[�̈ʒu)
    XMVECTOR goal = XMLoadFloat3(&goalValue_);

    //��]��-�ɂ��s���悤�ɂ���
    XMFLOAT3 checkGoal;
    XMStoreFloat3(&checkGoal, goal);

    XMVECTOR rotCross = XMVector3Cross(footVec_, goal);
    


    XMVECTOR goalN = XMVector3Normalize(goal);
    XMVECTOR footVecN = XMVector3Normalize(footVec_);
    XMVECTOR dot = XMVector3Dot(footVecN, goal); //���ς����߂�
    float dotLen = XMVectorGetX(dot);

    XMMATRIX rot = XMMatrixRotationAxis(rotCross, dotLen);

    footVec_ = XMVector3TransformCoord(goalVec_, rot);
    
}

//�`��
void PlayerFoot::Draw()
{
    Model::SetTransform(hModel_[0], footRoot_);
    Model::Draw(hModel_[0]);

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
        ImGui::SliderFloat("rotate_x", &footRoot_.rotate_.x, 0, 360);
        
        std::string str = std::to_string(footRoot_.rotate_.x);
        ImGui::Text(str.c_str());

        str = std::to_string(footRoot_.rotate_.y);
        ImGui::Text(str.c_str());

        str = std::to_string(footRoot_.rotate_.z);
        ImGui::Text(str.c_str());
    }

    //if (ImGui::TreeNode("Object")) {//Object�̃c���[���N���b�N�����


    //    ImGui::TreePop();
    //}

    ImGui::End();
}
