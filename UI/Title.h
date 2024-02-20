#pragma once
#include "../Engine/GameObject.h"

enum IMAGE {

    MAKE,
    AND,
    FIGHT,
    NUM
};

class Text;

/// <summary>
/// タイトルのロゴを管理するシーン
/// </summary>
class Title : public GameObject
{

public:
    //コンストラクタ
    Title(GameObject* parent);

    //デストラクタ
    ~Title();

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