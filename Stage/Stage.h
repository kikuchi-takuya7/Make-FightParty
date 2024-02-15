#pragma once
#include "../Engine/GameObject.h"
#include <vector>
#include <stack>

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


    ////////////////アクセス関数//////////////////

    /// <summary>
    /// ステージのコストをセットする
    /// </summary>
    /// <param name="pos">そのオブジェクトの位置</param>
    /// <param name="cost">オブジェクトのコスト</param>
    void SetStageCost(XMFLOAT3 pos, int cost);

    /// <summary>
    /// Astarアルゴリズムで出た経路を表示する為にモデルを変える為の関数
    /// </summary>
    /// <param name="pair">経路探索で出た経路</param>
    void SetStageModel(std::stack<std::pair<int,int>> pair);

    void SetCreateMode(CreateMode* createMode) { pCreateMode_ = createMode; }
    void PushStageSource(StageSourceBase* source) { pStageSourceList_.emplace_back(source); }
    int GetStageHandle() { return hModel_; }
    XMFLOAT3 GetStageSize();
    std::vector<std::vector<long>> GetMap() { return stageCost_; }
    

private:

    //普通の1マス分のステージのモデル番号
    int hModel_;

    //色を変える用の1マス分のステージモデル番号
    int debugModel_;

    //クリエイトモードのインスタンス
    CreateMode* pCreateMode_;

    //二次元配列でマップやコストを表す
    std::vector<std::vector<long>> stageCost_; 

    //Astarアルゴリズムのデバック用に色を変える為の配列
    std::vector<std::vector<long>> stageModel_;

    //クリエイトモードで作られたモデル一覧
    std::list<StageSourceBase*> pStageSourceList_;

};