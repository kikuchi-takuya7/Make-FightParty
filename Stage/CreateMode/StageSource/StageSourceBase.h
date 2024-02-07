#pragma once
#include "../../../Engine/GameObject.h"


class CreateMode;

//StageSource�̌��ƂȂ�N���X
class StageSourceBase : public GameObject
{

protected:

    int hModel_;

public:
    //�R���X�g���N�^
    StageSourceBase(GameObject* parent,std::string name);

    //�f�X�g���N�^
    ~StageSourceBase();

    //////////////�I�[�o�[���[�h�����֐�///////////////

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    

    ///////////////�p����Ŏg���֐�///////////////////////

    /// <summary>
    /// �p����p�̏�����
    /// </summary>
    virtual void ChildInitialize() {};

    /// <summary>
    /// �p����p��Update
    /// </summary>
    virtual void ChildUpdate() {};

    /// <summary>
    /// �p����p�̕`��
    /// </summary>
    virtual void ChildDraw() {};

    /// <summary>
    /// �p����p�̊J��
    /// </summary>
    virtual void ChildRelease() {};


    ////////////////�A�N�Z�X�֐�//////////////////

    int GetHandle() { return hModel_; }
    void SetHandle(int handle) { hModel_ = handle; }


private:

    


};