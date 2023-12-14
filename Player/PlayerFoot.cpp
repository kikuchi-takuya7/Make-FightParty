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
    prevBallRot_ = goalValue_;

    prevCosY_ = 0;
    prevCosZ_ = 0;

    

    //腕の長さ分だけ平行移動させる(今回はボールだから単位円の中)
    XMMATRIX moveLen = XMMatrixTranslation(1, 0, 0);

    XMMATRIX moveMatrix = moveLen;

    ballVec_ = XMVector3TransformCoord(ballVec_, moveMatrix);

    XMStoreFloat3(&ballTrans_.position_, ballVec_);
    
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
    XMVECTOR prevBallVec = ballVec_;

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
    XMVECTOR goalTmp = prevBallVec;
    goalTmp = XMVectorSetY(prevBallVec, 0);

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
    goalTmp = prevBallVec;
    goalTmp = XMVectorSetZ(prevBallVec, 0);
    //goalTmp = XMVectorSetY(prevBallVec, tmpFloat.y);

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

    //回転した差分だけ回転させる
    XMFLOAT3 tmp = Transform::Float3Sub(goalValue_, prevBallRot_);

    XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(tmp.x));
    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(tmp.y));
    XMMATRIX rotZ = XMMatrixRotationZ(XMConvertToRadians(tmp.z));

    //ワールド逆行列でローカル返還座標にする
    XMMATRIX worldMat = GetWorldMatrix();
    worldMat = XMMatrixInverse(nullptr, worldMat);

    XMMATRIX parentMat = transform_.matScale_ * transform_.matRotate_ * transform_.matTranslate_;
    parentMat = XMMatrixInverse(nullptr, parentMat);

    XMMATRIX rotMatrix = rotY * rotZ * rotX;//ロールピッチヨー回転の順番にしてみる

    //2軸で回転させるとワールド座標の軸で回転してしまうためローカル座標に変換してるつもりなんだけどなぁ
    ballVec_ = XMVector3TransformCoord(ballVec_, rotMatrix * worldMat);

    //prevを更新
    prevBallRot_ = goalValue_;

    //半径１からずれないように
    ballVec_ = XMVector3Normalize(ballVec_);

    //ボールの表示用トランスフォームに入れる
    XMStoreFloat3(&ballTrans_.position_, ballVec_);

    ///////////////ボール（目標位置）を回転させてから根元回転/////////////

    //現在のベクトル（先端）
    //先端の位置のベクトル
    XMVECTOR nowBallPosXZ = prevBallVec;
    nowBallPosXZ = XMVectorSetY(nowBallPosXZ, 0);
    
    //Y軸回転させるための変数
    XMVECTOR goalTmpXZ = ballVec_;
    goalTmpXZ = XMVectorSetY(goalTmpXZ, 0);

    //これでy軸回転の角度
    float acosY = DotCos(nowBallPosXZ, goalTmpXZ);

    //根本から回すから根元を回転させる
    acosY = -acosY;////////////////////////なぜかy軸の回転が逆だったからここマイナスにしてる。多分acosYの仕様？

    //acosYがマイナスになるように
    if (ballTrans_.position_.z <= 0) {
        acosY *= -1;
    }

    //根本から回すから根元を回転させる
    footRootTrans_.rotate_.y += prevCosY_ - acosY;

    prevCosY_ = acosY;

    ///////////////こっから縦軸回転///////////////////////
    
    ////y軸回転させてからz軸回転
    //XMVECTOR nowBallPosXY = ballVec_;
    //nowBallPosXY = XMVectorSetZ(nowBallPosXY, 0);

    ////z軸回転させるための変数
    //XMVECTOR goalTmpXY = prevBallVec;
    //goalTmpXY = XMVectorSetZ(goalTmpXY, 0);
    ////goalTmpXY = XMVectorSetY(prevBallVec, tmpFloat.y);

    ////これでz軸回転の角度
    //float acosZ = DotCos(nowBallPosXY, goalTmpXY);

    //if (ballTrans_.position_.y <= 0) {
    //    acosZ *= -1;
    //}

    //prevCosZ_ += acosZ;

    ////根本から回すから根元を回転させる
    //footRootTrans_.rotate_.z += acosZ;

    ////ボールの位置に足の先端の座標を回転出来たら更新と思ったけど足の先端は長さ4の位置にないとだから意味ないね
    //footTipTrans_.position_ = ballTrans_.position_;

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

        Setting_Float3(goalValue_, 0, 360, "prevBallVec");
        //ImGui::SliderFloat("rotate_x", &footRootTrans_.rotate_.x, 0, 360);
        
        ImGui::Text("footRootTrans.rotate");
        std::string str = std::to_string(footRootTrans_.rotate_.x);
        ImGui::Text(str.c_str());

        str = std::to_string(footRootTrans_.rotate_.y);
        ImGui::Text(str.c_str());

        str = std::to_string(footRootTrans_.rotate_.z);
        ImGui::Text(str.c_str());

        ImGui::Text("ballTrans.pos");
        str = std::to_string(ballTrans_.position_.x);
        ImGui::Text(str.c_str());

        str = std::to_string(ballTrans_.position_.y);
        ImGui::Text(str.c_str());

        str = std::to_string(ballTrans_.position_.z);
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
