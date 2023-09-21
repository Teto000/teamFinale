//===================================================
//
// �^�C�}�[�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _TIME_H_
#define _TIME_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "object2d.h"

//-------------------------------
// �O���錾
//-------------------------------
class CNumber;	//���l
class CMessage;

//================================
// �^�C�}�[�N���X
//================================
class CTime : CObject2D
{
public:
	CTime();	//�R���X�g���N�^
	~CTime();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();

	//----------------
	// �Z�b�^�[
	//----------------
	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }		//�ʒu�̐ݒ�
	void SetCntTime(bool bCnt) { m_bCntTime = bCnt; }	//���Ԃ𐔂����Ԃ̐ݒ�

	//----------------
	// �Q�b�^�[
	//----------------
	D3DXVECTOR3 GetPosition() override { return m_pos; }							//�ʒu�̎擾
	D3DXVECTOR3 GetPosOld() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�ʒu�̎擾
	float GetWidth() override { return 0.0f; }										//���̎擾
	float GetHeight() override { return 0.0f; }										//�����̎擾
	int GetTime() { return m_nTime; }												//���Ԃ̎擾

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CTime* Create(D3DXVECTOR3 pos);

private:
	//------------------
	// �萔
	//------------------
	static const int nMaxTime = 90;	//���Ԃ̍ő�l
	static const int nMaxObj = 2;

	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_numberPos;		//�����̈ʒu
	int m_nTime;					//����
	int m_nCntMove;					//�ړ��܂ł̎���
	int m_nFinTime;					//�Q�[���I���܂ł̎���
	int m_nCntFream;				//�t���[�����̃J�E���g
	float m_neeadleRotX;			//�j�̊p�x
	bool m_bCntTime;				//���Ԃ𐔂�����
	CMessage* m_pMessage;
	CObject2D* m_pObj[nMaxObj];		//�I�u�W�F�N�g
};

#endif