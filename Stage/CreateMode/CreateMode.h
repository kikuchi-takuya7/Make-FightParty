#pragma once
#include "../../Engine/GameObject.h"
#include "../Stage.h"
#include <stack>
#include <vector>

enum CREATESTATE {
	SELECT_MODE,
	SETTING_MODE,
	NONE
};

//新しいファイルを追加したら、こことCreateObjectに要素を手動で追加する
enum FBXPATTERN {
	CANNON,
	NEEDLE,
	ONEBROCK,
	PATTERN_END
};

struct ModelInfo {

	//モデル番号
	int hModel;

	//モデルの種類
	FBXPATTERN modelPattern;

	//コンストラクタ
	ModelInfo(int h, FBXPATTERN pattern) {
		hModel = h;
		modelPattern = pattern;
	}

};

struct SettingObjectInfo {

	//モデル番号
	int hModel;

	//Transform
	Transform trans;

	//移動し終わっているか
	bool moved;

	//コンストラクタ
	SettingObjectInfo() {
		hModel = -1;
		Transform t;
		trans = t;
		moved = false;
	}

	SettingObjectInfo(int h, Transform t,bool m) {
		hModel = h;
		trans = t;
		moved = m;
	}
};

class MetaAI;
class NavigationAI;
class Stage;
class StageSourceBase;
class Timer;

//オブジェクト追加モードを管理するクラス
//2つしかモードが無いからまとめたけどstateにした方が良い？
class CreateMode :public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	CreateMode(GameObject* parent);


	//初期化
	void Initialize() override;
	void SelectInit();
	void SettingInit();

	//更新
	void Update() override;
	void SelectUpdate();
	void SettingUpdate();

	//描画
	void Draw() override;

	//開放
	void Release() override;



	/// <summary>
	/// オブジェクトを作成する
	/// </summary>
	/// <param name="hModel">モデル番号</param>
	/// <param name="trans">モデルのTransform</param>
	/// <param name="element">何番目の要素か</param>
	void CreateObject(int hModel,Transform trans, int element);


	//createObjectListに入れる
	void AddCreateObject(StageSourceBase* object);

	/// <summary>
	/// マウスカーソルの位置から出るベクトルを取得する
	/// </summary>
	/// <param name="front">前のベクトル</param>
	/// <param name="back">後ろのベクトル</param>
	void GetCursorRay(XMVECTOR& front, XMVECTOR& back);

	//ディレクトリ内の指定した識別子のファイルネームを獲得	
	std::vector<std::string> GetFilePath(const std::string& dir_name, const std::string& extension) noexcept(false);

	//////////////////////セレクトモードで使う関数////////////////////////////////

	/// <summary>
	/// AIがオブジェクトを選択する関数
	/// </summary>
	/// <param name="ID">オブジェクトを選択する敵のID</param>
	void AISelectObject(int ID);

	/// <summary>
	/// settingObjectに選んだオブジェクトの情報を渡す
	/// </summary>
	/// <param name="ID">オブジェクトを選んだ人のID</param>
	void SelectObject(int ID);

	/// <summary>
	/// カーソルが浮かんでるオブジェクトに合わさっているか
	/// </summary>
	/// <param name="front">飛ばすレイの前方向ベクトル</param>
	/// <param name="back">後ろ方向のベクトル</param>
	/// <returns>当たっていたらtrue</returns>
	bool IsSelectingOverlapCursor(XMVECTOR front, XMVECTOR back);

	/// <summary>
	/// プレイヤー全員がオブジェクトを選び終わったか
	/// </summary>
	/// <returns>選び終わっていたらtrue</returns>
	bool IsAllDecidedObject();

	//////////////////////セッティングモードで使う関数////////////////////////////////

	bool IsStageOverlapCursor(XMVECTOR front, XMVECTOR back);

	bool IsOverlapPosition();

	/// <summary>
	/// Aiが選んだオブジェクトを動かす位置を決める
	/// </summary>
	void AIMovingObject();

	////////////////////////モードを切り替える関数///////////////////

	void ToSelectMode();
	void ToSettingMode();
	void ToGameMode();

	///////////////////////////アクセス関数///////////////////////////////

	CREATESTATE GetState() { return nowState_; }
	void SetMetaAI(MetaAI* AI) { pMetaAI_ = AI; }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void SetStage(Stage* stage) { pStage_ = stage; }
	void SetStartEnemyID(int ID) { startEnemyID_ = ID; }
	std::list<StageSourceBase*> GetCreateObjectList() { return createObjectList_; }


private:

	//モードを管理する変数
	CREATESTATE nowState_;

	/////////////AI等のインスタンス///////////

	MetaAI* pMetaAI_;
	NavigationAI* pNavigationAI_;
	Stage* pStage_;

	
	//////////////////////////オブジェクト操作に使う変数///////////////////////
	
	//モデルのデータを保存する配列
	std::vector<ModelInfo> modelData_;

	//表示させているオブジェクトの一覧（モデル番号）
	std::vector<int> viewObjectList_;

	//viewObjectListのどこが選ばれたか,settingモードではどこのsettingオブジェクトが選ばれたか
	int selecting_Object_;

	//プレイヤーが設置するオブジェクト。{モデル番号,そのモデルのTransform}どのプレイヤーが選んでるかは要素番目で示している
	std::vector<SettingObjectInfo> settingObject_;

	//クリエイトモード時のランキング
	std::vector<int> ranking_;

	//次に選択するプレイヤーのID(rankingでビリから順番に選ばせる用)
	int nextSelectCharacterID_;

	//選択したオブジェクトが移動中か
	bool isObjectMoving_;

	//////////////////////////その他//////////////////////////////

	//作成したオブジェクトリスト
	std::list<StageSourceBase*> createObjectList_;

	//モデルを回転させる変数
	float rotateObjectValue_;

	//敵の最初のID
	int startEnemyID_;

	//時間を置くのに使う
	Timer* timer_;


	//インスタンスを作成して色々するテンプレート
	template <class T>
	T* CreateInstance(int hModel, Transform trans, int ID)
	{
		T* pObject = Instantiate<T>(this);
		AddCreateObject(pObject);
		pStage_->PushStageSource(pObject);
		pStage_->SetStageCost(trans.position_, pObject->GetStageCost());
		
		//AIが選んだオブジェクトなら真ん中からゆっくり動くように
		if (ID >= startEnemyID_) {
			Transform objTrans;
			objTrans.position_ = XMFLOAT3(15.0f, ZERO, 15.0f);
			objTrans.rotate_ = trans.rotate_;
			pObject->SetMoveLastPos(trans.position_);
			pObject->SetTransform(objTrans);
		}
		else {
			pObject->SetMoveLastPos(trans.position_);
			pObject->SetTransform(trans);
		}

		pObject->Leave();
		pObject->SetHandle(hModel);
		return pObject;
	}

};