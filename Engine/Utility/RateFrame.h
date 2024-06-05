#pragma once
#include <cmath>
#include <DirectXMath.h>
#include <vector>
#include <map>
#include <string>

using std::string;
using std::map;

/// <summary>
/// 線形補完用の値等を管理するクラス
/// </summary>
namespace RateFrame
{

	/// <summary>
	/// フレーム等のデータ
	/// </summary>
	struct RateData {

		//1フレーム辺りの増加値
		float rate;

		//現在のフレーム
		float frame;

		//値を更新するか
		bool isUpdate;

		RateData() {
			rate = 0.0f;
			frame = 0.0f;
			isUpdate = false;
		}

		RateData(int r, bool is) {
			rate = r;
			frame = 0.0f;
			isUpdate = is;
		}

	};

	//線形補間するための情報を保存
	extern map<string, RateData> data;

	/// <summary>
	/// 線形補間する為の値をセットする
	/// </summary>
	/// <param name="s">保存したいデータの名前</param>
	/// <param name="rate">1フレーム毎に増加させる値(０～１)</param>
	/// <param name="isUpdate">値を更新するか否か</param>
	void SetData(string s, float rate, bool isUpdate);

	/// <summary>
	/// 更新するかどうかを設定する
	/// </summary>
	/// <param name="s">変更したいデータの名前</param>
	/// <param name="isUpdate">更新するか否か</param>
	void SetFlag(string s, bool isUpdate);

	/// <summary>
	/// 指定したデータの現在のフレームを獲得
	/// </summary>
	/// <param name="s">欲しいフレームを格納してるデータの名前</param>
	float GetNowFrame(string s);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 個別の解放処理
	/// </summary>
	/// <param name="s">解放したいdata</param>
	void Release(string s);

	/// <summary>
	/// 解放処理
	/// </summary>
	void Release();

};

