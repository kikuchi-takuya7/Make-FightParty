#pragma once
#include "PlayerState.h"

/// <summary>
/// �v���C���[�������Ă�����
/// </summary>
class PlayerKnockBackState : public PlayerState
{

public:

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	void Update(Player* player) override;


	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	void HandleInput(Player* player) override;

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	void Enter(Player* player) override;

	void SetEnemyRotate(XMFLOAT3 rot) { enemyRot_ = rot; }

	float GetRateValue(float begin, float end, float rate);

private:

	//���ԁi�t���[���P�ʁj
	int flame_;

	//�ɋ}��t���郌�[�g
	float rate_;

	//�ŏI�I�Ȉʒu
	XMFLOAT3 lastPoint_;

	XMFLOAT3 enemyRot_;
};

