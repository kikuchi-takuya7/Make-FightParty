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


namespace {
    const int PLAYER_NUM = 1;
    const int MAX_VIEW_OBJECT = 8;
    const XMFLOAT3 OBJECT_POS[MAX_VIEW_OBJECT] = { XMFLOAT3(10,22,15),XMFLOAT3(15,22,15) ,XMFLOAT3(20,22,15) ,XMFLOAT3(25,22,15),
                                                   XMFLOAT3(10,18,15) ,XMFLOAT3(15,18,15)  ,XMFLOAT3(20,18,15)  ,XMFLOAT3(25,18,15)};
}

//�R���X�g���N�^
CreateMode::CreateMode()
    : selecting_Object(PATTERN_END), nextObjectId_(0)
{


}

//������
void CreateMode::Initialize()
{
    //�t�@�C���̒��ɓ����Ă邷�ׂĂ�fbx�t�@�C���̖��O�̎擾
    fileName_ = GetFilePath("../Assets/StageResource/", "fbx");

    //fileName�̌����̗v�f�����m��
    modelData.assign(fileName_.size(), ModelInfo(-1, PATTERN_END));

    //�t�@�C���̒��ɓ����Ă����\�[�X�����ׂă��[�h����
    for (int i = 0; i < modelData.size(); i++) {
        std::string dir = "StageResource/";
        modelData.at(i).hModel = Model::Load(dir + fileName_.at(i));
        assert(modelData.at(i).hModel >= 0);
    }

    

    isUpdate_ = false;
}

void CreateMode::ViewInit()
{
    viewObjectList_.clear();


    for (int i = 0; i < MAX_VIEW_OBJECT; i++) {

        //hModel�̒����烉���_���ŕ\��������I�u�W�F�N�g�����߂�
        viewObjectList_.push_back(rand() % modelData.size() + modelData.at(0).hModel);
        //viewObjectList_.push_back(std::make_pair(modelData.at(i), i));
    }
}

//�X�V
void CreateMode::Update()
{

    if (!isUpdate_) {
        return;
    }

    //�J�[�\�������f���ɍ��킳���Ă�Ȃ�
    if (IsOverlapCursor()) {

        //�����Ń��f�������点����
        Debug::Log("hit",true);

        if (Input::IsMouseButtonDown(0))
        {
            SelectObject();
        }
    }
    else {
        Debug::Log("nohit", true);
    }
    
}

//�`��
void CreateMode::Draw()
{
    if (!isUpdate_) {
        return;
    }

    

    for (int i = 0; i < viewObjectList_.size(); i++) {

        Transform objPos;
        objPos.position_ = OBJECT_POS[i];
        
        if (i == selecting_Object) {
            objPos.scale_ = XMFLOAT3(1.2f, 1.2f, 1.2f);
        }

        Model::SetTransform(viewObjectList_.at(i), objPos);
        Model::Draw(viewObjectList_.at(i));
    }
}

//�J��
void CreateMode::Release()
{
}

GameObject* CreateMode::CreateObject()
{

    //for�ŉ񂵂�FBXPATTERN��filename�̗v�f�̏��Ԃ���v�����Ƃ���ŃI�u�W�F�N�g�����̂��z�肵������objectName�Ƃ����߂�ǂ������Ȃ邩�疳��
    //�Ή�����enum�^�̐����ɂȂ����炻�̃I�u�W�F�N�g���쐬����createObject�Ƀv�b�V���o�b�N����

    //���ꂼ��̃I�u�W�F�N�g�̃C���X�^���X���N���X�ϐ���vector�Ŏ����āA���[�����[������΂Ȃ񂩂����Ɗy�ł���������ˁH
    switch (selecting_Object)
    {
    case TESTFLOOR: {
        TestFloor* pObject = CreateInstance<TestFloor>();
        return pObject;
        break;
    }
    case PATTERN_END: {
        break;
    }
    default:
        break;
    }

    return NULL;   // �w��̃N���X������
}

void CreateMode::SelectObject()
{

    //�S�Ă�hModel��T������
    for (int i = 0; i < modelData.size(); i++) {

        if (viewObjectList_.at(selecting_Object) == modelData.at(i).hModel) {


            //�Z�b�e�B���O�I�u�W�F�N�g�ɏ���^���ėv�f������
            
        }
    }

}

void CreateMode::AddCreateObject(GameObject* object)
{
    //CheckDeleteObject();
    createObjectList_.push_back(object);
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
            file_names.push_back(win32fd.cFileName);
            printf("%s\n", file_names.back().c_str());

        }
    } while (FindNextFile(hFind, &win32fd));

    FindClose(hFind);

    return file_names;
}

void CreateMode::MoveCamPos()
{
    Camera::SetPosition(XMFLOAT3(15, 20, 0));
    Camera::SetTarget(XMFLOAT3(15, 20, 15));
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
        Transform objPos;
        objPos.position_ = OBJECT_POS[i];
        Model::SetTransform(viewObjectList_.at(i), objPos);

        Model::RayCast(viewObjectList_.at(i), &data);

        //�������Ă��瑦�I���@
        if (data.hit) {

            //
            selecting_Object = i;
            return true;
        }

        //���肦�Ȃ��l�ɂ��Ƃ�
        selecting_Object = 99999;
    }
    
    return false;
    
    
}
