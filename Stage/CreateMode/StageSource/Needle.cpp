#include "Needle.h"

namespace {

	const int COST = 5;
	const int NEEDLEPOWER = 1;

}

Needle::Needle(GameObject* parent)
	:StageSourceBase(parent, "Needle")
{
}

Needle::~Needle()
{
}

void Needle::ChildInitialize()
{

	//モデルのロードはCreateModeで全部終わらせちゃってるから、ここではしなくていい？逆にここですべき？
	cost_ = COST;

	needlePower_ = NEEDLEPOWER;

	AddCollider(pBoxCollision_, COLLIDER_OBSTRYCTION);
}

void Needle::ChildUpdate()
{
}

void Needle::ChildDraw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Needle::ChildRelease()
{
}

void Needle::OnCollision(GameObject* pTarget)
{
}
