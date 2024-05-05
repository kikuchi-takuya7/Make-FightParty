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

    void SetObjCsv(CsvReader* csv, int csvPos) override;


private:

    //発砲時のエフェクト
    void FiringEffect();

    //タイマー
    Timer* timer_;

    //効果音
    int hAudio_;

    //球の情報
    BulletData bulletData_;
};