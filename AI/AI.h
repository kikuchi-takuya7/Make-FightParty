#pragma once



/// <summary>
/// AI���Ǘ�������N���X
/// </summary>
class AI
{

public:

	//�R���X�g���N�^
	AI();

	//�f�X�g���N�^
	~AI();//virtual�t�����ق��������H��Œ��ׂ悤

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() {};

	/// <summary>
	/// ���
	/// </summary>
	virtual void Release() {};

private:

	

};

