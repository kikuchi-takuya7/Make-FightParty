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

    int hPict_[NUM];

    Text* pText_;

    Transform make_Trans_;
    Transform and_Trans_;
    Transform fight_Trans_;
};