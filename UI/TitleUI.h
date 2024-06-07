#pragma once
#include "../Engine/GameObject.h"

//タイトルの画像をenumで管理
enum IMAGE {

    MAKE,
    AND,
    FIGHT,
    NUM
};

class Text;
class RateFrame;

/// <summary>
/// タイトルのロゴを管理するクラス
/// </summary>
class TitleUI : public GameObject
{

public:
    //コンストラクタ
    TitleUI(GameObject* parent);

    //デストラクタ
    ~TitleUI();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

private:

    //タイトルロゴの画像番号
    int hPict_[NUM];

    //それぞれのロゴが動いたかどうか
    bool moved_[NUM];

    //それぞれのロゴの現在の位置
    XMFLOAT3 titlePos_[NUM];

    //テキストのインスタンス
    Text* pText_;

    //線形補間のレート値
    RateFrame* rate_;

    //背景画像番号
    int hBackGround_;
};