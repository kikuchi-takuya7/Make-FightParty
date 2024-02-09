#include "CreateMode.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Global.h"
#include "../../Engine/Debug.h"
#include "../../AI/MetaAI.h"
#include "../../AI/NavigationAI.h"
#include "StageSource/OneBrock.h"
#include "StageSource/Cannon.h"
#include "StageSource/Needle.h"


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

    const int INF = 999999;
}

//�R���X�g���N�^
CreateMode::CreateMode(GameObject* parent)
    : GameObject(parent, "CreateMode"), pMetaAI_(nullptr),pStage_(nullptr), selecting_Object_(0),nextObjectId_(0)
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
        modelData_.at(i).modelPattern = (FBXPATTERN)i;
        assert(modelData_.at(i).hModel >= 0);
    }

    ////�O��܂ł�viewObject�����ׂď������āA�V�����Z�b�g����
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
    selecting_Object_ = INF;
    
    //�O��̃Z�b�e�B���O�I�u�W�F�N�g�̏������ׂď���������
    for (int i = ZERO; i < PLAYER_NUM; i++) {

        Transform objPos;
        settingObject_.at(i).first = -1;
        settingObject_.at(i).second = objPos;
    }

    //�O��܂ł�viewObject�����ׂď������āA�V�����Z�b�g����
    //�v�fclear����̂߂�ǂ������C�����邯�ǁA-1�ɂ����������Ɠ�G���[�o�������
    //viewObjectList_.clear();
    //for (int i = 0; i < MAX_VIEW_OBJECT; i++) {

    //    //hModel�̒����烉���_���ŕ\��������I�u�W�F�N�g�����߂�
    //    viewObjectList_.emplace_back(rand() % modelData_.size() + modelData_.at(ZERO).hModel);
    //}

    for (int i = 0; i < MAX_VIEW_OBJECT; i++) {

        //hModel�̒����烉���_���ŕ\��������I�u�W�F�N�g�����߂�
        viewObjectList_.at(i) = rand() % modelData_.size() + modelData_.at(ZERO).hModel;
    }

}

void CreateMode::SettingInit()
{

    flame_ = ZERO;
    camMoveRate_ = ZERO;
    selecting_Object_ = INF;
   
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

            //�}�E�X���烌�C���΂��p�̃x�N�g�����l��
            XMVECTOR front;
            XMVECTOR back;
            GetCursorRay(front, back);
            //���C�L���X�g���邽�тɃ��C��start���ς���Ă�H

            if (IsSelectingOverlapCursor(front, back)) {

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

        //�}�E�X���烌�C���΂��p�̃x�N�g�����l��
        XMVECTOR front;
        XMVECTOR back;
        GetCursorRay(front, back);

        if (IsStageOverlapCursor(front, back)) {
            if (Input::IsMouseButtonDown(0) && IsOverlapPosition() == false) {

                //�ЂƂ܂��v���C���[��1�l�ڂ���������
                CreateObject(settingObject_.at(ZERO).first, settingObject_.at(ZERO).second, ZERO);
            }
        }

        //�S�ẴI�u�W�F�N�g��ݒu���I�������Q�[���ɖ߂�
        {
            bool isAllCreate = true;
            for (int i = 0; i < settingObject_.size(); i++) {

                //���f���ԍ���-1����Ȃ��Ȃ�
                if (settingObject_.at(i).first != -1) {
                    isAllCreate = false;
                }
            }

            if (isAllCreate) {
                //�Q�[���ɖ߂鏈��
                ToGameMode();
            }
        }


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

void CreateMode::CreateObject(int hModel, Transform trans, int element)
{

    FBXPATTERN pattern = PATTERN_END;

    //���f���ԍ���FBXPATTERN��T��
    for (int i = 0; i < modelData_.size(); i++) {
        if (modelData_.at(i).hModel == hModel) {
            pattern = modelData_.at(i).modelPattern;
        }
    }

    //���ꂼ��̃I�u�W�F�N�g�̃C���X�^���X���N���X�ϐ���vector�Ŏ����āA���[�����[������΂Ȃ񂩂����Ɗy�ł���������ˁH
    switch (pattern)
    {
    case CANNON:
        CreateInstance<Cannon>(hModel, trans);
        break;

    case NEEDLE:
        CreateInstance<Needle>(hModel, trans);
        break;

    case ONEBROCK:
        CreateInstance<OneBrock>(hModel, trans);
        break;

    case PATTERN_END:
    default:
        break;
    }

    //�N���b�N�����炻�̃I�u�W�F�N�g�������i���f���ԍ��𖳂����ď������Ȃ�����j
    settingObject_.at(element).first = -1;
}

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
    
    viewObjectList_.at(selecting_Object_) = -1;

}

void CreateMode::AddCreateObject(StageSourceBase* object)
{
    //��X�̂��ƍl������ID����U�����ق����������B��Ŕ��e�Ƃ��������鎖�l������
    createObjectList_.emplace_back(object);

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

void CreateMode::GetCursorRay(XMVECTOR& front, XMVECTOR& back)
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
    front = XMLoadFloat3(&mousePosFront);
    //2. 1��invVP,invPrj,invView��������
    front = XMVector3TransformCoord(front, invVP * invProj * invView);
    //3,mousePosBack���x�N�g���ɕϊ�
    back = XMLoadFloat3(&mousePosBack);
    //4,3��invVP,invPrj,invVeew��������
    back = XMVector3TransformCoord(back, invVP * invProj * invView);
    
}

bool CreateMode::IsSelectingOverlapCursor(XMVECTOR front,XMVECTOR back)
{
    //�J�[�\�������΂������C�����f���ɓ������Ă邩�m�F����
    for (int i = 0; i < viewObjectList_.size(); i++) {

        //���ɑI�����ꂽ�I�u�W�F�N�g�v�f�̈ʒu�Ȃ�
        if (viewObjectList_.at(i) == -1) {
            continue;
        }

        RayCastData data;
        XMStoreFloat3(&data.start, front);
        XMStoreFloat3(&data.dir, back - front);

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
        selecting_Object_ = INF;
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

bool CreateMode::IsStageOverlapCursor(XMVECTOR front, XMVECTOR back)
{

    XMFLOAT3 stageSize = pStage_->GetStageSize();
    int stageHandle = pStage_->GetStageHandle();

    //�J�[�\�������΂������C�����f���ɓ������Ă邩�m�F����
    for (int z = 0; z < stageSize.z; z++) {
        for (int x = 0; x < stageSize.x; x++) {

            RayCastData data;
            XMStoreFloat3(&data.start, front);
            XMStoreFloat3(&data.dir, back - front);

            //���f����Transform���Ō��Draw�����ʒu�̂܂܂ɂȂ��Ă��邽�߁A��x���ꂼ��̈ʒu�ɖ߂�
            Transform objTrans;
            objTrans.position_ = XMFLOAT3(x, ZERO, z);
            Model::SetTransform(stageHandle, objTrans);

            Model::RayCast(stageHandle, &data);

            //�������Ă��瑦�I���@
            if (data.hit) {

                settingObject_.at(ZERO).second = objTrans;
                selecting_Object_ = ZERO;
                return true;
            }
        }
    }

    selecting_Object_ = INF;

    return false;
}

bool CreateMode::IsOverlapPosition()
{

    Transform pos = settingObject_.at(selecting_Object_).second;


    for (int i = 0; i < settingObject_.size(); i++) {

        //�����Ȃ珈�����Ȃ�
        if (i == selecting_Object_) {
            continue;
        }

        if (settingObject_.at(i).second == pos) {
            return true;
        }
    }

    return false;
}

void CreateMode::AIMovingObject()
{

    std::vector<XMFLOAT3> pos;

    //���ɍ�����I�u�W�F�N�g�̑S�Ă̈ʒu���m�F����
    for (auto it = createObjectList_.begin(); it != createObjectList_.end(); it++) {

        pos.emplace_back((*it)->GetPosition());
    }

    //�i�r�Q�[�V����AI��ID�Ƃ��̃I�u�W�F�N�g��Trans��n���āA�������ŐF�X���Ă��炤��
    //���ł�settingObject��ID���ԂɂȂ��Ă�͂�
    for (int i = startEnemyID_; i < settingObject_.size(); i++) {


        while (true) {

            //���f����Transform�̈ʒu�����߂�
            settingObject_.at(i).second = pNavigationAI_->MoveSelectObject(i);
        
            bool isBreak = true;

            //���f���̈ʒu�����Ɣ���Ă�����A������x
            for (int i = 0; i < pos.size(); i++) {
                if (pos.at(i) == settingObject_.at(i).second.position_) {
                    isBreak = false;
                    break;
                }
            }

            if (isBreak)
                break;
        
        }
        
        CreateObject(settingObject_.at(i).first, settingObject_.at(i).second, i);
    }

    
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

float CreateMode::GetRateValue(float begin, float end, float rate)
{
    return (end - begin) * rate + begin;
}

void CreateMode::ToSelectMode()
{

    ViewInit();
    nowState_ = SELECT_MODE;

    pNavigationAI_->AllStopDraw();
}

void CreateMode::ToSettingMode()
{
    
    SettingInit();
    nowState_ = SETTING_MODE;
}

void CreateMode::ToGameMode()
{

    //�����ň�U�Ó]�Ƃ�������������ړ��͂����ł�����
    pMetaAI_->ResetGame();
    nowState_ = NONE;

    //pNavigationAI_->AllResetStatus();
}
