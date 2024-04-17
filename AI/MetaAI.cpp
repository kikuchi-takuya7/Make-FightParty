#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"
#include "../Character/CharacterState/CharacterState.h"
#include "../Engine/Camera.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Timer.h"
#include "../Engine/VFX.h"
#include "../Engine/Audio.h"
#include "../Engine/Text.h"
#include "../UI/CountDownUI.h"
#include "../UI/RankingUI.h"
#include "../UI/GaugeUI/RankingGaugeUI.h"
#include "../UI/WinnerUI.h"
#include "../UI/ChampionUI.h"
#include "../Stage/CreateMode/CreateMode.h"
#include "../VFXData/VFXData.h"

namespace {

	//�J������G�t�F�N�g�̈ʒu
	const XMFLOAT3 MAIN_GAME_CAM_POS = XMFLOAT3(15, 15, -15);
	const XMFLOAT3 MAIN_GAME_CAM_TAR = XMFLOAT3(15, 0, 15);
	const XMFLOAT3 MAIN_GAME_CAM_ANGLE = XMFLOAT3(1, 0, 1);
	const XMFLOAT3 CHAMPION_CAM_POS_DIFF = { ZERO,4,-5 };
	const XMFLOAT3 CHAMPION_CAM_TAR_DIFF = { ZERO,2,ZERO };
	const float CHAMPION_CAM_RATE = 0.05f;
	const float CHAMPION_EFFECT_DIFF = 2.0f;
	const XMFLOAT3 RANKING_CAM_POS = XMFLOAT3(15, 40, 0);
	const XMFLOAT3 RANKING_CAM_TAR = XMFLOAT3(15, 35, 15);
	const float RANKING_CAM_RATE = 0.1f;
	const float GAME_CAM_RATE = 0.01f;

	//�J�����̊p�x��
	const int CAM_ANGLE = 45;

	//�e�V�[�����ڂ̍ۂ̑ҋ@����
	const float WAIT_WINNER_TIME = 3.0f;
	const float WAIT_CHAMPION_TIME = 3.0f;

	//�X�R�A�֌W
	const int SCORE[GAUGE_NUM] = { 20,10,5 };
	const int VICTORY_POINT = 80;

	//�v���C���[�̍ő�l��
	const int PLAYER_MAX_NUM = 4;

	const int PLAYER_ID = ZERO;

	//�\�����錻�݂�AI�̏��
	const XMFLOAT3 TEXT_POS = { 10,20,ZERO };
	std::string nowModeText[MODE_NUM] = { ":Waiting...",":ChampionMode",":ResultMode" };
}

MetaAI::MetaAI(GameObject* parent)
	:AI(parent, "MetaAI"), pNavigationAI_(nullptr), No1CharaID_(ZERO),ranking_(ZERO),characterStatusList_(ZERO),
	endGame_(false),pWaitTimer_(Instantiate<Timer>(this)), pCountDown_(Instantiate<CountDownUI>(this)),pRankingUI_(Instantiate<RankingUI>(this)),
	pWinnerUI_(Instantiate<WinnerUI>(this)),pChampionUI_(nullptr),pText_(new Text)
{
}

MetaAI::~MetaAI()
{
}

void MetaAI::Initialize()
{
	//�F�X������
	for (int i = ZERO; i < PLAYER_MAX_NUM; i++) {
		No1CharaID_.emplace_back(i);
		ranking_.emplace_back(i);
		score_.emplace_back(ZERO);
	}

	pWaitTimer_->StopDraw();
	pWaitTimer_->Stop();
	pWaitTimer_->SetLimit(WAIT_WINNER_TIME);

	pRankingUI_->AllChildLeave();
	pRankingUI_->AllChildVisible();

	pWinnerUI_->Visible();
	
	hAudio_ = Audio::Load("Audio/FightBGM.wav", true);
	assert(hAudio_ >= ZERO);

	Audio::Play(hAudio_);

	pText_->Initialize();

}

void MetaAI::Update()
{
	mode_ = WAITING;

	//�D���҂����܂����玎�����~�߂�
	if (endGame_) {
		ChampionUpdate();
		return;
	}

	//�D���҂����܂��Ă�ꍇ�͏�ŁA���܂��ĂȂ��Ȃ炱�������g���B
	UsuallyUpdate();
	
}

void MetaAI::Draw()
{
	std::string str = GetObjectName() + nowModeText[mode_];
	pText_->Draw(TEXT_POS.x, TEXT_POS.y, str.c_str());
}

void MetaAI::Release()
{
}

// �_���ׂ�������w������֐�
// �����F������ID
// �߂�l�F�_���ׂ��G��ID
TargetInfo MetaAI::Targeting(int ID)
{
	int targetFrag = rand() % TARGET_NUM;

	TargetInfo target;

	target.mode = (TARGETPATTERNTEXT)targetFrag;

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

		target.mode = (TARGETPATTERNTEXT)TARGET_RANDAM;
	}

	//�S�̓I�Ɍ��Ĉ�ʂ̃v���C���[��D��I�ɑ_���悤��
	switch (target.mode)
	{
	//�L�����N�^�[�̒����烉���_���ő_��	
	case TARGET_RANDAM:
		while (true)
		{
			target.ID = rand() % characterStatusList_.size();

			//�_�������肪��������Ȃ��A����ł��Ȃ����
			if (target.ID != ID && characterStatusList_.at(target.ID).dead == false)
				return target;
		}
		break;
	
	//��ʂ̒�����N����_��
	case TARGET_NO_1:
		while (true)
		{
			//�_�������肪��������Ȃ����
			int tmp = rand() % No1CharaID_.size();
			target.ID = No1CharaID_.at(tmp);
			if (target.ID != ID)
				return target;
		}
		break;

	case TARGET_NUM:
	default:
		break;
	}

	return target;

}

// �Z���N�g���[�h�ŕ\�����ꂽ�I�u�W�F�N�g��I������֐�
// �����F�\������Ă���I�u�W�F�N�g�ꗗ
// �߂�l�F�ǂ̃I�u�W�F�N�g��I�񂾂�
int MetaAI::SelectObject(vector<int> model)
{
	//���͂Ƃ肠���������_���ŕԂ�
	return model.at(rand() % model.size());
}

// ���s�����܂��Ă�����N���G�C�g���[�h�ֈڍs����֐�
void MetaAI::DecidedWinner()
{
	int deadNum = ZERO;

	int winPlayer = ZERO;

	//����ł�l���𐔂���
	for (int i = ZERO; i < characterStatusList_.size(); i++) {
		if (characterStatusList_.at(i).dead) {
			deadNum++;
		}
		else {
			//�������l�̃v���C���[ID���o���Ă���
			winPlayer = i;
		}
	}

	//3�l�ȏ㎀��ł���΃N���G�C�g���[�h��
	if (deadNum >= PLAYER_MAX_NUM - 1 && pCreateMode_->GetState() == NONE) {
		ToCreateMode(winPlayer);
	}
}

// �Q�[���̏�Ԃ����Z�b�g���ăJ�E���g�_�E������֐�
void MetaAI::ResetGame()
{
	//������돉�������āA�J�E���g�_�E�����I���܂œ������Ȃ��B
	pNavigationAI_->AllEraseCollision();
	pNavigationAI_->AllResetStatus();
	pNavigationAI_->AllStartDraw();
	pNavigationAI_->AllStopUpdate();
	pNavigationAI_->AllResetAITarget();
	
	pCountDown_->Start();
	//GameCameraMove();

	Audio::Play(hAudio_);

}


// characterStatusList_�ɃX�e�[�^�X���v�b�V������Ɠ����ɁA���O��RankingUI�ɃZ�b�g����֐�
// �����F�v�b�V���������X�e�[�^�X
void MetaAI::PushCharacterStatus(Status status)
{
	characterStatusList_.emplace_back(status);
	pRankingUI_->SetPlayerName(characterStatusList_.size() - 1, status.playerName);
}


///////////////////////////////////////////////private�֐�///////////////////////////////////////////


// �D���҂����܂�������Update
void MetaAI::ChampionUpdate()
{
	//��莞�ԑ҂�����D���҂ɃJ������������
	if (pWaitTimer_->IsFinished()) {
		mode_ = CHAMPIONMODE;
		pChampionUI_->Invisible();
		pChampionUI_->Enter();
		pRankingUI_->AllChildVisible();
		pRankingUI_->AllChildLeave();
		MoveChampionCam();
		VictoryEffect();
		if (pChampionUI_->IsEnd() && Input::IsKeyDown(DIK_SPACE)) {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
		}
	}
}

// �ʏ펞��Update�֐�
void MetaAI::UsuallyUpdate()
{
	//�������I�������^�C�}�[���X�^�[�g���āA�I�������Ă΂��
	if (pWaitTimer_->IsFinished()) {
		mode_ = RESULTMODE;
		pNavigationAI_->AllStopDrawPlayerUI();
		pRankingUI_->AllChildInvisible();
		pRankingUI_->AllChildEnter();
		pWinnerUI_->Visible();
		Camera::MoveCam(RANKING_CAM_POS, RANKING_CAM_TAR, RANKING_CAM_RATE);


#ifdef _DEBUG //�f�o�b�N�p �Q�[�W�𑝂₷
		if (Input::IsKeyDown(DIK_2)) {
			pRankingUI_->SetScore(ZERO, WIN_GAUGE);
			score_.at(ZERO) += SCORE[WIN_GAUGE];
		}
		if (Input::IsKeyDown(DIK_3)) {
			pRankingUI_->SetScore(1, KILL_GAUGE);
			score_.at(ZERO) += SCORE[KILL_GAUGE];
		}
		if (Input::IsKeyDown(DIK_4)) {
			pRankingUI_->SetScore(2, TRAP_KILL_GAUGE);
			score_.at(ZERO) += SCORE[TRAP_KILL_GAUGE];
		}
#endif

		//�X�y�[�X�������ꂽ�玟�֐i��or�A�j���[�V�������I����ĂȂ��Ȃ�A�j���[�V�������X�L�b�v����
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
				pChampionUI_ = Instantiate<ChampionUI>(this);
				pChampionUI_->Visible();
				pChampionUI_->Leave();
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

	//�J�����𓮂���
	GameCameraMove();
}

// 1�ʂ̃L����ID�͒N���A���l���邩���m�F����֐�
void MetaAI::CheckNo1Chara()
{

	No1CharaID_.clear();

	//��ʂ̃|�C���g�Ƃ���Ɠ����_�������l���邩
	int No1Score = ZERO;

	vector<pair<int, int>> ranking;

	//�\�[�g����p�̔z��ɓ����
	for (int i = ZERO; i < characterStatusList_.size(); i++) {

		//�L�����̃X�R�A��ID������i���X�g�ɓ����Ă鏇�Ԃ����̂܂�ID�ɂȂ��Ă�j
		ranking.emplace_back(std::make_pair(score_.at(i), i));
	}

	//�~���Ń\�[�g����
	std::sort(ranking.rbegin(), ranking.rend());

	//��ʂ̃|�C���g��ID���o���Ă���
	No1Score = ranking.at(ZERO).first;
	No1CharaID_.emplace_back(ranking.at(ZERO).second);

	//���łɃ����o�ϐ��̃����L���O���X�V����
	ranking_.at(ZERO) = ranking.at(ZERO).second;

	//2�ʂ���X�V���邽�߁A1����for����
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


// �N���G�C�g���[�h�Ɉڍs����֐�
// �����F�������v���C���[��ID
void MetaAI::ToCreateMode(int winnerID)
{

	//�������v���C���[��winPoint�𑝂₵�āA���݂̏��ʂ��m�F����
	characterStatusList_.at(winnerID).winPoint++;

	pNavigationAI_->GetCaracter(winnerID)->ChangeState(IDLE);

	//�L�����N�^�[�N���X�ɂ�������
	pNavigationAI_->SetStatus(winnerID, characterStatusList_.at(winnerID));


	//���҂ɃX�R�A��ǉ�����
	pRankingUI_->SetScore(winnerID, WIN_GAUGE);
	score_.at(winnerID) += SCORE[WIN_GAUGE];

	//�L���������X�R�A�ɉ��Z����
	for (int i = ZERO; i < characterStatusList_.size(); i++) {

		pRankingUI_->SetScore(i, KILL_GAUGE, characterStatusList_.at(i).killPoint);
		score_.at(i) += SCORE[KILL_GAUGE] * characterStatusList_.at(i).killPoint;

		pRankingUI_->SetScore(i, TRAP_KILL_GAUGE, characterStatusList_.at(i).trapKillPoint);
		score_.at(i) += SCORE[TRAP_KILL_GAUGE] * characterStatusList_.at(i).trapKillPoint;
	}

	//����̈�ʂ��N���m�F����
	CheckNo1Chara();

	pRankingUI_->AllChildLeave();
	pNavigationAI_->AllStopUpdate();

	pWinnerUI_->SetWinnerID(winnerID);
	pWinnerUI_->Invisible();

	pWaitTimer_->Start();

	Audio::Stop(hAudio_);

}

// �Q�[���p�J�����ɃZ�b�g����֐�
void MetaAI::GameCameraSet()
{
	Camera::SetPosition(MAIN_GAME_CAM_POS);
	Camera::SetTarget(MAIN_GAME_CAM_TAR);
}

// �Q�[���J�����𓮂����֐�
void MetaAI::GameCameraMove()
{

#if 0 //��ԉ����G�Ƃ̊Ԃ𒍎��_�ɂ������

	//��ԉ����L������ID�ƃv���C���[��ID�̈ʒu�̐^�񒆂ɒ����_��u��
	int farthestID = pNavigationAI_->Farthest(PLAYER_ID);

	//���ɏ��҂����܂��Ă�����
	if (farthestID == -1) {
		return;
	}

	XMFLOAT3 farPos = pNavigationAI_->GetCaracter(farthestID)->GetPosition();
	XMFLOAT3 myPos = pNavigationAI_->GetCaracter(PLAYER_ID)->GetPosition();

	//�^�񒆂̒����_�����߂�
	XMFLOAT3 camTar = Float3Add(farPos, myPos) / 2;

	//���W�͐����̔��a����������΂���������.camTar�Ƃ̋������L�����̋��������炢�����Ă݂悤�Bx���W��y���W�����������Ȃ������H
	XMFLOAT3 camPos = camTar;
	camPos.z = MAIN_GAME_CAM_POS.z;
	camPos.y = MAIN_GAME_CAM_POS.y;

	float dis = pNavigationAI_->Distance(farthestID, PLAYER_ID);
	
	Camera::MoveCam(camPos, camTar, GAME_CAM_RATE);

#else //4�̂̐^�񒆂𒍎��_�ɂ��悤�Ƃ��Ă���
	
	//ID���ɃL�����N�^�[�̍��W
	vector<XMFLOAT3> playerPos;

	//�i�r�Q�[�V����AI����S�ẴL�����N�^�[�̍��W�𓾂�
	for (int i = ZERO; i < PLAYER_MAX_NUM; i++) {
		playerPos.emplace_back(pNavigationAI_->GetCaracter(i)->GetPosition());
	}

	float maxX = ZERO, maxZ = ZERO, minX = 9999, minZ = 9999;

	//x��y�̍ő�l�A�ŏ��l�����߂�
	for (int i = ZERO; i < playerPos.size(); i++) {

		if (maxX < playerPos.at(i).x) {
			maxX = playerPos.at(i).x;
		}
		else if (minX > playerPos.at(i).x) {
			minX = playerPos.at(i).x;
		}

		if (maxZ < playerPos.at(i).z) {
			maxZ = playerPos.at(i).z;
		}
		else if (minZ > playerPos.at(i).z) {
			minZ = playerPos.at(i).z;
		}
	}

	//��ԉ����L�����Ƃ̋����𑪂��āA���̒�����45�x�ŒP�ʉ~�Ƃ��ĎΕӂ̒��������߂āA���̒������g���ĉ��Ƃ�����z��y�����߂�΍s���邩��
	//���s�ړ��s�񌩂����Ȃ̕K�v���H
	float radian = XMConvertToRadians(CAM_ANGLE);
	float bottom = maxX - minX;
	float hypot = bottom / radian;

	//�l�p�`�̒��S�𒍎��_�ɂ���
	XMFLOAT3 centerPoint = XMFLOAT3((maxX + minX) / 2, ZERO, (maxZ + minZ) / 2);
	//Camera::SetPosition(XMFLOAT3(centerPoint.x, MAIN_GAME_CAM_POS.y, centerPoint.z));

	XMFLOAT3 tmp = XMFLOAT3(centerPoint.x, hypot / 2, -(hypot / 2 + MAIN_GAME_CAM_POS.z));
	SetPosition(tmp);

	XMVECTOR target = XMLoadFloat3(&centerPoint);
	Camera::SetTarget(target);



#endif

}

// �D���҂̕��ɃJ������������֐�
void MetaAI::MoveChampionCam()
{
	Character* pChampion = pNavigationAI_->GetCaracter(No1CharaID_.at(ZERO));
	XMFLOAT3 charaPos = pChampion->GetPosition();
	XMFLOAT3 camPos = XMFLOAT3(charaPos.x, charaPos.y + CHAMPION_CAM_POS_DIFF.y, charaPos.z + CHAMPION_CAM_POS_DIFF.z);
	XMFLOAT3 camTar = XMFLOAT3(charaPos.x, charaPos.y + CHAMPION_CAM_TAR_DIFF.y, charaPos.z + CHAMPION_CAM_TAR_DIFF.z);

	//�D���҂����킹�đO�Ɍ�������ׁA180�x(��ʂ̐^����)�ɉ�]������
	XMFLOAT3 rot = pChampion->GetRotate();
	RateMovePosition(rot, XMFLOAT3(rot.x, 180, rot.z), CHAMPION_CAM_RATE);
	pChampion->SetRotateY(rot.y);

	Camera::MoveCam(camPos, camTar, CHAMPION_CAM_RATE);
}

// �D���҂͒N�������߂�֐�
// �����F�D�������v���C���[��ID
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

// �D���҂̎���ɃG�t�F�N�g���o���֐�
void MetaAI::VictoryEffect()
{

	using namespace VictoryEffect;

	Character* pChampion = pNavigationAI_->GetCaracter(No1CharaID_.at(ZERO));
	XMFLOAT3 championPos = pChampion->GetPosition();

	EmitterData data;

	//���{�́i�v���C���[�̉E�ƍ��ɏo���j
	{
		using namespace Fire;

		data.textureFileName = FILENAME;
		data.position = XMFLOAT3(championPos.x + CHAMPION_EFFECT_DIFF, ZERO, championPos.z);
		data.positionRnd = POSITIONRND;
		data.direction = DIRECTION;
		data.directionRnd = DIRECTIONRND;
		data.speed = SPEED;
		data.speedRnd = SPEEDRND;
		data.accel = Fire::ACCEL;
		data.gravity = GRAVITY;
		data.color = COLOR;
		data.deltaColor = DELTACOLOR;
		data.rotate = ROTATE;
		data.rotateRnd = ROTATERND;
		data.spin = SPIN;
		data.size = Fire::SIZE;
		data.sizeRnd = SIZERND;
		data.scale = SCALE;
		data.lifeTime = LIFETIME;
		data.delay = DELAY;
		data.number = NUMBER;
		data.isBillBoard = ISBILLBOARD;

		VFX::Start(data);

		//���ɉ����o��
		data.position = XMFLOAT3(championPos.x - CHAMPION_EFFECT_DIFF, ZERO, championPos.z);
		VFX::Start(data);
	}
	
	//�΂̕�
	{
		using namespace FireSpark;

		data.textureFileName = FILENAME;
		data.position = XMFLOAT3(championPos.x + CHAMPION_EFFECT_DIFF, ZERO, championPos.z);
		data.positionRnd = POSITIONRND;
		data.direction = DIRECTION;
		data.directionRnd = DIRECTIONRND;
		data.speed = SPEED;
		data.speedRnd = SPEEDRND;
		data.accel = FireSpark::ACCEL;
		data.gravity = GRAVITY;
		data.color = COLOR;
		data.deltaColor = DELTACOLOR;
		data.rotate = ROTATE;
		data.rotateRnd = ROTATERND;
		data.spin = SPIN;
		data.size = FireSpark::SIZE;
		data.sizeRnd = SIZERND;
		data.scale = SCALE;
		data.lifeTime = LIFETIME;
		data.delay = DELAY;
		data.number = NUMBER;
		data.isBillBoard = ISBILLBOARD;

		VFX::Start(data);

		//���ɉ΂̕����o��
		data.position = XMFLOAT3(championPos.x - CHAMPION_EFFECT_DIFF, ZERO, championPos.z);
		VFX::Start(data);
	}
}
