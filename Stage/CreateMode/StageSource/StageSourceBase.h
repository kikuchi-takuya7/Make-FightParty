#pragma once
#include "../../../Engine/GameObject.h"

//球の各種情報
struct BulletData {

    int power_;     //球の攻撃力
    float speed_;   //球の速さ
    float interval_;//球を出す頻度
    float size_;    //球の大きさ

};

class CsvReader;
class RateFrame;

//StageSourceの元となるクラス
class StageSourceBase : public GameObject
{

protected:

    //モデル番号
    int hModel_;

    //ステージに置いたときのコスト。Astarアルゴリズムで使用
    int cost_;

    //このオブジェクトを生成したプレイヤーのID
    int authorID_;

    //このオブジェクトの攻撃力（デフォルトは0）
    int attackPower_;

    //当たり判定
    BoxCollider* pBoxCollision_;

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

    //////////////////メンバ関数/////////////////////////
    

    


    ////////////////アクセス関数//////////////////

    /// <summary>
    /// CSVと情報が入ってる場所をセットする
    /// </summary>
    /// <param name="csv">情報が入っているCSVのポインタ</param>
    /// <param name="csvPos">ほしい情報が入っている列</param>
    virtual void SetObjCsv(CsvReader* csv, int csvPos) {};

    int GetHandle() { return hModel_; }
    int GetStageCost() { return cost_; }
    int GetAuthorID() { return authorID_; }
    int GetAttackPower() { return attackPower_; }
    void SetHandle(int handle) { hModel_ = handle; }
    void SetMoveLastPos(XMFLOAT3 lastPos) { lastPos_ = lastPos; }
    void SetAuthorID(int ID) { authorID_ = ID; }
    
    
protected:

    

private:

    XMFLOAT3 lastPos_;

    RateFrame* rate_;


};