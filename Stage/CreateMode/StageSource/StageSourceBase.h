#pragma once
#include "../../../Engine/GameObject.h"


class CreateMode;

//StageSource�̌��ƂȂ�N���X
class StageSourceBase : public GameObject
{

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

    void OnCollision(GameObject* pTarget) override;

    ///////////////�p����Ŏg���֐�///////////////////////




    ////////////////�A�N�Z�X�֐�//////////////////

    int GetStageHandle() { return hModel_; }


private:

    int hModel_;


};