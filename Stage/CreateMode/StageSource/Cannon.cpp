#include "Cannon.h"
#include "../../../Character/Character.h"


namespace {

	const int COST = -1;

}

Cannon::Cannon(GameObject* parent)
	:StageSourceBase(parent, "Cannon")
{
}

Cannon::~Cannon()
{
}

void Cannon::ChildInitialize()
{

	//モデルのロードはCreateModeで全部終わらせちゃってるから、ここではしなくていい？逆にここですべき？
	cost_ = COST;

	AddCollider(pBoxCollision_, COLLIDER_BROCK);
}

void Cannon::ChildUpdate()
{
}

void Cannon::ChildDraw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Cannon::ChildRelease()
{
}

void Cannon::OnCollision(GameObject* pTarget)
{
	

}
