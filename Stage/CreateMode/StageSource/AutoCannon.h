#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

class Timer;
class MetaAI;
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
    void SetMetaAI(MetaAI* metaAI) { pMetaAI_ = metaAI; }
    void SetNavigationAI(NavigationAI* naviAI) { pNavigationAI_ = naviAI; }

private:

    //発砲時のエフェクト
    void FiringEffect();

    Timer* timer_;

    int hAudio_;

    //AIのインスタンス
    MetaAI* pMetaAI_;
    NavigationAI* pNavigationAI_;

    //ターゲットの情報
    int target_;

};