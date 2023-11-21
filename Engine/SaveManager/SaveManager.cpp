#include "SaveManager.h"
#include <iostream>
#include "../json-develop/include/nlohmann/json.hpp"
#include "../MapEditor/MapSource/TestWall.h"
#include "../MapEditor/MapSource/TestFloor.h"
#include "../MapEditor/MapSource/Room1.h"
#include "../MapEditor/MapData.h"
#include <fstream>

using json = nlohmann::json;
using string = std::string;


//コンストラクタ
SaveManager::SaveManager(GameObject* parent)
    :GameObject(parent, "SaveManager"),fileName_{"新規ファイル.json"}
{
}

//デストラクタ
SaveManager::~SaveManager()
{
}

//初期化
void SaveManager::Initialize()
{
    
}

//更新
void SaveManager::Update()
{

}

void SaveManager::Draw()
{
}

//開放
void SaveManager::Release()
{
    //m_SaveObjctList_.clear();
}

void SaveManager::Save(std::list<GameObject*> list)
{

    //ファイルを開く
    std::ofstream writing_file;
    writing_file.open(fileName_, std::ios::out);

    for (auto itr = list.begin(); itr != list.end();itr++) {


        //それぞれのTransformを検索して入れる
        XMFLOAT3 pos = (*itr)->GetPosition();
        XMFLOAT3 rot = (*itr)->GetRotate();
        XMFLOAT3 sca = (*itr)->GetScale();

        float arr[9] = { pos.x,pos.y,pos.z,
                         rot.x,rot.y,rot.z,
                         sca.x,sca.y,sca.z };

        //string型で保存しないとロードの時少しめんどくさくなる
        int ID = (*itr)->GetObjectID();
        std::string s = std::to_string(ID);

        json m_json = {
                {"objectName",(*itr)->GetObjectName()},
                {"Transform",arr},
                {"objectID",s} 
        };

        //一行ずつ入力
        writing_file << m_json.dump() << std::endl;
    }
        
    writing_file.close();
}

void SaveManager::AddSaveObj(GameObject* obj)
{
    //m_SaveObjctList_.push_back(obj);
}

void SaveManager::Load()
{

    //読み込みに失敗した場合はエラーを表示する
    std::ifstream ifs(fileName_);

    //eofが上手く使えないからファイルの行数分だけ先にいただく
    int fileLine = 0;

    //読み込めなかったら返す
    if (!ifs)
        return;

    while (true)
    {
        string line;
        // 1行読み取る。
        getline(ifs, line);
        fileLine++;

        // ファイルが終端まで来たらbreak 
        if (ifs.eof())
            break;
    }

    //一回ファイル読み込みを回したから一旦閉じる
    ifs.close();

    //入力の時に改行してるから一つ減らす
    fileLine--;

    ifs.open(fileName_, std::ios::in);

    //ファイルのラインの数だけ回す
    for (int i = 0; i < fileLine;i++) {
        json m_json;
        ifs >> m_json;

        //要素が空ならやめる
        if (m_json["objectName"].empty() || m_json["Transform"].empty() || m_json["objectID"].empty())
            continue;

        GameObject* object = CreateObj(m_json["objectName"]);
            
        //読み込んだデータをオブジェクトに入れる
        Transform objTrans;
        objTrans.position_.x = m_json["Transform"].at(0);
        objTrans.position_.y = m_json["Transform"].at(1);
        objTrans.position_.z = m_json["Transform"].at(2);
        objTrans.rotate_.x = m_json["Transform"].at(3);
        objTrans.rotate_.y = m_json["Transform"].at(4);
        objTrans.rotate_.z = m_json["Transform"].at(5);
        objTrans.scale_.x = m_json["Transform"].at(6);
        objTrans.scale_.y = m_json["Transform"].at(7);
        objTrans.scale_.z = m_json["Transform"].at(8);

        object->SetTransform(objTrans);

        //Stringをintに変えて保存
        std::string tmpString = m_json["objectID"];

        object->SetObjectID(std::stoi(tmpString));

    }

    ifs.close();
}

GameObject* SaveManager::CreateObj(std::string className)
{
    //ロードしたobjectNameに対応するオブジェクトを作成し、SaveManagerを呼び出したのがMapDataならcreateObjectに入れる
    if (className == "TestWall") {
        TestWall* object = CreateObject<TestWall>();
        return object;
    }
    else if (className == "TestFloor") {
        TestFloor* object = CreateObject<TestFloor>();
        return object;
    }
    else if (className == "Room1") {
        Room1* object = CreateObject<Room1>();
        return object;
    }

    return NULL;   // 指定のクラスが無い
}

void SaveManager::OpenFile()
{

    //「ファイルを保存」ダイアログの設定
    OPENFILENAME ofn;                         	//名前をつけて保存ダイアログの設定用構造体
    ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
    ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
    ofn.lpstrFilter = TEXT("マップデータ(*.json)\0*.json\0")        //─┬ファイルの種類
        TEXT("すべてのファイル(*.*)\0*.*\0\0");     //─┘
    ofn.lpstrFile = fileName_;               	//ファイル名
    ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
    ofn.Flags = OFN_FILEMUSTEXIST;   		//フラグ（同名ファイルが存在したら上書き確認）
    ofn.lpstrDefExt = "json";                  	//デフォルト拡張子

    //「ファイルを保存」ダイアログ
    BOOL selFile;
    selFile = GetOpenFileName(&ofn);

    //キャンセルしたら中断
    if (selFile == FALSE) return;

}

void SaveManager::NewCreateFile()
{
    //「ファイルを保存」ダイアログの設定
    OPENFILENAME ofn;                         	//名前をつけて保存ダイアログの設定用構造体
    ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
    ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
    ofn.lpstrFilter = TEXT("マップデータ(*.json)\0*.json\0")        //─┬ファイルの種類
        TEXT("すべてのファイル(*.*)\0*.*\0\0");     //─┘
    ofn.lpstrFile = fileName_;               	//ファイル名
    ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
    ofn.Flags = OFN_OVERWRITEPROMPT;   		//フラグ（同名ファイルが存在したら上書き確認）
    ofn.lpstrDefExt = "json";                  	//デフォルト拡張子

    //「ファイルを保存」ダイアログ
    BOOL selFile;
    selFile = GetSaveFileName(&ofn);

    //キャンセルしたら中断
    if (selFile == FALSE) return;
}

