#pragma once
#include "../../../Engine/GameObject.h"
#include "StageSourceBase.h"

/// <summary>
/// Cannonクラス等が使う球のクラス。当たり判定の大きさ等はそれぞれの親クラスで指定してもらう
/// </summary>
class Bullet : public StageSourceBase
{
public:

	//コンストラクタ
	Bullet(GameObject* parent);
	~Bullet();


	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	//描画
	void ChildDraw() override;

	//開放
	void ChildRelease() override;

	void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;

	void SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed);

	void SetStartRot(float rotY);


private:

	//移動した距離
	float moveLen_;

	//モデル番号
	int bulletModel_;
	
	//球のスピード
	float bulletSpeed_;

	//発射された時の大砲の角度
	float startRotateY_;

	XMVECTOR vec_;

	//砲台の判定から独立させるための変数
	Transform bulletTrans_;

	SphereCollider* collider_;



};