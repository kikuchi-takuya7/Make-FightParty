#pragma once
#include "../Engine/GameObject.h"

enum COUNTTIME {
    
    COUNT_GO,
    COUNT_1,
    COUNT_2,
    COUNT_3,
    COUNT_NUM

};

class Timer;

/// <summary>
/// カウントダウンのUIを管理するクラス
/// </summary>
class CountDown : public GameObject
{

public:
    //コンストラクタ
    CountDown(GameObject* parent);

    //デストラクタ
    ~CountDown();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void Reset();

    void Start();

    bool IsFinished();

private:

    int hPict_[COUNT_NUM];
    Timer* timer_;
    
    
};