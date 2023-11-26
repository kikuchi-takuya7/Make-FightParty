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
    
    //腕の長さ分余分に横に移動させようね。これが自由に動かせる先端の位置
    /*transform_.position_.x = 4.0f;
    transform_.position_.y = 1.0f;
    transform_.position_.z = 5.0f;*/

    footTrans_ = transform_;

    //腕の長さ分余分に横に移動させようね。これが自由に動かせる先端の位置
    footTrans_.position_.x = 4.0f;
    footTrans_.position_.y = 1.0f;
    footTrans_.position_.z = 5.0f;

    //モデルの根元のposition
    footRoot_ = footTrans_;
    
    footRoot_.position_.x += -4.0f;

    
}

//更新
void PlayerFoot::Update()
{

    //①まずy軸で回転させて横軸を合わせる
    //②次にz軸を使って縦を合わせる
    //③最後にx軸で回転させる？モデルを横向きにしてx軸に合うように学校で治すってか腕はそう作ってるから足も全部腕でいいんじゃね

    //モデル.positionでモデルの回転する根本を指して、それにx（横幅の長さ）を足した数を先端positionとする。（平行移動行列で横移動させてから角度の回転行列をかければいいかな）
    //角度が出来たらモデル.rotateで回転させて、

    //目標地点（向くべき方向）
    XMVECTOR goal = { 5,5,5,0 };

    //現在のベクトル
    XMFLOAT3 tmpFloat = footTrans_.position_;
    tmpFloat.y = 0;
    
    //先端の位置のベクトル
    XMVECTOR nowPos = XMLoadFloat3(&tmpFloat);


    //目標位置をローカル座標に( 多分いらない？)
     
    
    //ローカル座標から三角比を用いて色々計算する
    //x軸に回転させてからy軸に回転させようの巻き（セガのサイト通りに書いてるからx軸っぽいけど違う説もある）

    //Y軸回転させるための変数
    XMVECTOR goalTmp = goal;
    goalTmp = XMVectorSetY(goal, 0);

    XMVECTOR goalN = XMVector3Normalize(goalTmp);
    XMVECTOR nowPosN = XMVector3Normalize(nowPos);
    XMVECTOR dot = XMVector3Dot(goalN, nowPosN); //内積を求める
    float dotLen = XMVectorGetX(dot);

    //これでy軸回転の角度
    float cos = acos(dotLen);
    
    XMMATRIX rotX = XMMatrixIdentity();

    rotX = XMMatrixRotationX(cos);   //X軸で回転行列

    //rotX = XMMatrixRotationX(XMConvertToRadians(45));

    footRoot_.rotate_.y = XMConvertToDegrees(cos);

    //X軸回転行列を適用
    /*nowPos = XMVector3TransformCoord(nowPos, rotX);
    XMStoreFloat3(&f, nowPos);*/


    ///////////////こっから縦軸回転////////////

    tmpFloat = footTrans_.position_;
    tmpFloat.z = 0;

    nowPos = XMLoadFloat3(&tmpFloat);

    //z軸回転させるための変数
    goalTmp = goal;
    goalTmp = XMVectorSetZ(goal, 0);

    goalN = XMVector3Normalize(goalTmp);
    nowPosN = XMVector3Normalize(nowPos);
    dot = XMVector3Dot(goalN, nowPosN); //内積を求める
    dotLen = XMVectorGetX(dot);

    //これでz軸回転の角度
    cos = acos(dotLen);

    footRoot_.rotate_.z = XMConvertToDegrees(cos);

    //これでfootRootのrotateはゴールの向きに向いたっていう想定。無理だろうけど
    //footRoot.rotate分の回転行列をかけたあとに平行移動行列

    //footRoot.rotateの分だけ回転
    XMMATRIX rotZ,rotY;
    rotY = XMMatrixRotationY(XMConvertToRadians(footRoot_.rotate_.y));
    rotZ = XMMatrixRotationZ(XMConvertToRadians(footRoot_.rotate_.z));

    XMMATRIX rotMatrix = rotY * rotZ;

     //腕の長さ分だけ平行移動させる
    XMMATRIX moveLen = XMMatrixTranslation(4, 0, 0);

    //ベクトルにして行列を適用させる。モデルの長さ分動かしてるからモデルの根元のpositionをベクトルに
    tmpFloat = footRoot_.position_;

    nowPos = XMLoadFloat3(&tmpFloat);
    nowPos = XMVector3TransformCoord(nowPos, rotMatrix * moveLen);

    //行列を適用したベクトルをfootTransに入れる。footRootの位置からモデルの長さ分角度をつけて伸ばした位置にあるはず
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
