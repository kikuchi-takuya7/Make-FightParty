#pragma once
#include "../GameObject.h"
#include "../MapEditor/MapEditor.h"


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

    template <class T>
    T* CreateObject()
    {
        T* object = Instantiate<T>(this->GetParent());

        if (this->GetParent()->GetObjectName() == "MapEditor")
            ((MapEditor*)this->GetParent())->AddCreateObject(object);

        return object;
    }
    
};



//namespace�Ŏ������l��������CreateObj�Őe��T���ł��Ȃ����畁�ʂ�GameObject���p���������B�ǂ������������狳����
