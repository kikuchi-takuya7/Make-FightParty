#pragma once
#include "../../../Engine/GameObject.h"


/// <summary>
/// Cannonクラス等が使う球のクラス。当たり判定の大きさ等はそれぞれの親クラスで指定してもらう
/// </summary>
class Bullet : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
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

	void SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed);

	void SetStartRot(float rotY) { startRotateY_ = rotY; }
	
	int GetAttackPower() { return attackPower_; }

private:

	//移動した距離
	float moveLen_;

	//モデル番号
	int bulletModel_;

	//攻撃力
	int attackPower_;
	
	//球のスピード
	float bulletSpeed_;

	//発射された時の大砲の角度
	float startRotateY_;

	//砲台の判定から独立させるための変数
	Transform bulletTrans_;

	SphereCollider* collider_;



};