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


    //本当はx座標を移動させてもy軸しか動かないはずなのにz軸も動いてる。なぜ

    //目標地点(向くべき方向で、最終的な先端の位置)
    XMVECTOR goal = XMLoadFloat3(&goalValue_);

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

    cos = XMConvertToDegrees(cos);

    if (checkGoal.y <= 0) {
        cos *= -1;
    }

    //根本から回すから根元を回転させる
    footRoot_.rotate_.z = cos;

    //これでfootRootのrotateはゴールの向きに向いたっていう想定。
    //footRoot.rotate分の回転行列をかけたあとに平行移動行列

    //角度確認のテスト用
    //footRoot_.rotate_.z = 0;



    ////腕の長さ分だけ平行移動させる
    //XMMATRIX moveLen = XMMatrixTranslation(MODELLENGTH, 0, 0);

    ////ベクトルにして行列を適用させる。モデルの根元のpositionをベクトルに
    ////平行移動させる必要ないならまだ行列いらない？
    //tmpFloat = footRoot_.position_;

    ////footRoot.rotateの分だけ回転
    //XMMATRIX rotZ,rotY;
    //rotY = XMMatrixRotationY(XMConvertToRadians(footRoot_.rotate_.y));
    //rotZ = XMMatrixRotationZ(XMConvertToRadians(footRoot_.rotate_.z));

    //XMMATRIX rotMatrix = rotY * rotZ;

    //nowPos = XMLoadFloat3(&tmpFloat);
    //nowPos = XMVector3TransformCoord(nowPos, rotMatrix);
    
    ////行列を適用したベクトルをfootTransに入れる。footRootの位置からモデルの長さ分角度をつけて伸ばした位置にあるはず。そしてそれがゴールの位置のはず
    //XMStoreFloat3(&footRoot_.position_, nowPos);
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
