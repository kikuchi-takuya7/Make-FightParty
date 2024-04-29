#include "RotateBlade.h"
#include "../../../Engine/BoxCollider.h"

namespace {

	const int COST = -1;

	//�����蔻��̑傫��
	const XMFLOAT3 BLADE_CENTER = XMFLOAT3(ZERO, 0.5f, 0.5f);
	const XMFLOAT3 BLADE_SIZE = XMFLOAT3(0.5f, 0.5f, 1.5f);

	//�U����
	const int BLADE_POWER = 10;

	//��]����X�s�[�h
	const float ROT_SPEED = 0.5f;



}

RotateBlade::RotateBlade(GameObject* parent)
	:StageSourceBase(parent, "RotateBlade")
{
}

RotateBlade::~RotateBlade()
{
}

void RotateBlade::ChildInitialize()
{

	cost_ = COST;

	attackPower_ = BLADE_POWER;

	AddCollider(pBoxCollision_, COLLIDER_BROCK);

	BoxCollider* bladeCollision = new BoxCollider(BLADE_CENTER, BLADE_SIZE, ZERO_FLOAT3);
	AddCollider(bladeCollision, COLLIDER_OBJ_ATTACK);

}

void RotateBlade::ChildUpdate()
{
	transform_.rotate_.y += ROT_SPEED;
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
