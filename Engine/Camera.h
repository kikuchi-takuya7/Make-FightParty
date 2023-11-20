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

	XMFLOAT3 GetScreenPosition(XMFLOAT3 pos3d);



};