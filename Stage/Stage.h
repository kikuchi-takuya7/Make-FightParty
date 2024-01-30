#pragma once
#include "../Engine/GameObject.h"

//stage���Ǘ�����N���X
class Stage : public GameObject
{

public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;



private:

    int hModel_;




};