#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

/// <summary>
/// 一マス分の普通のブロック
/// </summary>
class OneBrock : public StageSourceBase
{
    
public:
    //コンストラクタ
    OneBrock(GameObject* parent);

    //デストラクタ
    ~OneBrock();

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