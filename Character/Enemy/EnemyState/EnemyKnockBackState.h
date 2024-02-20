#pragma once
#include "EnemyState.h"

/// <summary>
/// �v���C���[�������Ă�����
/// </summary>
class EnemyKnockBackState : public EnemyState
{

public:

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="enemy">Enemy�̃|�C���^</param>
	void Update(Enemy* enemy, CharacterAI* AI) override;


	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	/// <param name="enemy">Enemy�̃|�C���^</param>
	void HandleInput(Enemy* enemy, CharacterAI* AI) override;

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <param name="enemy">Enemy�̃|�C���^</param>
	void Enter(Enemy* enemy, CharacterAI* AI) override;

	void SetPlayerRotate(XMFLOAT3 rot) { playerRot_ = rot; }

	float GetRateValue(float begin, float end, float rate);

private:

	//���ԁi�t���[���P�ʁj
	int flame_;

	//�ɋ}��t���郌�[�g
	float rate_;

	//�ŏI�I�Ȉʒu
	XMFLOAT3 lastPoint_;

	XMFLOAT3 playerRot_;
};

