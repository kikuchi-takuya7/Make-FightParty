#pragma once
#include "../Engine/GameObject.h"
#include "CreateMode/CreateMode.h"

class CreateMode;

//stageを管理するクラス
class Stage : public GameObject
{

public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;


    ////////////////アクセス関数//////////////////

    void SetCreateMode(CreateMode* createMode) { pCreateMode_ = createMode; }

private:

    int hModel_;

    CreateMode* pCreateMode_;


};