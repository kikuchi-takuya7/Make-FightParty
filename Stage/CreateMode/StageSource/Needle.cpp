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

	//���f���̃��[�h��CreateMode�őS���I��点������Ă邩��A�����ł͂��Ȃ��Ă����H�t�ɂ����ł��ׂ��H

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
