#pragma once
#include "../../../Engine/GameObject.h"


class CreateMode;

//StageSourceの元となるクラス
class StageSourceBase : public GameObject
{

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

    void OnCollision(GameObject* pTarget) override;

    ///////////////継承先で使う関数///////////////////////




    ////////////////アクセス関数//////////////////

    int GetStageHandle() { return hModel_; }


private:

    int hModel_;


};