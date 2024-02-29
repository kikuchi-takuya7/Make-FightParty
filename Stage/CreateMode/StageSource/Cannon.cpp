#include "Cannon.h"
#include "../../../Character/Character.h"
#include "../../../Engine/Timer.h"
#include "../../../Engine/VFX.h"
#include "Bullet.h"

namespace {
	const int COST = -1;

	const XMFLOAT3 BULLET_COLLISION_CENTER = XMFLOAT3(ZERO, ZERO, ZERO);
	const float BULLET_COLLISION_SIZE = 0.3f;
	const float BULLET_INTERVAL = 3;
	const float BULLET_SIZE = 0.3f;

	const int BULLET_ATTACK_POWER = 10;
	const float BULLET_SPEED = 0.4f;
}

Cannon::Cannon(GameObject* parent)
	:StageSourceBase(parent, "Cannon"), timer_(Instantiate<Timer>(this))
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

	

	//球を打つ間隔
	timer_->SetLimit(BULLET_INTERVAL);
	
}

void Cannon::ChildUpdate()
{

	timer_->Start();

	//内部タイマーが0になったら打ち、またリセットする
	if (timer_->IsFinished()) {
		Bullet* pBullet = Instantiate<Bullet>(this);
		pBullet->SetScale(BULLET_SIZE);
		
		//球の当たり判定を作る
		SphereCollider* pBulletCollider = new SphereCollider(BULLET_COLLISION_CENTER, BULLET_COLLISION_SIZE);
		pBullet->SetBulletData(pBulletCollider, COLLIDER_BULLET, BULLET_ATTACK_POWER, BULLET_SPEED);
		timer_->Reset();
		timer_->Start();
		FiringEffect();
	}

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

void Cannon::FiringEffect()
{
	EmitterData data;

	data.textureFileName = "VFX/cloudA.png";
	data.position = XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z);
	data.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	data.delay = 5;
	data.number = 1;
	data.lifeTime = 30;
	data.direction = XMFLOAT3(0, 1, 0);
	data.directionRnd = XMFLOAT3(0, 0, 0);
	data.speed = 0.1f;
	data.accel = 0.98;
	data.speedRnd = 0.0;
	data.size = XMFLOAT2(2, 2);
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.01, 1.01);
	data.color = XMFLOAT4(1, 1, 1, 0.2);
	data.deltaColor = XMFLOAT4(0, 0, 0, -0.002);
	data.spin.z = 0.1;
	data.rotateRnd.z = 180;
	VFX::Start(data);
}
