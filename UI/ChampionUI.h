#pragma once
#include "../Engine/GameObject.h"

class Timer;
class Text;

/// <summary>
/// �D���҂����܂������ɏo��UI
/// </summary>
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

    bool IsEnd();

private:

    int hPict_;

    int hAudio_;

    Timer* pTimer_;

    Text* pText_;


};