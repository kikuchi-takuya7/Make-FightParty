#pragma once
#include "../../../Engine/GameObject.h"


class CreateMode;

//StageSourceの元となるクラス
class StageSourceBase : public GameObject
{

protected:

    int hModel_;

public:
    //コンストラクタ
    StageSourceBase(GameObject* parent,std::string name);

    //デストラクタ
    ~StageSourceBase();

    //////////////オーバーロードした関数///////////////

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    

    ///////////////継承先で使う関数///////////////////////

    /// <summary>
    /// 継承先用の初期化
    /// </summary>
    virtual void ChildInitialize() {};

    /// <summary>
    /// 継承先用のUpdate
    /// </summary>
    virtual void ChildUpdate() {};

    /// <summary>
    /// 継承先用の描画
    /// </summary>
    virtual void ChildDraw() {};

    /// <summary>
    /// 継承先用の開放
    /// </summary>
    virtual void ChildRelease() {};


    ////////////////アクセス関数//////////////////

    int GetHandle() { return hModel_; }
    void SetHandle(int handle) { hModel_ = handle; }


private:

    


};