#pragma once
#include "../Engine/GameObject.h"

enum IMAGE {

    MAKE,
    AND,
    FIGHT,
    NUM
};

class Text;

/// <summary>
/// �^�C�g���̃��S���Ǘ�����V�[��
/// </summary>
class Title : public GameObject
{

public:
    //�R���X�g���N�^
    Title(GameObject* parent);

    //�f�X�g���N�^
    ~Title();

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