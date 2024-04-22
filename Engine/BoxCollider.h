#pragma once
#include "Collider.h"


//-----------------------------------------------------------
//箱型の当たり判定
//-----------------------------------------------------------
class BoxCollider :	public Collider
{
	//Colliderクラスのprivateメンバにアクセスできるようにする
	friend class Collider;

public:
	//コンストラクタ（当たり判定の作成）
	//引数：center	当たり判定の中心位置（ゲームオブジェクトの原点から見た位置）
	//引数：size	当たり判定のサイズ（幅、高さ、奥行き）直径
	//引数：rotate	当たり判定を回転させる角度（まだ回ってない）
	BoxCollider(XMFLOAT3 center, XMFLOAT3 size, XMFLOAT3 rotate);

	~BoxCollider();

private:
	//接触判定
	//引数：target	相手の当たり判定
	//戻値：接触してればtrue
	bool IsHit(Collider* target) override;
};

