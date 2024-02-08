#include "MapEditor.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "../Engine/Global.h"
#include "../Stage/CreateMode/StageSource/TestFloor.h"
#include "../Stage/CreateMode/StageSource/TestWall.h"


//�R���X�g���N�^
MapEditor::MapEditor(GameObject* parent)
	: GameObject(parent, "MapEditor"),selecting_object(PATTERN_END),isSave_(false),nextObjectId_(0),isNewSave_(false),isLoad_(false)
{

    
}

//������
void MapEditor::Initialize()
{
    //�t�@�C���̒��ɓ����Ă邷�ׂĂ�fbx�t�@�C���̖��O�̎擾
    fileName_ = get_file_path_in_dir("./Map/", "fbx");
    
    //fileName�̌����̗v�f�����m��
    hModel_.assign(fileName_.size(),-1);

    for (int i = 0; i < hModel_.size(); i++) {
        std::string dir = "Map/";
        hModel_.at(i) = Model::Load(dir + fileName_.at(i));
        assert(hModel_.at(i) >= 0);
    }

    CheckDeleteObject();
    nextObjectId_ = MaxObjectId();
    nextObjectId_++;
}

//�X�V
void MapEditor::Update()
{
    //����`�F�b�N���Ȃ��ƃf���[�g�����^�C�~���O�ŃG���[�o��B����RootObject��Update�ŏ����ꂽ���ǂ����m�F���Ă邩��
    CheckDeleteObject();



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


    RayCastData data;
    XMStoreFloat3(&data.start, vMouseFront);
    XMStoreFloat3(&data.dir, vMouseBack - vMouseFront);

    Model::RayCast(hModel_[0], &data);

    /*if (data.hit) {
        data.hit = false;

    }*/

    Transform objPos;
    objPos.position_.y = 1.0f;

    //���N���b�N���ꂽ
    if (Input::IsMouseButtonDown(0))
    {
        //���炩�̏���
        CreateObject();
    }
}

//�`��
void MapEditor::Draw()
{

    if (selecting_object == PATTERN_END)
        return;

    Transform objPos;
    
    Model::SetTransform(hModel_.at(selecting_object), objPos);
    Model::Draw(hModel_.at(selecting_object));
}

//�J��
void MapEditor::Release()
{
}

void MapEditor::Imgui_Window()
{
}

GameObject* MapEditor::CreateObject()
{

    //for�ŉ񂵂�FBXPATTERN��filename�̗v�f�̏��Ԃ���v�����Ƃ���ŃI�u�W�F�N�g�����̂��z�肵������objectName�Ƃ����߂�ǂ������Ȃ邩�疳��
    //�Ή�����enum�^�̐����ɂȂ����炻�̃I�u�W�F�N�g���쐬����createObject�Ƀv�b�V���o�b�N����

    //���ꂼ��̃I�u�W�F�N�g�̃C���X�^���X���N���X�ϐ���vector�Ŏ����āA���[�����[������΂Ȃ񂩂����Ɗy�ł���������ˁH
    switch (selecting_object)
    {
    case TESTFLOOR: {
        TestFloor* pObject = CreateInstance<TestFloor>();
        return pObject;
        break;
    }
    case TESTWALL: {
        TestWall* pObject = CreateInstance<TestWall>();
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

void MapEditor::AddCreateObject(GameObject* object)
{
    //CheckDeleteObject();
    createObjectList_.push_back(object);
    nextObjectId_++;
}

std::vector<std::string> MapEditor::get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false)
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

void MapEditor::CheckDeleteObject()
{

    for (auto itr = createObjectList_.begin(); itr != createObjectList_.end();) {
        if ((*itr)->IsDead()) {
            itr = createObjectList_.erase(itr);
        }
        else {
            itr++;
        }
    }
}

void MapEditor::AllDeleteCreateObject()
{
    for (auto itr = createObjectList_.begin(); itr != createObjectList_.end();itr++) {
        (*itr)->KillMe();
    }

    createObjectList_.clear();
}

void MapEditor::ChengeUp(GameObject* pTarget)
{

    auto itr = createObjectList_.begin();

    //���ɐ擪�Ȃ�
    if ((*itr) == pTarget)
        return;

    for (itr ; itr != createObjectList_.end(); itr++) {
        if ((*itr) == pTarget) {
            createObjectList_.splice(std::next(itr, -1), createObjectList_, itr);
            break;
        }
    }


    //���̊֐����q����Ăяo���Ă�̂�KillAllChildren�łԂ��E���Ă邩��G���[�ɂȂ�
    //bool�^�ϐ��������true�Ȃ炱������UpDate���ɏ�̏���������z���l�������ǃt�@�C���̃��[�h����肭�ł��ĂȂ������B�v���W�F�N�g���s���̓t�@�C�����������Ă����s���ɂ͐V�����f�[�^�����[�h�ł��Ȃ��H
}

void MapEditor::ChengeDown(GameObject* pTarget)
{

    auto itr = createObjectList_.end();

    itr--;
    //���Ɉ�Ԍ��Ȃ�
    if ((*itr) == pTarget)
        return;

    while(itr!=createObjectList_.begin()) {

        itr--;

        if ((*itr) == pTarget) {
            createObjectList_.splice(std::next(itr, 2), createObjectList_, itr);
            break;
        }
    }

}

int MapEditor::MaxObjectId()
{
    int ID = 0;
    for (auto itr = createObjectList_.begin(); itr != createObjectList_.end(); itr++) {
        int tmp = (*itr)->GetObjectID();
        if (ID < tmp) {
            ID = tmp;
        }
    }

    return ID;
}

void MapEditor::BackUpSave()
{

}
