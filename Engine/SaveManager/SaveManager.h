#pragma once
#include "../GameObject.h"
#include "../../MapEditor/MapEditor.h"


//���������Ǘ�����N���X
class SaveManager
{

public:

    //�R���X�g���N�^
    SaveManager();

    //�f�X�g���N�^
    ~SaveManager();

    void Save(std::list<GameObject*> list);

    void AddSaveObj(GameObject* obj);

    void Load();

    GameObject* CreateObj(std::string className);     // �I�u�W�F�N�g����

    //�t�@�C�����J����SaveManager�ɕۑ�����
    void OpenFile();

    //�V�����t�@�C�������
    void NewCreateFile();

private:

    char fileName_[MAX_PATH];

    /// <summary>
    ///�@�I�u�W�F�N�g�����B�e��MapEditor�������ꍇ��mapEditor�̒���list�ɓ����
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="pParent">�Ăяo�����N���X�̐e�N���X</param>
    /// <returns>������I�u�W�F�N�g</returns>
    template <class T>
    T* CreateObject(GameObject* pParent)
    {
        /*T* object = Instantiate<T>(pParent);

        if (pParent->GetObjectName() == "MapEditor")
            ((MapEditor*)pParent->GetParent())->AddCreateObject(object);

        return object;*/
        return nullptr
    }
    //�Z�[�u�}�l�[�W���[�F�X�ς��Ă�Ƃ��ɕK�v�Ȃ����Č��_�Ɏ�����
    
};



//namespace�Ŏ������l��������CreateObj�Őe��T���ł��Ȃ����畁�ʂ�GameObject���p���������B�ǂ������������狳����
