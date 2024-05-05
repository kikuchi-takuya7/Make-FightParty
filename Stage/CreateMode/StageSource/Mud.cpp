#include "Mud.h"
#include "../../../Engine/CsvReader.h"

namespace {

	const int COST = 5;

	const float DECELERATION_RATE = 0.5f;

}

Mud::Mud(GameObject* parent)
	:StageSourceBase(parent, "Mud")
{
}

Mud::~Mud()
{
}

void Mud::ChildInitialize()
{

	cost_ = COST;

	deceleration_Rate_ = DECELERATION_RATE;

	AddCollider(pBoxCollision_, COLLIDER_MUD);
}

void Mud::ChildUpdate()
{
}

void Mud::ChildDraw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Mud::ChildRelease()
{
}

void Mud::OnCollision(GameObject* pTarget)
{
}

void Mud::SetObjCsv(CsvReader* csv, int csvPos)
{
	//CSV‚ÌˆÊ’u‚É‰ž‚¶‚Äî•ñ‚ðŠl“¾
	deceleration_Rate_ = csv->GetValueFloat(csvPos, 6);
}
