#include "PlayerFoot.h"
#include "../Engine/Model.h"
#include <cmath>

//コンストラクタ
PlayerFoot::PlayerFoot(GameObject* parent)
    :GameObject(parent, "PlayerFoot"), hModel_{-1,-1}
{
}

//デストラクタ
PlayerFoot::~PlayerFoot()
{
}

//初期化
void PlayerFoot::Initialize()
{
    //モデルデータのロード
    std::string fileName[NUM] = {
        "PlayerFbx/FootLegs.fbx",
        "PlayerFbx/ThighLegs.fbx"
    };
    for (int i = 0; i < NUM; i++) {
        hModel_[i] = Model::Load(fileName[i]);
        assert(hModel_[i] >= 0);
    }
    
}

//更新
void PlayerFoot::Update()
{
    //目標地点（向くべき方向）
    XMVECTOR goal = { -5,0,0,0 };
    
    //モデルの長さ
    float xLen = 4.0f;

    //ゴールのベクトルの長さ
    float yLength = Length(goal);

    //モデルと目標地点をつなぐ斜面（三平方の定理）
    float slope = std::hypot(xLen, yLength);

    //目標位置をローカル座標に( 多分いらない)
     
    
    //ローカル座標から三角比を用いて色々計算する

    float cosZ = std::cos(xLen);


}

//描画
void PlayerFoot::Draw()
{
    Model::SetTransform(hModel_[0], transform_);
    Model::Draw(hModel_[0]);
}

//開放
void PlayerFoot::Release()
{
}