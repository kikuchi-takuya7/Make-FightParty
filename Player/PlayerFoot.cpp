#include "PlayerFoot.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include <cmath>

//モデルの長さ
const float MODELLENGTH = 4.0f;

//コンストラクタ
PlayerFoot::PlayerFoot(GameObject* parent)
    :GameObject(parent, "PlayerFoot"), hModel_{-1,-1},hBallModel_(-1)
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

    hBallModel_ = Model::Load("EditorUIFbx/Ball.fbx");
    assert(hBallModel_ >= 0);
    
    /*transform_.position_.x = 4.0f;
    transform_.position_.y = 1.0f;
    transform_.position_.z = 5.0f;*/

    footRoot_ = transform_;

    //モデル根本の位置
    footRoot_.position_.x += 0.0f;
    footRoot_.position_.y += 0.0f;
    footRoot_.position_.z += 0.0f;

    //モデルの先端のposition
    footTrans_ = footRoot_;
    
    //モデルの長さを4にしてるから
    footTrans_.position_.x += MODELLENGTH;

    goalValue_ = { 0,0,0 };
    
}

//更新
void PlayerFoot::Update()
{

    //①まずy軸で回転させて横軸を合わせる
    //②次にz軸を使って縦を合わせる
    //③最後にx軸で回転させる？モデルを横向きにしてx軸に合うように学校で治すってか腕はそう作ってるから足も全部腕でいいんじゃね

    //モデル.positionでモデルの回転する根本を指して、それにx（横幅の長さ）を足した数を先端positionとする。（平行移動行列で横移動させてから角度の回転行列をかければいいかな）
    //角度が出来たらモデル.rotateで回転させて、


    //ローカル座標から三角比を用いて色々計算する
    //x軸に回転させてからy軸に回転させようの巻き（セガのサイト通りに書いてるからx軸っぽいけど違う説もある）
  

    //目標地点(向くべき方向で、最終的な先端の位置)
    XMVECTOR goal = XMLoadFloat3(&goalValue_);


    //この中はヨー回転とか実験中だったから中途半端
#if 1

    //回転が-にも行くようにする
    XMFLOAT3 checkGoal;
    XMStoreFloat3(&checkGoal, goal);

    //現在のベクトル（先端）
    XMFLOAT3 tmpFloat = footTrans_.position_;
    tmpFloat.y = 0;
    
    //先端の位置のベクトル
    XMVECTOR nowPos = XMLoadFloat3(&tmpFloat);

    //Y軸回転させるための変数
    XMVECTOR goalTmp = goal;
    goalTmp = XMVectorSetY(goal, 0);

    XMVECTOR goalN = XMVector3Normalize(goalTmp);
    XMVECTOR nowPosN = XMVector3Normalize(nowPos);
    XMVECTOR dot = XMVector3Dot(goalN, nowPosN); //内積を求める
    float dotLen = XMVectorGetX(dot);

    //これでy軸回転の角度
    float cos = acos(dotLen);

    float yaw = -cos;

    //根本から回すから根元を回転させる
    cos = -XMConvertToDegrees(cos);////////////////////////なぜかy軸の回転が逆だったからここマイナスにしてる。多分cosの仕様？

    //cosがマイナスになるように
    if (checkGoal.z <= 0) {
        cos *= -1;
    }

    

    footRoot_.rotate_.y = cos;
    

    ///////////////こっから縦軸回転///////////////////////
    //y軸回転させてからz軸回転

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

    float pitch = cos;

    cos = XMConvertToDegrees(cos);

    if (checkGoal.y <= 0) {
        cos *= -1;
    }

    

    //根本から回すから根元を回転させる
    footRoot_.rotate_.z = cos;


    //こんな行列があったけどまだ使う必要はなさそう。
    XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, 0);

    nowPos = XMLoadFloat3(&footRoot_.position_);
    nowPos = XMVector3Transform(nowPos, rotMatrix);
    
    //行列を適用したベクトルをfootTransに入れる。footRootの位置からモデルの長さ分角度をつけて伸ばした位置にあるはず。そしてそれがゴールの位置のはず
    XMStoreFloat3(&footRoot_.position_, nowPos);

#else

    //回転が-にも行くようにする
    XMFLOAT3 checkGoal;
    XMStoreFloat3(&checkGoal, goal);

    //現在のベクトル（先端）
    XMFLOAT3 tmpFloat = footTrans_.position_;
    tmpFloat.y = 0;
    XMVECTOR nowPosXZ = XMLoadFloat3(&tmpFloat);

    //Yの値を無くしてxz座標と考えた変数
    XMVECTOR goalTmp = goal;
    goalTmp = XMVectorSetY(goal, 0);

    //z（サイトではy）の長さを求める
    XMVECTOR LengthTmp = goalTmp - nowPosXZ;
    float zLength = Length(LengthTmp);

    tmpFloat = footTrans_.position_;
    tmpFloat.z = 0;
    XMVECTOR nowPosXY = XMLoadFloat3(&tmpFloat);

    //Zの値を無くしてxy座標と考えた変数
    goalTmp = goal;
    goalTmp = XMVectorSetZ(goal, 0);

    //y（サイトではz）の長さを求める
    LengthTmp = goalTmp - nowPosXY;
    float yLength = Length(LengthTmp);

    //xz座標から見た時の目標地点までの斜辺(高さ)
    float hypotZ = sqrt(pow(MODELLENGTH, 2) + pow(zLength, 2));

    //xy座標から見た時の斜辺(高さ)
    float hypotY = sqrt(pow(MODELLENGTH, 2) + pow(zLength, 2) + pow(yLength, 2));

    //コサインθy（サイトではz）
    float cosY = MODELLENGTH / hypotZ;
    float sinY = zLength / hypotZ;
    //コサインθz（サイトではy）
    float cosZ = hypotZ / hypotY;
    float sinZ = yLength / hypotY;

    ////xz平面で回転する回転行列を作る

    //XMMATRIX rotY = { cosY, -sinY,   0,0,
    //                  sinY,  cosY,   0,0,
    //                  0,     0,      0,0,
    //                  0,     0,      0,0 };


    XMVECTOR nowPos = XMLoadFloat3(&tmpFloat);

    //y軸で回転する回転行列を作る

    XMMATRIX rotY = { cosY,  0,   -sinY, 0,
                      0,     1,    0,    0,
                      sinY,  0,    cosY, 0,
                      0,     0,    0,    1 };

    //ベクトルに回転行列かけてもそのベクトルが回転するだけで根元の回転数はわからない。でも2ボーンIKの時に絶対必要になるから大事
    nowPos = XMVector3Transform(nowPos, rotY);

    XMMATRIX rotY = { cosY,  0,   -sinY, 0,
                      0,     1,    0,    0,
                      sinY,  0,    cosY, 0,
                      0,     0,    0,    1 };



#endif

}

//描画
void PlayerFoot::Draw()
{
    Model::SetTransform(hModel_[0], footRoot_);
    Model::Draw(hModel_[0]);

    Transform ballTrans;
    ballTrans.position_ = goalValue_;
    Model::SetTransform(hBallModel_, ballTrans);
    Model::Draw(hBallModel_);
}

//開放
void PlayerFoot::Release()
{
}

void PlayerFoot::Imgui_Window()
{

    ImGui::SetNextWindowPos(ImVec2(875, 400), ImGuiCond_Once);//, ImGuiCond_FirstUseEverこれを付けると初めて実行したときだけこの大きさに設定されて。それ以降はimgui.iniに保存される
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Once);//ImGuiCond_Onceを付けると呼び出すときだけこの大きさになる

    ImGui::Begin("DataWindow");
    if (ImGui::CollapsingHeader("MapEditor"))
    {
        if (ImGui::Button("reset")) {
            goalValue_.x = 0;
            goalValue_.y = 0;
            goalValue_.z = 0;
            goalValue_.x = 0;
        }

        Setting_Float3(goalValue_, -10, 10, "goal");
        ImGui::SliderFloat("rotate_x", &footRoot_.rotate_.x, 0, 360);
        
        std::string str = std::to_string(footRoot_.rotate_.x);
        ImGui::Text(str.c_str());

        str = std::to_string(footRoot_.rotate_.y);
        ImGui::Text(str.c_str());

        str = std::to_string(footRoot_.rotate_.z);
        ImGui::Text(str.c_str());
    }

    //if (ImGui::TreeNode("Object")) {//Objectのツリーをクリックすると


    //    ImGui::TreePop();
    //}

    ImGui::End();
}
