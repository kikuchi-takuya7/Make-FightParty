#include "PlayerStateManager.h"
#include "../Player.h"

PlayerStateManager::PlayerStateManager()
{
	playerAttackState_ = new PlayerAttackState;
	playerDieState_ = new PlayerDieState;
	playerIdleState_ = new PlayerIdleState;
	playerJumpState_ = new PlayerJumpState;
	playerKnockBackState_ = new PlayerKnockBackState;
	playerRunState_ = new PlayerRunState;

	playerState_ = playerIdleState_;
}

void PlayerStateManager::Update(Player* player)
{

	//�U�����Ă鎞�ɍU�����������ɍU������������p�B���ꂼ���Enter�ɒu����������������
	if (playerState_ != playerAttackState_) {
		player->EraseCollider(COLLIDER_ATTACK);
	}

	//�s���s�\��ԂȂ�ړ��͂��Ȃ�
	if (playerState_ == playerKnockBackState_ || playerState_ == playerDieState_) {
		playerState_->Update(player);
		return;
	}

	//���ʏ���
	if (player->GetStatus().dead) {
		ChangeState(PLAYER_DIE, player);
	}

	//�ړ��L�[��������Ă���Ȃ�
	if (Input::IsKey(DIK_A) || Input::IsKey(DIK_D)|| Input::IsKey(DIK_W) || Input::IsKey(DIK_S)){
		//Runstate�ňړ����Ȃ瑬�x�������āA����state�Ȃ�ړ����x�x������Ƃ����ǂ��C������
		MovePlayer(player);
		//ChangeState(PLAYER_RUN, player);
	}

	playerState_->Update(player);
}

void PlayerStateManager::HandleInput(Player* player)
{
}

void PlayerStateManager::Enter(Player* player)
{
}

void PlayerStateManager::ChangeState(PlayerStatePattern nextState, Player* player)
{

	//��Ԃ�ύX���āA���̏�Ԃ̏������������s��
	switch (nextState)
	{
	case PLAYER_ATTACK:
		playerState_ = playerAttackState_;
		break;

	case PLAYER_DIE:
		playerState_ = playerDieState_;
		break;

	case PLAYER_IDLE:
		playerState_ = playerIdleState_;
		break;

	case PLAYER_JUMP:
		playerState_ = playerJumpState_;
		break;

	case PLAYER_KNOCKBACK:
		playerState_ = playerKnockBackState_;
		break;

	case PLAYER_RUN:
		playerState_ = playerRunState_;
		break;

	default:
		return;
		break;
	}

	playerState_->Enter(player);
	
}

void PlayerStateManager::MovePlayer(Player* player)
{
	XMFLOAT3 fMove = ZERO_FLOAT3;

	////�����̈����Ńv���C���[�����w�肷��
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	XMFLOAT3 playerPos = player->GetPosition();

	//���ǌ�Ő��K�����Ă邩�炱���̒l�͑傫���Ă��Ӗ��Ȃ�
	if (Input::IsKey(DIK_A) && playerPos.x >= 0.5)
	{
		fMove.x = -0.01f;
	}
	if (Input::IsKey(DIK_D) && playerPos.x <= 28.5)
	{
		fMove.x = 0.01f;
	}
	if (Input::IsKey(DIK_W) && playerPos.z <= 28.5)
	{
		fMove.z = 0.01f;
	}
	if (Input::IsKey(DIK_S) && playerPos.z >= 0.5)
	{
		fMove.z = -0.01f;
	}

	XMVECTOR vMove = XMLoadFloat3(&fMove);

	//�΂߂̈ړ��ł������Ȃ�Ȃ��悤��(�K�v���H)
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	//���x����
	fMove.x *= 0.5;
	fMove.z *= 0.5;

	playerPos.x += fMove.x;
	playerPos.z += fMove.z;

	player->SetPosition(playerPos);

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

		player->SetRotateY(degree);

		player->SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));

	}
}
