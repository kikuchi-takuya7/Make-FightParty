#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"

MetaAI::MetaAI():pNavigationAI_(nullptr)
{
}

MetaAI::~MetaAI()
{
}

void MetaAI::Initialize()
{
}

void MetaAI::Release()
{
}

int MetaAI::Targeting(int ID)
{
	Status tmp = characterStatusList_.at(ID);

	int targetFrag = rand() % 3;

	switch (targetFrag)
	{

		//��ʂ̒�����N����_��
	case 0:
	case 1:
		return rand() % No1CharaID_.size();
		break;

		//�v���C���̒����烉���_���ő_��
	case 2:
		return rand() % 4;
	
	default:
		break;
	}

}

void MetaAI::CheckNo1Chara()
{

	//��ʂ̃|�C���g�Ƃ���Ɠ����_�������l���邩
	int No1WinPoint = 0;
	int sameRateChara = 0;
	
	vector<pair<int,int>> ranking;

	//�\�[�g����p�̔z��ɓ����
	for (int i = 0; i < characterStatusList_.size(); i++) {

		//�L�����̃X�e�[�^�X��ID������i���X�g�ɓ����Ă鏇�Ԃ����̂܂�ID�ɂȂ��Ă�j
		ranking.push_back(std::make_pair(characterStatusList_.at(i).winPoint,i));
	}

	//�~���Ń\�[�g����
	std::sort(ranking.rbegin(), ranking.rend());

	//��ʂ̃|�C���g��ID���o���Ă���
	No1WinPoint = ranking.at(0).first;
	No1CharaID_.push_back(ranking.at(0).second);
	sameRateChara++;

	for (int i = 1; i < ranking.size(); i++) {

		//��ʂ̐l�Ɠ����|�C���g�Ȃ�
		if (No1WinPoint == characterStatusList_.at(i).winPoint) {

			sameRateChara++;
			No1CharaID_.push_back(ranking.at(i).second);
		}
		else {
			//��ʈȉ��͒T�����Ȃ�
			break;
		}
	}

	
}
