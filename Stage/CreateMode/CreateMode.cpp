#include "CreateMode.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Global.h"
#include "../../Engine/Debug.h"
#include "../../Engine/Timer.h"
#include "../../Engine/Audio.h"
#include "../../Engine/Text.h"
#include "../../AI/MetaAI.h"
#include "../../AI/NavigationAI.h"
#include "StageSource/OneBrock.h"
#include "StageSource/Cannon.h"
#include "StageSource/Needle.h"
#include "StageSource/AutoCannon.h"


//�萔�錾
namespace {
    const int PLAYER_ID = 0;
    const int MAX_CHARACTER_NUM = 4;
    const int MAX_VIEW_OBJECT = 8;
    const float CAM_MOVE_RATE = 0.05f;
    const float OBJ_MOVE_RATE = 0.05f;
    const XMFLOAT3 OBJECT_POS[MAX_VIEW_OBJECT] = { XMFLOAT3(7,22,15),XMFLOAT3(12,22,15) ,XMFLOAT3(17,22,15) ,XMFLOAT3(22,22,15),
                                                   XMFLOAT3(7,18,15) ,XMFLOAT3(12,18,15)  ,XMFLOAT3(17,18,15)  ,XMFLOAT3(22,18,15)};
    //�I�����ꂽ�I�u�W�F�N�g��\������ʒu
    const XMFLOAT3 PLAYER_UI_POS[MAX_CHARACTER_NUM] = { XMFLOAT3(7,15,15),XMFLOAT3(12,15,15) ,XMFLOAT3(17,15,15) ,XMFLOAT3(22,15,15) };

    //�J�����̈ʒu
    const XMFLOAT3 SELECT_CAM_POS = XMFLOAT3(15, 20, ZERO);
    const XMFLOAT3 SELECT_CAM_TAR = XMFLOAT3(15, 20, 15);
    const XMFLOAT3 SETTING_CAM_POS = XMFLOAT3(15, 20, -20);
    const XMFLOAT3 SETTING_CAM_TAR = XMFLOAT3(15, ZERO, 15);
    const XMFLOAT3 GAME_CAM_POS = XMFLOAT3(15, 10, -20);
    const XMFLOAT3 GAME_CAM_TAR = XMFLOAT3(15, ZERO, 15);
    const float WAIT_TIME = 1.5f;

    //�������p
    const int INF = 999999;

    //�^�񒆂ɃI�u�W�F�N�g��ǉ�����p�̍��W�B�c��ň�̍��W�ƂȂ��Ă�
    const int STAGE_ADDX[9] = { 14,15,15,15,16,15,15,13,17 };
    const int STAGE_ADDZ[9] = { 15,14,15,16,15,13,17,15,15 };

    //�I�u�W�F�N�g���̑傫���ix��z�ŉ��}�X�g���Ă��邩�j
    const XMFLOAT2 OBJECT_SIZE[PATTERN_END] = { XMFLOAT2(1,1),XMFLOAT2(1,1),XMFLOAT2(1,1),XMFLOAT2(1,1) };

    //CreateMode��\������ʒu
    std::string TEXT_NAME = "CREATEMODE";
    const XMFLOAT3 TEXT_POS = { 400,30,ZERO };

}

//�R���X�g���N�^
CreateMode::CreateMode(GameObject* parent)
    : GameObject(parent, "CreateMode"), pMetaAI_(nullptr),pStage_(nullptr),pText_(nullptr), pTimer_(Instantiate<Timer>(this)), hCreateSound_{-1,-1}, hBGM_(-1)
{

}

//������
void CreateMode::Initialize()
{
    //Map�t�@�C���̒��ɓ����Ă�fbx�t�@�C���̖��O������
    std::vector<std::string> fileName;

    //�t�@�C���̒��ɓ����Ă邷�ׂĂ�fbx�t�@�C���̖��O�̎擾
    fileName = GetFilePath("../Assets/StageResource/", "fbx");

    //fileName�̌����̗v�f�����m��
    modelData_.assign(fileName.size(), ModelInfo(-1, PATTERN_END));

    //�t�@�C���̒��ɓ����Ă����\�[�X�����ׂă��[�h����
    for (int i = ZERO; i < modelData_.size(); i++) {
        std::string dir = "StageResource/";
        modelData_.at(i).hModel = Model::Load(dir + fileName.at(i));
        modelData_.at(i).modelPattern = (FBXPATTERN)i;
        assert(modelData_.at(i).hModel >= ZERO);
    }

    //�^�񒆂ɏ\���^�̕ǂ����BAstar�킩��₷������ׂ�
    for (int i = 0; i < 9; i++) {
        Transform trans;
        trans.position_.x = STAGE_ADDX[i];
        trans.position_.z = STAGE_ADDZ[i];
        CreateInstance<OneBrock>(modelData_.at(ONEBROCK).hModel, trans, PLAYER_ID, OBJECT_SIZE[ONEBROCK]);
    }

    //MAX_VIEW_OBJECT���̗v�f�����O�Ɏ���Ă���
    for (int i = ZERO; i < MAX_VIEW_OBJECT; i++) {

        viewObjectList_.emplace_back(-1);
    }

    //���O�Ƀv���C���[�̐������v�f��p�ӂ��ď��������Ă���
    for (int i = ZERO; i < MAX_CHARACTER_NUM; i++) {

        SettingObjectInfo obj;
        settingObject_.emplace_back(obj);
    }

    nowState_ = NONE;
    pText_ = new Text;
    pText_->Initialize();

    pTimer_->SetLimit(WAIT_TIME);


    //�����f�[�^�̃��[�h
    std::string str[CREATESOUND_NUM] = { "Sellect","Setting"};

    for (int i = ZERO; i < CREATESOUND_NUM; i++) {

        std::string dir = "Audio/SE/";
        std::string extention = ".wav";

        std::string fileName = dir + str[i] + extention;

        hCreateSound_[i] = Audio::Load(fileName, false, 3);
        assert(hCreateSound_[i] >= ZERO);

        Audio::Stop(hCreateSound_[i]);
    }

    hBGM_ = Audio::Load("Audio/CreateModeBGM.wav", true);
    Audio::Stop(hBGM_);
    
}

//�X�V
void CreateMode::Update()
{

    switch (nowState_)
    {
    case SELECT_MODE:
        SelectUpdate();
        break;
    
    case SETTING_MODE:
        SettingUpdate();
        break;

    case NONE:
    default:
        return;
    }
}


//�`��
void CreateMode::Draw()
{

    

    //�A�b�v�f�[�g���ŃN���G�C�g���[�h�ƃZ�b�g���[�h�Ő؂�ւ���
    switch (nowState_)
    {
    case SELECT_MODE:

        SelectDraw();
        break;

    case SETTING_MODE:

        for (int i = ZERO; i < settingObject_.size(); i++) {

            Model::SetTransform(settingObject_.at(i).hModel, settingObject_.at(i).trans);
            Model::Draw(settingObject_.at(i).hModel);
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

//�Z���N�g���[�h��
void CreateMode::ToSelectMode()
{

    SelectInit();
    nowState_ = SELECT_MODE;

    pNavigationAI_->AllStopDraw();
    pNavigationAI_->AllStopUpdate();
    //pNavigationAI_->AllEraseCollision();
}

//�Z�b�e�B���O���[�h��
void CreateMode::ToSettingMode()
{
    SettingInit();
    nowState_ = SETTING_MODE;
}

//�Q�[���ɖ߂�
void CreateMode::ToGameMode()
{
    //�����ň�U�Ó]�Ƃ�������������ړ��͂����ł���
    pMetaAI_->ResetGame();
    nowState_ = NONE;

    Audio::Stop(hBGM_);
}


///////////////////////////////private�֐�//////////////////////////////////////////


// �f�B���N�g�����̎w�肵�����ʎq�̃t�@�C���l�[�����l������֐�
// �����P�F�T���������f�B���N�g��
// �����Q�F�T�������t�@�C���̊g���q
// �߂�l�F�݂����t�@�C���̖��O���������z��
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

//�Z���N�g���[�h�p�̏�����
void CreateMode::SelectInit()
{

    rotateObjectValue_ = ZERO;
    selecting_Object_ = INF;
    nextSelectCharacterID_ = MAX_CHARACTER_NUM - 1;

    isObjectMoving_ = false;

    ranking_ = pMetaAI_->GetRanking();

    pTimer_->Reset();

    //�O��̃Z�b�e�B���O�I�u�W�F�N�g�̏������ׂď���������
    for (int i = ZERO; i < MAX_CHARACTER_NUM; i++) {
        Transform objPos;
        settingObject_.at(i).hModel = -1;
        settingObject_.at(i).trans = objPos;
        settingObject_.at(i).moved = false;
    }

    //hModel�̒����烉���_���ŕ\��������I�u�W�F�N�g�����߂�
    for (int i = ZERO; i < MAX_VIEW_OBJECT; i++) {
        viewObjectList_.at(i) = rand() % modelData_.size() + modelData_.at(ZERO).hModel;
    }

    Audio::Play(hBGM_);
}

//�Z�b�e�B���O���[�h�p�̏�����
void CreateMode::SettingInit()
{

    selecting_Object_ = INF;

    //settingObject�̈ʒu���X�e�[�W�̐^�񒆂ɐݒ肷��
    for (int i = ZERO; i < settingObject_.size(); i++) {

        Transform objPos;
        objPos.position_ = XMFLOAT3(15.0f, ZERO, 15.0f);

        settingObject_.at(i).trans = objPos;
        settingObject_.at(i).moved = false;
    }

    pTimer_->Reset();
}

//�Z���N�g���[�h���̍X�V����
void CreateMode::SelectUpdate()
{
    if (Camera::MoveCam(SELECT_CAM_POS, SELECT_CAM_TAR, CAM_MOVE_RATE) == false) {
        return;
    }

    //�I�u�W�F�N�g���v���C���[���I������Ă��Ȃ�������
    if (!IsAllDecidedObject()) {

        //�I�u�W�F�N�g���ړ����Ȃ�X�V���Ȃ�
        if (isObjectMoving_) {
            return;
        }

        //���ɃI�u�W�F�N�g��I�Ԑl��AI�Ȃ�AI�p�̏���������
        if (ranking_.at(nextSelectCharacterID_) >= startEnemyID_) {
            AISelectObject(ranking_.at(nextSelectCharacterID_));
            nextSelectCharacterID_--;
            isObjectMoving_ = true;
            Audio::Play(hCreateSound_[SELECT]);
            return;
        }

        //�}�E�X���烌�C���΂��p�̃x�N�g�����l��
        XMVECTOR front;
        XMVECTOR back;
        GetCursorRay(front, back);
        //memo.���C�L���X�g���邽�тɃ��C��start���ς���Ă�

        //�I�u�W�F�N�g�ɃJ�[�\���������Ă��ԂŃN���b�N���ꂽ��
        if (IsSelectingOverlapCursor(front, back)) {
            if (Input::IsMouseButtonDown(0)) {
                SelectObject(ranking_.at(nextSelectCharacterID_));
                nextSelectCharacterID_--;
                isObjectMoving_ = true;
                Audio::Play(hCreateSound_[SELECT]);
            }
        }

        return;
    }

    //�����܂ŗ������A�̗��ꂪ�I����Ă�̂Ń^�C�}�[�X�^�[�g
    pTimer_->Start();
    if (pTimer_->IsFinished()) {
        ToSettingMode();
    }
}

//�Z�b�e�B���O���[�h���̍X�V����
void CreateMode::SettingUpdate()
{
    if (Camera::MoveCam(SETTING_CAM_POS, SETTING_CAM_TAR, CAM_MOVE_RATE) == false) {
        return; 
    }

    //�ړ����鏈���B
    if (settingObject_.at(ZERO).moved) {
        AIMovingObject();
        Audio::Play(hCreateSound_[SETTING]);
    }

    //�}�E�X���烌�C���΂��p�̃x�N�g�����l��
    XMVECTOR front;
    XMVECTOR back;
    GetCursorRay(front, back);

    //�}�E�X�J�[�\�����X�e�[�W��ɏd�Ȃ��Ă��邩
    if (IsStageOverlapCursor(front, back)) {

        //���N���b�N����āA���@���łɐݒu���ꂽ�I�u�W�F�N�g�������Ȃ�
        if (Input::IsMouseButtonDown(ZERO) && IsOverlapPosition() == false) {

            //�ЂƂ܂��v���C���[��1�l�ڂ���������ZERO��
            CreateObject(settingObject_.at(ZERO).hModel, settingObject_.at(ZERO).trans, ZERO);
            Audio::Play(hCreateSound_[SETTING]);
        }

        //�E�N���b�N���ꂽ��iIsMouseButtonDown�̈����ɂP��^������E�N���b�N���ꂽ���ǂ����ɂȂ�j
        if (Input::IsMouseButtonDown(1)) {
            settingObject_.at(ZERO).trans.rotate_.y += 90;
            if (settingObject_.at(ZERO).trans.rotate_.y >= 360) {
                settingObject_.at(ZERO).trans.rotate_.y = ZERO;
            }
        }
    }

    //�S�ẴI�u�W�F�N�g��ݒu���I�������Q�[���ɖ߂�
    {
        bool isAllCreate = true;
        for (int i = ZERO; i < settingObject_.size(); i++) {

            //���f���ԍ���-1����Ȃ��Ȃ�
            if (settingObject_.at(i).hModel != -1) {
                isAllCreate = false;
            }
        }

        //���ׂĐݒu����I�������
        if (isAllCreate) {

            //�I�����1�b�҂�
            pTimer_->Start();
            if (pTimer_->IsFinished()) {
                ToGameMode();
            }
        }
    }
}

void CreateMode::SelectDraw()
{
    //�󒆂ɕ����I�u�W�F�N�g��\������
    for (int i = ZERO; i < viewObjectList_.size(); i++) {

        Transform objTrans;
        objTrans.position_ = OBJECT_POS[i];
        objTrans.rotate_.y = rotateObjectValue_;

        if (i == selecting_Object_) {
            objTrans.scale_ = XMFLOAT3(1.2f, 1.2f, 1.2f);
        }

        Model::SetTransform(viewObjectList_.at(i), objTrans);
        Model::Draw(viewObjectList_.at(i));
    }

    //���ɑI�΂ꂽ�I�u�W�F�N�g��\������
    for (int i = ZERO; i < settingObject_.size(); i++) {

        //-1�Ȃ�X�V���Ȃ��B���ꂪ�����Ə���ɓ������Ⴄ
        if (settingObject_.at(i).hModel == -1) {
            continue;
        }

        //�ړ����I����ĂȂ��I�u�W�F�N�g�����炩�ɓ�����
        if (settingObject_.at(i).moved == false) {
            if (RateMovePosition(settingObject_.at(i).trans.position_, PLAYER_UI_POS[i], OBJ_MOVE_RATE)) {
                settingObject_.at(i).moved = true;
                isObjectMoving_ = false;
            }
        }



        settingObject_.at(i).trans.rotate_.y = rotateObjectValue_;

        Model::SetTransform(settingObject_.at(i).hModel, settingObject_.at(i).trans);
        Model::Draw(settingObject_.at(i).hModel);
    }

    rotateObjectValue_++;

    //�N���G�C�g���[�h���ƌ�������\��
    pText_->Draw(TEXT_POS.x, TEXT_POS.y, TEXT_NAME.c_str());
}

// �I�u�W�F�N�g���쐬����
// �����P�F���f���ԍ�
// �����Q�F���f����transform
// �����R�F���Ԗڂ̗v�f��
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
    case AUTO_CANNON:
        CreateInstance<AutoCannon>(hModel, trans, element, OBJECT_SIZE[pattern]);
        break;

    case CANNON:
        CreateInstance<Cannon>(hModel, trans, element, OBJECT_SIZE[pattern]);
        break;

    case NEEDLE:
        CreateInstance<Needle>(hModel, trans, element, OBJECT_SIZE[pattern]);
        break;

    case ONEBROCK:
        CreateInstance<OneBrock>(hModel, trans, element, OBJECT_SIZE[pattern]);
        break;

    case PATTERN_END:
    default:
        break;
    }

    settingObject_.at(element).moved = true;

    //�N���b�N�����炻�̃I�u�W�F�N�g�������i���f���ԍ��𖳂����ď������Ȃ�����j
    settingObject_.at(element).hModel = -1;
}

// createObjectList�ɓ����
// �����P�F�ǉ��������I�u�W�F�N�g�̃|�C���^
void CreateMode::AddCreateObject(StageSourceBase* object)
{
    //��X�̂��ƍl������ID����U�����ق����������B��Ŕ��e�Ƃ��������鎖�l������
    createObjectList_.emplace_back(object);
}

//�}�E�X�J�[�\���̈ʒu����o��x�N�g�����Q�Ɠn���Ŏ擾����
//�����P�F�O�̃x�N�g��
//�����Q�F���̃x�N�g��
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

// AI���I�u�W�F�N�g��I������֐�
// �����P�F�I�u�W�F�N�g��I������G��ID
void CreateMode::AISelectObject(int ID)
{

    vector<int> modelList;

    //�\������Ă郂�f���̃��f���ԍ���S�Ď擾����
    for (int i = ZERO; i < viewObjectList_.size(); i++) {

        //-1�͔��肵�Ȃ�
        if (viewObjectList_.at(i) == -1) {
            continue;
        }

        //����modelList�ɓ���Ă郂�f���ԍ���
        bool duplicate = false;

        //modelList�Ɋ��ɓ���Ă�ԍ����m�F����
        for (int m = ZERO; m < modelList.size(); m++) {
            if (modelList.at(m) == viewObjectList_.at(i)) {
                duplicate = true;
            }
        }

        //�d�����ĂȂ����f���ԍ��Ȃ�AmodelList�ɓ����
        if (duplicate == false) {
            modelList.emplace_back(viewObjectList_.at(i));
        }
    }

    //�I������I�u�W�F�N�g�̃��f���ԍ����o����
    int selectModel = pMetaAI_->SelectObject(modelList);

    //�I�����ꂽ���f���ԍ���T���āAselectingObject�ɓ����
    for (int i = ZERO; i < viewObjectList_.size(); i++) {
        if (viewObjectList_.at(i) == selectModel) {
            selecting_Object_ = i;
            break;
        }

    }

    //�I������
    SelectObject(ID);


}

// settingObject�ɑI�񂾃I�u�W�F�N�g�̏���n��
// �����F�I�u�W�F�N�g��I�񂾐l��ID
void CreateMode::SelectObject(int ID)
{

    Transform objPos;
    objPos.position_ = OBJECT_POS[selecting_Object_];

    //�I�������I�u�W�F�N�g�����Ă�
    settingObject_.at(ID).hModel = viewObjectList_.at(selecting_Object_);
    settingObject_.at(ID).trans = objPos;

    //�I�����ꂽ�ʒu�̃I�u�W�F�N�g�͏���
    viewObjectList_.at(selecting_Object_) = -1;

}

// �J�[�\����������ł�I�u�W�F�N�g�ɍ��킳���Ă��邩
// �����P�F��΂����C�̑O�����x�N�g��
// �����Q�F�������̃x�N�g��
bool CreateMode::IsSelectingOverlapCursor(XMVECTOR front, XMVECTOR back)
{
    //�J�[�\�������΂������C�����f���ɓ������Ă邩�m�F����
    for (int i = ZERO; i < viewObjectList_.size(); i++) {

        //���ɑI�����ꂽ�I�u�W�F�N�g�v�f�̈ʒu�Ȃ�
        if (viewObjectList_.at(i) == -1) {
            continue;
        }

        RayCastData data;
        XMStoreFloat3(&data.start, front);
        XMStoreFloat3(&data.dir, back - front);

        //���f����Transform���Ō��Draw�����ʒu�̂܂܂ɂȂ��Ă��邽�߁A��x���ꂼ��̈ʒu�ɖ߂��B����handle�ŕ����`�悵�Ă�̂�����
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

// �v���C���[�S�����I�u�W�F�N�g��I�яI�������
// �߂�l�F�I�яI����Ă�����true
bool CreateMode::IsAllDecidedObject()
{

    //�L�����N�^�[�S�����I�u�W�F�N�g��I�����I����Ă�����
    for (int i = ZERO; i < settingObject_.size(); i++) {

        //�܂��I������Ă��Ȃ��I�u�W�F�N�g����������
        if (settingObject_.at(i).hModel == -1) {
            return false;
        }
    }

    return true;
}

// �X�e�[�W�̏�ɃJ�[�\�������邩�ǂ���
// �����P�F��΂����C�̑O�����x�N�g��
// �����Q�F�������̃x�N�g��
// �߂�l�F�������Ă�����true
bool CreateMode::IsStageOverlapCursor(XMVECTOR front, XMVECTOR back)
{

    XMFLOAT3 stageSize = pStage_->GetStageSize();
    int stageHandle = pStage_->GetStageHandle();

    //�J�[�\�������΂������C�����f���ɓ������Ă邩�m�F����
    for (int z = ZERO; z < stageSize.z; z++) {
        for (int x = ZERO; x < stageSize.x; x++) {

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

                //��]�̏�񂾂��͎c���Ă���
                objTrans.rotate_ = settingObject_.at(ZERO).trans.rotate_;
                settingObject_.at(ZERO).trans = objTrans;
                selecting_Object_ = ZERO;
                return true;
            }
        }
    }

    selecting_Object_ = INF;

    return false;
}

// �ݒu���悤�Ƃ����ꏊ�����ɐݒu����Ă���I�u�W�F�N�g�Ɣ���Ă��邩�ǂ���
// �����P�F�������Ă�����true
bool CreateMode::IsOverlapPosition()
{
    Transform pos = settingObject_.at(selecting_Object_).trans;

    //���ɍ쐬���ꂽ�I�u�W�F�N�g�Ɣ�����ʒu���m�F����
    for (auto it = createObjectList_.begin(); it != createObjectList_.end(); it++) {
        if ((*it)->GetPosition() == pos.position_) {
            return true;
        }
    }

    //���Z�b�g���Ă�r���̃I�u�W�F�N�g�ƈʒu������Ă邩�ǂ���
    for (int i = 0; i < settingObject_.size(); i++) {

        //�����Ȃ珈�����Ȃ�
        if (i == selecting_Object_) {
            continue;
        }

        if (settingObject_.at(i).trans == pos) {
            return true;
        }
    }

    return false;
}

// Ai���I�񂾃I�u�W�F�N�g�𓮂����ʒu�����߂�
void CreateMode::AIMovingObject()
{
    //�I�u�W�F�N�g�̈ʒu������ĂȂ����m�F����p
    std::vector<XMFLOAT3> pos;

    //���ɍ�����I�u�W�F�N�g�̑S�Ă̈ʒu���m�F����
    for (auto it = createObjectList_.begin(); it != createObjectList_.end(); it++) {

        pos.emplace_back((*it)->GetPosition());
    }

    //AI���I�񂾃I�u�W�F�N�g��u������
    for (int i = startEnemyID_; i < settingObject_.size(); i++) {

        //���f����Transform�̈ʒu�𑼂̃I�u�W�F�N�g�Ɣ���ĂȂ��ʒu�ɒu����܂ŌJ��ւ���
        while (true) {

            //NavigationAI���o�R���Ăǂ��ɒu���������߂�
            settingObject_.at(i).trans = pNavigationAI_->MoveSelectObject(i);

            //�v���C���[�̈ʒu�Ɣ���Ă����������x
            if (pNavigationAI_->IsOverlapPos(settingObject_.at(i).trans.position_)) {
                srand(time(NULL));
                continue;
            }

            bool isBreak = true;

            //���f���̈ʒu�����Ɣ���Ă�����A������x
            for (int f = 0; f < pos.size(); f++) {
                if (pos.at(f) == settingObject_.at(i).trans.position_) {
                    isBreak = false;
                    srand(time(NULL));
                    continue;
                }
            }

            if (isBreak)
                break;

        }

        CreateObject(settingObject_.at(i).hModel, settingObject_.at(i).trans, i);
    }
}

template <class T>
T* CreateMode::CreateInstance(int hModel, Transform trans, int ID, XMFLOAT2 square)
{
    T* pObject = Instantiate<T>(this);
    AddCreateObject(pObject);
    pStage_->PushStageSource(pObject);

    //��]�s������A�l�p�`�̃I�u�W�F�N�g�̃R�X�g�̈ʒu����]������
    XMMATRIX rotateX, rotateY;
    rotateX = XMMatrixIdentity();
    rotateY = XMMatrixRotationY(XMConvertToRadians(trans.rotate_.y));
    XMMATRIX matRot = rotateX * rotateY;

    //��]�s���K��
    XMVECTOR vec = XMLoadFloat2(&square);
    vec = XMVector2Transform(vec, rotateY);
    XMStoreFloat2(&square, vec);

    //�R�X�g������
    pStage_->SetStageCost(trans.position_, pObject->GetStageCost(), square.x, square.y);

    //AI���I�񂾃I�u�W�F�N�g�Ȃ�^�񒆂��������蓮���悤��
    if (ID >= startEnemyID_) {
        Transform objTrans;
        objTrans.position_ = XMFLOAT3(15.0f, ZERO, 15.0f);
        objTrans.rotate_ = trans.rotate_;
        pObject->SetMoveLastPos(trans.position_);
        pObject->SetTransform(objTrans);
    }
    else {
        pObject->SetMoveLastPos(trans.position_);
        pObject->SetTransform(trans);
    }

    pObject->Leave();
    pObject->SetHandle(hModel);
    return pObject;
}