#pragma once
#include "GameObject.h"

class Text;

class Timer :
	public GameObject 
{
public:

	Timer(GameObject* parent);
	~Timer();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	//�^�C�}�[�Z�b�g
	void SetLimit(float seconds);

	//�^�C�}�[�X�^�[�g
	void Start();

	//�^�C�}�[�X�g�b�v
	void Stop();

	//�^�C�}�[���Z�b�g�i�X�g�b�v�������j
	void Reset();

	//Draw����
	void StartDraw();

	//Draw���Ȃ�
	void StopDraw();
	
	//�I�������true
	bool IsFinished();

	/////////////�A�N�Z�X�֐�///////////////////

	int GetNowFlame() { return flame_; }

private:
	
	int flame_;
	int startFlame_;
	float drawX_;
	float drawY_;
	Text* num_;

	

};

