#pragma once
#include "../Engine/GameObject.h"

class RankingUI : public GameObject
{


public:

    //�R���X�g���N�^
    RankingUI(GameObject* parent);

    //�f�X�g���N�^
    ~RankingUI();

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