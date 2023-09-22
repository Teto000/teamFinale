//===================================================
//
// �X�R�A�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _SCORE_H_
#define _SCORE_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "object.h"

//-------------------------------
// �O���錾
//-------------------------------
class CNumber;	//���l
class CMessage;

//================================
// �X�R�A�N���X
//================================
class CScore : CObject
{
public:
	CScore();	//�R���X�g���N�^
	~CScore();	//�f�X�g���N�^

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
	void SetScore(int nScore);		//�X�R�A�̐ݒ�
	void AddScore(int nScore);		//�X�R�A�̉��Z
	void SetColor(D3DXCOLOR col);	//�F�̐ݒ�
	void SetDraw(bool bDraw);		//�`���Ԃ̐ݒ�

	//----------------
	// �Q�b�^�[
	//----------------
	D3DXVECTOR3 GetPosition() override { return m_pos; }							//�ʒu�̎擾
	D3DXVECTOR3 GetPosOld() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�ʒu�̎擾
	float GetWidth() override { return 0.0f; }										//���̎擾
	float GetHeight() override { return 0.0f; }										//�����̎擾
	int GetScore() { return m_nScore; }												//���Ԃ̎擾

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CScore* Create(D3DXVECTOR3 pos);

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
	int m_nScore;					//�X�R�A
	int m_aPosTexU[nMaxDigits];		//���̌��̐��l
	float fInterval;				//���l�̊Ԋu
	CNumber* m_pNumber[nMaxDigits];	//���l
};

#endif