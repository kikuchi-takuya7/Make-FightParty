#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

/// <summary>
/// 踏むと鈍足になる泥
/// </summary>
class Mud : public StageSourceBase
{

public:
    //コンストラクタ
    Mud(GameObject* parent);

    //デストラクタ
    ~Mud();

    //初期化
    void ChildInitialize() override;

    //更新
    void ChildUpdate() override;

    //描画
    void ChildDraw() override;

    //開放
    void ChildRelease() override;


    void OnCollision(GameObject* pTarget) override;

    //アクセス関数
    float GetDeceleration() { return deceleration_Rate_; }

private:

    //この泥を踏んでいる時の減速率
    float deceleration_Rate_;

};