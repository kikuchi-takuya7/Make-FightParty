#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

class Timer;
class NavigationAI;

/// <summary>
/// 一定間隔で攻撃する砲台
/// </summary>
class AutoCannon : public StageSourceBase
{

public:
    //コンストラクタ
    AutoCannon(GameObject* parent);

    //デストラクタ
    ~AutoCannon();

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
    void SetNavigationAI(GameObject* AI) { pNavoigationAI = AI; }

private:

    void FiringEffect();

    Timer* timer_;

    int hAudio_;

    NavigationAI* pNavoigationAI;
};