#include "StageSourceBase.h"

namespace {
	const XMFLOAT3 BOX_COLLISION_CENTER = XMFLOAT3(ZERO, 0.5f, ZERO);
	const XMFLOAT3 BOX_COLLISION_SIZE = XMFLOAT3(1, 1, 1);

	const float MOVE_SPEED = 0.05f;
}

StageSourceBase::StageSourceBase(GameObject* parent, std::string name)
	:GameObject(parent,name), hModel_(-1), pBoxCollision_(nullptr)
{
}

StageSourceBase::~StageSourceBase()
{
}

void StageSourceBase::Initialize()
{

	pBoxCollision_ = new BoxCollider(BOX_COLLISION_CENTER, BOX_COLLISION_SIZE, ZERO_FLOAT3);
	
	ChildInitialize();
}

void StageSourceBase::Update()
{

	RateMovePosition(transform_.position_, lastPos_, MOVE_SPEED);

	if (IsEntered()) {
		ChildUpdate();
	}

	
}

void StageSourceBase::Draw()
{
	ChildDraw();

	CollisionDraw();

}

void StageSourceBase::Release()
{
	ChildRelease();
}
