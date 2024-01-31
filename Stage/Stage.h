#pragma once
#include "../Engine/GameObject.h"
#include "CreateMode/CreateMode.h"

class CreateMode;

//stage���Ǘ�����N���X
class Stage : public GameObject
{

public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;


    ////////////////�A�N�Z�X�֐�//////////////////

    void SetCreateMode(CreateMode* createMode) { pCreateMode_ = createMode; }

private:

    int hModel_;

    CreateMode* pCreateMode_;


};