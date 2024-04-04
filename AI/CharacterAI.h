#pragma once
#include "AI.h"

class NavigationAI;
class MetaAI;
class Enemy;
class Text;
class Timer;
enum TARGETPATTERN;

enum TARGETPATTERNTEXT {
	RANDAM,
	NO_1,
	COUNTER,
	TEXT_NUM,
};

//�_���Ă���GID�ƃ��[�h
struct TargetInfo {

	//�_���Ă���G��ID
	int ID;

	//����ID��_���̂Ɏg�����m���̃p�^�[���i���݂̏�Ԃ�`�悷��̂Ɏg���j
	TARGETPATTERNTEXT mode;
};

/// <summary>
/// �G�L�����N�^�[�𓮂���AI
/// </summary>
class CharacterAI : public AI
{

public:

	//�R���X�g���N�^
	CharacterAI(GameObject* parent);
	CharacterAI(GameObject* parent,Enemy* enemy, NavigationAI* naviAI);

	//�f�X�g���N�^
	~CharacterAI();

	//////////////�I�[�o�[���C�h�����֐�////////////////

	//������
	void Initialize() override;

	//�`��
	void Draw() override;

	//���
	void Release() override;

	/////////////////�����o�֐�/////////////////////////

	/// <summary>
	/// �_���ׂ��G��MetaAI�ɕ����֐�
	/// </summary>
	void AskTarget();

	/// <summary>
	/// MetaAI�ɏ���`����֐�
	/// </summary>
	void TellStatus();

	/// <summary>
	/// NavigationAI�ɍs���ׂ��ꏊ�𕷂��A�ړ�����֐�
	/// </summary>
	void MoveEnemy();

	/// <summary>
	/// �U�����邩�ǂ������w������֐�
	/// </summary>
	void IsAttack();

	/// <summary>
	/// �N���G�C�g���[�h�őI�������I�u�W�F�N�g���ړ�������֐�
	/// </summary>
	/// <returns>�����������Transform</returns>
	Transform MoveSelectObject();

	///////////////////�A�N�Z�X�֐�///////////////////

	void SetEnemy(Enemy* enemy) { pEnemy_ = enemy; }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void SetMetaAI(MetaAI* AI) { pMetaAI_ = AI; }
	void SetAttackRange(float range) { attackRange_ = range; }
	void SetAttackProbability(int probability) { startAttackProbability_ = probability; attackProbability_ = probability; }
	void SetAttackAddPro(int addProbability) { attackAddProbability_ = addProbability; }
	void SetAttackCoolDown(float time) { attackCoolDown_ = time; }

	void SetTarget(TargetInfo target) { target_ = target; }

private:

	NavigationAI* pNavigationAI_;

	MetaAI* pMetaAI_;

	//����������G�̃C���X�^���X
	Enemy* pEnemy_;

	//�_���Ă���G
	TargetInfo target_;

	//////AI���ɕς��X�e�[�^�X///////////////////

	//�U�����鎞�̎˒�
	float attackRange_;

	//�ŏ��̍U������m��
	int startAttackProbability_;

	//�U������m��
	int attackProbability_;

	//�ǉ������U���m��
	int attackAddProbability_;

	//�U���̃N�[���_�E��
	float attackCoolDown_;
	Timer* pCoolDown_;

	//���݂̏�Ԃ�\������p�̃e�L�X�g
	Text* pText_;
	
};

