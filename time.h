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
#include "object.h"

//-------------------------------
// �O���錾
//-------------------------------
class CNumber;	//���l

//================================
// �^�C�}�[�N���X
//================================
class CTime : CObject
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
	void SetTime(int nTime);		//���Ԃ̐ݒ�
	void SetColor(D3DXCOLOR col);	//�F�̐ݒ�
	void SetDraw(bool bDraw);		//�`���Ԃ̐ݒ�
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
	void SetNumber();			//���l�̐ݒ�

private:
	//------------------
	// �萔
	//------------------
	static const int nMaxDigits = 3;	//�ő包��

	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_numberPos;		//�����̈ʒu
	int m_nTime;					//����
	int m_nCntMove;					//�ړ��܂ł̎���
	int m_nCntFream;				//�t���[�����̃J�E���g
	int m_aPosTexU[nMaxDigits];		//���̌��̐��l
	float fInterval;				//���l�̊Ԋu
	bool m_bCntTime;				//���Ԃ𐔂�����
	CNumber* m_pNumber[nMaxDigits];	//���l
};

#endif