#pragma once
#include "../GameObject.h"
#include <stack>
#include <vector>

class SaveManager;

//新しいファイルを追加したら、こことCreateObjectに要素を手動で追加する
enum FBXPATTERN {
	//SCHOOL,
	ROOM_1,
	TESTFLOOR,
	TESTWALL,
	PATTERN_END
};

struct BACKUPDATA {
	std::string objectName;
	int objectId;
	Transform objectTrans;
};

//■■シーンを管理するクラス
class MapData : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	MapData(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void Imgui_Window() override;

	std::list<GameObject*> GetCreateObjectList() { return createObjectList_; }

	/// <summary>
	/// selecting_objectに対応したオブジェクトを作成する
	/// </summary>
	/// <returns>作成したオブジェクト</returns>
	GameObject* CreateObject();

	//createObjectListに入れる
	void AddCreateObject(GameObject* object);

	//ディレクトリ内の指定した識別子のファイルネームを獲得
	std::vector<std::string> get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false);

	//createObjectの中にdeleteされたオブジェクトがあるか
	void CheckDeleteObject();

	void AllDeleteCreateObject();

	//オブジェクトの位置（CreateList）を上に上げる
	void ChengeUp(GameObject* pTarget);
	void ChengeDown(GameObject* pTarget);

	//ロードしたすべてのIDを調べて最大値を知っておく
	int MaxObjectId();

	//オブジェクトが動かされた時にバックアップをとる関数
	void BackUpSave();

private:

	std::vector<int> hModel_;
	
	//Mapファイルの中に入ってるfbxファイルの名前を入れる
	std::vector<std::string> fileName_;
	
	//imguiで選択されているオブジェクト
	FBXPATTERN selecting_object;

	//作成したオブジェクトリスト
	std::list<GameObject*> createObjectList_;

	//std::pair<>

	//std::stack<BACKUPDATA> objectBackUp_;

	SaveManager* pSaveManager_;

	//セーブするかのフラグ
	bool isSave_;

	bool isLoad_;

	bool isNewSave_;

	int nextObjectId_;

	//インスタンスを作成してobjectListに入れるテンプレート
	template <class T>
	T* CreateInstance()
	{
		T* pObject = Instantiate<T>(this);
		AddCreateObject(pObject);
		pObject->SetObjectID(nextObjectId_); //作ったオブジェクト順に識別するためのIDを付ける
		return pObject;
	}

};