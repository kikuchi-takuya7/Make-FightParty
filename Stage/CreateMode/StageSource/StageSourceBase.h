#pragma once
#include "../../../Engine/GameObject.h"

//���̊e����
struct BulletData {

    int power_;     //���̍U����
    float speed_;   //���̑���
    float interval_;//�����o���p�x
    float size_;    //���̑傫��

};

class CsvReader;
class RateFrame;

//StageSource�̌��ƂȂ�N���X
class StageSourceBase : public GameObject
{

protected:

    //���f���ԍ�
    int hModel_;

    //�X�e�[�W�ɒu�����Ƃ��̃R�X�g�BAstar�A���S���Y���Ŏg�p
    int cost_;

    //���̃I�u�W�F�N�g�𐶐������v���C���[��ID
    int authorID_;

    //���̃I�u�W�F�N�g�̍U���́i�f�t�H���g��0�j
    int attackPower_;

    //�����蔻��
    BoxCollider* pBoxCollision_;

public:
    //�R���X�g���N�^
    StageSourceBase(GameObject* parent,std::string name);

    //�f�X�g���N�^
    ~StageSourceBase();

    //////////////�I�[�o�[���[�h�����֐�///////////////

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    

    ///////////////�p����Ŏg���֐�///////////////////////

    /// <summary>
    /// �p����p�̏�����
    /// </summary>
    virtual void ChildInitialize() {};

    /// <summary>
    /// �p����p��Update
    /// </summary>
    virtual void ChildUpdate() {};

    /// <summary>
    /// �p����p�̕`��
    /// </summary>
    virtual void ChildDraw() {};

    /// <summary>
    /// �p����p�̊J��
    /// </summary>
    virtual void ChildRelease() {};

    //////////////////�����o�֐�/////////////////////////
    

    


    ////////////////�A�N�Z�X�֐�//////////////////

    /// <summary>
    /// CSV�Ə�񂪓����Ă�ꏊ���Z�b�g����
    /// </summary>
    /// <param name="csv">��񂪓����Ă���CSV�̃|�C���^</param>
    /// <param name="csvPos">�ق�����񂪓����Ă����</param>
    virtual void SetObjCsv(CsvReader* csv, int csvPos) {};

    int GetHandle() { return hModel_; }
    int GetStageCost() { return cost_; }
    int GetAuthorID() { return authorID_; }
    int GetAttackPower() { return attackPower_; }
    void SetHandle(int handle) { hModel_ = handle; }
    void SetMoveLastPos(XMFLOAT3 lastPos) { lastPos_ = lastPos; }
    void SetAuthorID(int ID) { authorID_ = ID; }
    
    
protected:

    

private:

    XMFLOAT3 lastPos_;

    RateFrame* rate_;


};