#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

/// <summary>
/// 回転する刃のオブジェクト
/// </summary>
class RotateBlade : public StageSourceBase
{

public:
    //コンストラクタ
    RotateBlade(GameObject* parent);

    //デストラクタ
    ~RotateBlade();

    //初期化
    void ChildInitialize() override;

    //更新
    void ChildUpdate() override;

    //描画
    void ChildDraw() override;

    //開放
    void ChildRelease() override;


    void OnCollision(GameObject* pTarget) override;

private:


};