#pragma once
#include "../../GameObject.h"
#include "StageSourceBase.h"

//◆◆◆を管理するクラス
class TestFloor : public StageSourceBase
{


public:
    //コンストラクタ
    TestFloor(GameObject* parent);

    //デストラクタ
    ~TestFloor();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

};