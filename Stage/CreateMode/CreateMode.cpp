#include "CreateMode.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Global.h"
#include "StageSource/TestWall.h"
#include "StageSource/TestFloor.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "../../Engine/Debug.h"


namespace {
    const int PLAYER_NUM = 1;
    const int MAX_VIEW_OBJECT = 8;
    const XMFLOAT3 OBJECT_POS[MAX_VIEW_OBJECT] = { XMFLOAT3(10,22,15),XMFLOAT3(15,22,15) ,XMFLOAT3(20,22,15) ,XMFLOAT3(25,22,15),
                                                   XMFLOAT3(10,18,15) ,XMFLOAT3(15,18,15)  ,XMFLOAT3(20,18,15)  ,XMFLOAT3(25,18,15)};
}

//コンストラクタ
CreateMode::CreateMode()
    : selecting_Object(PATTERN_END), nextObjectId_(0)
{


}

//初期化
void CreateMode::Initialize()
{
    //ファイルの中に入ってるすべてのfbxファイルの名前の取得
    fileName_ = GetFilePath("../Assets/StageResource/", "fbx");

    //fileNameの個数分の要素数を確保
    modelData.assign(fileName_.size(), ModelInfo(-1, PATTERN_END));

    //ファイルの中に入ってたリソースをすべてロードする
    for (int i = 0; i < modelData.size(); i++) {
        std::string dir = "StageResource/";
        modelData.at(i).hModel = Model::Load(dir + fileName_.at(i));
        assert(modelData.at(i).hModel >= 0);
    }

    

    isUpdate_ = false;
}

void CreateMode::ViewInit()
{
    viewObjectList_.clear();


    for (int i = 0; i < MAX_VIEW_OBJECT; i++) {

        //hModelの中からランダムで表示させるオブジェクトを決める
        viewObjectList_.push_back(rand() % modelData.size() + modelData.at(0).hModel);
        //viewObjectList_.push_back(std::make_pair(modelData.at(i), i));
    }
}

//更新
void CreateMode::Update()
{

    if (!isUpdate_) {
        return;
    }

    //カーソルがモデルに合わさってるなら
    if (IsOverlapCursor()) {

        //ここでモデルを光らせたい
        Debug::Log("hit",true);

        if (Input::IsMouseButtonDown(0))
        {
            SelectObject();
        }
    }
    else {
        Debug::Log("nohit", true);
    }
    
}

//描画
void CreateMode::Draw()
{
    if (!isUpdate_) {
        return;
    }

    

    for (int i = 0; i < viewObjectList_.size(); i++) {

        Transform objPos;
        objPos.position_ = OBJECT_POS[i];
        
        if (i == selecting_Object) {
            objPos.scale_ = XMFLOAT3(1.2f, 1.2f, 1.2f);
        }

        Model::SetTransform(viewObjectList_.at(i), objPos);
        Model::Draw(viewObjectList_.at(i));
    }
}

//開放
void CreateMode::Release()
{
}

GameObject* CreateMode::CreateObject()
{

    //forで回してFBXPATTERNとfilenameの要素の順番が一致したところでオブジェクトを作るのも想定したけどobjectNameとかがめんどくさくなるから無し
    //対応したenum型の数字になったらそのオブジェクトを作成してcreateObjectにプッシュバックする

    //それぞれのオブジェクトのインスタンスをクラス変数にvectorで持って、あーだこーだすればなんかもっと楽できそうじゃね？
    switch (selecting_Object)
    {
    case TESTFLOOR: {
        TestFloor* pObject = CreateInstance<TestFloor>();
        return pObject;
        break;
    }
    case PATTERN_END: {
        break;
    }
    default:
        break;
    }

    return NULL;   // 指定のクラスが無い
}

void CreateMode::SelectObject()
{

    //全てのhModelを探索する
    for (int i = 0; i < modelData.size(); i++) {

        if (viewObjectList_.at(selecting_Object) == modelData.at(i).hModel) {


            //セッティングオブジェクトに情報を与えて要素を消す
            
        }
    }

}

void CreateMode::AddCreateObject(GameObject* object)
{
    //CheckDeleteObject();
    createObjectList_.push_back(object);
    nextObjectId_++;
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
            file_names.push_back(win32fd.cFileName);
            printf("%s\n", file_names.back().c_str());

        }
    } while (FindNextFile(hFind, &win32fd));

    FindClose(hFind);

    return file_names;
}

void CreateMode::MoveCamPos()
{
    Camera::SetPosition(XMFLOAT3(15, 20, 0));
    Camera::SetTarget(XMFLOAT3(15, 20, 15));
}

bool CreateMode::IsOverlapCursor()
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
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    //2. 1にinvVP,invPrj,invViewをかける
    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
    //3,mousePosBackをベクトルに変換
    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    //4,3にinvVP,invPrj,invVeewをかける
    vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);
    //5,2から4に向かってレイを打つ（とりあえず）

    int changeX = 0;
    int	changeZ = 0;
    float minDist = 9999;

    //レイキャストするたびにレイのstartが変わってる？
    /*RayCastData data;
    XMStoreFloat3(&data.start, vMouseFront);
    XMStoreFloat3(&data.dir, vMouseBack - vMouseFront);*/

    //カーソルから飛ばしたレイがモデルに当たってるか確認する
    for (int i = 0; i < viewObjectList_.size(); i++) {
        RayCastData data;
        XMStoreFloat3(&data.start, vMouseFront);
        XMStoreFloat3(&data.dir, vMouseBack - vMouseFront);

        //モデルのTransformが最後にDrawした位置のままになっているため、一度それぞれの位置に戻す
        Transform objPos;
        objPos.position_ = OBJECT_POS[i];
        Model::SetTransform(viewObjectList_.at(i), objPos);

        Model::RayCast(viewObjectList_.at(i), &data);

        //当たってたら即終了　
        if (data.hit) {

            //
            selecting_Object = i;
            return true;
        }

        //ありえない値にしとく
        selecting_Object = 99999;
    }
    
    return false;
    
    
}
