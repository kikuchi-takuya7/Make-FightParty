#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"
#include "../Engine/Camera.h"

MetaAI::MetaAI(GameObject* parent)
	:AI(parent, "MetaAI"), pNavigationAI_(nullptr), No1CharaID_(0),characterStatusList_(0)
{
}

MetaAI::~MetaAI()
{
}

void MetaAI::Initialize()
{

	//�ŏ��͒N����ʂł�����
	No1CharaID_.emplace_back(ZERO);
}

void MetaAI::Release()
{
}

//�_���ׂ���������߂�֐�
int MetaAI::Targeting(int ID)
{
	int targetFrag = rand() % 3;

	//������1�ʂ������ꍇ0�ɌŒ肷��i�����ł��j
	if (characterStatusList_.at(No1CharaID_.at(ZERO)).winPoint == characterStatusList_.at(ID).winPoint) {

		targetFrag = 0;
	}

	//�S�̂����Ĉ�ʂ̃v���C���[��D��I�ɑ_���悤��
	switch (targetFrag)
	{

	//�L�����N�^�[�̒����烉���_���ő_��	
	case 0:
		while (true)
		{
			int targetID = rand() % characterStatusList_.size();

			//�_�������肪��������Ȃ����
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
	int No1WinPoint = ZERO;
	int sameRateChara = ZERO;
	
	vector<pair<int,int>> ranking;

	//�\�[�g����p�̔z��ɓ����
	for (int i = ZERO; i < characterStatusList_.size(); i++) {

		//�L�����̃X�e�[�^�X��ID������i���X�g�ɓ����Ă鏇�Ԃ����̂܂�ID�ɂȂ��Ă�j
		ranking.emplace_back(std::make_pair(characterStatusList_.at(i).winPoint,i));
	}

	//�~���Ń\�[�g����
	std::sort(ranking.rbegin(), ranking.rend());

	//��ʂ̃|�C���g��ID���o���Ă���
	No1WinPoint = ranking.at(ZERO).first;
	No1CharaID_.emplace_back(ranking.at(ZERO).second);
	sameRateChara++;

	for (int i = 1; i < ranking.size(); i++) {

		//��ʂ̐l�Ɠ����|�C���g�Ȃ�
		if (No1WinPoint == characterStatusList_.at(i).winPoint) {

			sameRateChara++;
			No1CharaID_.emplace_back(ranking.at(i).second);
		}
		else {
			//��ʈȉ��͒T�����Ȃ�
			break;
		}
	}

	
}

void MetaAI::NextGame()
{
	
	int deadNum = 0;
	
	//����ł�l���𐔂���
	for (int i = 0; i < characterStatusList_.size(); i++) {
		if (characterStatusList_.at(i).dead) {
			deadNum++;
		}
	}

	//3�l�ȏ㎀��ł�����
	if (deadNum >= 3 && pCreateMode_->GetState() == NONE) {
		pCreateMode_->ToSelectMode();
	}

	//�f�o�b�N�p
	if (Input::IsKeyDown(DIK_1) && pCreateMode_->GetState() == NONE) {
		pCreateMode_->ToSelectMode();
	}
}

void MetaAI::GameCameraSet()
{
	Camera::SetPosition(XMFLOAT3(15, 10, -20));
	Camera::SetTarget(XMFLOAT3(15, 0, 15));
}
