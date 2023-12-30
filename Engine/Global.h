#pragma once
#include "Direct3D.h"

//安全にメモリを開放するためのマクロ
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}



//0の定数
#define ZERO 0.0f



////////関数///////////

//XMFLOAT3型2つを足し算する
XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
}

//XMFLOAT3型2つを引き算する
XMFLOAT3 Float3Sub(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
}

//XMVECTOR型の長さ(X)をfloatで出してくれる
float Length(XMVECTOR v) {
	XMVECTOR lenVec = XMVector3Length(v);
	return XMVectorGetX(lenVec);
}

//XMVECTORの変数をXMFLOAT3に変えて返してくれる
static XMFLOAT3 VectorToFloat3(XMVECTOR v)
{
	XMFLOAT3 a;
	XMStoreFloat3(&a, v);

	return a;
}

XMFLOAT3 operator + (const XMFLOAT3& v1, const XMVECTOR& v2) {

	XMVECTOR pv = XMLoadFloat3(&v1);
	pv += v2;
	XMFLOAT3 out;
	XMStoreFloat3(&out, pv);
	return out;
}

XMFLOAT3 operator + (const XMFLOAT3& f1, const XMFLOAT3& f2) {

	return XMFLOAT3(f1.x + f2.x, f1.y + f2.y, f1.z + f2.z);
}

XMVECTOR operator -(const XMFLOAT3& p1, const XMFLOAT3& p2) {
	XMVECTOR p1v = XMLoadFloat3(&p1);
	XMVECTOR p2v = XMLoadFloat3(&p2);
	return p1v - p2v;
}

XMVECTOR operator -(const XMFLOAT3& p1, const XMVECTOR& p2) {
	XMVECTOR p1v = XMLoadFloat3(&p1);
	return p1v - p2;
}

bool operator ==(const XMFLOAT3& f1, const XMFLOAT3& f2) {

	bool ans = false;

	if (f1.x == f2.x && f1.y == f2.y && f1.z == f2.z) {
		ans = true;
	}

	return ans;
}
