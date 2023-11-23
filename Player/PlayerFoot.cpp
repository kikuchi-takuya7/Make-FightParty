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
        "PlayerFbx/FootLegs.fbx",
        "PlayerFbx/ThighLegs.fbx"
    };
    for (int i = 0; i < NUM; i++) {
        hModel_[i] = Model::Load(fileName[i]);
        assert(hModel_[i] >= 0);
    }
    
    footTrans_ = transform_;

}

//更新
void PlayerFoot::Update()
{
    static int tmp = 0;

    if (Input::IsKey(DIK_Z)) {
        tmp += 1;
    }

    //目標地点（向くべき方向）
    XMVECTOR goal = { 3,5,5,0 };

    //モデルの中心を先端にしてるからとりあえずこれで。
    XMFLOAT3 f = footTrans_.position_;
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


    //ベクトルが足りない説。終点しか指定してないから始点も指定するべき？一つの座標だけでベクトルってのもおかしな話な気がしてきた
    XMVECTOR goalN = XMVector3Normalize(goal);
    XMVECTOR nowPosN = XMVector3Normalize(nowPos);
    XMVECTOR dot = XMVector3Dot(goalN, nowPosN); //内積を求める
    float dotLen = XMVectorGetX(dot);

    //これでx軸回転の角度
    float cosZ = acos(dotLen);
    
    XMMATRIX rotX = XMMatrixIdentity();

    //rotX = XMMatrixRotationX(cosZ);   //X軸で回転行列

    rotX = XMMatrixRotationX(XMConvertToRadians(45));

    footTrans_.rotate_.x = XMConvertToDegrees(cosZ);

    //X軸回転行列を適用
    /*nowPos = XMVector3TransformCoord(nowPos, rotX);
    XMStoreFloat3(&footTrans_.position_, nowPos);*/

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