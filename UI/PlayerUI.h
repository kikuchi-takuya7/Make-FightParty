#pragma once
#include "../Engine/GameObject.h"

class Text;
class Gauge;

/// <summary>
/// �^�C�g���̃��S���Ǘ�����V�[��
/// </summary>
class PlayerUI : public GameObject
{

public:
    //�R���X�g���N�^
    PlayerUI(GameObject* parent);

    //�f�X�g���N�^
    ~PlayerUI();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;


    void SetNowHp(int nowHp);

private:

    int hPict_;

    Text* pText_;

    Gauge* pGauge_;

    Transform playerUITrans_;

};