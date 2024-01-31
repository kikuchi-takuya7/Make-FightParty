#pragma once
#include "../../Engine/GameObject.h"
#include <stack>
#include <vector>

//新しいファイルを追加したら、こことCreateObjectに要素を手動で追加する
enum FBXPATTERN {
	//SCHOOL,
	TEST,
	TESTFLOOR,
	TESTWALL,
	PATTERN_END
};

struct BACKUPDATA {
	std::string objectName;
	int objectId;
	Transform objectTrans;
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

	//createObjectListに入れる
	void AddCreateObject(GameObject* object);

	//ディレクトリ内の指定した識別子のファイルネームを獲得
	std::vector<std::string> GetFilePath(const std::string& dir_name, const std::string& extension) noexcept(false);

	void MoveCamPos();

	bool IsOverlapCursor();

	void Enter() { isUpdate_ = true; }
	void Leave() { isUpdate_ = false; }

private:

	std::vector<int> hModel_;

	//Mapファイルの中に入ってるfbxファイルの名前を入れる
	std::vector<std::string> fileName_;

	//imguiで選択されているオブジェクト
	FBXPATTERN selecting_Object;

	//作成したオブジェクトリスト
	std::list<GameObject*> createObjectList_;

	//hModelがどのモデルかのペアを表す
	std::vector<std::pair<int, FBXPATTERN>> modelPair_;

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