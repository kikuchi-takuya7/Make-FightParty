#pragma once
#include "../Engine/GameObject.h"

//https://ai-kenkyujo.com/news/gameai/
//�\���̎Q�l�T�C�g

/// <summary>
/// AI���Ǘ�������N���X.
/// </summary>
class AI : public GameObject
{

public:

	//�R���X�g���N�^
	AI(GameObject* parent, std::string name);

	//�f�X�g���N�^
	~AI();//virtual�t�����ق��������H��Œ��ׂ悤

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() override;

	/// <summary>
	/// ���
	/// </summary>
	virtual void Release() override;

private:

	

};

