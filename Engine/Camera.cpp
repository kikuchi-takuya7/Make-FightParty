#include "Camera.h"
#include "Direct3D.h"
#include "Global.h"

namespace Camera {
	//変数
	XMVECTOR position_;	//カメラの位置（視点）
	XMVECTOR target_;	//見る位置（焦点）
	XMMATRIX viewMatrix_;	//ビュー行列
	XMMATRIX projMatrix_;	//プロジェクション行列
	XMMATRIX billBoard_;
	float	 camMoveRate_;	//カメラの移動レート
	bool	 isEnter_;		//最初だけEnterを呼び出す為の変数
}

//初期化
void Camera::Initialize()
{
	position_ = XMVectorSet(0, 3, -10, 0);	//カメラの位置
	target_ = XMVectorSet(0, 0, 0, 0);	//カメラの焦点

	//プロジェクション行列
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);

	camMoveRate_ = ZERO;
	isEnter_ = true;
}

//更新
void Camera::Update()
{
	//ビュー行列の作成
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
	/*XMFLOAT3 position;
	XMStoreFloat3(&position, position_);
	XMFLOAT3 target;
	XMStoreFloat3(&target, target_);
	viewMatrix_ = XMMatrixLookAtLH(XMVectorSet(position.x, position.y, position.z, 0),
	XMVectorSet(target.x, target.y, target.z, 0), XMVectorSet(0, 1, 0, 0));*/

	//ビルボード行列
	//（常にカメラの方を向くように回転させる行列。パーティクルでしか使わない）
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	billBoard_ = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), target_ - position_, XMVectorSet(0, 1, 0, 0));
	billBoard_ = XMMatrixInverse(nullptr, billBoard_);
}

//位置を設定
void Camera::SetPosition(XMVECTOR position)
{
	position_ = position;
}

void Camera::SetPosition(XMFLOAT3 position)
{
	SetPosition(XMLoadFloat3(&position));
}

//焦点を設定
void Camera::SetTarget(XMVECTOR target)
{
	target_ = target;
}

void Camera::SetTarget(XMFLOAT3 target)
{
	SetTarget(XMLoadFloat3(&target));
}

//位置を取得
XMFLOAT3 Camera::GetPosition() 
{ 
	XMFLOAT3 f;

	XMStoreFloat3(&f, position_);
	return f;
}

//焦点を取得
XMFLOAT3 Camera::GetTarget()
{
	XMFLOAT3 f;

	XMStoreFloat3(&f, target_);
	return f;
}

XMVECTOR Camera::GetPositionVector()
{
	return position_;
}

XMVECTOR Camera::GetTargetVector()
{
	return target_;
}


//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix()
{
	//return XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
	return viewMatrix_;
}

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix()
{
	//return XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);
	return projMatrix_;
}

//ビルボード用回転行列を取得
XMMATRIX Camera::GetBillboardMatrix() 
{
	return billBoard_; 
}

//3D座標を画面上の2D座標に合わせる
//引数：3次元座標
XMFLOAT3 Camera::GetScreenPosition(XMFLOAT3 pos3d)
{
	XMVECTOR v2 = XMVector3Transform(XMLoadFloat3(&pos3d), Camera::GetViewMatrix());
	v2 = XMVector3Transform(v2, Camera::GetProjectionMatrix());
	float x = XMVectorGetX(v2);
	float y = XMVectorGetY(v2);
	float z = XMVectorGetZ(v2);
	return XMFLOAT3(
		x / z * Direct3D::screenWidth_ / 2.0f + Direct3D::screenWidth_ / 2.0f,
		-y / z * Direct3D::screenHeight_ / 2.0f + Direct3D::screenHeight_ / 2.0f,
		0);
}

//MoveCam用変数の初期化
void Camera::MoveCamEnter()
{
	camMoveRate_ = ZERO;
	isEnter_ = false;
}

//カメラを滑らかに移動させる
bool Camera::MoveCam(XMFLOAT3 lastPos, XMFLOAT3 lastTar, float moveRate)
{

	/*if (isEnter_)
		MoveCamEnter();*/

	//カメラの位置と見る地点を徐々に変える
	XMFLOAT3 nowCamPos = Camera::GetPosition();
	XMFLOAT3 nowCamTar = Camera::GetTarget();

	//レートでぬるぬる動くように
	if (camMoveRate_ < 1.0f) {
		camMoveRate_ += moveRate;

		// 変な数字で止まらないように
		if (camMoveRate_ > 1.0f)
			camMoveRate_ = 1.0f;

		//ターゲットとポジションが同じだとエラー起きるから注意

		nowCamPos.x = GetRateValue(nowCamPos.x, lastPos.x, camMoveRate_);
		nowCamPos.y = GetRateValue(nowCamPos.y, lastPos.y, camMoveRate_);
		nowCamPos.z = GetRateValue(nowCamPos.z, lastPos.z, camMoveRate_);

		Camera::SetPosition(nowCamPos);

		nowCamTar.x = GetRateValue(nowCamTar.x, lastTar.x, camMoveRate_);
		nowCamTar.y = GetRateValue(nowCamTar.y, lastTar.y, camMoveRate_);
		nowCamTar.z = GetRateValue(nowCamTar.z, lastTar.z, camMoveRate_);

		Camera::SetTarget(nowCamTar);
	}

	//目標地点に着いたら、変数を初期化しておしまい
	if (lastPos == nowCamPos && lastTar == nowCamTar) {
		camMoveRate_ = ZERO;
		isEnter_ = false;
		return true;
	}

	return false;
}


float Camera::GetRateValue(float begin, float end, float rate)
{
	return (end - begin) * rate + begin;
}