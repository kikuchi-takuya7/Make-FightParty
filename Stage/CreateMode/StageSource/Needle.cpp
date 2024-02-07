#include "Needle.h"

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
