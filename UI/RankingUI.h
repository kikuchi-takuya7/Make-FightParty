#pragma once
#include "../Engine/GameObject.h"
#include <vector>
#include <queue>

class RankingGaugeUI;
enum SCOREGAUGELIST;

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

    bool IsAllEndAnim();

    void EndAnim();

    void ResetPos();

    ////////////////�A�N�Z�X�֐�///////////////

    void SetPlayerName(int ID, std::string str);

    void SetScore(int ID, SCOREGAUGELIST score, int num);

private:

    int hPict_;

    //{�Q�[�W�̃C���X�^���X�A�X�R�A}
    std::vector<RankingGaugeUI*> pGaugeList_;
};