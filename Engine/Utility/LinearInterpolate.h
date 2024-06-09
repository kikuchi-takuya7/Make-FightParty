#pragma once
#include <DirectXMath.h>
#include "../Direct3D.h"

namespace LinearInterpolate {

	/// <summary>
	/// 線形補間を使い現在の値を求める関数
	/// </summary>
	/// <param name="begin">はじめの値</param>
	/// <param name="end">終わりの値</param>
	/// <param name="rate">レート(0～1)</param>
	/// <returns></returns>
	float GetRateValue(float begin, float end, float rate);

	/// <summary>
	/// レートに沿って滑らかに移動させる関数(positionを更新し続けるなら定数で等速直線運動になる)
	/// </summary>
	/// <param name="position">現在の座標</param>
	/// <param name="lastPos">最終の座標</param>
	/// <param name="moveRate">現在のレート値(0～1)</param>
	/// <returns>移動後の値</returns>
	XMFLOAT3 RateMovePosition(XMFLOAT3 position, XMFLOAT3 lastPos, float moveRate);
}