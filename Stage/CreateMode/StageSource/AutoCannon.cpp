#include "AutoCannon.h"
#include "../../../Character/Character.h"
#include "../../../Engine/Timer.h"
#include "../../../Engine/VFX.h"
#include "../../../Engine/Audio.h"
#include "../../../Engine/CsvReader.h"
#include "../../../AI/MetaAI.h"
#include "../../../AI/NavigationAI.h"
#include "../../../VFXData/VFXData.h"
#include "Bullet.h"

//�萔�錾
namespace {
	const int COST = -1;

	const int MAX_PLAYER = 4;

	const XMFLOAT3 BULLET_COLLISION_CENTER = XMFLOAT3(ZERO, ZERO, ZERO);
	const float BULLET_COLLISION_SIZE = 0.3f;
	const float BULLET_INTERVAL = 7.0f;
	const float BULLET_SIZE = 0.3f;

	const int BULLET_ATTACK_POWER = 5;
	const float BULLET_SPEED = 0.05f;

	const int SAME_SOUND = 3;
}

AutoCannon::AutoCannon(GameObject* parent)
	:StageSourceBase(parent, "AutoCannon"), timer_(Instantiate<Timer>(this)), pMetaAI_(nullptr),pNavigationAI_(nullptr),target_(ZERO)
{
}

AutoCannon::~AutoCannon()
{
}

void AutoCannon::ChildInitialize()
{


	cost_ = COST;

	AddCollider(pBoxCollision_, COLLIDER_BROCK);

	hAudio_ = Audio::Load("Audio/SE/Cannon.wav", false, SAME_SOUND);
	Audio::Stop(hAudio_);

	//�J�n���͐ݒu�����v���C���[�ȊO�������_���ő_���悤�ɂ���B
	while (true)
	{
		target_ = rand() % MAX_PLAYER;
		if (target_ != authorID_) {
			break;
		}
	}
	

}

void AutoCannon::ChildUpdate()
{

	//�_���Ă���G������ł�����^�[�Q�b�g��ς���
	if (pNavigationAI_->GetCaracter(target_)->GetStatus().dead == true) {
		target_ = pMetaAI_->Targeting(authorID_).ID;
	}

	timer_->Start();

	//�����^�C�}�[��0�ɂȂ�����ł��A�܂����Z�b�g����
	if (timer_->IsFinished()) {
		Bullet* pBullet = Instantiate<Bullet>(GetParent());
		pBullet->SetScale(bulletData_.size_);
		pBullet->SetPosition(transform_.position_);
		pBullet->SetAuthorID(authorID_);

		//���̓����蔻������
		SphereCollider* pBulletCollider = new SphereCollider(BULLET_COLLISION_CENTER, bulletData_.size_);
		pBullet->SetBulletData(pBulletCollider, COLLIDER_BULLET, bulletData_.power_, bulletData_.speed_, transform_.rotate_.y);
		timer_->Reset();
		timer_->Start();
		FiringEffect();
		Audio::Play(hAudio_);
	}


	//�_���Ă���G�ɑ�C����]������

	//���_���Ă���G�̍��W��atan2�Ŋl��
	XMFLOAT3 targetPos = pNavigationAI_->GetCaracter(target_)->GetPosition();
	targetPos = Float3Sub(targetPos,transform_.position_);

	//x��z�Ƃ��āAy��z�Ƃ��鎖�ŁAtransform.rotate��0�x��x�������킹�Ċp�x�����̂܂܎g����l��
	float angle = atan2(targetPos.x,targetPos.z);
	float degree = XMConvertToDegrees(angle);

	SetRotateY(degree);

}

void AutoCannon::ChildDraw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void AutoCannon::ChildRelease()
{
}

void AutoCannon::OnCollision(GameObject* pTarget)
{


}

void AutoCannon::SetObjCsv(CsvReader* csv, int csvPos)
{

	//CSV�̈ʒu�ɉ����ď����l��
	bulletData_.power_ = csv->GetValueInt(csvPos, 1);
	bulletData_.speed_ = csv->GetValueFloat(csvPos, 2);
	bulletData_.interval_ = csv->GetValueFloat(csvPos, 3);
	bulletData_.size_ = csv->GetValueFloat(csvPos, 4);

	//����łԊu
	timer_->SetLimit(bulletData_.interval_);
 }

void AutoCannon::FiringEffect()
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
