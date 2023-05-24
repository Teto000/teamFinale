//===================================================
//
// �{�^���A�ŃQ�[���w�b�_�[
// Author : Kajita Hiromu
//
//===================================================
#ifndef _MG_BUTTONMASH_H_
#define _MG_BUTTONMASH_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "mini_game_basis.h"

//-------------------------------
// �}�N����`
//-------------------------------
#define MAX_LIFEPOLYGON		(29)	//���C�t�|���S����

//-------------------------------
// �O���錾
//-------------------------------
class CNumber;	//���l

//================================
// �~�j�Q�[����ՃN���X
//================================
class CButtonMash : public CMiniGameBasis
{
public:

	CButtonMash();				//�R���X�g���N�^
	~CButtonMash() override;	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CButtonMash* Create(D3DXVECTOR3 pos);

private:

	//------------------
	// �����o�ϐ�
	//------------------
	CObject2D *pObj2D[2];			//�I�u�W�F�N�g2D
	CObject2D *pLife[29];			//���C�t�|���S��
	D3DXCOLOR m_col[3];				//�J���[
	D3DXVECTOR3 m_PolygonPos;		//�|���S���̈ʒu
	D3DXVECTOR3 m_pos;				//�ʒu
	
	int m_nCounterAnim;	//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;	//�A�j���[�V�����p�^�[��
	int m_nMashCounter;	//�A�Ő�
};

#endif