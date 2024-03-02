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

    int hPict_[NUM];

    Text* pText_;

    Transform make_Trans_;
    Transform and_Trans_;
    Transform fight_Trans_;
};