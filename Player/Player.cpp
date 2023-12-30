#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),hModel_(-1)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("PlayerFbx/Body.fbx");
    assert(hModel_ >= 0);
}

//更新
void Player::Update()
{
    pState_->Update(this);
    

}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}

//状態を変更
void Player::ChangeState(PlayerState nextState)
{
}
