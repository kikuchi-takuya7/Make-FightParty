#include "RotateBlade.h"
#include "../../../Engine/BoxCollider.h"
#include "../../../Engine/CsvReader.h"

namespace {

	const int COST = -1;

	//“–‚½‚è”»’è‚Ì‘å‚«‚³
	const XMFLOAT3 BLADE_CENTER = XMFLOAT3(ZERO, 0.5f, 0.5f);
	const XMFLOAT3 BLADE_SIZE = XMFLOAT3(0.5f, 0.5f, 1.5f);

	//UŒ‚—Í
	const int BLADE_POWER = 10;

	//‰ñ“]‚·‚éƒXƒs[ƒh
	const float ROT_SPEED = 0.5f;



}

RotateBlade::RotateBlade(GameObject* parent)
	:StageSourceBase(parent, "RotateBlade"),rotSpeed_(ZERO)
{
}

RotateBlade::~RotateBlade()
{
}

void RotateBlade::ChildInitialize()
{

	cost_ = COST;

	attackPower_ = BLADE_POWER;
	rotSpeed_ = ROT_SPEED;

	AddCollider(pBoxCollision_, COLLIDER_BROCK);

	BoxCollider* bladeCollision = new BoxCollider(BLADE_CENTER, BLADE_SIZE, ZERO_FLOAT3);
	AddCollider(bladeCollision, COLLIDER_OBJ_ATTACK);

}

void RotateBlade::ChildUpdate()
{
	transform_.rotate_.y += rotSpeed_;
}

void RotateBlade::ChildDraw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void RotateBlade::ChildRelease()
{
}

void RotateBlade::OnCollision(GameObject* pTarget)
{
}

void RotateBlade::SetObjCsv(CsvReader* csv, int csvPos)
{
	attackPower_ = csv->GetValueInt(csvPos, 1);
	rotSpeed_ = csv->GetValueFloat(csvPos, 7);
}
