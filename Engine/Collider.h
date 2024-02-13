#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <../../Global.h>


using namespace DirectX;

//クラスの前方宣言
class GameObject;
class BoxCollider;
class SphereCollider;

//あたり判定のタイプ
enum ColliderType
{
	COLLIDER_BOX,		//箱型
	COLLIDER_CIRCLE		//球体
};

//どこの当たり判定か(体か攻撃判定か)
enum ColliderAttackType 
{
	COLLIDER_BODY,			//体
	COLLIDER_ATTACK,		//体での攻撃(殴るとか)
	COLLIDER_WEAPON,		//武器での攻撃(砲台の球等もこれ)
	COLLIDER_BROCK,			//ブロックのオブジェクト
	COLLIDER_OBSTRYCTION,	//トゲ等のオブジェクト

};

//-----------------------------------------------------------
//あたり判定を管理するクラス
//-----------------------------------------------------------
class Collider
{
	//それぞれのクラスのprivateメンバにアクセスできるようにする
	friend class BoxCollider;
	friend class SphereCollider;

protected:
	GameObject*		pGameObject_;	//この判定をつけたゲームオブジェクト
	ColliderType	type_;			//種類
	ColliderAttackType attackType_;	//どこの当たり判定だったか
	XMFLOAT3		center_;		//中心位置（ゲームオブジェクトの原点から見た位置）
	XMFLOAT3		size_;			//判定サイズ（幅、高さ、奥行き）
	XMFLOAT3		rotate_;		//centerから回転させる角度。と思ったけど結局その四角形の形のまま動くからちゃんと回転してるわけではない。
	//std::string		colliderName_;	//コライダー毎の名前。判定をコライダー毎に変える用
	int				hDebugModel_;	//デバッグ表示用のモデルのID

public:
	//コンストラクタ
	Collider();

	//デストラクタ
	virtual ~Collider();

	//接触判定（継承先のSphereColliderかBoxColliderでオーバーライド）
	//引数：target	相手の当たり判定
	//戻値：接触してればtrue
	virtual bool IsHit(Collider* target) = 0;

	//箱型同士の衝突判定
	//引数：boxA	１つ目の箱型判定
	//引数：boxB	２つ目の箱型判定
	//戻値：接触していればtrue
	bool IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB);

	//箱型と球体の衝突判定
	//引数：box	箱型判定
	//引数：sphere	２つ目の箱型判定
	//戻値：接触していればtrue
	bool IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere);

	//球体同士の衝突判定
	//引数：circleA	１つ目の球体判定
	//引数：circleB	２つ目の球体判定
	//戻値：接触していればtrue
	bool IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB);

	/// <summary>
	/// 回転した後のposを計算する
	/// </summary>
	/// <returns>回転後のcenter</returns>
	XMFLOAT3 CalclationCenter();

	/// <summary>
	/// 回転した後のSizeを計算する（実際には回転してる訳では無くそれっぽく移動してるだけかも怪しいかもしれない）
	/// </summary>
	/// <returns>回転後のSize</returns>
	XMFLOAT3 CalclationSize();

	//テスト表示用の枠を描画
	//引数：position	オブジェクトの位置
	void Draw(XMFLOAT3 position);

	//////////アクセス関数////////////
	void SetGameObject(GameObject* gameObject) { pGameObject_ = gameObject; }
	//void SetName(std::string name) { colliderName_ = name; }
	void SetAttackType(ColliderAttackType type) { attackType_ = type; }
	void SetCenter(XMFLOAT3 center) { center_ = center; }
	void SetSize(XMFLOAT3 size) { size_ = size; }
	void SetRotate(XMFLOAT3 rotate) { rotate_ = rotate; }
	//std::string GetName() { return colliderName_; }
	ColliderAttackType GetAttackType() { return attackType_; }
	XMFLOAT3 GetCenter() { return center_; }
	XMFLOAT3 GetSize() { return size_; }
	XMFLOAT3 GetRotate() { return rotate_; }

};

