#pragma once
#include "../Engine/GameObject.h"

class WinPlayerUI : public GameObject
{


public:

    //�R���X�g���N�^
    WinPlayerUI(GameObject* parent);

    //�f�X�g���N�^
    ~WinPlayerUI();

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