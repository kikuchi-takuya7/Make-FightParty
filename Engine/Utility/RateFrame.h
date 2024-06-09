#pragma once
#include <cmath>
#include <DirectXMath.h>
#include <vector>
#include "../../Engine/GameObject.h"

using std::string;

//どのように値を増やすかの種類
enum ADDTYPE {
	CONSTANT,		//等速（a）
	ACCELERATION	//加速（a+a）
};

/// <summary>
/// 0～1までの値を管理するクラス
/// </summary>
class RateFrame : public GameObject
{
public:

	//コンストラクタ
	RateFrame(GameObject* parent);
	//デストラクタ
	~RateFrame();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 解放処理
	/// </summary>
	void Release() override;

	/// <summary>
	/// レートをリセットする
	/// </summary>
	void Reset();


	///////////////////////アクセス関数///////////////////////

	/// <summary>
	/// 線形補間する為の値をセットする
	/// </summary>
	/// <param name="rate">1フレーム毎に増加させる値(０～１)</param>
	/// <param name="isUpdate">値を更新するか否か</param>
	/// <param name="type">値を追加するパターン</param>
	void SetData(float rate, bool isUpdate, ADDTYPE type);

	/// <summary>
	/// 1フレーム毎に増加させる値(０～１)をセットする
	/// </summary>
	/// <param name="rate">どのくらい増加させるか</param>
	void SetRate(float rate);

	/// <summary>
	/// 更新するかどうかのフラグを設定する
	/// </summary>
	/// <param name="isUpdate">更新するか否か</param>
	void SetFlag(bool isUpdate);

	/// <summary>
	/// 指定したデータの現在のフレームを獲得
	/// </summary>
	float GetNowFrame();

private:

	//1フレーム辺りの増加値
	float rate_;

	//リセット用のrate_値
	float startRate_;

	//現在のフレーム
	float frame_;

	//値を更新するか
	bool isUpdate_;

	//値を増やすパターン
	ADDTYPE type_;

};

