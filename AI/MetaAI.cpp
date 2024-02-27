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
#include "../UI/WinnerUI.h"
#include "../UI/ChampionUI.h"
#include "../Stage/CreateMode/CreateMode.h"

namespace {

	const XMFLOAT3 MAIN_GAME_CAM_POS = XMFLOAT3(15, 10, -20);
	const XMFLOAT3 MAIN_GAME_CAM_TAR = XMFLOAT3(15, 0, 15);
	const XMFLOAT3 CHAMPION_CAM_POS_DIFF = { ZERO,4,-5 };
	const XMFLOAT3 CHAMPION_CAM_TAR_DIFF = { ZERO,2,ZERO };
	const float CHAMPION_CAM_RATE = 0.05f;

	const XMFLOAT3 RANKING_CAM_POS = XMFLOAT3(15, 40, 0);
	const XMFLOAT3 RANKING_CAM_TAR = XMFLOAT3(15, 35, 15);
	const float RANKING_CAM_RATE = 0.1f;

	const float WAIT_WINNER_TIME = 1.0f;
	const float WAIT_CHAMPION_TIME = 1.0f;

	const int SCORE[GAUGE_NUM] = { 20,10,5 };
	const int VICTORY_POINT = 80;
}

MetaAI::MetaAI(GameObject* parent)
	:AI(parent, "MetaAI"), pNavigationAI_(nullptr), No1CharaID_(ZERO),ranking_(ZERO),characterStatusList_(ZERO),
	endGame_(false),pWaitTimer_(Instantiate<Timer>(this)), pCountDown_(Instantiate<CountDownUI>(this)),pRankingUI_(Instantiate<RankingUI>(this)),
	pWinnerUI_(Instantiate<WinnerUI>(this)),pChampionUI_(Instantiate<ChampionUI>(this))
{
}

MetaAI::~MetaAI()
{
}

void MetaAI::Initialize()
{
	//�F�X������
	for (int i = ZERO; i < 4; i++) {
		No1CharaID_.emplace_back(i);
	}
	for (int i = ZERO; i < 4; i++) {
		ranking_.emplace_back(i);
	}
	for (int i = ZERO; i < 4; i++) {
		score_.emplace_back(ZERO);
	}

	pWaitTimer_->StopDraw();
	pWaitTimer_->Stop();
	pWaitTimer_->SetLimit(WAIT_WINNER_TIME);

	pRankingUI_->AllChildLeave();
	pRankingUI_->AllChildVisible();

	pWinnerUI_->Visible();
	pChampionUI_->Visible();
}

void MetaAI::Update()
{
	//�D���҂����܂����玎�����~�߂�
	if (endGame_) {

		//��莞�ԑ҂�����D���҂ɃJ������������
		if (pWaitTimer_->IsFinished()) {
			pChampionUI_->Invisible();
			pRankingUI_->AllChildVisible();
			pRankingUI_->AllChildLeave();
			MoveChampionCam();
		}

		return;
	}

	//�D���҂����܂��Ă�ꍇ�͏�ŁA���܂��ĂȂ��Ȃ炱�����Ń^�C�}�[���g���B
	if (pWaitTimer_->IsFinished()) {
		pNavigationAI_->AllStopDrawPlayerUI();
		pRankingUI_->AllChildInvisible();
		pRankingUI_->AllChildEnter();
		pWinnerUI_->Visible();
		Camera::MoveCam(RANKING_CAM_POS, RANKING_CAM_TAR, RANKING_CAM_RATE);

		if (Input::IsKeyDown(DIK_2)) {
			pRankingUI_->SetScore(ZERO, WIN_GAUGE,1);
			score_.at(ZERO) += SCORE[WIN_GAUGE];
		}
		if (Input::IsKeyDown(DIK_3)) {
			pRankingUI_->SetScore(1, KILL_GAUGE,1);
			score_.at(1) += SCORE[KILL_GAUGE];
		}
		if (Input::IsKeyDown(DIK_4)) {
			pRankingUI_->SetScore(2, TRAP_KILL_GAUGE, 1);
			score_.at(2) += SCORE[TRAP_KILL_GAUGE];
		}
		
		if (Input::IsKeyDown(DIK_SPACE)) {

			if (pRankingUI_->IsAllEndAnim() == false) {
				pRankingUI_->EndAnim();
				return;
			}

			pWaitTimer_->Reset();
			

			//�D���҂����܂��Ă烊�U���g�V�[����
			int ID = VictoryPlayer();
			if (ID != -1) {
				endGame_ = true;
				pNavigationAI_->AllEraseCollision();
				pWaitTimer_->Start();
				return;
			}

			pCreateMode_->ToSelectMode();
			pNavigationAI_->AllStopDraw();
			pRankingUI_->AllChildVisible();
			pRankingUI_->AllChildLeave();

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
	if (score_.at(ranking_.at(ZERO)) == score_.at(ID) || No1AllDead == true) {

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

	No1CharaID_.clear();

	//��ʂ̃|�C���g�Ƃ���Ɠ����_�������l���邩
	int No1Score = ZERO;
	
	vector<pair<int,int>> ranking;

	//�\�[�g����p�̔z��ɓ����
	for (int i = ZERO; i < characterStatusList_.size(); i++) {

		//�L�����̃X�R�A��ID������i���X�g�ɓ����Ă鏇�Ԃ����̂܂�ID�ɂȂ��Ă�j
		ranking.emplace_back(std::make_pair(score_.at(i),i));
	}

	//�~���Ń\�[�g����
	std::sort(ranking.rbegin(), ranking.rend());

	//��ʂ̃|�C���g��ID���o���Ă���
	No1Score = ranking.at(ZERO).first;
	No1CharaID_.emplace_back(ranking.at(ZERO).second);
	
	//���łɃ����o�ϐ��̃����L���O���X�V����
	ranking_.at(ZERO) = ranking.at(ZERO).second;

	for (int i = 1; i < ranking.size(); i++) {

		//��ʂ̐l�Ɠ����|�C���g�Ȃ瓯���P�ʂ�����
		if (No1Score == score_.at(i)) {

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

	//3�l�ȏ㎀��ł����珟�����v���C���[��winPoint�𑝂₵�āA���݂̏��ʂ��m�F����
	if (deadNum >= 3 && pCreateMode_->GetState() == NONE) {
		
		characterStatusList_.at(winPlayer).winPoint++;

		//�L�����N�^�[�N���X�ɂ�������
		pNavigationAI_->SetStatus(winPlayer, characterStatusList_.at(winPlayer));


		//�X�R�A���m�F����
		pRankingUI_->SetScore(winPlayer, WIN_GAUGE,1);
		score_.at(winPlayer) += SCORE[WIN_GAUGE];

		//�L���������X�R�A�ɉ��Z����
		for (int i = 0; i < characterStatusList_.size(); i++) {

			pRankingUI_->SetScore(i, KILL_GAUGE, characterStatusList_.at(i).killPoint);
			score_.at(i) += SCORE[KILL_GAUGE] * characterStatusList_.at(i).killPoint;
			
			pRankingUI_->SetScore(i, TRAP_KILL_GAUGE, characterStatusList_.at(i).trapKillPoint);
			score_.at(i) += SCORE[TRAP_KILL_GAUGE] * characterStatusList_.at(i).trapKillPoint;
		}

		//����̈�ʂ��N���m�F����
		CheckNo1Chara();

		pRankingUI_->AllChildLeave();
		pNavigationAI_->AllStopUpdate();
		
		pWinnerUI_->SetWinnerID(winPlayer);
		pWinnerUI_->Invisible();

		pWaitTimer_->Start();
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
	XMFLOAT3 camPos = XMFLOAT3(charaPos.x, charaPos.y + CHAMPION_CAM_POS_DIFF.y, charaPos.z + CHAMPION_CAM_POS_DIFF.z);
	XMFLOAT3 camTar = XMFLOAT3(charaPos.x, charaPos.y + CHAMPION_CAM_TAR_DIFF.y, charaPos.z + CHAMPION_CAM_TAR_DIFF.z);

	//�D���҂����킹�đO�Ɍ�������
	XMFLOAT3 rot = pChampion->GetRotate();
	RateMovePosition(rot, XMFLOAT3(rot.x, 180, rot.z), CHAMPION_CAM_RATE);
	pChampion->SetRotateY(rot.y);

	Camera::MoveCam(camPos, camTar, CHAMPION_CAM_RATE);
}

int MetaAI::VictoryPlayer()
{
	int winner = -1;
	int maxScore = ZERO;
	bool sameScore = false;


	for (int i = ZERO; i < score_.size(); i++) {

		//��ʂƓ_��������Ă��邩�m�F����
		if (maxScore == score_.at(i)) {
			sameScore = true;
		}

		//�����Ƀ{�[�_�[�ɂ��ǂ蒅���\�������邽�߈�ԃX�R�A�̍����l���o���Ă���
		if (score_.at(i) >= VICTORY_POINT && maxScore < score_.at(i)) {
			winner = i;
			maxScore = score_.at(i);
			sameScore = false;
		}
	}

	if (sameScore) {
		//���_�������ꍇ�������������ق�������
	}

	return winner;
}
