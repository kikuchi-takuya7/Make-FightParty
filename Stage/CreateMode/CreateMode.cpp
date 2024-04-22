#include "CreateMode.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Global.h"
#include "../../Engine/Debug.h"
#include "../../Engine/Timer.h"
#include "../../Engine/Audio.h"
#include "../../Engine/Text.h"
#include "../../AI/MetaAI.h"
#include "../../AI/NavigationAI.h"
#include "StageSource/OneBrock.h"
#include "StageSource/Cannon.h"
#include "StageSource/Needle.h"
#include "StageSource/AutoCannon.h"


//定数宣言
namespace {
    const int PLAYER_ID = 0;
    const int MAX_CHARACTER_NUM = 4;
    const int MAX_VIEW_OBJECT = 8;
    const float CAM_MOVE_RATE = 0.05f;
    const float OBJ_MOVE_RATE = 0.05f;
    const XMFLOAT3 OBJECT_POS[MAX_VIEW_OBJECT] = { XMFLOAT3(7,22,15),XMFLOAT3(12,22,15) ,XMFLOAT3(17,22,15) ,XMFLOAT3(22,22,15),
                                                   XMFLOAT3(7,18,15) ,XMFLOAT3(12,18,15)  ,XMFLOAT3(17,18,15)  ,XMFLOAT3(22,18,15)};
    //選択されたオブジェクトを表示する位置
    const XMFLOAT3 PLAYER_UI_POS[MAX_CHARACTER_NUM] = { XMFLOAT3(7,15,15),XMFLOAT3(12,15,15) ,XMFLOAT3(17,15,15) ,XMFLOAT3(22,15,15) };

    //カメラの位置
    const XMFLOAT3 SELECT_CAM_POS = XMFLOAT3(15, 20, ZERO);
    const XMFLOAT3 SELECT_CAM_TAR = XMFLOAT3(15, 20, 15);
    const XMFLOAT3 SETTING_CAM_POS = XMFLOAT3(15, 20, -20);
    const XMFLOAT3 SETTING_CAM_TAR = XMFLOAT3(15, ZERO, 15);
    const XMFLOAT3 GAME_CAM_POS = XMFLOAT3(15, 10, -20);
    const XMFLOAT3 GAME_CAM_TAR = XMFLOAT3(15, ZERO, 15);
    const float WAIT_TIME = 1.5f;

    //初期化用
    const int INF = 999999;

    //真ん中にオブジェクトを追加する用の座標。縦二つで一つの座標となってる
    const int STAGE_ADDX[9] = { 14,15,15,15,16,15,15,13,17 };
    const int STAGE_ADDZ[9] = { 15,14,15,16,15,13,17,15,15 };

    //オブジェクト毎の大きさ（xとzで何マス使っているか）
    const XMFLOAT2 OBJECT_SIZE[PATTERN_END] = { XMFLOAT2(1,1),XMFLOAT2(1,1),XMFLOAT2(1,1),XMFLOAT2(1,1) };

    //CreateModeを表示する位置
    std::string TEXT_NAME = "CREATEMODE";
    const XMFLOAT3 TEXT_POS = { 400,30,ZERO };

}

//コンストラクタ
CreateMode::CreateMode(GameObject* parent)
    : GameObject(parent, "CreateMode"), pMetaAI_(nullptr),pStage_(nullptr),pText_(nullptr), pTimer_(Instantiate<Timer>(this)), hCreateSound_{-1,-1}, hBGM_(-1)
{

}

//初期化
void CreateMode::Initialize()
{
    //Mapファイルの中に入ってるfbxファイルの名前を入れる
    std::vector<std::string> fileName;

    //ファイルの中に入ってるすべてのfbxファイルの名前の取得
    fileName = GetFilePath("../Assets/StageResource/", "fbx");

    //fileNameの個数分の要素数を確保
    modelData_.assign(fileName.size(), ModelInfo(-1, PATTERN_END));

    //ファイルの中に入ってたリソースをすべてロードする
    for (int i = ZERO; i < modelData_.size(); i++) {
        std::string dir = "StageResource/";
        modelData_.at(i).hModel = Model::Load(dir + fileName.at(i));
        modelData_.at(i).modelPattern = (FBXPATTERN)i;
        assert(modelData_.at(i).hModel >= ZERO);
    }

    //真ん中に十字型の壁を作る。Astarわかりやすくする為に
    for (int i = 0; i < 9; i++) {
        Transform trans;
        trans.position_.x = STAGE_ADDX[i];
        trans.position_.z = STAGE_ADDZ[i];
        CreateInstance<OneBrock>(modelData_.at(ONEBROCK).hModel, trans, PLAYER_ID, OBJECT_SIZE[ONEBROCK]);
    }

    //MAX_VIEW_OBJECT分の要素を事前に取っておく
    for (int i = ZERO; i < MAX_VIEW_OBJECT; i++) {

        viewObjectList_.emplace_back(-1);
    }

    //事前にプレイヤーの数だけ要素を用意して初期化しておく
    for (int i = ZERO; i < MAX_CHARACTER_NUM; i++) {

        SettingObjectInfo obj;
        settingObject_.emplace_back(obj);
    }

    nowState_ = NONE;
    pText_ = new Text;
    pText_->Initialize();

    pTimer_->SetLimit(WAIT_TIME);


    //音声データのロード
    std::string str[CREATESOUND_NUM] = { "Sellect","Setting"};

    for (int i = ZERO; i < CREATESOUND_NUM; i++) {

        std::string dir = "Audio/SE/";
        std::string extention = ".wav";

        std::string fileName = dir + str[i] + extention;

        hCreateSound_[i] = Audio::Load(fileName, false, 3);
        assert(hCreateSound_[i] >= ZERO);

        Audio::Stop(hCreateSound_[i]);
    }

    hBGM_ = Audio::Load("Audio/CreateModeBGM.wav", true);
    Audio::Stop(hBGM_);
    
}

//更新
void CreateMode::Update()
{

    switch (nowState_)
    {
    case SELECT_MODE:
        SelectUpdate();
        break;
    
    case SETTING_MODE:
        SettingUpdate();
        break;

    case NONE:
    default:
        return;
    }
}


//描画
void CreateMode::Draw()
{

    

    //アップデート内でクリエイトモードとセットモードで切り替える
    switch (nowState_)
    {
    case SELECT_MODE:

        SelectDraw();
        break;

    case SETTING_MODE:

        for (int i = ZERO; i < settingObject_.size(); i++) {

            Model::SetTransform(settingObject_.at(i).hModel, settingObject_.at(i).trans);
            Model::Draw(settingObject_.at(i).hModel);
        }
        break;

    case NONE:
    default:
        return;
    }
}

//開放
void CreateMode::Release()
{
}

//セレクトモードに
void CreateMode::ToSelectMode()
{

    SelectInit();
    nowState_ = SELECT_MODE;

    pNavigationAI_->AllStopDraw();
    pNavigationAI_->AllStopUpdate();
    //pNavigationAI_->AllEraseCollision();
}

//セッティングモードに
void CreateMode::ToSettingMode()
{
    SettingInit();
    nowState_ = SETTING_MODE;
}

//ゲームに戻す
void CreateMode::ToGameMode()
{
    //ここで一旦暗転とかさせたいから移動はすぐでいい
    pMetaAI_->ResetGame();
    nowState_ = NONE;

    Audio::Stop(hBGM_);
}


///////////////////////////////private関数//////////////////////////////////////////


// ディレクトリ内の指定した識別子のファイルネームを獲得する関数
// 引数１：探索したいディレクトリ
// 引数２：探したいファイルの拡張子
// 戻り値：みつけたファイルの名前が入った配列
std::vector<std::string> CreateMode::GetFilePath(const std::string& dir_name, const std::string& extension) noexcept(false)
{
    HANDLE hFind;
    WIN32_FIND_DATA win32fd;//defined at Windwos.h
    std::vector<std::string> file_names;

    //拡張子の設定
    std::string search_name = dir_name + "*." + extension;

    hFind = FindFirstFile(search_name.c_str(), &win32fd);

    if (hFind == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("file not found");
    }

    do {
        if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        }
        else {
            file_names.emplace_back(win32fd.cFileName);
            printf("%s\n", file_names.back().c_str());

        }
    } while (FindNextFile(hFind, &win32fd));

    FindClose(hFind);

    return file_names;
}

//セレクトモード用の初期化
void CreateMode::SelectInit()
{

    rotateObjectValue_ = ZERO;
    selecting_Object_ = INF;
    nextSelectCharacterID_ = MAX_CHARACTER_NUM - 1;

    isObjectMoving_ = false;

    ranking_ = pMetaAI_->GetRanking();

    pTimer_->Reset();

    //前回のセッティングオブジェクトの情報をすべて初期化する
    for (int i = ZERO; i < MAX_CHARACTER_NUM; i++) {
        Transform objPos;
        settingObject_.at(i).hModel = -1;
        settingObject_.at(i).trans = objPos;
        settingObject_.at(i).moved = false;
    }

    //hModelの中からランダムで表示させるオブジェクトを決める
    for (int i = ZERO; i < MAX_VIEW_OBJECT; i++) {
        viewObjectList_.at(i) = rand() % modelData_.size() + modelData_.at(ZERO).hModel;
    }

    Audio::Play(hBGM_);
}

//セッティングモード用の初期化
void CreateMode::SettingInit()
{

    selecting_Object_ = INF;

    //settingObjectの位置をステージの真ん中に設定する
    for (int i = ZERO; i < settingObject_.size(); i++) {

        Transform objPos;
        objPos.position_ = XMFLOAT3(15.0f, ZERO, 15.0f);

        settingObject_.at(i).trans = objPos;
        settingObject_.at(i).moved = false;
    }

    pTimer_->Reset();
}

//セレクトモード時の更新処理
void CreateMode::SelectUpdate()
{
    if (Camera::MoveCam(SELECT_CAM_POS, SELECT_CAM_TAR, CAM_MOVE_RATE) == false) {
        return;
    }

    //オブジェクトがプレイヤー分選択されていなかったら
    if (!IsAllDecidedObject()) {

        //オブジェクトが移動中なら更新しない
        if (isObjectMoving_) {
            return;
        }

        //次にオブジェクトを選ぶ人がAIならAI用の処理をする
        if (ranking_.at(nextSelectCharacterID_) >= startEnemyID_) {
            AISelectObject(ranking_.at(nextSelectCharacterID_));
            nextSelectCharacterID_--;
            isObjectMoving_ = true;
            Audio::Play(hCreateSound_[SELECT]);
            return;
        }

        //マウスからレイを飛ばす用のベクトルを獲得
        XMVECTOR front;
        XMVECTOR back;
        GetCursorRay(front, back);
        //memo.レイキャストするたびにレイのstartが変わってる

        //オブジェクトにカーソルがあってる状態でクリックされたら
        if (IsSelectingOverlapCursor(front, back)) {
            if (Input::IsMouseButtonDown(0)) {
                SelectObject(ranking_.at(nextSelectCharacterID_));
                nextSelectCharacterID_--;
                isObjectMoving_ = true;
                Audio::Play(hCreateSound_[SELECT]);
            }
        }

        return;
    }

    //ここまで来たら一連の流れが終わってるのでタイマースタート
    pTimer_->Start();
    if (pTimer_->IsFinished()) {
        ToSettingMode();
    }
}

//セッティングモード時の更新処理
void CreateMode::SettingUpdate()
{
    if (Camera::MoveCam(SETTING_CAM_POS, SETTING_CAM_TAR, CAM_MOVE_RATE) == false) {
        return; 
    }

    //移動する処理。
    if (settingObject_.at(ZERO).moved) {
        AIMovingObject();
        Audio::Play(hCreateSound_[SETTING]);
    }

    //マウスからレイを飛ばす用のベクトルを獲得
    XMVECTOR front;
    XMVECTOR back;
    GetCursorRay(front, back);

    //マウスカーソルがステージ上に重なっているか
    if (IsStageOverlapCursor(front, back)) {

        //左クリックされて、かつ　すでに設置されたオブジェクトが無いなら
        if (Input::IsMouseButtonDown(ZERO) && IsOverlapPosition() == false) {

            //ひとまずプレイヤーは1人目だけだからZEROで
            CreateObject(settingObject_.at(ZERO).hModel, settingObject_.at(ZERO).trans, ZERO);
            Audio::Play(hCreateSound_[SETTING]);
        }

        //右クリックされたら（IsMouseButtonDownの引数に１を与えたら右クリックされたかどうかになる）
        if (Input::IsMouseButtonDown(1)) {
            settingObject_.at(ZERO).trans.rotate_.y += 90;
            if (settingObject_.at(ZERO).trans.rotate_.y >= 360) {
                settingObject_.at(ZERO).trans.rotate_.y = ZERO;
            }
        }
    }

    //全てのオブジェクトを設置し終わったらゲームに戻る
    {
        bool isAllCreate = true;
        for (int i = ZERO; i < settingObject_.size(); i++) {

            //モデル番号が-1じゃないなら
            if (settingObject_.at(i).hModel != -1) {
                isAllCreate = false;
            }
        }

        //すべて設置され終わったら
        if (isAllCreate) {

            //選択後に1秒待つ
            pTimer_->Start();
            if (pTimer_->IsFinished()) {
                ToGameMode();
            }
        }
    }
}

void CreateMode::SelectDraw()
{
    //空中に浮くオブジェクトを表示する
    for (int i = ZERO; i < viewObjectList_.size(); i++) {

        Transform objTrans;
        objTrans.position_ = OBJECT_POS[i];
        objTrans.rotate_.y = rotateObjectValue_;

        if (i == selecting_Object_) {
            objTrans.scale_ = XMFLOAT3(1.2f, 1.2f, 1.2f);
        }

        Model::SetTransform(viewObjectList_.at(i), objTrans);
        Model::Draw(viewObjectList_.at(i));
    }

    //既に選ばれたオブジェクトを表示する
    for (int i = ZERO; i < settingObject_.size(); i++) {

        //-1なら更新しない。これが無いと勝手に動いちゃう
        if (settingObject_.at(i).hModel == -1) {
            continue;
        }

        //移動し終わってないオブジェクトを滑らかに動かす
        if (settingObject_.at(i).moved == false) {
            if (RateMovePosition(settingObject_.at(i).trans.position_, PLAYER_UI_POS[i], OBJ_MOVE_RATE)) {
                settingObject_.at(i).moved = true;
                isObjectMoving_ = false;
            }
        }



        settingObject_.at(i).trans.rotate_.y = rotateObjectValue_;

        Model::SetTransform(settingObject_.at(i).hModel, settingObject_.at(i).trans);
        Model::Draw(settingObject_.at(i).hModel);
    }

    rotateObjectValue_++;

    //クリエイトモードだと言う事を表示
    pText_->Draw(TEXT_POS.x, TEXT_POS.y, TEXT_NAME.c_str());
}

// オブジェクトを作成する
// 引数１：モデル番号
// 引数２：モデルのtransform
// 引数３：何番目の要素か
void CreateMode::CreateObject(int hModel, Transform trans, int element)
{

    FBXPATTERN pattern = PATTERN_END;

    //モデル番号のFBXPATTERNを探す
    for (int i = 0; i < modelData_.size(); i++) {
        if (modelData_.at(i).hModel == hModel) {
            pattern = modelData_.at(i).modelPattern;
        }
    }

    //それぞれのオブジェクトのインスタンスをクラス変数にvectorで持って、あーだこーだすればなんかもっと楽できそうじゃね？
    switch (pattern)
    {
    case AUTO_CANNON:
        CreateInstance<AutoCannon>(hModel, trans, element, OBJECT_SIZE[pattern]);
        break;

    case CANNON:
        CreateInstance<Cannon>(hModel, trans, element, OBJECT_SIZE[pattern]);
        break;

    case NEEDLE:
        CreateInstance<Needle>(hModel, trans, element, OBJECT_SIZE[pattern]);
        break;

    case ONEBROCK:
        CreateInstance<OneBrock>(hModel, trans, element, OBJECT_SIZE[pattern]);
        break;

    case PATTERN_END:
    default:
        break;
    }

    settingObject_.at(element).moved = true;

    //クリックしたらそのオブジェクトを消す（モデル番号を無くして処理しなくする）
    settingObject_.at(element).hModel = -1;
}

// createObjectListに入れる
// 引数１：追加したいオブジェクトのポインタ
void CreateMode::AddCreateObject(StageSourceBase* object)
{
    //後々のこと考えたらID割り振ったほうがいいか。後で爆弾とか実装する事考えたら
    createObjectList_.emplace_back(object);
}

//マウスカーソルの位置から出るベクトルを参照渡しで取得する
//引数１：前のベクトル
//引数２：後ろのベクトル
void CreateMode::GetCursorRay(XMVECTOR& front, XMVECTOR& back)
{
    float w = (float)(Direct3D::screenWidth_ / 2.0f);
    float h = (float)(Direct3D::screenHeight_ / 2.0f);
    float offsetX = 0;
    float offsetY = 0;
    float minZ = 0;
    float maxZ = 1;

    //ビューポート作成
    XMMATRIX vp =
    {
        w                ,0                ,0           ,0,
        0                ,-h               ,0           ,0,
        0                ,0                ,maxZ - minZ ,0,
        offsetX + w      ,offsetY + h      ,minZ        ,1
    };

    //ビューポートを逆行列に
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    //プロジェクション変換
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    //びゅー変換
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;

    //1,mousePosFrontをベクトルに変換
    front = XMLoadFloat3(&mousePosFront);
    //2. 1にinvVP,invPrj,invViewをかける
    front = XMVector3TransformCoord(front, invVP * invProj * invView);
    //3,mousePosBackをベクトルに変換
    back = XMLoadFloat3(&mousePosBack);
    //4,3にinvVP,invPrj,invVeewをかける
    back = XMVector3TransformCoord(back, invVP * invProj * invView);

}

// AIがオブジェクトを選択する関数
// 引数１：オブジェクトを選択する敵のID
void CreateMode::AISelectObject(int ID)
{

    vector<int> modelList;

    //表示されてるモデルのモデル番号を全て取得する
    for (int i = ZERO; i < viewObjectList_.size(); i++) {

        //-1は判定しない
        if (viewObjectList_.at(i) == -1) {
            continue;
        }

        //既にmodelListに入れてるモデル番号か
        bool duplicate = false;

        //modelListに既に入れてる番号か確認する
        for (int m = ZERO; m < modelList.size(); m++) {
            if (modelList.at(m) == viewObjectList_.at(i)) {
                duplicate = true;
            }
        }

        //重複してないモデル番号なら、modelListに入れる
        if (duplicate == false) {
            modelList.emplace_back(viewObjectList_.at(i));
        }
    }

    //選択するオブジェクトのモデル番号を覚える
    int selectModel = pMetaAI_->SelectObject(modelList);

    //選択されたモデル番号を探して、selectingObjectに入れる
    for (int i = ZERO; i < viewObjectList_.size(); i++) {
        if (viewObjectList_.at(i) == selectModel) {
            selecting_Object_ = i;
            break;
        }

    }

    //選択する
    SelectObject(ID);


}

// settingObjectに選んだオブジェクトの情報を渡す
// 引数：オブジェクトを選んだ人のID
void CreateMode::SelectObject(int ID)
{

    Transform objPos;
    objPos.position_ = OBJECT_POS[selecting_Object_];

    //選択したオブジェクトを入れてく
    settingObject_.at(ID).hModel = viewObjectList_.at(selecting_Object_);
    settingObject_.at(ID).trans = objPos;

    //選択された位置のオブジェクトは消す
    viewObjectList_.at(selecting_Object_) = -1;

}

// カーソルが浮かんでるオブジェクトに合わさっているか
// 引数１：飛ばすレイの前方向ベクトル
// 引数２：後ろ方向のベクトル
bool CreateMode::IsSelectingOverlapCursor(XMVECTOR front, XMVECTOR back)
{
    //カーソルから飛ばしたレイがモデルに当たってるか確認する
    for (int i = ZERO; i < viewObjectList_.size(); i++) {

        //既に選択されたオブジェクト要素の位置なら
        if (viewObjectList_.at(i) == -1) {
            continue;
        }

        RayCastData data;
        XMStoreFloat3(&data.start, front);
        XMStoreFloat3(&data.dir, back - front);

        //モデルのTransformが最後にDrawした位置のままになっているため、一度それぞれの位置に戻す。同じhandleで複数描画してるのが原因
        Transform objTrans;
        objTrans.position_ = OBJECT_POS[i];
        Model::SetTransform(viewObjectList_.at(i), objTrans);

        Model::RayCast(viewObjectList_.at(i), &data);

        //当たってたら即終了　
        if (data.hit) {

            //
            selecting_Object_ = i;
            return true;
        }

        //ありえない値にしとく
        selecting_Object_ = INF;
    }

    return false;
}

// プレイヤー全員がオブジェクトを選び終わったか
// 戻り値：選び終わっていたらtrue
bool CreateMode::IsAllDecidedObject()
{

    //キャラクター全員がオブジェクトを選択し終わっていたら
    for (int i = ZERO; i < settingObject_.size(); i++) {

        //まだ選択されていないオブジェクトがあったら
        if (settingObject_.at(i).hModel == -1) {
            return false;
        }
    }

    return true;
}

// ステージの上にカーソルがあるかどうか
// 引数１：飛ばすレイの前方向ベクトル
// 引数２：後ろ方向のベクトル
// 戻り値：当たっていたらtrue
bool CreateMode::IsStageOverlapCursor(XMVECTOR front, XMVECTOR back)
{

    XMFLOAT3 stageSize = pStage_->GetStageSize();
    int stageHandle = pStage_->GetStageHandle();

    //カーソルから飛ばしたレイがモデルに当たってるか確認する
    for (int z = ZERO; z < stageSize.z; z++) {
        for (int x = ZERO; x < stageSize.x; x++) {

            RayCastData data;
            XMStoreFloat3(&data.start, front);
            XMStoreFloat3(&data.dir, back - front);

            //モデルのTransformが最後にDrawした位置のままになっているため、一度それぞれの位置に戻す
            Transform objTrans;
            objTrans.position_ = XMFLOAT3(x, ZERO, z);
            Model::SetTransform(stageHandle, objTrans);

            Model::RayCast(stageHandle, &data);

            //当たってたら即終了　
            if (data.hit) {

                //回転の情報だけは残しておく
                objTrans.rotate_ = settingObject_.at(ZERO).trans.rotate_;
                settingObject_.at(ZERO).trans = objTrans;
                selecting_Object_ = ZERO;
                return true;
            }
        }
    }

    selecting_Object_ = INF;

    return false;
}

// 設置しようとした場所が既に設置されているオブジェクトと被っているかどうか
// 引数１：当たっていたらtrue
bool CreateMode::IsOverlapPosition()
{
    Transform pos = settingObject_.at(selecting_Object_).trans;

    //既に作成されたオブジェクトと被った位置か確認する
    for (auto it = createObjectList_.begin(); it != createObjectList_.end(); it++) {
        if ((*it)->GetPosition() == pos.position_) {
            return true;
        }
    }

    //今セットしてる途中のオブジェクトと位置が被ってるかどうか
    for (int i = 0; i < settingObject_.size(); i++) {

        //自分なら処理しない
        if (i == selecting_Object_) {
            continue;
        }

        if (settingObject_.at(i).trans == pos) {
            return true;
        }
    }

    return false;
}

// Aiが選んだオブジェクトを動かす位置を決める
void CreateMode::AIMovingObject()
{
    //オブジェクトの位置が被ってないか確認する用
    std::vector<XMFLOAT3> pos;

    //既に作ったオブジェクトの全ての位置を確認する
    for (auto it = createObjectList_.begin(); it != createObjectList_.end(); it++) {

        pos.emplace_back((*it)->GetPosition());
    }

    //AIが選んだオブジェクトを置かせる
    for (int i = startEnemyID_; i < settingObject_.size(); i++) {

        //モデルのTransformの位置を他のオブジェクトと被ってない位置に置けるまで繰り替えす
        while (true) {

            //NavigationAIを経由してどこに置くかを決める
            settingObject_.at(i).trans = pNavigationAI_->MoveSelectObject(i);

            //プレイヤーの位置と被っていたらもう一度
            if (pNavigationAI_->IsOverlapPos(settingObject_.at(i).trans.position_)) {
                srand(time(NULL));
                continue;
            }

            bool isBreak = true;

            //モデルの位置が他と被っていたら、もう一度
            for (int f = 0; f < pos.size(); f++) {
                if (pos.at(f) == settingObject_.at(i).trans.position_) {
                    isBreak = false;
                    srand(time(NULL));
                    continue;
                }
            }

            if (isBreak)
                break;

        }

        CreateObject(settingObject_.at(i).hModel, settingObject_.at(i).trans, i);
    }
}

template <class T>
T* CreateMode::CreateInstance(int hModel, Transform trans, int ID, XMFLOAT2 square)
{
    T* pObject = Instantiate<T>(this);
    AddCreateObject(pObject);
    pStage_->PushStageSource(pObject);

    //回転行列を作り、四角形のオブジェクトのコストの位置を回転させる
    XMMATRIX rotateX, rotateY;
    rotateX = XMMatrixIdentity();
    rotateY = XMMatrixRotationY(XMConvertToRadians(trans.rotate_.y));
    XMMATRIX matRot = rotateX * rotateY;

    //回転行列を適応
    XMVECTOR vec = XMLoadFloat2(&square);
    vec = XMVector2Transform(vec, rotateY);
    XMStoreFloat2(&square, vec);

    //コストをつける
    pStage_->SetStageCost(trans.position_, pObject->GetStageCost(), square.x, square.y);

    //AIが選んだオブジェクトなら真ん中からゆっくり動くように
    if (ID >= startEnemyID_) {
        Transform objTrans;
        objTrans.position_ = XMFLOAT3(15.0f, ZERO, 15.0f);
        objTrans.rotate_ = trans.rotate_;
        pObject->SetMoveLastPos(trans.position_);
        pObject->SetTransform(objTrans);
    }
    else {
        pObject->SetMoveLastPos(trans.position_);
        pObject->SetTransform(trans);
    }

    pObject->Leave();
    pObject->SetHandle(hModel);
    return pObject;
}