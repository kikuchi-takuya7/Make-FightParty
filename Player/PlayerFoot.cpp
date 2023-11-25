#include "PlayerFoot.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
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
        "PlayerFbx/HandArms.fbx",
        "PlayerFbx/ThighLegs.fbx"
    };
    for (int i = 0; i < NUM; i++) {
        hModel_[i] = Model::Load(fileName[i]);
        assert(hModel_[i] >= 0);
    }
    
    footTrans_ = transform_;
    //footTrans_.rotate_.x = 90.0f;
}

//更新
void PlayerFoot::Update()
{
    static int tmp = 0;

    if (Input::IsKey(DIK_Z)) {
        tmp += 1;
    }

    //目標地点（向くべき方向）
    XMVECTOR goal = { 5,5,5,0 };


    //①まずy軸で回転させて横軸を合わせる
    //②次にz軸を使って縦を合わせる
    //③最後にx軸で回転させる？モデルを横向きにしてx軸に合うように学校で治すってか腕はそう作ってるから足も全部腕でいいんじゃね

    //rotateで回転させてもそれはあくまでposition軸に回転させてて、positionは指定した位置から変わってないからrotateで回転させたとしても結局positionが変わってないからその次が無い。

    //
    footTrans_.position_.x = 10.0f;
    footTrans_.position_.y = 1.0f;
    footTrans_.position_.z = 5.0f;
    XMFLOAT3 f = footTrans_.position_;
    f.y = 0;
    XMVECTOR nowPos = XMLoadFloat3(&f);

    //モデルの長さ
    //float xLen = 4.0f;

    //ゴールのベクトルの長さ
    //float yLength = Length(goal);

    //モデルと目標地点をつなぐ斜面（三平方の定理）
    //float slope = std::hypot(xLen, yLength);

    //目標位置をローカル座標に( 多分いらない)
     
    
    //ローカル座標から三角比を用いて色々計算する
    //x軸に回転させてからy軸に回転させようの巻き（セガのサイト通りに書いてるからx軸っぽいけど違う説もある）

    //Y軸回転させるための変数
    XMVECTOR goalY = goal;
    goalY = XMVectorSetY(goal, 0);

    XMVECTOR goalN = XMVector3Normalize(goalY);
    XMVECTOR nowPosN = XMVector3Normalize(nowPos);
    XMVECTOR dot = XMVector3Dot(goalN, nowPosN); //内積を求める
    float dotLen = XMVectorGetX(dot);

    //サイトと同じようにやってみる
    //XMVECTOR cosSZ = nowPos / (nowPos * nowPos) + (goal * goal);

    //これでx軸回転の角度
    float cosZ = acos(dotLen);
    
    XMMATRIX rotX = XMMatrixIdentity();

    rotX = XMMatrixRotationX(cosZ);   //X軸で回転行列

    //rotX = XMMatrixRotationX(XMConvertToRadians(45));

    //footTrans_.rotate_.x = XMConvertToDegrees(cosZ);

    //X軸回転行列を適用
    nowPos = XMVector3TransformCoord(nowPos, rotX);
    XMStoreFloat3(&footTrans_.position_, nowPos);

}

//描画
void PlayerFoot::Draw()
{
    Model::SetTransform(hModel_[0], footTrans_);
    Model::Draw(hModel_[0]);
}

//開放
void PlayerFoot::Release()
{
}

void PlayerFoot::Imgui_Window()
{
    ImGui::Begin("DataWindow");
    if (ImGui::CollapsingHeader("MapEditor"))
    {
    }

    if (ImGui::TreeNode("Object")) {//Objectのツリーをクリックすると


        ImGui::TreePop();
    }

    ImGui::End();
}
