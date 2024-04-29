#include "Mud.h"

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
