#include "AutoCannon.h"
#include "../../../Character/Character.h"
#include "../../../Engine/Timer.h"
#include "../../../Engine/VFX.h"
#include "../../../Engine/Audio.h"
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
	const float BULLET_INTERVAL = 1;
	const float BULLET_SIZE = 0.3f;

	const int BULLET_ATTACK_POWER = 5;
	const float BULLET_SPEED = 0.1f;

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

	//���f���̃��[�h��CreateMode�őS���I��点������Ă邩��A�����ł͂��Ȃ��Ă����H�t�ɂ����ł��ׂ��H
	cost_ = COST;

	AddCollider(pBoxCollision_, COLLIDER_BROCK);

	hAudio_ = Audio::Load("Audio/SE/Cannon.wav", false, SAME_SOUND);
	Audio::Stop(hAudio_);

	//����łԊu
	timer_->SetLimit(BULLET_INTERVAL);

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

	target_ = 0;

	if (pNavigationAI_->GetCaracter(target_)->GetStatus().dead == true) {
		target_ = pMetaAI_->Targeting(authorID_).ID;
	}

	timer_->Start();

	//�����^�C�}�[��0�ɂȂ�����ł��A�܂����Z�b�g����
	if (timer_->IsFinished()) {
		Bullet* pBullet = Instantiate<Bullet>(this);
		pBullet->SetScale(BULLET_SIZE);
		//pBullet->SetPosition(transform_.position_);
		//pBullet->SetStartRot(transform_.rotate_.y);
		//bullet�̒��̃��[���h��rotate��ς���K�v������


		//���̓����蔻������
		SphereCollider* pBulletCollider = new SphereCollider(BULLET_COLLISION_CENTER, BULLET_COLLISION_SIZE);
		pBullet->SetBulletData(pBulletCollider, COLLIDER_BULLET, BULLET_ATTACK_POWER, BULLET_SPEED);
		timer_->Reset();
		timer_->Start();
		FiringEffect();
		Audio::Play(hAudio_);
	}


	//�_���Ă���G�ɑ�C����]������

#if 1 //���߂ɏ㉺���E�ǂ��������Ă鎖���l���������

	//���_���Ă���G�̍��W���l��
	XMFLOAT3 targetPos = pNavigationAI_->GetCaracter(target_)->GetPosition();
	XMVECTOR targetVec = XMVector3Normalize(XMLoadFloat3(&targetPos));
	
	//XMVECTOR myVec = XMVector3Normalize(XMLoadFloat3(&transform_.position_));
	//XMVECTOR rotVec = XMVector3Normalize(targetVec - myVec);

	//�O�x�N�g���������Ă�������ɕϊ����āA���K��
	XMVECTOR vFront = { 0,0,1,0 };

	//���ς���p�x�����߂�
	XMVECTOR vDot = XMVector3Dot(vFront, targetVec);
	float dot = XMVectorGetX(vDot);
	float angle = acos(dot);

	//�O�ς�-�ɂȂ�p�x�Ȃ�
	XMVECTOR vCross = XMVector3Cross(vFront, targetVec);
	if (XMVectorGetY(vCross) < ZERO) {

		angle *= -1;
	}

	float degree = XMConvertToDegrees(angle);

	SetRotateY(degree);

	//transform_.rotate_.y += degree;

#else //�f�t�H���g���O�����Ă���@�̂��

	//���_���Ă���G�̍��W���l��
	XMFLOAT3 targetPos = pNavigationAI_->GetCaracter(target_)->GetPosition();
	XMVECTOR targetVec = XMVector3Normalize(XMLoadFloat3(&targetPos));

	XMVECTOR myVec = XMVector3Normalize(XMLoadFloat3(&transform_.position_));

	XMVECTOR rotVec = XMVector3Normalize(myVec - targetVec);

	//�O�x�N�g���������Ă�������ɕϊ����āA���K��
	XMVECTOR vFront = { 0,0,1,0 };
	vFront = XMVector3Normalize(vFront);

	//���ς���p�x�����߂�
	XMVECTOR vDot = XMVector3Dot(vFront, targetVec);
	float dot = XMVectorGetX(vDot);
	float angle = acos(dot);

	//�O�ς�-�ɂȂ�p�x�Ȃ�
	XMVECTOR vCross = XMVector3Cross(vFront, targetVec);
	if (XMVectorGetY(vCross) < ZERO) {

		angle *= -1;
	}

	float degree = XMConvertToDegrees(angle);

	//transform_.rotate_.y += degree;

	SetRotateY(degree);

#endif

	transform_.rotate_.y += 1;
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
