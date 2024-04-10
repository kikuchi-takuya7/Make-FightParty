#include "Stage.h"
#include "../Engine/Model.h"
#include "../Engine/Global.h"
#include "CreateMode/CreateMode.h"
#include "../Stage/CreateMode/StageSource/OneBrock.h"


namespace {
	XMFLOAT3 STAGE_SIZE = XMFLOAT3(30.0f, ZERO, 30.0f);
	const int STAGE_COST = 1;

	//�ǉ������I�u�W�F�N�g�̎��͂ɒǉ�����R�X�g�B���S�ȕǂ������ꍇ�G���~�܂��Ă��܂�����
	const int ADD_COST = 10;

	const int moveZ[4] = { ZERO,ZERO,   1,  -1};
	const int moveX[4] = { 1,   -1,  ZERO,ZERO};

	//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��
	/*const int moveZ[8] = { ZERO,ZERO,	1,	-1, 1, 1,-1,-1 };
	const int moveX[8] = { 1,  -1,ZERO,ZERO, 1,-1, 1,-1 };*/
}

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"),hModel_(-1),debugModel_(-1), pCreateMode_(nullptr), pStageSourceList_(ZERO)
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

	

	for (int z = ZERO; z < STAGE_SIZE.z; z++) {
		for (int x = ZERO; x < STAGE_SIZE.x; x++) {
			Transform blockTrans;
			blockTrans.position_.z = z;
			blockTrans.position_.x = x;
			Model::SetTransform(stageModel_.at(z).at(x), blockTrans);
			Model::Draw(stageModel_.at(z).at(x));
		}
	}

	//�`�悵�I������玟��Astar�o�H��\������ׂɃ��f����S�ď���������
	for (int z = ZERO; z < STAGE_SIZE.z; z++) {
		for (int x = ZERO; x < STAGE_SIZE.x; x++) {
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
// �����R�Fx�����̑傫��
// �����S�Fy�����̑傫��
void Stage::SetStageCost(XMFLOAT3 pos, int cost, int xSize, int zSize)
{
	XMFLOAT3 stagePos = pos;

	//x��z�̃T�C�Y���R�X�g������
	for (int x = ZERO; x < xSize; x++) {
		for (int z = ZERO; z < zSize; z++) {

			//���W�̂̈ʒu�ɃR�X�g������
			stageCost_.at(stagePos.z).at(stagePos.x) = cost;

			//��}�X�����ǂɂ���Ǝ΂߈ړ�����Ƃ��Ɉ��������邩��㉺���R�X�g�𔽉f������
			for (int i = ZERO; i < ARRAYSIZE(moveZ); i++) {

				int sz = stagePos.z + moveZ[i];
				int sx = stagePos.x + moveX[i];

				//��ʊO���������߂�
				if (sx >= STAGE_SIZE.x || sx < ZERO || sz >= STAGE_SIZE.z || sz < ZERO) {
					continue;
				}

				//���ۂɕǂƂ����킯�ł͂Ȃ��̂ŕǂɂ͂��Ȃ����ǃR�X�g���d������
				stageCost_.at(sz).at(sx) = cost + ADD_COST;
			}

			stagePos.z++;
		}
		stagePos.x++;
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
