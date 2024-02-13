#pragma once
#include <DirectXMath.h>
#include <list>
#include <string>
#include <assert.h>
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "Imgui/Imgui.h"
#include "Global.h"

using namespace DirectX;

//-----------------------------------------------------------
//全てのゲームオブジェクト（シーンも含めて）が継承するインターフェース
// ゲームオブジェクトは、親子構造になっていて、
// マトリクスの影響を受けることになる
//-----------------------------------------------------------
class GameObject
{
protected:
	//位置や向きなどを管理するオブジェクト
	Transform				transform_;

	//オブジェクトの名前
	std::string				objectName_;

	//衝突判定リスト
	std::list<Collider*>	colliderList_;

public:
	//コンストラクタ
	GameObject();
	GameObject(GameObject* parent);
	GameObject(GameObject* parent, const std::string& name);

	//デストラクタ
	virtual ~GameObject();

	//各オブジェクトで必ず作る関数
	virtual void Initialize(void) {}
	virtual void Update(void) {}
	virtual void Draw() {}
	virtual void Release(void) {}
	
	//ImGuiで変更したい数値がある時に作る関数
	virtual void Imgui_Window() {}

	/// <summary>
	/// Imguiで使うセーブデータとか用のやつ
	/// </summary>
	virtual void Imgui_Data_Edit() {}

	//自分の該当関数を読んだ後、子供の関数も呼ぶ
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();
	void Imgui_WindowSub();

	//memo 使ってないからこれで正しいか不明
	////ローカル行列の取得（このオブジェクトの行列）
	////戻値：ローカル行列
	XMMATRIX GetLocalMatrix();

	//ワールド行列の取得（親の影響を受けた最終的な行列）
	//戻値：ワールド行列
	XMMATRIX GetWorldMatrix();

	/// <summary>
	/// 呼び出されたオブジェクトのtransformを変更できるスライダーを表示
	/// </summary>
	/// <param name="posmin">positionの最小値</param>
	/// <param name="posmax">positionの最大値</param>
	/// <param name="rot">rotateの最大値</param>
	/// <param name="scl">scaleの最大値</param>
	/// <param name="s">表示する名前</param>
	void Setting_Transform(Transform& _transform, float posmin, float posmax, float rot, float scl, std::string s);

	//SettingTransformのXMFLOAT3だけバージョン（position想定）
	void Setting_Float3(XMFLOAT3& _float3, float posmin, float posmax, std::string s);

	/// <summary>
	/// 呼び出されたオブジェクトのtransformを保存する関数
	/// </summary>
	/// <param name="hFile">クラスで作成したファイルのやつ</param>
	/// <param name="fileName">セーブするファイルの名前（もしかしたら同じファイル名だと上書きされちゃうから気を付けて）</param>
	void Save_Transform_File(Transform _transform, HANDLE hFile, LPCSTR fileName);

	/// <summary>
	/// 呼び出されたオブジェクトのtransformをロードする関数
	/// </summary>
	/// <param name="hFile">クラスで作成したファイルのやつ</param>
	/// <param name="fileName">ロードするファイルの名前</param>
	void Load_Transform_File(HANDLE hFile, LPCSTR fileName);

	
	/// <summary>
	/// 滑らかに移動させる
	/// </summary>
	/// <param name="position">動かしたいオブジェクトの座標</param>
	/// <param name="lastPos">最終的なポジション</param>
	/// <param name="moveRate">どのぐらい滑らかに移動させるか(最大1.0f)</param>
	/// <returns>移動し終わったらtrue</returns>
	bool RateMovePosition(XMFLOAT3& position, XMFLOAT3 lastPos, float moveRate);

	//各フラグの制御
	bool IsDead();			// 削除するかどうか
	void KillMe();			// 自分を削除する
	void Enter();			// Updateを許可
	void Leave();			// Updateを拒否
	void Visible();			// Drawを許可
	void Invisible();		// Drawを拒否
	bool IsInitialized();	// 初期化済みかどうか
	void SetInitialized();	// 初期化済みにする
	bool IsEntered();		// Update実行していいか
	bool IsVisibled();		// Draw実行していいか


	//子オブジェクトリストを取得
	//戻値：子オブジェクトリスト
	std::list<GameObject*>* GetChildList();

	//親オブジェクトを取得
	//戻値：親オブジェクトのアドレス
	GameObject* GetParent();

	//名前でオブジェクトを検索（対象は自分の子供以下）
	//引数：name	検索する名前
	//戻値：見つけたオブジェクトのアドレス（見つからなければnullptr）
	GameObject* FindChildObject(const std::string& name);

	/// <summary>
	/// クラス名で検索できるもの
	/// </summary>
	template<class C>
	C* FindGameObject() {
		auto list = GetChildList();
		for (GameObject* obj : *list) {
			C* ret = dynamic_cast<C*>(obj);
			if (ret != nullptr) {
				return ret;
			}
		}
		return nullptr;
	}

	template<class C>
	std::list<C*> FindGameObjects() {
		std::list<C*> rets;
		auto list = GetChildList();
		for (GameObject* obj : *list) {
			C* ret = dynamic_cast<C*>(obj);
			if (ret != nullptr) {
				rets.push_back(ret);
			}
		}
		return rets;
	}

	/// <summary>
	/// クラス名で検索できるもの
	/// </summary>
	template<class C>
	C* FindGameObject(const std::string& tag) {
		auto list = GetChildList();
		for (GameObject* obj : *list) {
			C* ret = dynamic_cast<C*>(obj);
			if (ret != nullptr) {
				if (obj->GetObjectName() == tag) {
					return ret;
				}
			}
		}
		return nullptr;
	}

	template<class C>
	std::list<C*> FindGameObjects(const std::string& tag) {
		std::list<C*> rets;
		auto list = GetChildList();
		for (GameObject* obj : *list) {
			C* ret = dynamic_cast<C*>(obj);
			if (ret != nullptr) {
				if (obj->GetObjectName() == tag) {
					rets.push_back(ret);
				}
			}
		}
		return rets;
	}

	//名前でオブジェクトを検索（対象は全体）
	//引数：検索する名前
	//戻値：見つけたオブジェクトのアドレス
	GameObject* FindObject(const std::string& name) { return GetRootJob()->FindChildObject(name); }

	//オブジェクトの名前を取得
	//戻値：名前
	const std::string& GetObjectName(void) const;

	//子オブジェクトを追加（リストの最後へ）
	//引数：追加するオブジェクト
	void PushBackChild(GameObject* obj);

	//子オブジェクトを追加（リストの先頭へ）
	//引数：obj 追加するオブジェクト
	void PushFrontChild(GameObject* obj);

	//子オブジェクトを全て削除
	void KillAllChildren();

	/// <summary>
	/// コライダー（衝突判定）を追加する
	/// </summary>
	/// <param name="collider">追加するCollider</param>
	/// <param name="type">追加するColliderのattackType</param>
	void AddCollider(Collider* collider, ColliderAttackType type);

	/// <summary>
	/// 特定のコライダーを破棄する
	/// </summary>
	/// <param name="type">破棄したいコライダーの種類</param>
	void EraseCollider(ColliderAttackType type);
	
	/// <summary>
	/// 何かと衝突した場合に呼ばれる（オーバーライド用）
	/// </summary>
	/// <param name="pTarget">衝突した相手</param>
	virtual void OnCollision(GameObject* pTarget) {};

	/// <summary>
	/// 何かと衝突した場合に呼ばれる（オーバーライド用）
	/// </summary>
	/// <param name="pTarget">衝突した相手</param>
	/// <param name="myType">当たったcolliderの自分のattackType</param>
	/// <param name="targetType">当たったcolliderの相手のattackType</param>
	virtual void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) {};

	//コライダー（衝突判定）を削除
	void ClearCollider();

	//衝突判定
	//引数：pTarget	衝突してるか調べる相手
	void Collision(GameObject* pTarget);

	//テスト用の衝突判定枠を表示
	void CollisionDraw();

	//RootJobを取得
	GameObject* GetRootJob();


	//各アクセス関数
	Transform GetTransform() { return transform_; }
	XMFLOAT3 GetPosition() { return transform_.position_; }
	XMFLOAT3 GetRotate() { return transform_.rotate_; }
	XMFLOAT3 GetScale() { return transform_.scale_; }
	XMFLOAT3 GetWorldPosition() { return Float3Add(GetParent()->transform_.position_, transform_.position_); }
	XMFLOAT3 GetWorldRotate() { return Float3Add(GetParent()->transform_.rotate_, transform_.rotate_); }
	XMFLOAT3 GetWorldScale() { return Float3Add(GetParent()->transform_.scale_, transform_.scale_); }
	void SetPosition(XMFLOAT3 position) { transform_.position_ = position; }
	void SetPosition(float x, float y, float z) { SetPosition(XMFLOAT3(x, y, z)); }
	void SetRotate(XMFLOAT3 rotate) { transform_.rotate_ = rotate; }
	void SetRotate(float x, float y, float z) { SetRotate(XMFLOAT3(x, y, z)); }
	void SetRotateX(float x) { SetRotate(x, transform_.rotate_.y, transform_.rotate_.z); }
	void SetRotateY(float y) { SetRotate(transform_.rotate_.x, y, transform_.rotate_.z); }
	void SetRotateZ(float z) { SetRotate(transform_.rotate_.x, transform_.rotate_.y, z); }
	void SetScale(XMFLOAT3 scale) { transform_.scale_ = scale; }
	void SetScale(float x, float y, float z) { SetScale(XMFLOAT3(x, y, z)); }
	void SetScale(float s) { SetScale(XMFLOAT3(s, s, s)); }
	void SetTransform(Transform transform) { transform_ = transform; }
	

	void SetObjectID(int ID) { objectID_ = ID; }
	int GetObjectID() { return objectID_; }

	

private:

	//オブジェクト削除（再帰）
	//引数：obj　削除するオブジェクト
	void KillObjectSub(GameObject* obj);

	float GetRateValue(float begin, float end, float rate);

private:
	//フラグ
	struct OBJECT_STATE
	{
		unsigned initialized : 1;	//初期化済みか
		unsigned entered : 1;		//更新するか
		unsigned visible : 1;		//描画するか
		unsigned dead : 1;			//削除するか
	};
	OBJECT_STATE state_;

	//親オブジェクト
	GameObject* pParent_;

	//子オブジェクトリスト
	std::list<GameObject*> childList_;

	//オブジェクトを識別するIDというか順番みたいな感じになってる。IDがないとImguiで識別できなくなっちゃう
	int objectID_;

	//オブジェクトを滑らかに動かすために必要
	float moveRate_;

};


//オブジェクトを作成するテンプレート
template <class T>
T* Instantiate(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}