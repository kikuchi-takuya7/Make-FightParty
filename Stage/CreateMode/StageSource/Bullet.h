#pragma once
#include "../../../Engine/GameObject.h"
#include "StageSourceBase.h"

/// <summary>
/// Cannonクラス等が使う球のクラス。当たり判定の大きさ等はそれぞれの親クラスで指定してもらう
/// </summary>
class Bullet : public GameObject
{
public:

	//コンストラクタ
	Bullet(GameObject* parent);
	~Bullet();


	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;

	/// <summary>
	/// 大砲の情報をセット
	/// </summary>
	/// <param name="collider">球の当たり判定</param>
	/// <param name="type">コライダーのタイプ</param>
	/// <param name="attackPower">大砲の攻撃力</param>
	/// <param name="speed">球のスピード</param>
	/// <param name="rotY">球を発射した時のオブジェクトの角度</param>
	void SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed, float rotY);


	//アクセス関数
	int GetBulletPower() { return attackPower_; }
	int GetAuthorID() { return authorID_; }
	void SetAuthorID(int id) { authorID_ = id; }


private:

	//移動した距離
	float moveLen_;

	//モデル番号
	int bulletModel_;
	
	//球のスピード
	float bulletSpeed_;

	//発射された時の大砲の角度
	float startRotateY_;

	//球の攻撃力
	int attackPower_;

	//このオブジェクトを生成したプレイヤーのID
	int authorID_;

	//球が発射する向きのベクトル
	XMVECTOR forwardVec_;

	//砲台の判定から独立させるための変数
	Transform bulletTrans_;

	SphereCollider* collider_;



};