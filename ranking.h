//===================================================
//
// �����L���O�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _RANKING_H_
#define _RANKING_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "object.h"

//-------------------------------
// �O���錾
//-------------------------------
class CTime;	//����

//================================
// �����L���O�N���X
//================================
class CRanking : CObject
{
public:
	CRanking();	//�R���X�g���N�^
	~CRanking();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();

	void Save();
	void Load();
	void Ranking();

	//----------------
	// �Z�b�^�[
	//----------------
	static void SetNewTime(int nTime) { m_nTime = nTime; }							//�V�������Ԃ�ݒ�
	void SetPos(D3DXVECTOR3 pos) override {}									//�ʒu�̐ݒ�

	//----------------
	// �Q�b�^�[
	//----------------
	D3DXVECTOR3 GetPosition() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }	//�ʒu�̎擾
	D3DXVECTOR3 GetPosOld() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�ʒu�̎擾
	float GetWidth() override { return 0.0f; }										//���̎擾
	float GetHeight() override { return 0.0f; }										//�����̎擾

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CRanking* Create();

private:
	//------------------
	// �萔
	//------------------
	static const int nMaxRanking = 5;	//�\�����郉���L���O�̍ő吔

	//------------------
	// �����o�ϐ�
	//------------------
	int	m_nRankUpdate;				//�X�V�����NNo.
	CTime*	m_pTime[nMaxRanking];	//����

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static int m_nTime;	//����
};

#endif