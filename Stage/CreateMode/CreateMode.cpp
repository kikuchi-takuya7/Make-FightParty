#include "CreateMode.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Global.h"
#include "StageSource/TestWall.h"
#include "StageSource/TestFloor.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "../../Engine/Debug.h"
#include "../../AI/MetaAI.h"
#include "../../AI/NavigationAI.h"


//�萔�錾
namespace {
    const int PLAYER_NUM = 4;
    const int MAX_VIEW_OBJECT = 8;
    const XMFLOAT3 OBJECT_POS[MAX_VIEW_OBJECT] = { XMFLOAT3(7,22,15),XMFLOAT3(12,22,15) ,XMFLOAT3(17,22,15) ,XMFLOAT3(22,22,15),
                                                   XMFLOAT3(7,18,15) ,XMFLOAT3(12,18,15)  ,XMFLOAT3(17,18,15)  ,XMFLOAT3(22,18,15)};
    //�Q������v���C���[�̍ő�l����
    const XMFLOAT3 PLAYER_UI_POS[4] = { XMFLOAT3(5,15,15),XMFLOAT3(10,15,15) ,XMFLOAT3(15,15,15) ,XMFLOAT3(20,15,15) };
    const XMFLOAT3 SELECT_CAM_POS = XMFLOAT3(15, 20, 0);
    const XMFLOAT3 SELECT_CAM_TAR = XMFLOAT3(15, 20, 15);
    const XMFLOAT3 SETTING_CAM_POS = XMFLOAT3(15, 15, -15);
    const XMFLOAT3 SETTING_CAM_TAR = XMFLOAT3(15, 0, 15);
    const XMFLOAT3 GAME_CAM_POS = XMFLOAT3(15, 10, -20);
    const XMFLOAT3 GAME_CAM_TAR = XMFLOAT3(15, 0, 15);
    const int WAIT_FLAME = 120;

}

//�R���X�g���N�^
CreateMode::CreateMode(GameObject* parent)
    : GameObject(parent, "CreateMode"), pMetaAI_(nullptr),pStage_(nullptr), selecting_Object_(PATTERN_END),nextObjectId_(0)
{


}

//������
void CreateMode::Initialize()
{
    //�t�@�C���̒��ɓ����Ă邷�ׂĂ�fbx�t�@�C���̖��O�̎擾
    fileName_ = GetFilePath("../Assets/StageResource/", "fbx");

    //fileName�̌����̗v�f�����m��
    modelData_.assign(fileName_.size(), ModelInfo(-1, PATTERN_END));

    //�t�@�C���̒��ɓ����Ă����\�[�X�����ׂă��[�h����
    for (int i = 0; i < modelData_.size(); i++) {
        std::string dir = "StageResource/";
        modelData_.at(i).hModel = Model::Load(dir + fileName_.at(i));
        assert(modelData_.at(i).hModel >= 0);
    }

    //�O��܂ł�viewObject�����ׂď������āA�V�����Z�b�g����
    viewObjectList_.clear();
    for (int i = 0; i < MAX_VIEW_OBJECT; i++) {

        //hModel�̒����烉���_���ŕ\��������I�u�W�F�N�g�����߂�
        viewObjectList_.emplace_back(rand() % modelData_.size() + modelData_.at(0).hModel);
    }

    //���O�Ƀv���C���[�̐������v�f��p�ӂ��ď��������Ă���
    for (int i = ZERO; i < PLAYER_NUM; i++) {

        Transform objPos;
        settingObject_.emplace_back(std::make_pair(-1, objPos));
    }



    rotateObjectValue_ = 0;
    nowState_ = NONE;
    flame_ = 0;
}

void CreateMode::ViewInit()
{
    flame_ = 0;
    rotateObjectValue_ = 0;
    camMoveRate_ = 0.0f;
    
    //�O��̃Z�b�e�B���O�I�u�W�F�N�g�̏������ׂď���������
    for (int i = ZERO; i < PLAYER_NUM; i++) {

        Transform objPos;
        settingObject_.at(i).first = -1;
        settingObject_.at(i).second = objPos;
    }

    //hModel�̒����烉���_���ŕ\��������I�u�W�F�N�g�����Ȃ���
    for (int i = 0; i < MAX_VIEW_OBJECT; i++) {

        viewObjectList_.at(i) = rand() % modelData_.size() + modelData_.at(0).hModel;
    }
}

void CreateMode::SettingInit()
{

    flame_ = 0;
    camMoveRate_ = 0.0f;
   
}

//�X�V
void CreateMode::Update()
{

    switch (nowState_)
    {
    case SELECT_MODE:

        MoveCam(SELECT_CAM_POS, SELECT_CAM_TAR);

        //�I�u�W�F�N�g���v���C���[���I�����ꂽ��
        if (!IsAllDecidedObject()) {

            //�J�[�\�������f���ɍ��킳���Ă�Ȃ�
            if (IsOverlapCursor()) {

                //�����Ń��f�������点����
                Debug::Log("hit", true);

                if (Input::IsMouseButtonDown(0)) {
                    SelectObject();
                }
            }
            else {
                Debug::Log("nohit", true);
            }

            break;
        }

        flame_++;
        if (flame_ == WAIT_FLAME) {
            ToSettingMode();
        }
        
        break;
    
    case SETTING_MODE:

        MoveCam(SETTING_CAM_POS, SETTING_CAM_TAR);

        //�ړ����鏈���B
        if (Input::IsKeyDown(DIK_0)) {
            AIMovingObject();
        }

        PlayerMovingObject();

        break;

    case NONE:
    default:
        return;
    }

    

    
}

//�`��
void CreateMode::Draw()
{

    //�A�b�v�f�[�g���ŃN���G�C�g���[�h�ƃZ�b�g���[�h�Ő؂�ւ��邩

    switch (nowState_)
    {
    case SELECT_MODE:

        //�󒆂ɕ����I�u�W�F�N�g��\������
        for (int i = 0; i < viewObjectList_.size(); i++) {

            Transform objTrans;
            objTrans.position_ = OBJECT_POS[i];
            objTrans.rotate_.y = rotateObjectValue_;
            
            if (i == selecting_Object_) {
                objTrans.scale_ = XMFLOAT3(1.2f, 1.2f, 1.2f);
            }

            Model::SetTransform(viewObjectList_.at(i), objTrans);
            Model::Draw(viewObjectList_.at(i));
        }

        //vector<int> ranking = pMetaAI_->GetRanking();

        //���ɑI�΂ꂽ�I�u�W�F�N�g��\������
        for (int i = 0; i < settingObject_.size(); i++) {
            
            //�ŉ��ʂ���I�u�W�F�N�g��I�����邽�߁A�I�񂾐l�̈ʒu����u��
            Transform objTrans;

            //settingObject�͂��łɏ��ʏ��ɂȂ��Ă邩�炻�̂܂ܕ\�����悤�Ƃ��đ��v�Ȃ͂�
            objTrans.position_ = PLAYER_UI_POS[i];
            objTrans.rotate_.y = rotateObjectValue_;

            Model::SetTransform(settingObject_.at(i).first, objTrans);
            Model::Draw(settingObject_.at(i).first);
        }

        rotateObjectValue_++;
        break;

    case SETTING_MODE:
        
        for (int i = 0; i < settingObject_.size(); i++) {

            Model::SetTransform(settingObject_.at(i).first, settingObject_.at(i).second);
            Model::Draw(settingObject_.at(i).first);
        }
        break;

    case NONE:
    default:
        return;
    }

    
}

//�J��
void CreateMode::Release()
{
}

//GameObject* CreateMode::CreateObject()
//{
//
//    //for�ŉ񂵂�FBXPATTERN��filename�̗v�f�̏��Ԃ���v�����Ƃ���ŃI�u�W�F�N�g�����̂��z�肵������objectName�Ƃ����߂�ǂ������Ȃ邩�疳��
//    //�Ή�����enum�^�̐����ɂȂ����炻�̃I�u�W�F�N�g���쐬����createObject�Ƀv�b�V���o�b�N����
//
//    //���ꂼ��̃I�u�W�F�N�g�̃C���X�^���X���N���X�ϐ���vector�Ŏ����āA���[�����[������΂Ȃ񂩂����Ɗy�ł���������ˁH
//    switch (selecting_Object_)
//    {
//    case TESTFLOOR: {
//        TestFloor* pObject = CreateInstance<TestFloor>();
//        return pObject;
//        break;
//    }
//    case PATTERN_END: {
//        break;
//    }
//    default:
//        break;
//    }
//
//    return NULL;   // �w��̃N���X������
//}

void CreateMode::SelectObject()
{   
    //�Z�b�e�B���O�I�u�W�F�N�g��initialize�̎��_��4���v�f�m�ۂ��Ƃ��āA����銴���̕����ǂ����H
    //�Z�b�e�B���O�I�u�W�F�N�g�ɏ���^���ėv�f������.���̎��_��Character���ɂ����Ⴂ�����H
    
    Transform objPos;
    objPos.position_ = XMFLOAT3(15.0f, 0, 15.0f);
    //settingObject_.emplace_back(std::make_pair(viewObjectList_.at(selecting_Object_), objPos));
    
    //ranking�̃r������Z�b�g����
    int selectedObjectNum = 3;
    for (int i = 0; i < settingObject_.size(); i++) {
        
        //�I�΂ꂽ�I�u�W�F�N�g����������A���̏��ʂ̐l��I������
        if (settingObject_.at(i).first != -1) {
            selectedObjectNum--;
        }
    }

    //�I�������r���̈ʒu���珇�ɃI�u�W�F�N�g�����Ă�
    settingObject_.at(selectedObjectNum).first = viewObjectList_.at(selecting_Object_);
    settingObject_.at(selectedObjectNum).second = objPos;

    viewObjectList_.erase(viewObjectList_.begin() + selecting_Object_);

}

void CreateMode::AddCreateObject(GameObject* object)
{
    //CheckDeleteObject();
    createObjectList_.emplace_back(object);
    nextObjectId_++;
}

std::vector<std::string> CreateMode::GetFilePath(const std::string& dir_name, const std::string& extension) noexcept(false)
{
    HANDLE hFind;
    WIN32_FIND_DATA win32fd;//defined at Windwos.h
    std::vector<std::string> file_names;

    //�g���q�̐ݒ�
    std::string search_name = dir_name + "*." + extension;

    hFind = FindFirstFile(search_name.c_str(), &win32fd);

    if (hFind == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("file not found");
    }

    do {
        if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        }
        else {
            file_names.emplace_back(win32fd.cFileName);
            printf("%s\n", file_names.back().c_str());

        }
    } while (FindNextFile(hFind, &win32fd));

    FindClose(hFind);

    return file_names;
}

bool CreateMode::IsOverlapCursor()
{
    float w = (float)(Direct3D::screenWidth_ / 2.0f);
    float h = (float)(Direct3D::screenHeight_ / 2.0f);
    float offsetX = 0;
    float offsetY = 0;
    float minZ = 0;
    float maxZ = 1;

    //�r���[�|�[�g�쐬
    XMMATRIX vp =
    {
        w                ,0                ,0           ,0,
        0                ,-h               ,0           ,0,
        0                ,0                ,maxZ - minZ ,0,
        offsetX + w      ,offsetY + h      ,minZ        ,1
    };

    //�r���[�|�[�g���t�s���
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    //�v���W�F�N�V�����ϊ�
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    //�т�[�ϊ�
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;

    //1,mousePosFront���x�N�g���ɕϊ�
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    //2. 1��invVP,invPrj,invView��������
    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
    //3,mousePosBack���x�N�g���ɕϊ�
    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    //4,3��invVP,invPrj,invVeew��������
    vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);
    //5,2����4�Ɍ������ă��C��łi�Ƃ肠�����j

    int changeX = 0;
    int	changeZ = 0;
    float minDist = 9999;

    //���C�L���X�g���邽�тɃ��C��start���ς���Ă�H
    /*RayCastData data;
    XMStoreFloat3(&data.start, vMouseFront);
    XMStoreFloat3(&data.dir, vMouseBack - vMouseFront);*/

    //�J�[�\�������΂������C�����f���ɓ������Ă邩�m�F����
    for (int i = 0; i < viewObjectList_.size(); i++) {
        RayCastData data;
        XMStoreFloat3(&data.start, vMouseFront);
        XMStoreFloat3(&data.dir, vMouseBack - vMouseFront);

        //���f����Transform���Ō��Draw�����ʒu�̂܂܂ɂȂ��Ă��邽�߁A��x���ꂼ��̈ʒu�ɖ߂�
        Transform objTrans;
        objTrans.position_ = OBJECT_POS[i];
        Model::SetTransform(viewObjectList_.at(i), objTrans);

        Model::RayCast(viewObjectList_.at(i), &data);

        //�������Ă��瑦�I���@
        if (data.hit) {

            //
            selecting_Object_ = i;
            return true;
        }

        //���肦�Ȃ��l�ɂ��Ƃ�
        selecting_Object_ = 99999;
    }
    
    return false;
    
    
}

bool CreateMode::IsAllDecidedObject()
{

    //�L�����N�^�[�S�����I�u�W�F�N�g��I�����I����Ă�����

    for (int i = ZERO; i < settingObject_.size(); i++) {

        //�܂��I������Ă��Ȃ��I�u�W�F�N�g����������
        if (settingObject_.at(i).first == -1) {
            return false;
        }
    }

    return true;
}

void CreateMode::AIMovingObject()
{

    //�R���g���[���[�ł��Ƃ�����J�[�\���̈ʒu���烌�C���΂�����ǂ��̍��W�ɓ������������d�v�ɂȂ��Ă���
    //�X�e�[�W�𗧕��̂Ŗ��߂��z�ɂ��āA���������z�̏�ɍڂ�����������`����
    
    vector<int> ranking = pMetaAI_->GetRanking();

    //�i�r�Q�[�V����AI��ID�Ƃ��̃I�u�W�F�N�g��Trans��n���āA�������ŐF�X���Ă��炤��
    //���ł�settingObject��ID���ԂɂȂ��Ă�͂�
    for (int i = startEnemyID_; i < settingObject_.size(); i++) {

        //�����Ƃ��Ė߂�l�Ƃ��ĕԂ����A�A�h���X�n���ĕς��Ă��炤���ǂ����ɂ���B���Ďv�������ǂ�������Transform�����œn���K�v�Ȃ���
        //settingObject_.at(i).second = pNavigationAI_->MoveSelectObject(i);
        settingObject_.at(i).second = pNavigationAI_->MoveSelectObject(i);
    }
}

void CreateMode::PlayerMovingObject()
{
    XMFLOAT3 stageSize = pStage_->GetStageSize();
    int stageModel = pStage_->GetStageHandle();



}

float CreateMode::GetRateValue(float begin, float end, float rate)
{
    return (end - begin) * rate + begin;
}

void CreateMode::MoveCam(XMFLOAT3 lastPos, XMFLOAT3 lastTar)
{
    //�J�����̈ʒu�ƌ���n�_�����X�ɕς���
    XMFLOAT3 nowCamPos = Camera::GetPosition();
    XMFLOAT3 nowCamTar = Camera::GetTarget();

    //���[�g�łʂ�ʂ铮���悤��
    if (camMoveRate_ < 1.0f) {
        camMoveRate_ += 0.05f;

        // �ςȐ����Ŏ~�܂�Ȃ��悤��
        if (camMoveRate_ > 1.0f)
            camMoveRate_ = 1.0f;

        //�^�[�Q�b�g�ƃ|�W�V�������������ƃG���[�N���邩�璍��

        nowCamPos.x = GetRateValue(nowCamPos.x, lastPos.x, camMoveRate_);
        nowCamPos.y = GetRateValue(nowCamPos.y, lastPos.y, camMoveRate_);
        nowCamPos.z = GetRateValue(nowCamPos.z, lastPos.z, camMoveRate_);

        Camera::SetPosition(nowCamPos);

        nowCamTar.x = GetRateValue(nowCamTar.x, lastTar.x, camMoveRate_);
        nowCamTar.y = GetRateValue(nowCamTar.y, lastTar.y, camMoveRate_);
        nowCamTar.z = GetRateValue(nowCamTar.z, lastTar.z, camMoveRate_);

        Camera::SetTarget(nowCamTar);

    }
}

void CreateMode::ToSelectMode()
{
    ViewInit();
    nowState_ = SELECT_MODE;
}

void CreateMode::ToSettingMode()
{
    
    SettingInit();
    nowState_ = SETTING_MODE;
}
