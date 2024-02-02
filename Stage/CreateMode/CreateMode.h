#pragma once
#include "../../Engine/GameObject.h"
#include <stack>
#include <vector>

//新しいファイルを追加したら、こことCreateObjectに要素を手動で追加する
enum FBXPATTERN {
	//SCHOOL,
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

	//初期化
	ModelInfo(int h, FBXPATTERN pattern) {
		hModel = h;
		modelPattern = pattern;
	}

};

struct SelectModelInfo {


	//


};

//オブジェクト追加モードを管理するクラス
class CreateMode
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	CreateMode();

	//初期化
	void Initialize();
	void ViewInit();

	//更新
	void Update();

	//描画
	void Draw();

	//開放
	void Release();

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

	void MoveCamPos();

	bool IsOverlapCursor();

	bool IsAllDecidedObject();

	void Enter() { isUpdate_ = true; }
	void Leave() { isUpdate_ = false; }

private:

	std::vector<ModelInfo> modelData;

	//Mapファイルの中に入ってるfbxファイルの名前を入れる
	std::vector<std::string> fileName_;

	//viewObjectListのどこが選ばれたか
	int selecting_Object;

	//作成したオブジェクトリスト
	std::list<GameObject*> createObjectList_;

	//hModelがどのモデルかのペアを表す
	//std::vector<std::pair<int, FBXPATTERN>> modelPair_;

	//表示させているオブジェクトの一覧（モデル番号）
	std::vector<int> viewObjectList_;

	//プレイヤーが設置するオブジェクト。{モデル番号,座標}どのプレイヤーが選んでるかは要素番目で示す.モデルパターンは入れる必要なしかな
	std::vector<std::pair<int,XMFLOAT3>> settingObject_;

	bool isUpdate_;

	int nextObjectId_;

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