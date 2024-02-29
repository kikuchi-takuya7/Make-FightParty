#include "Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../../Engine/VFX.h"
#include "../../AI/MetaAI.h"
#include "../../Scene/MainGameScene.h"
#include "../../Stage/CreateMode/StageSource/Bullet.h"
#include "../../UI/PlayerUI.h"
#include "../CharacterState/CharacterStateManager.h"

//�萔
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 100;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);


}

//�R���X�g���N�^
Player::Player(GameObject* parent)
	:Character(parent, "Player")
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::ChildInitialize()
{

	//�J�n�n�_�Ɉړ�����
	SetPosition(startPos_);

	//addcollider�����珟��ɊJ������邩���
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	status_.attackPower = PLAYER_ATTACK_POWER;

	//���f���f�[�^�̃��[�h
	//hModel_ = Model::Load("PlayerFbx/playerTest.fbx");
	//assert(hModel_ >= 0);

	

	
	
}

//�X�V
void Player::ChildUpdate()
{

	

	//�ړ��L�[��������Ă���Ȃ�
	if (Input::IsKey(DIK_A) || Input::IsKey(DIK_D) || Input::IsKey(DIK_W) || Input::IsKey(DIK_S))
	{

		//Runstate�ňړ����Ȃ瑬�x�������āA����state�Ȃ�ړ����x�x������Ƃ����ǂ��C������
		MoveCharacter();
		ChangeState(RUN);
	}
	else {
		ChangeState(IDLE);
	}

	if (Input::IsKeyDown(DIK_F)) {
		ChangeState(ATTACK);
	}

	if (Input::IsKeyDown(DIK_SPACE)) {
		//ChangeState(JUMP);
	}

}

//�`��
void Player::ChildDraw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);


#ifdef _DEBUG
	CollisionDraw();
#endif

	
}

//�J��
void Player::ChildRelease()
{

}

//���������������̏���
void Player::ChildOnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//�U���ɓ��������Ƃ��̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{

		////�G�̕����Ɍ����Ȃ���
		//SetTargetRotate(pTarget->GetRotate());
		//pState_->ChangeState(KNOCKBACK);

		////���̍U���ł��ꂽ��A����̃L���|�C���g�𑝂₷
		//if (HitDamage(((Character*)pTarget)->GetStatus().attackPower)) {
		//	Status status = ((Character*)pTarget)->GetStatus();
		//	status.killPoint++;
		//	((Character*)pTarget)->SetStatus(status);
		//	((Character*)pTarget)->TellStatus();
		//}

		
	}

}

void Player::MoveCharacter()
{
	XMFLOAT3 fMove = ZERO_FLOAT3;

	////�����̈����Ńv���C���[�����w�肷��
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	XMFLOAT3 characterPos = GetPosition();

	//���ǌ�Ő��K�����Ă邩�炱���̒l�͑傫���Ă��Ӗ��Ȃ�
	if (Input::IsKey(DIK_A) && characterPos.x >= 0.5)
	{
		fMove.x = -0.01f;
	}
	if (Input::IsKey(DIK_D) && characterPos.x <= 28.5)
	{
		fMove.x = 0.01f;
	}
	if (Input::IsKey(DIK_W) && characterPos.z <= 28.5)
	{
		fMove.z = 0.01f;
	}
	if (Input::IsKey(DIK_S) && characterPos.z >= 0.5)
	{
		fMove.z = -0.01f;
	}

	XMVECTOR vMove = XMLoadFloat3(&fMove);

	//�΂߂̈ړ��ł������Ȃ�Ȃ��悤��(�K�v���H)
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	//���x����
	fMove.x *= 0.2;
	fMove.z *= 0.2;

	characterPos.x += fMove.x;
	characterPos.z += fMove.z;

	SetPosition(characterPos);

	float length = Length(vMove);

	

	//�����Ă���Ȃ�p�x�����߂ĉ�]����
	if (length != ZERO) {

		XMVECTOR vFront = { 0,0,1,0 };
		vMove = XMVector3Normalize(vMove);

		//���ς���p�x�����߂�
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		//�O�ς�-�ɂȂ�p�x�Ȃ�
		XMVECTOR vCross = XMVector3Cross(vFront, vMove);
		if (XMVectorGetY(vCross) < ZERO) {

			angle *= -1;
		}

		float degree = XMConvertToDegrees(angle);

		SetRotateY(degree);

		SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));
	}
}

void Player::TellStatus()
{
	
	//�ǂ������Ⴄ�C������B�ǂ�����ăv���C���[����MetaAI�Ɏ��񂾂��Ƃ�`����H���O������������Ă����H

	//((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ChangeStatus(GetObjectID(), GetStatus());
	//((MainGameScene*)GetParent())->CallStatus(GetObjectID(), GetStatus());

	((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ChangeStatus(GetObjectID(), GetStatus());
	((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ToCreateMode();
}