#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"
#include "../Engine/Camera.h"
#include "../Stage/CreateMode/CreateMode.h"
#include "../UI/CountDown.h"
#include "../Engine/SceneManager.h"

MetaAI::MetaAI(GameObject* parent)
	:AI(parent, "MetaAI"), pNavigationAI_(nullptr), No1CharaID_(ZERO),ranking_(ZERO),characterStatusList_(ZERO),
	countDown_(Instantiate<CountDown>(this)),endGame_(false)
{
}

MetaAI::~MetaAI()
{
}

void MetaAI::Initialize()
{

	//�ŏ��͒N����ʂł�����
	No1CharaID_.emplace_back(ZERO);

	//�Ƃ肠������ID��������Ƃ�
	for (int i = ZERO; i < 4; i++) {
		ranking_.emplace_back(i);
	}
}

void MetaAI::Update()
{

	if (endGame_) {
		pNavigationAI_->AllEraseCollision();
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}

	if (countDown_->IsFinished()) {
		pNavigationAI_->AllStartUpdate();
		countDown_->Reset();
	}

	
}

void MetaAI::Release()
{
}

//�_���ׂ���������߂�֐�
int MetaAI::Targeting(int ID)
{
	int targetFrag = rand() % NUM;

	TARGETPATTERN target = (TARGETPATTERN)targetFrag;

	bool No1AllDead = true;

	//�P�ʂ��N�����琶���c���Ă��邩�ǂ���
	for (int i = ZERO; i < No1CharaID_.size(); i++) {
		if (characterStatusList_.at(No1CharaID_.at(i)).dead == false) {
			No1AllDead = false;
			break;
		}
	}

	//������1�ʂ������ꍇ0�ɌŒ肷��i�����ł��jor ��ʂ��S������łĂ�0�ɌŒ�
	if (characterStatusList_.at(ranking_.at(ZERO)).winPoint == characterStatusList_.at(ID).winPoint || No1AllDead == true) {

		target = TARGET_RANDAM;
	}

	//�S�̂����Ĉ�ʂ̃v���C���[��D��I�ɑ_���悤��
	switch (target)
	{
	//�L�����N�^�[�̒����烉���_���ő_��	
	case TARGET_RANDAM:
		while (true)
		{
			int targetID = rand() % characterStatusList_.size();

			//�_�������肪��������Ȃ��A����ł��Ȃ����
			if (targetID != ID)
				return targetID;
		}
		break;
	
	//��ʂ̒�����N����_��
	case TARGET_NO_1:
		while (true)
		{
			//�_�������肪��������Ȃ����
			int targetID = rand() % No1CharaID_.size();
			if (targetID != ID)
				return targetID;
		}
		break;

	case NUM:
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

		//�L������WinPoint��ID������i���X�g�ɓ����Ă鏇�Ԃ����̂܂�ID�ɂȂ��Ă�j
		ranking.emplace_back(std::make_pair(characterStatusList_.at(i).winPoint,i));
	}

	//�~���Ń\�[�g����
	std::sort(ranking.rbegin(), ranking.rend());

	//��ʂ̃|�C���g��ID���o���Ă���
	No1WinPoint = ranking.at(ZERO).first;
	No1CharaID_.emplace_back(ranking.at(ZERO).second);
	
	//���łɃ����o�ϐ��̃����L���O���X�V����
	ranking_.at(ZERO) = ranking.at(ZERO).second;
	sameRateChara++;

	for (int i = 1; i < ranking.size(); i++) {

		//��ʂ̐l�Ɠ����|�C���g�Ȃ瓯���P�ʂ�����
		if (No1WinPoint == characterStatusList_.at(i).winPoint) {

			sameRateChara++;
			No1CharaID_.emplace_back(ranking.at(i).second);
			ranking_.at(i) = ranking.at(i).second;
		}
		else {
			
			//2�ʈȉ����X�V
			ranking_.at(i) = ranking.at(i).second;
		}
	}

	
}

void MetaAI::ToCreateMode()
{

	int deadNum = 0;
	
	int winPlayer = 0;

	//����ł�l���𐔂���
	for (int i = 0; i < characterStatusList_.size(); i++) {
		
		if (characterStatusList_.at(i).dead) {
			deadNum++;
		}
		else {
			//��������̃v���C���[ID���o���Ă���
			winPlayer = i;
		}

		
	}

	//�������v���C���[��winPoint�𑝂₵�ăN���G�C�g���[�h��

	//3�l�ȏ㎀��ł�����
	if (deadNum >= 3 && pCreateMode_->GetState() == NONE) {
		
		//�������v���C���[��winPoint�𑝂₵�āA���݂̏��ʂ��m�F����
		characterStatusList_.at(winPlayer).winPoint++;

		//�L�����N�^�[�N���X�ɂ�������
		pNavigationAI_->SetStatus(winPlayer, characterStatusList_.at(winPlayer));
		CheckNo1Chara();

		//�D���҂����܂����烊�U���g�V�[����
		if (characterStatusList_.at(winPlayer).winPoint >= 4) {
			

			endGame_ = true;
		}

		pCreateMode_->ToSelectMode();
	}

	//�f�o�b�N�p
	if (Input::IsKeyDown(DIK_1) && pCreateMode_->GetState() == NONE) {
		
		characterStatusList_.at(ZERO).winPoint++;
		pNavigationAI_->SetStatus(ZERO, characterStatusList_.at(ZERO));
		CheckNo1Chara();

		if (characterStatusList_.at(ZERO).winPoint >= 4) {
			endGame_ = true;
		}
		pCreateMode_->ToSelectMode();
	}
}

void MetaAI::StartGame()
{
	
	pNavigationAI_->AllStartDraw();
	pNavigationAI_->AllStopUpdate();

	countDown_->Start();
	GameCameraSet();
}

void MetaAI::ResetGame()
{
	//������돉�������āA�J�E���g�_�E�����I���܂œ������Ȃ��B
	pNavigationAI_->AllEraseCollision();
	pNavigationAI_->AllResetStatus();
	pNavigationAI_->AllStartDraw();
	pNavigationAI_->AllStopUpdate();
	
	countDown_->Start();
	GameCameraSet();

}

void MetaAI::GameCameraSet()
{
	Camera::SetPosition(XMFLOAT3(15, 10, -20));
	Camera::SetTarget(XMFLOAT3(15, 0, 15));
}

int MetaAI::SelectObject(vector<int> model)
{

	//���͂Ƃ肠���������_���ŕԂ�
	return model.at(rand() % model.size());


}
