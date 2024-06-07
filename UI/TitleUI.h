#pragma once
#include "../Engine/GameObject.h"

//�^�C�g���̉摜��enum�ŊǗ�
enum IMAGE {

    MAKE,
    AND,
    FIGHT,
    NUM
};

class Text;
class RateFrame;

/// <summary>
/// �^�C�g���̃��S���Ǘ�����N���X
/// </summary>
class TitleUI : public GameObject
{

public:
    //�R���X�g���N�^
    TitleUI(GameObject* parent);

    //�f�X�g���N�^
    ~TitleUI();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

private:

    //�^�C�g�����S�̉摜�ԍ�
    int hPict_[NUM];

    //���ꂼ��̃��S�����������ǂ���
    bool moved_[NUM];

    //���ꂼ��̃��S�̌��݂̈ʒu
    XMFLOAT3 titlePos_[NUM];

    //�e�L�X�g�̃C���X�^���X
    Text* pText_;

    //���`��Ԃ̃��[�g�l
    RateFrame* rate_;

    //�w�i�摜�ԍ�
    int hBackGround_;
};