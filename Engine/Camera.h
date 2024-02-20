#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//カメラ
//-----------------------------------------------------------
namespace Camera
{
	//初期化（プロジェクション行列作成）
	void Initialize();

	//更新（ビュー行列作成）
	void Update();

	//視点（カメラの位置）を設定
	void SetPosition(XMVECTOR position);
	void SetPosition(XMFLOAT3 position);

	//焦点（見る位置）を設定
	void SetTarget(XMVECTOR target);
	void SetTarget(XMFLOAT3 target);

	//位置を取得
	XMFLOAT3 GetPosition();

	//焦点を取得
	XMFLOAT3 GetTarget();

	//位置を取得
	XMVECTOR GetPositionVector();

	//焦点を取得
	XMVECTOR GetTargetVector();
	
	//ビュー行列を取得
	XMMATRIX GetViewMatrix();

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix();

	//ビルボード用回転行列を取得
	XMMATRIX GetBillboardMatrix();

	/// <summary>
	/// 3次元座標を２次元座標に変換する
	/// </summary>
	/// <param name="pos3d">3D座標</param>
	/// <returns>2D座標</returns>
	XMFLOAT3 GetScreenPosition(XMFLOAT3 pos3d);

	/// <summary>
	/// MoveCamの変数を初期化させる
	/// </summary>
	void MoveCamEnter();

	/// <summary>
	/// カメラを滑らかに移動させる
	/// </summary>
	/// <param name="lastPos">最終的なカメラポジション</param>
	/// <param name="lastTar">最終的なカメラターゲット</param>
	/// <param name="moveRate">どのぐらい滑らかに移動させるか(最大1.0f)</param>
	/// <returns>移動し終わったらtrue</returns>
	bool MoveCam(XMFLOAT3 lastPos, XMFLOAT3 lastTar, float moveRate);

	float GetRateValue(float begin, float end, float rate);

};