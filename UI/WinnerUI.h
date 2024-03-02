#pragma once
#include "../Engine/GameObject.h"

//�����̉摜��enum�ŊǗ�
enum PLAYERNUMBER {
    ONE,
    TWO,
    THREE,
    FOUR,
    PLAYER_NUM
};

/// <summary>
/// �N������������\������UI
/// </summary>
class WinnerUI : public GameObject
{


public:

    //�R���X�g���N�^
    WinnerUI(GameObject* parent);

    //�f�X�g���N�^
    ~WinnerUI();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    /// <summary>
    /// �������v���C���[��ID���Z�b�g����
    /// </summary>
    /// <param name="ID">�������v���C���[��ID</param>
    void SetWinnerID(int ID) { winnerID_ = ID; }

private:

    int hPict_[PLAYER_NUM];
    int hWinnerPict_;

    int winnerID_;

};