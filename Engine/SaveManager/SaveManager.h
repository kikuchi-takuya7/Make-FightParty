#pragma once
#include "../GameObject.h"


//◆◆◆を管理するクラス
class SaveManager : public GameObject
{

public:
    //コンストラクタ
    SaveManager(GameObject* parent);

    //デストラクタ
    ~SaveManager();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void Save(std::string fileName, std::list<GameObject*> list);

    void AddSaveObj(GameObject* obj);

    void Load(std::string fileName);

    GameObject* CreateObj(std::string className);     // オブジェクト生成

private:

    /*template <class T>
    T* CreateObject(GameObject* pParent)
    {
        T* object = Instantiate<T>(this->GetParent());

        if (this->GetParent()->GetObjectName() == "MapData")
            ((MapData*)this->GetParent())->AddCreateObject(object);

        return object;
    }*/
    
};



//namespaceで実装も考えたけどCreateObjで親を探索できないから普通にGameObjectを継承させた。良いやり方あったら教えて
