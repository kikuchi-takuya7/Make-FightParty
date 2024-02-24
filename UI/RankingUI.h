#pragma once
#include "../Engine/GameObject.h"
#include <vector>

class RankingGaugeUI;

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

    void AddGaugeValue(int ID, int value);

    bool IsAllEndAnim();


    ///////////�����L���O�Q�[�W���ꏏ�ɑ���֐�/////////////
    void StopDraw();
    void StartDraw();
    void StopUpdate();
    void StartUpdate();

private:

    int hPict_;

    std::vector<RankingGaugeUI*> pGaugeList_;

};