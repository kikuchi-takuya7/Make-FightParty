#pragma once
#include "../Engine/GameObject.h"
#include <vector>
#include <queue>

class RankingGaugeUI;
class Text;
enum SCOREGAUGELIST;
class RateFrame;

/// <summary>
/// �ꎎ���̏��҂����܂�����ɏo�郉���L���O��UI
/// </summary>
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

    /// <summary>
    /// �v���C���[�̖��O��ݒ�
    /// </summary>
    /// <param name="ID">�ݒ肵�����v���C���[��ID</param>
    /// <param name="str">���O</param>
    void SetPlayerName(int ID, std::string str);

    /// <summary>
    /// �X�R�A��ǉ�����
    /// </summary>
    /// <param name="ID">�X�R�A��ǉ��������v���C���[��ID</param>
    /// <param name="score">�ǉ�����X�R�A�̎��</param>
    /// <param name="num">���ǉ����邩</param>
    void SetScore(int ID, SCOREGAUGELIST score, int num = 1);

private:

    int hPict_;

    //{�Q�[�W�̃C���X�^���X�A�X�R�A}
    std::vector<RankingGaugeUI*> pGaugeList_;

    Text* pText_;

    RateFrame* rate_;
};