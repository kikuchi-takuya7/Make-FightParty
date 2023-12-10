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

    footRootTrans_ = transform_;

    //モデル根本の位置
    footRootTrans_.position_.x += 0.0f;
    footRootTrans_.position_.y += 0.0f;
    footRootTrans_.position_.z += 0.0f;

    //モデルの先端のposition
    footTipTrans_ = footRootTrans_;
    
    //モデルの長さを4にしてるから
    footTipTrans_.position_.x += MODELLENGTH;

    goalValue_ = { 0,0,0 };
    ballTrans_.position_ = { 0,0,0 };
    prevBallRot_ = { 0,0,0 };

    prevCosY_ = 0;
    prevCosZ_ = 0;

    XMVECTOR nowFootTipPos = XMLoadFloat3(&ballTrans_.position_);

    //腕の長さ分だけ平行移動させる(今回はボールだから単位円の中)
    XMMATRIX moveLen = XMMatrixTranslation(1, 0, 0);

    XMMATRIX rotMatrix = moveLen;

    nowFootTipPos = XMVector3TransformCoord(nowFootTipPos, rotMatrix);

    XMStoreFloat3(&ballTrans_.position_, nowFootTipPos);

    prevBallRot_ = ballTrans_.position_;
    
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
    XMVECTOR goal = XMLoadFloat3(&ballTrans_.position_);

    //ballTrans_.rotate_ = goalValue_;

    if (goalValue_ == prevBallRot_) {
        return;
    }

#if 0

    //現在のベクトル（先端）
    XMFLOAT3 tmpFloat = footTipTrans_.position_;
    tmpFloat.y = 0;
    
    //先端の位置のベクトル
    XMVECTOR nowFootTipPos = XMLoadFloat3(&tmpFloat);

    //Y軸回転させるための変数
    XMVECTOR goalTmp = goal;
    goalTmp = XMVectorSetY(goal, 0);

    XMVECTOR goalN = XMVector3Normalize(goalTmp);
    XMVECTOR nowFootTipPosN = XMVector3Normalize(nowFootTipPos);
    XMVECTOR dot = XMVector3Dot(goalN, nowFootTipPosN); //内積を求める
    float dotLen = XMVectorGetX(dot);

    //これでy軸回転の角度
    float cos = acos(dotLen);

    float yaw = cos;

    //根本から回すから根元を回転させる
    cos = -XMConvertToDegrees(cos);////////////////////////なぜかy軸の回転が逆だったからここマイナスにしてる。多分cosの仕様？

    //cosがマイナスになるように
    if (goalValue_.z <= 0) {
        cos *= -1;
    }

    prevCosY_ += cos;
    

    footRootTrans_.rotate_.y = cos;
    

    ///////////////こっから縦軸回転///////////////////////
    //y軸回転させてからz軸回転

    tmpFloat = footTipTrans_.position_;
    tmpFloat.z = 0;

    nowFootTipPos = XMLoadFloat3(&tmpFloat);

    //z軸回転させるための変数
    goalTmp = goal;
    goalTmp = XMVectorSetZ(goal, 0);
    //goalTmp = XMVectorSetY(goal, tmpFloat.y);

    goalN = XMVector3Normalize(goalTmp);
    nowFootTipPosN = XMVector3Normalize(nowFootTipPos);
    dot = XMVector3Dot(goalN, nowFootTipPosN); //内積を求める
    dotLen = XMVectorGetX(dot);

    //これでz軸回転の角度
    cos = acos(dotLen);

    float pitch = cos;

    cos = XMConvertToDegrees(cos);

    if (goalValue_.y <= 0) {
        cos *= -1;
    }

    prevCosZ_ += cos;

    //根本から回すから根元を回転させる
    footRootTrans_.rotate_.z = cos;


    ////こんな行列があったけどまだ使う必要はなさそう。
    //XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, 0);

    //nowFootTipPos = XMLoadFloat3(&footTipTrans_.position_);
    //nowFootTipPos = XMVector3Transform(nowFootTipPos, rotMatrix);
    //
    ////行列を適用したベクトルをfootTransに入れる。footRootの位置からモデルの長さ分角度をつけて伸ばした位置にあるはず。そしてそれがゴールの位置のはず
    //XMStoreFloat3(&footTipTrans_.position_, nowFootTipPos);

    //prevBallRot_ = goalValue_;
    //footTipTrans_.position_ = goalValue_;

#else

    ////現在のベクトル（先端）
    //XMFLOAT3 tmpFloat = footTipTrans_.position_;
    //tmpFloat.y = 0;
    //XMVECTOR nowPosXZ = XMLoadFloat3(&tmpFloat);

    ////Yの値を無くしてxz座標と考えた変数
    //XMVECTOR goalTmp = goal;
    //goalTmp = XMVectorSetY(goal, 0);

    ////z（サイトではy）の長さを求める
    //XMVECTOR LengthTmp = goalTmp - nowPosXZ;
    //float zLength = Length(LengthTmp);

 
    //////////////////////ここからyの長さを求める///////////////////////
    //
    //tmpFloat = footTipTrans_.position_;
    //tmpFloat.z = 0;
    //XMVECTOR nowPosXY = XMLoadFloat3(&tmpFloat);

    ////Zの値を無くしてxy座標と考えた変数
    //goalTmp = goal;
    //goalTmp = XMVectorSetZ(goal, 0);

    ////y（サイトではz）の長さを求める
    //LengthTmp = goalTmp - nowPosXY;
    //float yLength = Length(LengthTmp);


    ///////////////////////ここから斜辺とか求める////////////////////////////////////


    ////xz座標から見た時の目標地点までの斜辺(高さ)
    //float hypotZ = sqrt(pow(MODELLENGTH, 2) + pow(zLength, 2));

    ////xy座標から見た時の斜辺(高さ)
    //float hypotY = sqrt(pow(MODELLENGTH, 2) + pow(zLength, 2) + pow(yLength, 2));

    ////コサインθy（サイトではz）
    //float cosY = MODELLENGTH / hypotZ;
    //float sinY = zLength / hypotZ;
    ////コサインθz（サイトではy）
    //float cosZ = hypotZ / hypotY;
    //float sinZ = yLength / hypotY;


    

    ////y軸で回転する回転行列を作る
    //XMMATRIX rotY = { cosY,  0,   -sinY, 0,
    //                  0,     1,    0,    0,
    //                  sinY,  0,    cosY, 0,
    //                  0,     0,    0,    1 };

    ////ベクトルに回転行列かけてもそのベクトルが回転するだけで根元の回転数はわからない。でも2ボーンIKの時に多分必要になるから大事
    //nowFootTipPos = XMVector3TransformCoord(nowFootTipPos, rotY);

    ////DirectXの座標系だとこれrotXになっちゃってる可能性。http://marupeke296.com/DXG_No39_WorldMatrixInformation.html
    //XMMATRIX rotZ = { 0,     0,       0,      0,
    //                  0,     1,       0,      0,
    //                  0,     cosZ,   -sinY,   0,
    //                  0,     sinY,    cosY,   1 };


    //nowFootTipPos = XMVector3TransformCoord(nowFootTipPos, rotZ);




    ////現在のベクトル（先端）
    //XMFLOAT3 tmpFloat = prevBallRot_;
    //tmpFloat.y = 0;

    ////先端の位置のベクトル
    //XMVECTOR nowBallPos = XMLoadFloat3(&tmpFloat);

    ////Y軸回転させるための変数
    //XMVECTOR goalTmp = goal;
    //goalTmp = XMVectorSetY(goal, 0);

    ////これでy軸回転の角度
    //float cos = DotCos(nowBallPos,goalTmp);

    ////根本から回すから根元を回転させる
    //cos = -cos;////////////////////////なぜかy軸の回転が逆だったからここマイナスにしてる。多分cosの仕様？

    ////cosがマイナスになるように
    ///*if (goalValue_.z <= 0) {
    //    cos *= -1;
    //}*/

    //XMMATRIX rotY = XMMatrixRotationY(cos);

    /////////////////こっから縦軸回転///////////////////////
    ////y軸回転させてからz軸回転

    //tmpFloat = prevBallRot_;
    //tmpFloat.z = 0;

    //nowBallPos = XMLoadFloat3(&tmpFloat);

    ////z軸回転させるための変数
    //goalTmp = goal;
    //goalTmp = XMVectorSetZ(goal, 0);
    ////goalTmp = XMVectorSetY(goal, tmpFloat.y);

    ////これでz軸回転の角度
    //cos = DotCos(nowBallPos, goalTmp);

    ///*if (goalValue_.y <= 0) {
    //    cos *= -1;
    //}*/

    //XMMATRIX rotZ = XMMatrixRotationZ(cos);



    XMVECTOR nowFootTipPos = XMLoadFloat3(&ballTrans_.position_);

    float te = XMConvertToRadians(goalValue_.y);

    XMFLOAT3 tmp = Transform::Float3Sub(goalValue_, prevBallRot_);

    XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(tmp.x));
    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(tmp.y));
    XMMATRIX rotZ = XMMatrixRotationZ(XMConvertToRadians(tmp.z));

    XMMATRIX rocalMat = GetWorldMatrix();

    rocalMat = XMMatrixInverse(nullptr, rocalMat);

    XMMATRIX rotMatrix = rotZ * rotX * rotY;//ロールピッチヨー回転の順番

    nowFootTipPos = XMVector3TransformCoord(nowFootTipPos, rotMatrix * rocalMat);

    XMStoreFloat3(&ballTrans_.position_, nowFootTipPos);

    prevBallRot_ = goalValue_;

#endif

}

//描画
void PlayerFoot::Draw()
{
    Model::SetTransform(hModel_[TIP], footRootTrans_);
    Model::Draw(hModel_[TIP]);

    
    
    Model::SetTransform(hBallModel_, ballTrans_);
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
        }

        Setting_Float3(goalValue_, 0, 360, "goal");
        //ImGui::SliderFloat("rotate_x", &footRootTrans_.rotate_.x, 0, 360);
        
        ImGui::Text("footRootTrans.rotate");
        std::string str = std::to_string(footRootTrans_.rotate_.x);
        ImGui::Text(str.c_str());

        str = std::to_string(footRootTrans_.rotate_.y);
        ImGui::Text(str.c_str());

        str = std::to_string(footRootTrans_.rotate_.z);
        ImGui::Text(str.c_str());

        ImGui::Text("ballTrans.rotate");
        str = std::to_string(ballTrans_.rotate_.x);
        ImGui::Text(str.c_str());

        str = std::to_string(footRootTrans_.rotate_.y);
        ImGui::Text(str.c_str());

        str = std::to_string(footRootTrans_.rotate_.z);
        ImGui::Text(str.c_str());
    }

    //if (ImGui::TreeNode("Object")) {//Objectのツリーをクリックすると


    //    ImGui::TreePop();
    //}

    ImGui::End();
}

float PlayerFoot::DotCos(XMVECTOR vec1, XMVECTOR vec2)
{

    XMVECTOR goalN = XMVector3Normalize(vec1);
    XMVECTOR nowBallPosN = XMVector3Normalize(vec2);
    XMVECTOR dot = XMVector3Dot(goalN, nowBallPosN); //内積を求める
    float dotLen = XMVectorGetX(dot);

    //これで軸回転の角度
    return acos(dotLen);
}
