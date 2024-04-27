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
	COLLIDER_BODY,				//体
	COLLIDER_ATTACK,			//体での攻撃(殴るとか)
	COLLIDER_WEAPON,			//武器での攻撃
	COLLIDER_BROCK,				//ブロックのオブジェクト
	COLLIDER_OBSTRYCTION,		//トゲ等のオブジェクト
	COLLIDER_OBJ_ATTACK			//球での攻撃
};

//3方向のベクトル
enum ColliderVec {
	VEC_X,
	VEC_Y,
	VEC_Z,
	VEC_NUM
};

//-----------------------------------------------------------
//あたり判定を管理するクラス(分離軸判定を使用)
//参考にしたサイト：http://marupeke296.com/COL_3D_No13_OBBvsOBB.html
//-----------------------------------------------------------
class Collider
{
	//それぞれのクラスのprivateメンバにアクセスできるようにする
	friend class BoxCollider;
	friend class SphereCollider;

protected:
	GameObject*		pGameObject_;					//この判定をつけたゲームオブジェクト
	ColliderType	type_;							//種類
	ColliderAttackType attackType_;					//どこの当たり判定だったか
	XMVECTOR		center_;						//中心位置（ゲームオブジェクトの原点から見た位置）
	XMVECTOR		directionNormalVec_[VEC_NUM];	//各軸ベクトル（各軸の方向を指す）
	float			length_[VEC_NUM];				//判定サイズ(各軸のベクトルの長さ)

	XMFLOAT3		rotate_;				//コライダー自体に設定された回転
	XMFLOAT3		size_;					//コライダーのsize
	
	int				hDebugModel_;			//デバッグ表示用のモデルのID

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

	// 分離軸に投影された軸成分から投影線分長を算出
	// 引数：分離軸となるベクトル
	// 引数：一つ目の方向ベクトル
	// 引数：二つ目の方向ベクトル
	// 引数：三つ目の方向ベクトル（必要なら）
	float LenSegOnSeparateAxis(XMVECTOR* Sep, XMVECTOR* e1, XMVECTOR* e2, XMVECTOR* e3 = 0);

	//各軸の方向ベクトルを計算
	void Calclation();

	//テスト表示用の枠を描画
	//引数：position	オブジェクトの位置
	void Draw(XMFLOAT3 position);

	//////////アクセス関数////////////
	void SetGameObject(GameObject* gameObject) { pGameObject_ = gameObject; }
	void SetAttackType(ColliderAttackType type) { attackType_ = type; }
	void SetCenter(XMFLOAT3 center);
	void SetSize(XMFLOAT3 size);
	void SetRotate(XMFLOAT3 rotate);

	ColliderAttackType GetAttackType() { return attackType_; }
	XMVECTOR GetDirect(int elem) { return directionNormalVec_[elem]; }   // 指定軸番号の方向ベクトルを取得
	float GetLen(int elem) { return length_[elem]; }          // 指定軸方向の長さを取得
	XMVECTOR GetCenter() { return center_; }             // 中心を取得

};

