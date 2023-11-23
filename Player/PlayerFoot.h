#pragma once
#include "../Engine/GameObject.h"



//���������Ǘ�����N���X
class PlayerFoot : public GameObject
{

public:
    //�R���X�g���N�^
    PlayerFoot(GameObject* parent);

    //�f�X�g���N�^
    ~PlayerFoot();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

private:

    enum PLAYERFOOT {

        FOOT,
        LEG,
        NUM
    };

    int hModel_[NUM];
    Transform footTrans_;

};