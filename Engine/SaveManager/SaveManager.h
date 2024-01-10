#pragma once
#include "../GameObject.h"
#include "../../MapEditor/MapEditor.h"


//◆◆◆を管理するクラス
class SaveManager
{

public:

    //コンストラクタ
    SaveManager();

    //デストラクタ
    ~SaveManager();

    void Save(std::list<GameObject*> list);

    void AddSaveObj(GameObject* obj);

    void Load();

    GameObject* CreateObj(std::string className);     // オブジェクト生成

    //ファイルを開いてSaveManagerに保存する
    void OpenFile();

    //新しくファイルを作る
    void NewCreateFile();

private:

    char fileName_[MAX_PATH];

    /// <summary>
    ///　オブジェクトを作る。親がMapEditorだった場合はmapEditorの中のlistに入れる
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="pParent">呼び出したクラスの親クラス</param>
    /// <returns>作ったオブジェクト</returns>
    template <class T>
    T* CreateObject(GameObject* pParent)
    {
        /*T* object = Instantiate<T>(pParent);

        if (pParent->GetObjectName() == "MapEditor")
            ((MapEditor*)pParent->GetParent())->AddCreateObject(object);

        return object;*/
        return nullptr
    }
    //セーブマネージャー色々変えてるときに必要ないって結論に至った
    
};



//namespaceで実装も考えたけどCreateObjで親を探索できないから普通にGameObjectを継承させた。良いやり方あったら教えて
