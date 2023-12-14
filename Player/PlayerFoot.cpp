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
    prevBallRot_ = goalValue_;

    prevCosY_ = 0;
    prevCosZ_ = 0;

    

    //�r�̒������������s�ړ�������(����̓{�[��������P�ʉ~�̒�)
    XMMATRIX moveLen = XMMatrixTranslation(1, 0, 0);

    XMMATRIX moveMatrix = moveLen;

    ballVec_ = XMVector3TransformCoord(ballVec_, moveMatrix);

    XMStoreFloat3(&ballTrans_.position_, ballVec_);
    
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
    XMVECTOR prevBallVec = ballVec_;

    if (goalValue_ == prevBallRot_) {
        return;
    }

#if 0

    //���݂̃x�N�g���i��[�j
    XMFLOAT3 tmpFloat = footTipTrans_.position_;
    tmpFloat.y = 0;
    
    //��[�̈ʒu�̃x�N�g��
    XMVECTOR nowFootTipPos = XMLoadFloat3(&tmpFloat);

    //Y����]�����邽�߂̕ϐ�
    XMVECTOR goalTmp = prevBallVec;
    goalTmp = XMVectorSetY(prevBallVec, 0);

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
    if (goalValue_.z <= 0) {
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
    goalTmp = prevBallVec;
    goalTmp = XMVectorSetZ(prevBallVec, 0);
    //goalTmp = XMVectorSetY(prevBallVec, tmpFloat.y);

    goalN = XMVector3Normalize(goalTmp);
    nowFootTipPosN = XMVector3Normalize(nowFootTipPos);
    dot = XMVector3Dot(goalN, nowFootTipPosN); //���ς����߂�
    dotLen = XMVectorGetX(dot);

    //�����z����]�̊p�x
    cos = acos(dotLen);

    float pitch = cos;

    cos = XMConvertToDegrees(cos);

    if (goalValue_.y <= 0) {
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

    //prevBallRot_ = goalValue_;
    //footTipTrans_.position_ = goalValue_;

#else

    //��]��������������]������
    XMFLOAT3 tmp = Transform::Float3Sub(goalValue_, prevBallRot_);

    XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(tmp.x));
    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(tmp.y));
    XMMATRIX rotZ = XMMatrixRotationZ(XMConvertToRadians(tmp.z));

    //���[���h�t�s��Ń��[�J���Ԋҍ��W�ɂ���
    XMMATRIX worldMat = GetWorldMatrix();
    worldMat = XMMatrixInverse(nullptr, worldMat);

    XMMATRIX parentMat = transform_.matScale_ * transform_.matRotate_ * transform_.matTranslate_;
    parentMat = XMMatrixInverse(nullptr, parentMat);

    XMMATRIX rotMatrix = rotY * rotZ * rotX;//���[���s�b�`���[��]�̏��Ԃɂ��Ă݂�

    //2���ŉ�]������ƃ��[���h���W�̎��ŉ�]���Ă��܂����߃��[�J�����W�ɕϊ����Ă����Ȃ񂾂��ǂȂ�
    ballVec_ = XMVector3TransformCoord(ballVec_, rotMatrix * worldMat);

    //prev���X�V
    prevBallRot_ = goalValue_;

    //���a�P���炸��Ȃ��悤��
    ballVec_ = XMVector3Normalize(ballVec_);

    //�{�[���̕\���p�g�����X�t�H�[���ɓ����
    XMStoreFloat3(&ballTrans_.position_, ballVec_);

    ///////////////�{�[���i�ڕW�ʒu�j����]�����Ă��獪����]/////////////

    //���݂̃x�N�g���i��[�j
    //��[�̈ʒu�̃x�N�g��
    XMVECTOR nowBallPosXZ = prevBallVec;
    nowBallPosXZ = XMVectorSetY(nowBallPosXZ, 0);
    
    //Y����]�����邽�߂̕ϐ�
    XMVECTOR goalTmpXZ = ballVec_;
    goalTmpXZ = XMVectorSetY(goalTmpXZ, 0);

    //�����y����]�̊p�x
    float acosY = DotCos(nowBallPosXZ, goalTmpXZ);

    //���{����񂷂��獪������]������
    acosY = -acosY;////////////////////////�Ȃ���y���̉�]���t���������炱���}�C�i�X�ɂ��Ă�B����acosY�̎d�l�H

    //acosY���}�C�i�X�ɂȂ�悤��
    if (ballTrans_.position_.z <= 0) {
        acosY *= -1;
    }

    //���{����񂷂��獪������]������
    footRootTrans_.rotate_.y += prevCosY_ - acosY;

    prevCosY_ = acosY;

    ///////////////��������c����]///////////////////////
    
    ////y����]�����Ă���z����]
    //XMVECTOR nowBallPosXY = ballVec_;
    //nowBallPosXY = XMVectorSetZ(nowBallPosXY, 0);

    ////z����]�����邽�߂̕ϐ�
    //XMVECTOR goalTmpXY = prevBallVec;
    //goalTmpXY = XMVectorSetZ(goalTmpXY, 0);
    ////goalTmpXY = XMVectorSetY(prevBallVec, tmpFloat.y);

    ////�����z����]�̊p�x
    //float acosZ = DotCos(nowBallPosXY, goalTmpXY);

    //if (ballTrans_.position_.y <= 0) {
    //    acosZ *= -1;
    //}

    //prevCosZ_ += acosZ;

    ////���{����񂷂��獪������]������
    //footRootTrans_.rotate_.z += acosZ;

    ////�{�[���̈ʒu�ɑ��̐�[�̍��W����]�o������X�V�Ǝv�������Ǒ��̐�[�͒���4�̈ʒu�ɂȂ��Ƃ�����Ӗ��Ȃ���
    //footTipTrans_.position_ = ballTrans_.position_;

#endif

}

//�`��
void PlayerFoot::Draw()
{
    Model::SetTransform(hModel_[TIP], footRootTrans_);
    Model::Draw(hModel_[TIP]);
    
    Model::SetTransform(hBallModel_, ballTrans_);
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
        }

        Setting_Float3(goalValue_, 0, 360, "prevBallVec");
        //ImGui::SliderFloat("rotate_x", &footRootTrans_.rotate_.x, 0, 360);
        
        ImGui::Text("footRootTrans.rotate");
        std::string str = std::to_string(footRootTrans_.rotate_.x);
        ImGui::Text(str.c_str());

        str = std::to_string(footRootTrans_.rotate_.y);
        ImGui::Text(str.c_str());

        str = std::to_string(footRootTrans_.rotate_.z);
        ImGui::Text(str.c_str());

        ImGui::Text("ballTrans.pos");
        str = std::to_string(ballTrans_.position_.x);
        ImGui::Text(str.c_str());

        str = std::to_string(ballTrans_.position_.y);
        ImGui::Text(str.c_str());

        str = std::to_string(ballTrans_.position_.z);
        ImGui::Text(str.c_str());


    }

    //if (ImGui::TreeNode("Object")) {//Object�̃c���[���N���b�N�����


    //    ImGui::TreePop();
    //}

    ImGui::End();
}

float PlayerFoot::DotCos(XMVECTOR vec1, XMVECTOR vec2)
{

    XMVECTOR goalN = XMVector3Normalize(vec1);
    XMVECTOR nowBallPosN = XMVector3Normalize(vec2);
    XMVECTOR dot = XMVector3Dot(goalN, nowBallPosN); //���ς����߂�
    float dotLen = XMVectorGetX(dot);

    //����Ŏ���]�̊p�x
    return acos(dotLen);
}
