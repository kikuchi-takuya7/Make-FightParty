#include "StageSourceBase.h"
#include "../../../Engine/Utility/LinearInterpolate.h"
#include "../../../Engine/Utility/RateFrame.h"

namespace {
	const XMFLOAT3 BOX_COLLISION_CENTER = XMFLOAT3(ZERO, 0.5f, ZERO);
	const XMFLOAT3 BOX_COLLISION_SIZE = XMFLOAT3(0.5f, 0.5f, 0.5f);

	const float MOVE_SPEED = 0.05f;
}

StageSourceBase::StageSourceBase(GameObject* parent, std::string name)
	:GameObject(parent,name), hModel_(-1),attackPower_(ZERO), pBoxCollision_(nullptr),rate_(Instantiate<RateFrame>(this))
{
}

StageSourceBase::~StageSourceBase()
{
}

void StageSourceBase::Initialize()
{
	//�u���b�N�{�̂̓����蔻��p
	pBoxCollision_ = new BoxCollider(BOX_COLLISION_CENTER, BOX_COLLISION_SIZE, ZERO_FLOAT3);
	
	rate_->SetData(MOVE_SPEED, true, ACCELERATION);

	ChildInitialize();
}

void StageSourceBase::Update()
{
	//�ݒ肳�ꂽ�ʒu�܂ňړ�������
	transform_.position_ = LinearInterpolate::RateMovePosition(transform_.position_, lastPos_, MOVE_SPEED);

	//�X�V���������邩�ǂ���
	if (IsEntered()) {
		ChildUpdate();
	}

	
}

void StageSourceBase::Draw()
{
	ChildDraw();

#ifdef _DEBUG
	CollisionDraw();
#endif

}

void StageSourceBase::Release()
{
	ChildRelease();
}