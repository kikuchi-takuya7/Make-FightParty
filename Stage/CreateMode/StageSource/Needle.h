#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

/// <summary>
/// 一マス分の普通のブロック
/// </summary>
class Needle : public StageSourceBase
{

public:
    //コンストラクタ
    Needle(GameObject* parent);

    //デストラクタ
    ~Needle();

    //初期化
    void ChildInitialize() override;

    //更新
    void ChildUpdate() override;

    //描画
    void ChildDraw() override;

    //開放
    void ChildRelease() override;


    void OnCollision(GameObject* pTarget) override;


    int GetNeedlePower() { return needlePower_;}

private:

    int needlePower_;

};