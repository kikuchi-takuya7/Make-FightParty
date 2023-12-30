#pragma once
#include "../Engine/GameObject.h"
#include "../State/PlayerState.h"
#include "../Engine/Global.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    

private:

    int hModel_;

    PlayerState* pState_; //プレイヤーの状態を表す

};