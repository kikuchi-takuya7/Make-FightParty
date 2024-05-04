#include "Cannon.h"
#include "../../../Character/Character.h"
#include "../../../Engine/Timer.h"
#include "../../../Engine/VFX.h"
#include "../../../Engine/Audio.h"
#include "../../../VFXData/VFXData.h"
#include "Bullet.h"

//定数宣言
namespace {
	const int COST = -1;

	const XMFLOAT3 BULLET_COLLISION_CENTER = XMFLOAT3(ZERO, ZERO, ZERO);
	const float BULLET_COLLISION_SIZE = 0.3f;
	const float BULLET_INTERVAL = 3.0f;
	const float BULLET_SIZE = 0.3f;

	const int BULLET_ATTACK_POWER = 20;
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

	cost_ = COST;

	AddCollider(pBoxCollision_, COLLIDER_BROCK);

	hAudio_ = Audio::Load("Audio/SE/Cannon.wav", false,3);
	Audio::Stop(hAudio_);

	//球を打つ間隔
	timer_->SetLimit(BULLET_INTERVAL);
	
}

void Cannon::ChildUpdate()
{

	timer_->Start();

	//内部タイマーが0になったら打ち、またリセットする
	if (timer_->IsFinished()) {
		Bullet* pBullet = Instantiate<Bullet>(GetParent());
		pBullet->SetScale(BULLET_SIZE);
		pBullet->SetPosition(transform_.position_);
		
		//球の当たり判定を作る
		SphereCollider* pBulletCollider = new SphereCollider(BULLET_COLLISION_CENTER, BULLET_COLLISION_SIZE);
		pBullet->SetBulletData(pBulletCollider, COLLIDER_BULLET, BULLET_ATTACK_POWER, BULLET_SPEED, transform_.rotate_.y);
		timer_->Reset();
		timer_->Start();
		FiringEffect();
		Audio::Play(hAudio_);
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

	using namespace FiringEffect;

	data.textureFileName = FILENAME;
	data.position = transform_.position_;
	data.positionRnd = POSITIONRND;
	data.direction = DIRECTION;
	data.directionRnd = DIRECTIONRND;
	data.speed = SPEED;
	data.speedRnd = SPEEDRND;
	data.accel = FiringEffect::ACCEL;
	data.gravity = GRAVITY;
	data.color = COLOR;
	data.deltaColor = DELTACOLOR;
	data.rotate = ROTATE;
	data.rotateRnd = ROTATERND;
	data.spin = SPIN;
	data.size = FiringEffect::SIZE;
	data.sizeRnd = SIZERND;
	data.scale = SCALE;
	data.lifeTime = LIFETIME;
	data.delay = DELAY;
	data.number = NUMBER;
	data.isBillBoard = ISBILLBOARD;

	VFX::Start(data);
}
