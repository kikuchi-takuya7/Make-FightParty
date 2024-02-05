#pragma once
#include "../../Engine/GameObject.h"

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
	TESTFLOOR,
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

struct SelectModelInfo {


	//


};

//オブジェクト追加モードを管理するクラス
class CreateMode :public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	CreateMode(GameObject* parent);

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

	std::list<GameObject*> GetCreateObjectList() { return createObjectList_; }

	/// <summary>
	/// selecting_objectに対応したオブジェクトを作成する
	/// </summary>
	/// <returns>作成したオブジェクト</returns>
	GameObject* CreateObject();

	void SelectObject();

	//createObjectListに入れる
	void AddCreateObject(GameObject* object);

	//ディレクトリ内の指定した識別子のファイルネームを獲得
	std::vector<std::string> GetFilePath(const std::string& dir_name, const std::string& extension) noexcept(false);

	//////////////////////セレクトモードで使う関数////////////////////////////////

	bool IsOverlapCursor();

	bool IsAllDecidedObject();

	//事前にプレイヤーの数だけ用意して、その順位に対応した位置に置くから大丈夫？
	//void SwapElements();

	//////////////////////セッティングモードで使う関数////////////////////////////////

	void MovingObject();



	/////////////////////////カメラ移動で使う関数//////////////////////////////////

	float GetRateValue(float begin, float end, float rate);

	void MoveCam(XMFLOAT3 lastPos, XMFLOAT3 lastTar);

	///////////////////////////アクセス関数///////////////////////////////
	void ToSelectMode();
	void ToSettingMode();
	CREATESTATE GetState() { return nowState_; }
	void SetMetaAI(MetaAI* AI) { pMetaAI_ = AI; }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }

private:

	MetaAI* pMetaAI_;
	NavigationAI* pNavigationAI_;

	CREATESTATE nowState_;

	std::vector<ModelInfo> modelData;

	//Mapファイルの中に入ってるfbxファイルの名前を入れる
	std::vector<std::string> fileName_;

	//viewObjectListのどこが選ばれたか
	int selecting_Object;

	//作成したオブジェクトリスト
	std::list<GameObject*> createObjectList_;

	//表示させているオブジェクトの一覧（モデル番号）
	std::vector<int> viewObjectList_;

	//プレイヤーが設置するオブジェクト。{モデル番号,そのモデルのTransform}どのプレイヤーが選んでるかは要素番目で示す.モデルパターンは入れる必要なしかな
	std::vector<std::pair<int,Transform>> settingObject_;

	float rotateObjectValue_;

	int nextObjectId_;

	int flame_;
	
	//////カメラを滑らかに動かすのに使う変数

	//緩急を付けるレート
	float camMoveRate_;



	//インスタンスを作成してobjectListに入れるテンプレート
	template <class T>
	T* CreateInstance()
	{
		//T* pObject = Instantiate<T>(this);
		//AddCreateObject(pObject);
		//pObject->SetObjectID(nextObjectId_); //作ったオブジェクト順に識別するためのIDを付ける
		//return pObject;
		return nullptr;
	}

};