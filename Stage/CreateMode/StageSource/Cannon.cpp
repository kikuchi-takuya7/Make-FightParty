#include "Cannon.h"
#include "../../../Character/Character.h"
#include "../../../Engine/Timer.h"


namespace {
	const int COST = -1;

	const XMFLOAT3 BULLET_COLLISION_CENTER = XMFLOAT3(ZERO, 0.7f, ZERO);
	const float BULLET_COLLISION_SIZE = 1.0f;
	const float BULLET_INTERVAL = 1.5f;
}

Cannon::Cannon(GameObject* parent)
	:StageSourceBase(parent, "Cannon"), pBulletCollider_(nullptr), timer_(Instantiate<Timer>(this))
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

	pBulletCollider_ = new SphereCollider(BULLET_COLLISION_CENTER, BULLET_COLLISION_SIZE);

	timer_->SetLimit(BULLET_INTERVAL);
	
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
