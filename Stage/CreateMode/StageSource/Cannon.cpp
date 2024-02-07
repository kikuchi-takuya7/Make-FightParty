#include "Cannon.h"

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
