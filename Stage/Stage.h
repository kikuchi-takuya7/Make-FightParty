#pragma once
#include "../Engine/GameObject.h"
#include <vector>

class CreateMode;
class StageSourceBase;

//stageを管理するクラス
class Stage : public GameObject
{

public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //////////////オーバーロードした関数///////////////

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void AllStartUpdate();

    void AllStopUpdate();

    ///////////////CreateModeで使う関数///////////////////////

    void StageCostCheck();


    ////////////////アクセス関数//////////////////

    /// <summary>
    /// ステージのコストをセットする
    /// </summary>
    /// <param name="pos">そのオブジェクトの位置</param>
    /// <param name="cost">オブジェクトのコスト</param>
    void SetStageCost(XMFLOAT3 pos, int cost);

    void SetCreateMode(CreateMode* createMode) { pCreateMode_ = createMode; }
    void PushStageSource(StageSourceBase* source) { pStageSourceList_.emplace_back(source); }
    int GetStageHandle() { return hModel_; }
    XMFLOAT3 GetStageSize();
    std::vector<std::vector<long>> GetMap() { return map_; }
    

private:

    int hModel_;

    CreateMode* pCreateMode_;

    //二次元配列でマップやコストを表す
    std::vector<std::vector<long>> map_; 

    //必要あるかはわからない
    std::list<StageSourceBase*> pStageSourceList_;

};