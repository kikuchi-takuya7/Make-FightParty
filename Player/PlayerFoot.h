#pragma once
#include "../Engine/GameObject.h"



//◆◆◆を管理するクラス
class PlayerFoot : public GameObject
{

public:
    //コンストラクタ
    PlayerFoot(GameObject* parent);

    //デストラクタ
    ~PlayerFoot();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void Imgui_Window() override;

private:

    enum PLAYERFOOT {

        FOOT,
        LEG,
        NUM
    };

    int hModel_[NUM];
    int hBallModel_;
    Transform footTrans_;
    Transform footRoot_;
    XMFLOAT3 goalValue_;
};