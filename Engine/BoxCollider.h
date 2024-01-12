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

	/// <summary>
	/// コンストラクタ（当たり判定の作成）
	/// </summary>
	/// <param name="basePos">当たり判定の中心位置（ゲームオブジェクトの原点から見た位置）</param>
	/// <param name="size">当たり判定のサイズ（幅、高さ、奥行き）</param>
	/// <param name="rotate">centerから回転させる角度</param>
	BoxCollider(XMFLOAT3 basePos, XMFLOAT3 size, XMFLOAT3 rotate);

private:
	//接触判定
	//引数：target	相手の当たり判定
	//戻値：接触してればtrue
	bool IsHit(Collider* target) override;

	
};

