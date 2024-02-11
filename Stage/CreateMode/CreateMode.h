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
class Timer;

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


	//createObjectListに入れる
	void AddCreateObject(StageSourceBase* object);

	void GetCursorRay(XMVECTOR& front, XMVECTOR& back);

	//ディレクトリ内の指定した識別子のファイルネームを獲得	
	std::vector<std::string> GetFilePath(const std::string& dir_name, const std::string& extension) noexcept(false);

	//////////////////////セレクトモードで使う関数////////////////////////////////

	void AISelectObject(int ID);

	void SelectObject(int ID);

	bool IsSelectingOverlapCursor(XMVECTOR front, XMVECTOR back);

	bool IsAllDecidedObject();

	//////////////////////セッティングモードで使う関数////////////////////////////////

	bool IsStageOverlapCursor(XMVECTOR front, XMVECTOR back);

	bool IsOverlapPosition();

	void AIMovingObject();

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


private:

	//モードを管理する変数
	CREATESTATE nowState_;

	/////////////AI等のインスタンス///////////

	MetaAI* pMetaAI_;
	NavigationAI* pNavigationAI_;
	Stage* pStage_;


	/////////オブジェクト操作に使う変数////////////

	//モデルのデータを保存する配列
	std::vector<ModelInfo> modelData_;

	//viewObjectListのどこが選ばれたか,settingモードではどこのsettingオブジェクトが選ばれたか
	int selecting_Object_;

	//表示させているオブジェクトの一覧（モデル番号）
	std::vector<int> viewObjectList_;

	//プレイヤーが設置するオブジェクト。{モデル番号,そのモデルのTransform}どのプレイヤーが選んでるかは要素番目で示している
	std::vector<std::pair<int,Transform>> settingObject_;

	//クリエイトモード時のランキング
	std::vector<int> ranking_;

	//次に選択するプレイヤーのID
	int nextSelectCharacterID_;

	/////////////その他/////////

	//作成したオブジェクトリスト
	std::list<StageSourceBase*> createObjectList_;

	//モデルを回転させる変数
	float rotateObjectValue_;

	//待機する時間
	int flame_;

	//敵の最初のID
	int startEnemyID_;

	Timer* timer_;

	//////カメラを滑らかに動かすのに使う変数

	bool isCamMoveEnd_;

	//インスタンスを作成して色々するテンプレート
	template <class T>
	T* CreateInstance(int hModel, Transform trans)
	{
		T* pObject = Instantiate<T>(this);
		AddCreateObject(pObject);
		pStage_->PushStageSource(pObject);
		pStage_->SetStageCost(trans.position_, pObject->GetStageCost());
		pObject->SetTransform(trans);
		pObject->SetHandle(hModel);
		return pObject;
	}

};