#include "CreateMode.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Global.h"
#include "../../Engine/Debug.h"
#include "../../AI/MetaAI.h"
#include "../../AI/NavigationAI.h"
#include "StageSource/OneBrock.h"
#include "StageSource/Cannon.h"
#include "StageSource/Needle.h"


//定数宣言
namespace {
    const int MAX_CHARACTER_NUM = 4;
    const int MAX_VIEW_OBJECT = 8;
    const XMFLOAT3 OBJECT_POS[MAX_VIEW_OBJECT] = { XMFLOAT3(7,22,15),XMFLOAT3(12,22,15) ,XMFLOAT3(17,22,15) ,XMFLOAT3(22,22,15),
                                                   XMFLOAT3(7,18,15) ,XMFLOAT3(12,18,15)  ,XMFLOAT3(17,18,15)  ,XMFLOAT3(22,18,15)};
    //参加するプレイヤーの最大人数分
    const XMFLOAT3 PLAYER_UI_POS[MAX_CHARACTER_NUM] = { XMFLOAT3(7,15,15),XMFLOAT3(12,15,15) ,XMFLOAT3(17,15,15) ,XMFLOAT3(22,15,15) };
    const XMFLOAT3 SELECT_CAM_POS = XMFLOAT3(15, 20, 0);
    const XMFLOAT3 SELECT_CAM_TAR = XMFLOAT3(15, 20, 15);
    const XMFLOAT3 SETTING_CAM_POS = XMFLOAT3(15, 15, -15);
    const XMFLOAT3 SETTING_CAM_TAR = XMFLOAT3(15, 0, 15);
    const XMFLOAT3 GAME_CAM_POS = XMFLOAT3(15, 10, -20);
    const XMFLOAT3 GAME_CAM_TAR = XMFLOAT3(15, 0, 15);
    const int WAIT_FLAME = 120;

    const int INF = 999999;
}

//コンストラクタ
CreateMode::CreateMode(GameObject* parent)
    : GameObject(parent, "CreateMode"), pMetaAI_(nullptr),pStage_(nullptr), selecting_Object_(0),nextSelectCharacterID_(0)
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
        assert(modelData_.at(i).hModel >= 0);
    }

    //MAX_VIEW_OBJECT分の要素を事前に取っておく
    for (int i = ZERO; i < MAX_VIEW_OBJECT; i++) {

        viewObjectList_.emplace_back(-1);
    }

    //事前にプレイヤーの数だけ要素を用意して初期化しておく
    for (int i = ZERO; i < MAX_CHARACTER_NUM; i++) {

        Transform objPos;
        settingObject_.emplace_back(std::make_pair(-1, objPos));
    }



    rotateObjectValue_ = ZERO;
    nowState_ = NONE;
    flame_ = ZERO;
}

void CreateMode::ViewInit()
{

    flame_ = ZERO;
    rotateObjectValue_ = ZERO;
    camMoveRate_ = ZERO;
    selecting_Object_ = INF;
    nextSelectCharacterID_ = MAX_CHARACTER_NUM - 1;

    ranking_ = pMetaAI_->GetRanking();

    
    //前回のセッティングオブジェクトの情報をすべて初期化する
    for (int i = ZERO; i < MAX_CHARACTER_NUM; i++) {
        Transform objPos;
        settingObject_.at(i).first = -1;
        settingObject_.at(i).second = objPos;
    }

    //hModelの中からランダムで表示させるオブジェクトを決める
    for (int i = 0; i < MAX_VIEW_OBJECT; i++) {
        viewObjectList_.at(i) = rand() % modelData_.size() + modelData_.at(ZERO).hModel;
    }


    

}

void CreateMode::SettingInit()
{

    flame_ = ZERO;
    camMoveRate_ = ZERO;
    selecting_Object_ = INF;
   
}

//更新
void CreateMode::Update()
{

    switch (nowState_)
    {
    case SELECT_MODE:

        MoveCam(SELECT_CAM_POS, SELECT_CAM_TAR);

        //オブジェクトがプレイヤー分選択されていなかったら
        if (!IsAllDecidedObject()) {

            //次にオブジェクトを選ぶ人がAIならAI用の処理をする
            if (ranking_.at(nextSelectCharacterID_) >= startEnemyID_) {
                AISelectObject(ranking_.at(nextSelectCharacterID_));
                nextSelectCharacterID_--;
                break;
            }

            //マウスからレイを飛ばす用のベクトルを獲得
            XMVECTOR front;
            XMVECTOR back;
            GetCursorRay(front, back);
            //レイキャストするたびにレイのstartが変わってる？

            //オブジェクトにカーソルがあってる状態でクリックされたら
            if (IsSelectingOverlapCursor(front, back)) {
                if (Input::IsMouseButtonDown(0)) {
                    SelectObject(ranking_.at(nextSelectCharacterID_));
                    nextSelectCharacterID_--;
                }
            }

            break;
        }

        flame_++;
        if (flame_ >= WAIT_FLAME) {
            ToSettingMode();
        }
        
        break;
    
    case SETTING_MODE:

        MoveCam(SETTING_CAM_POS, SETTING_CAM_TAR);

        //移動する処理。
        if (Input::IsKeyDown(DIK_0)) {
            AIMovingObject();
        }

        //マウスからレイを飛ばす用のベクトルを獲得
        XMVECTOR front;
        XMVECTOR back;
        GetCursorRay(front, back);

        if (IsStageOverlapCursor(front, back)) {
            if (Input::IsMouseButtonDown(0) && IsOverlapPosition() == false) {

                //ひとまずプレイヤーは1人目だけだから
                CreateObject(settingObject_.at(ZERO).first, settingObject_.at(ZERO).second, ZERO);
            }
        }

        //全てのオブジェクトを設置し終わったらゲームに戻る
        {
            bool isAllCreate = true;
            for (int i = 0; i < settingObject_.size(); i++) {

                //モデル番号が-1じゃないなら
                if (settingObject_.at(i).first != -1) {
                    isAllCreate = false;
                }
            }

            if (isAllCreate) {
                //ゲームに戻る処理
                ToGameMode();
            }
        }


        break;

    case NONE:
    default:
        return;
    }

    

    
}

//描画
void CreateMode::Draw()
{

    //アップデート内でクリエイトモードとセットモードで切り替えるか

    switch (nowState_)
    {
    case SELECT_MODE:

        //空中に浮くオブジェクトを表示する
        for (int i = 0; i < viewObjectList_.size(); i++) {

            Transform objTrans;
            objTrans.position_ = OBJECT_POS[i];
            objTrans.rotate_.y = rotateObjectValue_;
            
            if (i == selecting_Object_) {
                objTrans.scale_ = XMFLOAT3(1.2f, 1.2f, 1.2f);
            }

            Model::SetTransform(viewObjectList_.at(i), objTrans);
            Model::Draw(viewObjectList_.at(i));
        }

        //vector<int> ranking = pMetaAI_->GetRanking();

        //既に選ばれたオブジェクトを表示する
        for (int i = 0; i < settingObject_.size(); i++) {
            
            //最下位からオブジェクトを選択するため、選んだ人の位置から置く
            Transform objTrans;

            //settingObjectはすでに順位順になってるからそのまま表示しようとして大丈夫なはず
            objTrans.position_ = PLAYER_UI_POS[i];
            objTrans.rotate_.y = rotateObjectValue_;

            Model::SetTransform(settingObject_.at(i).first, objTrans);
            Model::Draw(settingObject_.at(i).first);
        }

        rotateObjectValue_++;
        break;

    case SETTING_MODE:
        
        for (int i = 0; i < settingObject_.size(); i++) {

            Model::SetTransform(settingObject_.at(i).first, settingObject_.at(i).second);
            Model::Draw(settingObject_.at(i).first);
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
    case CANNON:
        CreateInstance<Cannon>(hModel, trans);
        break;

    case NEEDLE:
        CreateInstance<Needle>(hModel, trans);
        break;

    case ONEBROCK:
        CreateInstance<OneBrock>(hModel, trans);
        break;

    case PATTERN_END:
    default:
        break;
    }

    Graph test = pStage_->GetMap();



    //クリックしたらそのオブジェクトを消す（モデル番号を無くして処理しなくする）
    settingObject_.at(element).first = -1;
}



void CreateMode::AddCreateObject(StageSourceBase* object)
{
    //後々のこと考えたらID割り振ったほうがいいか。後で爆弾とか実装する事考えたら
    createObjectList_.emplace_back(object);

}

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

void CreateMode::SelectObject(int ID)
{
  
    Transform objPos;
    objPos.position_ = XMFLOAT3(15.0f, ZERO, 15.0f);

  
    //選択したオブジェクトを入れてく
    settingObject_.at(ID).first = viewObjectList_.at(selecting_Object_);
    settingObject_.at(ID).second = objPos;

    //選択されたオブジェクトは消す
    viewObjectList_.at(selecting_Object_) = -1;

}

bool CreateMode::IsSelectingOverlapCursor(XMVECTOR front,XMVECTOR back)
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

        //モデルのTransformが最後にDrawした位置のままになっているため、一度それぞれの位置に戻す
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

bool CreateMode::IsAllDecidedObject()
{

    //キャラクター全員がオブジェクトを選択し終わっていたら
    for (int i = ZERO; i < settingObject_.size(); i++) {

        //まだ選択されていないオブジェクトがあったら
        if (settingObject_.at(i).first == -1) {
            return false;
        }
    }

    return true;
}

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

                settingObject_.at(ZERO).second = objTrans;
                selecting_Object_ = ZERO;
                return true;
            }
        }
    }

    selecting_Object_ = INF;

    return false;
}

bool CreateMode::IsOverlapPosition()
{

    Transform pos = settingObject_.at(selecting_Object_).second;

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

        if (settingObject_.at(i).second == pos) {
            return true;
        }
    }

    return false;
}

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
            settingObject_.at(i).second = pNavigationAI_->MoveSelectObject(i);
        
            //プレイヤーの位置と被っていたらもう一度
            if (pNavigationAI_->IsOverlapPos(settingObject_.at(i).second.position_)) {
                srand(time(NULL));
                continue;
            }
            
            bool isBreak = true;

            //モデルの位置が他と被っていたら、もう一度
            for (int f = 0; f < pos.size(); f++) {
                if (pos.at(f) == settingObject_.at(i).second.position_) {
                    isBreak = false;
                    srand(time(NULL));
                    break;
                }
            }
            
            if (isBreak)
                break;
        
        }
        
        CreateObject(settingObject_.at(i).first, settingObject_.at(i).second, i);
    }

    
}

void CreateMode::MoveCam(XMFLOAT3 lastPos, XMFLOAT3 lastTar)
{
    //カメラの位置と見る地点を徐々に変える
    XMFLOAT3 nowCamPos = Camera::GetPosition();
    XMFLOAT3 nowCamTar = Camera::GetTarget();

    //レートでぬるぬる動くように
    if (camMoveRate_ < 1.0f) {
        camMoveRate_ += 0.05f;

        // 変な数字で止まらないように
        if (camMoveRate_ > 1.0f)
            camMoveRate_ = 1.0f;

        //ターゲットとポジションが同じだとエラー起きるから注意

        nowCamPos.x = GetRateValue(nowCamPos.x, lastPos.x, camMoveRate_);
        nowCamPos.y = GetRateValue(nowCamPos.y, lastPos.y, camMoveRate_);
        nowCamPos.z = GetRateValue(nowCamPos.z, lastPos.z, camMoveRate_);

        Camera::SetPosition(nowCamPos);

        nowCamTar.x = GetRateValue(nowCamTar.x, lastTar.x, camMoveRate_);
        nowCamTar.y = GetRateValue(nowCamTar.y, lastTar.y, camMoveRate_);
        nowCamTar.z = GetRateValue(nowCamTar.z, lastTar.z, camMoveRate_);

        Camera::SetTarget(nowCamTar);

    }
}

float CreateMode::GetRateValue(float begin, float end, float rate)
{
    return (end - begin) * rate + begin;
}

void CreateMode::ToSelectMode()
{

    ViewInit();
    nowState_ = SELECT_MODE;

    pNavigationAI_->AllStopDraw();
}

void CreateMode::ToSettingMode()
{
    
    SettingInit();
    nowState_ = SETTING_MODE;
}

void CreateMode::ToGameMode()
{

    //ここで一旦暗転とかさせたいから移動はすぐでいいや
    pMetaAI_->ResetGame();
    nowState_ = NONE;

    //pNavigationAI_->AllResetStatus();
}
