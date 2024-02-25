#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"
#include "../Engine/Camera.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Timer.h"
#include "../UI/CountDownUI.h"
#include "../UI/RankingUI.h"
#include "../UI/GaugeUI/RankingGaugeUI.h"
#include "../Stage/CreateMode/CreateMode.h"

namespace {

	const XMFLOAT3 MAIN_GAME_CAM_POS = XMFLOAT3(15, 10, -20);
	const XMFLOAT3 MAIN_GAME_CAM_TAR = XMFLOAT3(15, 0, 15);
	const XMFLOAT3 CHAMPION_CAM_DIFF = { ZERO,4,-5 };
	const float CHAMPION_CAM_RATE = 0.1f;

	const XMFLOAT3 RANKING_CAM_POS = XMFLOAT3(15, 40, 0);
	const XMFLOAT3 RANKING_CAM_TAR = XMFLOAT3(15, 35, 15);
	const float RANKING_CAM_RATE = 0.1f;

	const float WAIT_WINNER_TIME = 1.0f;
	const float WAIT_CHAMPION_TIME = 1.0f;


	const int WIN_POINT = 20;
	const int KILL_POINT = 10;
	const int OBJECT_KILL_POINT = 5;
}

MetaAI::MetaAI(GameObject* parent)
	:AI(parent, "MetaAI"), pNavigationAI_(nullptr), No1CharaID_(ZERO),ranking_(ZERO),characterStatusList_(ZERO),
	endGame_(false),pWaitTimer_(Instantiate<Timer>(this)), pCountDown_(Instantiate<CountDownUI>(this)),pRankingUI_(Instantiate<RankingUI>(this))
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

	pWaitTimer_->StopDraw();
	pWaitTimer_->Stop();
	pWaitTimer_->SetLimit(WAIT_WINNER_TIME);

	pRankingUI_->AllChildLeave();
	pRankingUI_->AllChildVisible();
}

void MetaAI::Update()
{
	

	//�D���҂����܂����玎�����~�߂�
	if (endGame_) {
		pNavigationAI_->AllEraseCollision();
		pWaitTimer_->Start();

		//��莞�ԑ҂�����D���҂ɃJ������������
		if (pWaitTimer_->IsFinished()) {
			MoveChampionCam();
		}

		return;
	}

	//�D���҂����܂��Ă�ꍇ�͏�ŁA���܂��ĂȂ��Ȃ炱�����Ń^�C�}�[���g���B
	if (pWaitTimer_->IsFinished() || Input::IsKey(DIK_K)) {
		//pCreateMode_->ToSelectMode();

		pNavigationAI_->AllStopDraw();
		pRankingUI_->AllChildInvisible();
		pRankingUI_->AllChildEnter();
		Camera::MoveCam(RANKING_CAM_POS, RANKING_CAM_TAR, RANKING_CAM_RATE);
		
		if (pRankingUI_->IsAllEndAnim() && Input::IsKeyDown(DIK_SPACE)) {
			pCreateMode_->ToSelectMode();
		}

	}

	//�J�E���g�_�E�����I������瓮�������o��
	if (pCountDown_->IsFinished()) {
		pNavigationAI_->AllStartUpdate();
		pCountDown_->Reset();
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

void MetaAI::Release()
{
}

//�_���ׂ���������߂�֐�
int MetaAI::Targeting(int ID)
{
	int targetFrag = rand() % TARGET_NUM;

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

	case TARGET_NUM:
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

	//���ł��������ꍇ
	if (deadNum == 4) {

	}

	//3�l�ȏ㎀��ł�����
	if (deadNum >= 3 && pCreateMode_->GetState() == NONE) {
		
		//�������v���C���[��winPoint�𑝂₵�āA���݂̏��ʂ��m�F����
		characterStatusList_.at(winPlayer).winPoint++;

		//�D���҂����܂����烊�U���g�V�[����
		if (characterStatusList_.at(winPlayer).winPoint >= 4) {
			endGame_ = true;
			//pNavigationAI_->AllStopUpdate();
			pWaitTimer_->SetLimit(WAIT_CHAMPION_TIME);
			pWaitTimer_->Start();
			return;
		}

		//�L�����N�^�[�N���X�ɂ�������
		pNavigationAI_->SetStatus(winPlayer, characterStatusList_.at(winPlayer));
		CheckNo1Chara();

		pWaitTimer_->Start();

		pRankingUI_->SetScore(winPlayer, WIN_GAUGE);
		pNavigationAI_->AllStopUpdate();
		

	}
}

void MetaAI::StartGame()
{
	pNavigationAI_->AllStartDraw();
	pNavigationAI_->AllStopUpdate();

	pCountDown_->Start();
	GameCameraSet();
}

void MetaAI::ResetGame()
{
	//������돉�������āA�J�E���g�_�E�����I���܂œ������Ȃ��B
	pNavigationAI_->AllEraseCollision();
	pNavigationAI_->AllResetStatus();
	pNavigationAI_->AllStartDraw();
	pNavigationAI_->AllStopUpdate();
	
	pCountDown_->Start();
	GameCameraSet();

}

void MetaAI::GameCameraSet()
{
	Camera::SetPosition(MAIN_GAME_CAM_POS);
	Camera::SetTarget(MAIN_GAME_CAM_TAR);
}

int MetaAI::SelectObject(vector<int> model)
{

	//���͂Ƃ肠���������_���ŕԂ�
	return model.at(rand() % model.size());


}

void MetaAI::PushCharacterStatus(Status status)
{
	characterStatusList_.emplace_back(status);
	pRankingUI_->SetPlayerName(characterStatusList_.size() - 1, status.playerName);
}

void MetaAI::MoveChampionCam()
{
	Character* pChampion = pNavigationAI_->GetCaracter(No1CharaID_.at(ZERO));
	XMFLOAT3 charaPos = pChampion->GetPosition();
	XMFLOAT3 camPos = XMFLOAT3(charaPos.x, charaPos.y + CHAMPION_CAM_DIFF.y, charaPos.z + CHAMPION_CAM_DIFF.z);

	//�D���҂����킹�đO�Ɍ�������
	XMFLOAT3 rot = pChampion->GetRotate();
	RateMovePosition(rot, XMFLOAT3(rot.x, 180, rot.z), CHAMPION_CAM_RATE);
	pChampion->SetRotateY(rot.y);

	Camera::MoveCam(camPos, charaPos, CHAMPION_CAM_RATE);
}
