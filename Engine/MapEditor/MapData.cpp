#include "MapData.h"
#include "../Model.h"
#include "../Input.h"
#include "../Camera.h"
#include "../SaveManager/SaveManager.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "../Global.h"
#include "MapSource/TestWall.h"
#include "MapSource/TestFloor.h"
#include "MapSource/Room1.h"


//コンストラクタ
MapData::MapData(GameObject* parent)
	: GameObject(parent, "MapData"),selecting_object(PATTERN_END),isSave_(false),nextObjectId_(0)
{

    
}

//初期化
void MapData::Initialize()
{
    //ファイルの中に入ってるすべてのfbxファイルの名前の取得
    fileName_ = get_file_path_in_dir("./Map/", "fbx");
    
    //fileNameの個数分の要素数を確保
    hModel_.assign(fileName_.size(),-1);

    for (int i = 0; i < hModel_.size(); i++) {
        std::string dir = "Map/";
        hModel_.at(i) = Model::Load(dir + fileName_.at(i));
        assert(hModel_.at(i) >= 0);
    }
    
    SaveManager* pSaveManager = Instantiate<SaveManager>(this);
    pSaveManager->Load("SaveFile/SaveTest.json");

    CheckDeleteObject();
    nextObjectId_ = MaxObjectId();
    nextObjectId_++;
}

//更新
void MapData::Update()
{
    
    CheckDeleteObject();

    //ちゃんとセーブされるのにロードできない。なんでやねん
    //Model::AllRelease()を使えば行けそうっていうメモ

    //if (Input::IsMouseButtonDown(0)) {

    //    float w = (float)(Direct3D::screenWidth_ / 2.0f);
    //    float h = (float)(Direct3D::screenHeight_ / 2.0f);
    //    float offsetX = 0;
    //    float offsetY = 0;
    //    float minZ = 0;
    //    float maxZ = 1;

    //    //ビューポート作成
    //    XMMATRIX vp =
    //    {
    //        w                ,0                ,0           ,0,
    //        0                ,-h               ,0           ,0,
    //        0                ,0                ,maxZ - minZ ,0,
    //        offsetX + w      ,offsetY + h      ,minZ        ,1
    //    };

    //    //ビューポートを逆行列に
    //    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    //    //プロジェクション変換
    //    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    //    //びゅー変換
    //    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

    //    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    //    mousePosFront.z = 0.0;
    //    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    //    mousePosBack.z = 1.0f;

    //    //1,mousePosFrontをベクトルに変換
    //    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    //    //2. 1にinvVP,invPrj,invViewをかける
    //    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
    //    //3,mousePosBackをベクトルに変換
    //    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    //    //4,3にinvVP,invPrj,invVeewをかける
    //    vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);
    //    //5,2から4に向かってレイを打つ（とりあえず）

    //    int changeX = 0;
    //    int	changeZ = 0;
    //    float minDist = 9999;
    //    for (int x = 0; x < 15; x++) {
    //        
    //        RayCastData data;
    //        XMStoreFloat3(&data.start, vMouseFront);
    //        XMStoreFloat3(&data.dir, vMouseBack - vMouseFront);
    //        Transform trans;
    //        trans.position_.x = x;
    //        trans.position_.y = 0;
    //        trans.position_.z = z;
    //        Model::SetTransform(hModel_[0], trans);

    //        Model::RayCast(hModel_[0], &data);

    //        if (data.hit) {
    //            if (data.dist > minDist)
    //                continue;
    //            data.hit = false;
    //            continue;
    //        }
    //    }

    //    table_[changeX][changeZ].height++;
    //}

    //左クリックされた
    if (Input::IsMouseButtonDown(0))
    {
        //何らかの処理
        CreateObject();
    }
}

//描画
void MapData::Draw()
{
   

    Transform objPos;
    objPos.position_.y = 1.0f;

    if (selecting_object == PATTERN_END)
        return;

    //マウスの位置にオブジェクトを仮で表示したい
    Model::SetTransform(hModel_[selecting_object], objPos);
    Model::Draw(hModel_[selecting_object]);

}

//開放
void MapData::Release()
{
}

void MapData::Imgui_Window()
{
    ImGui::Begin("DataWindow");
    if (ImGui::CollapsingHeader("MapEditor"))
    {

        if (ImGui::TreeNode("Object")){//Objectのツリーをクリックすると

            int tmp = selecting_object;
            for (int i = 0; i < fileName_.size(); i++) { //fileName分だけその名前のラジオボタンが出るように。iとselecting_objectが一致したらそこだけ選択できる
                ImGui::RadioButton(fileName_.at(i).c_str(), &tmp, i);
            }

            ImGui::RadioButton("stay", &tmp, PATTERN_END);//何も選択していない状態にしたい時用
            selecting_object = static_cast<FBXPATTERN>(tmp);//intからenumに
            ImGui::TreePop();
        }

        
        if (ImGui::Button("Save")) {
            isSave_ = true;
        }

        //Saveが押されたらここが表示される
        if (isSave_) {
            ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEverこれを付けると初めて実行したときだけこの大きさに設定されて。それ以降はimgui.iniに保存される
            ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Once);
            ImGui::Begin("SaveOk?",&isSave_);
            if (ImGui::Button("Save")) {
                //CheckDeleteObject();
                SaveManager* pSaveManager = Instantiate<SaveManager>(this);
                pSaveManager->Save("SaveTest", createObjectList_);
                isSave_ = false;
            }
            ImGui::End();
        }
    }


    //ここに各オブジェクトのTransformとかまとめて処理したかったけど、listがGameObject型だからそれぞれのisDelete_とアクセスできないし一旦やめた
    if (ImGui::CollapsingHeader("ObjectData"))
    {
        if (ImGui::TreeNode("Data")) {//Objectのツリーをクリックすると
            for (auto itr = createObjectList_.begin(); itr != createObjectList_.end(); itr++) {
            
            

                (*itr)->Imgui_Data_Edit();
                
            }

            ImGui::TreePop();
        }
    }
    ImGui::End();
}

GameObject* MapData::CreateObject()
{

    //forで回してFBXPATTERNとfilenameの要素の順番が一致したところでオブジェクトを作るのも想定したけどobjectNameとかがめんどくさくなるから無し
    //対応したenum型の数字になったらそのオブジェクトを作成してcreateObjectにプッシュバックする
    switch (selecting_object)
    {
    case ROOM_1: {
        Room1* pRoom = Instantiate<Room1>(this);
        AddCreateObject(pRoom);
        pRoom->SetObjectID(nextObjectId_); //作ったオブジェクト順に識別するためのIDを付ける
        return pRoom;
        break;
    }
    case TESTFLOOR: {
        TestFloor* pTestFloor = Instantiate<TestFloor>(this);
        AddCreateObject(pTestFloor);
        pTestFloor->SetObjectID(nextObjectId_); //作ったオブジェクト順に識別するためのIDを付ける
        return pTestFloor;
        break;
    }
    case TESTWALL: {
        TestWall* pTestWall = Instantiate<TestWall>(this);
        AddCreateObject(pTestWall);
        pTestWall->SetObjectID(nextObjectId_); //作ったオブジェクト順に識別するためのIDを付ける
        return pTestWall;
    }
    case PATTERN_END: {
        break;
    }
    default:
        break;
    }

    return NULL;   // 指定のクラスが無い
}

void MapData::AddCreateObject(GameObject* object)
{
    //CheckDeleteObject();
    createObjectList_.push_back(object);
    nextObjectId_++;
}

std::vector<std::string> MapData::get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false)
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

void MapData::CheckDeleteObject()
{

    for (auto itr = createObjectList_.begin(); itr != createObjectList_.end();) {
        if ((*itr)->IsDead()) {
            itr = createObjectList_.erase(itr);
        }
        else {
            itr++;
        }
    }

}

void MapData::ChengeUp(GameObject* pTarget)
{

    auto itr = createObjectList_.begin();

    //既に先頭なら
    if ((*itr) == pTarget)
        return;

    for (itr ; itr != createObjectList_.end(); itr++) {
        if ((*itr) == pTarget) {
            createObjectList_.splice(std::next(itr, -1), createObjectList_, itr);
            break;
        }
    }

    //isUp_ = true;

    /*SaveManager* pSaveManager = Instantiate<SaveManager>(this);
    pSaveManager->Save("SaveFile/SaveTest.json", createObjectList_);*/
    /*KillAllChildren();
    createObjectList_.clear();
    SaveManager* pSaveManager2 = Instantiate<SaveManager>(this);
    pSaveManager2->Load("SaveFile/SaveTest.json");*/

    //この関数を子から呼び出してるのにKillAllChildrenでぶっ殺してるからエラーになる
    //bool型変数を作ってtrueならこっちのUpDate中に上の処理をする奴も考えたけどファイルのロードが上手くできてなかった。プロジェクト実行中はファイル書き換えても実行中には新しいデータをロードできない？
}

void MapData::ChengeDown(GameObject* pTarget)
{

    auto itr = createObjectList_.end();

    itr--;
    //既に一番後ろなら
    if ((*itr) == pTarget)
        return;

    while(itr!=createObjectList_.begin()) {

        itr--;

        if ((*itr) == pTarget) {
            createObjectList_.splice(std::next(itr, 2), createObjectList_, itr);
            break;
        }
    }

}

int MapData::MaxObjectId()
{
    int ID = 0;
    for (auto itr = createObjectList_.begin(); itr != createObjectList_.end(); itr++) {
        int tmp = (*itr)->GetObjectID();
        if (ID < tmp) {
            ID = tmp;
        }
    }

    return ID;
}
