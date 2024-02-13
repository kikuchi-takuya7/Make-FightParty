#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

class Timer;

/// <summary>
/// 一定間隔で攻撃する砲台
/// </summary>
class Cannon : public StageSourceBase
{

public:
    //コンストラクタ
    Cannon(GameObject* parent);

    //デストラクタ
    ~Cannon();

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

    //砲台の球
    SphereCollider* pBulletCollider_;

    Timer* timer_;
};