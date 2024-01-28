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
	//�ŏ��͒N����ʂł�����
	No1CharaID_.push_back(0);
}

void MetaAI::Release()
{
}

//�_���ׂ���������߂�֐�
int MetaAI::Targeting(int ID)
{
	int targetFrag = rand() % 3;

	//����ꂽ�����_���\�����c������

	//������1�ʂ������ꍇ0�ɌŒ肷��i�����ł��j
	if (characterStatusList_.at(No1CharaID_.at(0)).winPoint == characterStatusList_.at(ID).winPoint) {

		targetFrag = 0;
	}

	//�S�̂����Ĉ�ʂ̃v���C���[��D��I�ɑ_���悤��
	switch (targetFrag)
	{

	//�v���C���[�̒����烉���_���ő_��	
	case 0:
		while (true)
		{
			//�_�������肪��������Ȃ����
			int targetID = rand() % characterStatusList_.size();
			if (targetID != ID)
				return targetID;
		}
		break;
	
	//��ʂ̒�����N����_��
	case 1:
	case 2:
		while (true)
		{
			//�_�������肪��������Ȃ����
			int targetID = rand() % No1CharaID_.size();
			if (targetID != ID)
				return targetID;
		}
		break;

	default:
		break;
	}

	return 0;

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
