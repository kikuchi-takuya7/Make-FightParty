#include "EasingFunction.h"

namespace LinearInterpolate {

	/// <summary>
	/// 線形補間を使い現在の値を求める関数
	/// </summary>
	/// <param name="begin">はじめの値</param>
	/// <param name="end">終わりの値</param>
	/// <param name="rate">レート(0～1)</param>
	/// <returns></returns>
	float GetRateValue(float begin, float end, float rate)
	{
		//1以上なら1に戻す.RateFrameクラスを使ってレートを管理してたらいらないから必要ないかも？
		if (rate > 1.0f) {
			rate = 1.0f;
		}
		return (end - begin) * rate + begin;
	}

	/// <summary>
	/// レートに沿って滑らかに移動させる関数
	/// </summary>
	/// <param name="position">現在の座標</param>
	/// <param name="lastPos">最終の座標</param>
	/// <param name="moveRate">現在のレート値(0～1)</param>
	/// <returns>移動後の値</returns>
	XMFLOAT3 RateMovePosition(XMFLOAT3 position, XMFLOAT3 lastPos, float moveRate)
	{
		position.x = GetRateValue(position.x, lastPos.x, moveRate);
		position.y = GetRateValue(position.y, lastPos.y, moveRate);
		position.z = GetRateValue(position.z, lastPos.z, moveRate);

		return position;
	}
}