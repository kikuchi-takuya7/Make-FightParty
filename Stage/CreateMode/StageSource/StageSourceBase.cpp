#include "StageSourceBase.h"

StageSourceBase::StageSourceBase(GameObject* parent, std::string name)
	:GameObject(parent,name), hModel_(-1)
{
}

StageSourceBase::~StageSourceBase()
{
}

void StageSourceBase::Initialize()
{
	ChildInitialize();
}

void StageSourceBase::Update()
{
	ChildUpdate();
}

void StageSourceBase::Draw()
{
	ChildDraw();
}

void StageSourceBase::Release()
{
	ChildRelease();
}
