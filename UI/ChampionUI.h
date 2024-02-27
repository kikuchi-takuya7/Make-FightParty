#pragma once
#include "../Engine/GameObject.h"

class ChampionUI : public GameObject
{


public:

    //�R���X�g���N�^
    ChampionUI(GameObject* parent);

    //�f�X�g���N�^
    ~ChampionUI();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

private:

    int hPict_;
};