#include "Stage.h"
#include "../Engine/Model.h"
#include "../Engine/Global.h"
#include "CreateMode/CreateMode.h"
#include "../Stage/CreateMode/StageSource/OneBrock.h"


namespace {
	XMFLOAT3 STAGE_SIZE = XMFLOAT3(30.0f, ZERO, 30.0f);
	const int STAGE_COST = 1;
	const int moveZ[4] = { ZERO,ZERO,   1,  -1};
	const int moveX[4] = { 1,   -1,  ZERO,ZERO};
}

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"),hModel_(-1),debugModel_(-1), pCreateMode_(nullptr), pStageSourceList_(0)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{

	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Stage/StageBrock.fbx");
	assert(hModel_ >= ZERO);

	//debug�p�̃��f���f�[�^�̃��[�h
	debugModel_ = Model::Load("Stage/DebugBrock.fbx");
	assert(hModel_ >= ZERO);

	transform_.position_.x = ZERO;
	transform_.position_.z = ZERO;

	//width���̍s����height�񕪂����m�ۂ��Ă���
	for (int i = ZERO; i < STAGE_SIZE.z; i++) {
		stageCost_.emplace_back(STAGE_SIZE.x);
		stageModel_.emplace_back(STAGE_SIZE.x);
	}

	//�X�e�[�W�̏��X��������
	for (int z = ZERO; z < STAGE_SIZE.z; z++) {
		for (int x = ZERO; x < STAGE_SIZE.x; x++) {

			stageCost_.at(z).at(x) = STAGE_COST;
			stageModel_.at(z).at(x) = hModel_;
		}
	}

}

void Stage::Update()
{
	//pCreateMode_->Update();
}

void Stage::Draw()
{

	Transform blockTrans;

	for (int z = 0; z < STAGE_SIZE.z; z++) {
		for (int x = 0; x < STAGE_SIZE.x; x++) {
			blockTrans.position_.z = z;
			blockTrans.position_.x = x;
			Model::SetTransform(stageModel_.at(z).at(x), blockTrans);
			Model::Draw(stageModel_.at(z).at(x));
		}
	}

	//�`�悵�I������玟��Astar�o�H��\������ׂɃ��f����S�ď���������
	for (int z = 0; z < STAGE_SIZE.z; z++) {
		for (int x = 0; x < STAGE_SIZE.x; x++) {
			stageModel_.at(z).at(x) = hModel_;
		}
	}

}

void Stage::Release()
{
	//SAFE_DELETE(pCreateMode_);
}

// �S�Ă�update������
void Stage::AllStartUpdate()
{
	for (auto it = pStageSourceList_.begin(); it != pStageSourceList_.end(); it++) {
		(*it)->Enter();
	}
}

//�S�Ă�update���~�߂�
void Stage::AllStopUpdate()
{
	for (auto it = pStageSourceList_.begin(); it != pStageSourceList_.end(); it++) {
		(*it)->Leave();
	}
}

// �X�e�[�W�̃R�X�g���Z�b�g����
// �����P�F���̃I�u�W�F�N�g�̈ʒu
// �����Q�F�I�u�W�F�N�g�̃R�X�g
void Stage::SetStageCost(XMFLOAT3 pos, int cost)
{
	stageCost_.at(pos.z).at(pos.x) = cost;

	//��}�X�����ǂɂ���Ǝ΂߈ړ�����Ƃ��Ɉ��������邩��㉺���R�X�g�𔽉f�����Ă݂�
	for (int i = 0; i < 4; i++) {

		int sz = pos.z + moveZ[i];
		int sx = pos.x + moveX[i];

		//��ʊO���������߂�
		if (sx >= STAGE_SIZE.x || sx < 0 || sz >= STAGE_SIZE.y || sz < 0) {
			continue;
		}
		stageCost_.at(sz).at(sx) = cost;
	}
}

// Astar�A���S���Y���ŏo���o�H��\������ׂɃ��f����ς���ׂ̊֐�
// �����F�o�H�T���łł��o�H
void Stage::SetDebugModel(std::stack<std::pair<int, int>> pair)
{
	//Astar�̌o�H�T���ŏo���ꏊ�̃��f����ς���
	while (!pair.empty())
	{
		stageModel_.at(pair.top().first).at(pair.top().second) = debugModel_;
		pair.pop();
	}
}

XMFLOAT3 Stage::GetStageSize()
{
	return STAGE_SIZE;
}
