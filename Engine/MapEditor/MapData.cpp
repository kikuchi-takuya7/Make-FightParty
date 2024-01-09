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


//コンストラクタ
MapData::MapData(GameObject* parent)
	: GameObject(parent, "MapData"),selecting_object(PATTERN_END),isSave_(false),nextObjectId_(0),isNewSave_(false),isLoad_(false)
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
    
    //セーブマネージャ作成
    pSaveManager_ = new SaveManager;
    pSaveManager_->OpenFile();
    pSaveManager_->Load();

    CheckDeleteObject();
    nextObjectId_ = MaxObjectId();
    nextObjectId_++;
}

//更新
void MapData::Update()
{
    //毎回チェックしないとデリートしたタイミングでエラー出る。多分RootObjectのUpdateで消されたかどうか確認してるから
    CheckDeleteObject();



    //float w = (float)(Direct3D::screenWidth_ / 2.0f);
    //float h = (float)(Direct3D::screenHeight_ / 2.0f);
    //float offsetX = 0;
    //float offsetY = 0;
    //float minZ = 0;
    //float maxZ = 1;

    ////ビューポート作成
    //XMMATRIX vp =
    //{
    //    w                ,0                ,0           ,0,
    //    0                ,-h               ,0           ,0,
    //    0                ,0                ,maxZ - minZ ,0,
    //    offsetX + w      ,offsetY + h      ,minZ        ,1
    //};

    ////ビューポートを逆行列に
    //XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    ////プロジェクション変換
    //XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    ////びゅー変換
    //XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

    //XMFLOAT3 mousePosFront = Input::GetMousePosition();
    //mousePosFront.z = 0.0;
    //XMFLOAT3 mousePosBack = Input::GetMousePosition();
    //mousePosBack.z = 1.0f;

    ////1,mousePosFrontをベクトルに変換
    //XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    ////2. 1にinvVP,invPrj,invViewをかける
    //vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
    ////3,mousePosBackをベクトルに変換
    //XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    ////4,3にinvVP,invPrj,invVeewをかける
    //vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);
    ////5,2から4に向かってレイを打つ（とりあえず）

    //int changeX = 0;
    //int	changeZ = 0;
    //float minDist = 9999;


    //RayCastData data;
    //XMStoreFloat3(&data.start, vMouseFront);
    //XMStoreFloat3(&data.dir, vMouseBack - vMouseFront);

    //Model::RayCast(hModel_[0], &data);

    //if (data.hit) {
    //    data.hit = false;

    //}

    //Transform objPos;
    //objPos.position_.y = 1.0f;

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

    if (selecting_object == PATTERN_END)
        return;

    Transform objPos;
    //objPos.position_.y = 1.0f;
    Model::SetTransform(hModel_.at(selecting_object), objPos);
    Model::Draw(hModel_.at(selecting_object));
}

//開放
void MapData::Release()
{
    SAFE_DELETE(pSaveManager_);
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

        //新規作成
        if (ImGui::Button("CreateNewFile")) {
            isNewSave_ = true;
        }

        //ロード
        if (ImGui::Button("Load")) {
            isLoad_ = true;
        }
        
        //セーブ
        if (ImGui::Button("Save")) {
            isSave_ = true;
        }

        //新規作成
        if (isNewSave_) {
            ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Once);
            ImGui::Begin("CreateNewFile?", &isNewSave_);
            if (ImGui::Button("Create")) {
                //CheckDeleteObject();
                AllDeleteCreateObject();
                pSaveManager_->NewCreateFile();
                pSaveManager_->Save(createObjectList_);
                isNewSave_ = false;
            }
            ImGui::End();
        }

        //ロード
        if (isLoad_) {
            ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEverこれを付けると初めて実行したときだけこの大きさに設定されて。それ以降はimgui.iniに保存される
            ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Once);
            ImGui::Begin("LoadOk?", &isSave_);
            if (ImGui::Button("Load")) {
                AllDeleteCreateObject();
                pSaveManager_->OpenFile();
                pSaveManager_->Load();
                isLoad_ = false;
            }
            ImGui::End();
        }

        //Saveが押されたらここが表示される
        if (isSave_) {
            ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEverこれを付けると初めて実行したときだけこの大きさに設定されて。それ以降はimgui.iniに保存される
            ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Once);
            ImGui::Begin("SaveOk?",&isSave_);
            if (ImGui::Button("Save")) {
                //CheckDeleteObject();
                pSaveManager_->Save(createObjectList_);
                isSave_ = false;
            }
            ImGui::End();
        }

        
    }


    //ここに各オブジェクトのTransformとかまとめて処理したかったけど、listがGameObject型だからそれぞれのisDelete_とアクセスできないし一旦やめた
    if (ImGui::CollapsingHeader("ObjectData"))
    {
        if (ImGui::TreeNode("Data")) {//Objectのツリーをクリックすると

            //それぞれのオブジェクト毎のvectorインスタンス持っておけば二重for文でわざわざGameObject型に関数作らなくても行けるんじゃね？
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

    //それぞれのオブジェクトのインスタンスをクラス変数にvectorで持って、あーだこーだすればなんかもっと楽できそうじゃね？
    switch (selecting_object)
    {
    case TESTFLOOR: {
        TestFloor* pObject = CreateInstance<TestFloor>();
        return pObject;
        break;
    }
    case TESTWALL: {
        TestWall* pObject = CreateInstance<TestWall>();
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

void MapData::AllDeleteCreateObject()
{
    for (auto itr = createObjectList_.begin(); itr != createObjectList_.end();itr++) {
        (*itr)->KillMe();
    }

    createObjectList_.clear();
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

void MapData::BackUpSave()
{

}
