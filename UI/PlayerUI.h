#pragma once
#include "../Engine/GameObject.h"

class Text;
class HpGaugeUI;

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

    

    //////////////�A�N�Z�X�֐�/////////////

    void SetMaxHp(int nowHp, int maxHp);
    void SetNowHp(int nowHp);
    void SetPlayerUIPos(XMFLOAT3 pos);
    void SetPlayerName(std::string name) { playerName_ = name; }

    void StopDraw();
    void StartDraw();

private:
    
    //PlayerUI�̉摜�n���h��
    int hPict_;

    //�v���C���[��
    Text* pText_;

    //HP�Q�[�W
    HpGaugeUI* pHpGauge_;

    Transform playerUITrans_;

    //�ׂ�UI�Ƃ̋���
    int diff_;

    //�v���C���[�̖��O
    std::string playerName_;

};