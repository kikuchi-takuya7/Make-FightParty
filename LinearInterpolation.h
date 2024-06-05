#pragma once
#include <cmath>
#include <DirectXMath.h>
#include <vector>
#include <map>
#include <string>

using std::string;
using std::map;

/// <summary>
/// フレーム等のデータ
/// </summary>
struct RateData {

	//1フレーム辺りの増加値
	float rate;

	//現在のフレーム
	float flame;

	//値を更新するか
	bool isUpdate;

	RateData() {
		rate = 0.0f;
		flame = 0.0f;
		isUpdate = false;
	}

	RateData(int r , bool is) {
		rate = r;
		flame = 0.0f;
		isUpdate = is;
	}

};

namespace LinearInterpolation
{
	//線形補間するための情報を保存
	map<string, RateData> mp;

	/// <summary>
	/// 線形補間する為の値をセットする
	/// </summary>
	/// <param name="s">保存したいデータの名前</param>
	/// <param name="rate">1フレーム毎に増加させる値(０～１)</param>
	/// <param name="isUpdate">値を更新するか否か</param>
	void SetData(string s, float rate, bool isUpdate) { mp.insert(std::make_pair(s, RateData(rate, isUpdate))); }

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 解放処理
	/// </summary>
	/// <param name="s">解放したい</param>
	void Release(string s);

};

