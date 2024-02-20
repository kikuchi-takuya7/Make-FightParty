#pragma once
#include "../Engine/GameObject.h"

enum HPIMAGE {
    FLAME,
    GAUGEMAIN,
    GAUGELOW,
    GAUGEWHITE,
    HPIMAGE_NUM
};


//ゲージクラスはゲージの最大を100%（つまり1.0）となるように作る。
//表示の大きさによって表示サイズを変えられるように作る
//表示する位置は、外から（使う側）から指定できるようにする
//加算する関数と、減算する関数と、現在の値を取得する関数を用意する

class Gauge : public GameObject
{


public:

    

    //コンストラクタ
    Gauge(GameObject* parent);

    //デストラクタ
    ~Gauge();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    /// <summary>
    /// ゲージの値をセットする
    /// </summary>
    /// <param name="nowGauge">今の値</param>
    /// <param name="maxGauge">値の最大値</param>
    void SetGauge(int nowGauge, int maxGauge);

    /// <summary>
    /// 今のゲージの値を変える
    /// </summary>
    /// <param name="nowGauge">今の値</param>
    void SetNowGauge(int nowGauge);

    /// <summary>
    /// 値を加減算する
    /// </summary>
    /// <param name="v">加算したい値</param>
    void AddValue(float v);

    /// <summary>
    /// 値を引数の値に変更する
    /// </summary>
    /// <param name="v">変更後の値</param>
    void SetValue(float v);

    float GetValue();

private:

    int hPict_[HPIMAGE_NUM];

    float nowGauge_; //今の値
    int maxGauge_; //最大値
    float animGauge_; //アニメーション上のHP
};