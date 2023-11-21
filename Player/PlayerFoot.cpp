#include "PlayerFoot.h"
#include "../Engine/Model.h"

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