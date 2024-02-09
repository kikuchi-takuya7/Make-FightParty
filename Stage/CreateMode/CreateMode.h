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

class MetaAI;
class NavigationAI;
class Stage;
class StageSourceBase;

//オブジェクト追加モードを管理するクラス
//2つしかモードが無いからまとめたけどstateにした方が良い？
class CreateMode :public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	CreateMode(GameObject* parent);

	//////////////////オーバーライドした関数///////////////////////

	//初期化
	void Initialize() override;
	void ViewInit();
	void SettingInit();

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;


	////////////////////オブジェクトを操る関数/////////////////////

	/// <summary>
	/// オブジェクトを作成する
	/// </summary>
	/// <param name="hModel">モデル番号</param>
	/// <param name="trans">モデルのTransform</param>
	/// <param name="element">何番目の要素か</param>
	void CreateObject(int hModel,Transform trans, int element);

	/// <summary>
	/// 
	/// </summary>
	void SelectObject();

	void GetCursorRay(XMVECTOR& front, XMVECTOR& back);

	//ディレクトリ内の指定した識別子のファイルネームを獲得	
	std::vector<std::string> GetFilePath(const std::string& dir_name, const std::string& extension) noexcept(false);

	//////////////////////セレクトモードで使う関数////////////////////////////////

	bool IsSelectingOverlapCursor(XMVECTOR front, XMVECTOR back);

	bool IsAllDecidedObject();

	//////////////////////セッティングモードで使う関数////////////////////////////////

	bool IsStageOverlapCursor(XMVECTOR front, XMVECTOR back);

	bool IsOverlapPosition();

	void AIMovingObject();

	/////////////////////////カメラ移動で使う関数//////////////////////////////////

	void MoveCam(XMFLOAT3 lastPos, XMFLOAT3 lastTar);

	float GetRateValue(float begin, float end, float rate);

	///////////////////////////アクセス関数///////////////////////////////
	void ToSelectMode();
	void ToSettingMode();
	void ToGameMode();
	CREATESTATE GetState() { return nowState_; }
	void SetMetaAI(MetaAI* AI) { pMetaAI_ = AI; }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void SetStage(Stage* stage) { pStage_ = stage; }
	void SetStartEnemyID(int ID) { startEnemyID_ = ID; }
	std::list<StageSourceBase*> GetCreateObjectList() { return createObjectList_; }

	//createObjectListに入れる
	void AddCreateObject(StageSourceBase* object);

private:

	MetaAI* pMetaAI_;
	NavigationAI* pNavigationAI_;
	Stage* pStage_;

	CREATESTATE nowState_;

	std::vector<ModelInfo> modelData_;

	

	//viewObjectListのどこが選ばれたか,settingモードではどこのsettingオブジェクトが選ばれたか
	int selecting_Object_;

	//表示させているオブジェクトの一覧（モデル番号）
	std::vector<int> viewObjectList_;

	//プレイヤーが設置するオブジェクト。{モデル番号,そのモデルのTransform}どのプレイヤーが選んでるかは要素番目で示している
	std::vector<std::pair<int,Transform>> settingObject_;

	//作成したオブジェクトリスト
	std::list<StageSourceBase*> createObjectList_;

	float rotateObjectValue_;

	int nextObjectId_;

	int flame_;

	int startEnemyID_;

	//////カメラを滑らかに動かすのに使う変数

	//緩急を付けるレート
	float camMoveRate_;

	//インスタンスを作成してobjectListに入れるテンプレート
	template <class T>
	T* CreateInstance(int hModel, Transform trans)
	{
		T* pObject = Instantiate<T>(this);
		AddCreateObject(pObject);
		pStage_->PushStageSource(pObject);
		//pStage_->SetStageCost(trans.position_, pObject->GetStageCost());
		pObject->SetTransform(trans);
		pObject->SetHandle(hModel);
		return pObject;
	}

};