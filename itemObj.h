//=============================================================================
//
// �A�C�e���N���X(itemObj.h)
// Author : �������l
// �T�v : �A�C�e���������s��
//
//=============================================================================
#ifndef _ITEMOBJ_H_			// ���̃}�N����`������ĂȂ�������
#define _ITEMOBJ_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "objectX.h"

//=============================================================================
// ���f���I�u�W�F�N�g�N���X
// Author : �������l
// �T�v : ���f���I�u�W�F�N�g�������s���N���X
//=============================================================================
class CItemObj : public CObjectX
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CItemObj *Create();	// ���f���I�u�W�F�N�g�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CItemObj();
	~CItemObj();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init(D3DXVECTOR3 pos) override;											// ������
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��
	void SetParent(CModel3D *pParent) { m_pParent = pParent; }						// �e�̐ݒ�
	void SetParent() { m_pParent = nullptr; }										// �e�̐ݒ����
	void SetPosOffset(D3DXVECTOR3 posOffset) { m_posOffset = posOffset; }			// �ʒu�̍����̐ݒ�
	void SetRotOffset(D3DXVECTOR3 rotOffset) { m_rotOffset = rotOffset; }			// �����̍����̐ݒ�

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CModel3D *m_pParent;			// �e���f���̏��
	D3DXVECTOR3 m_posOffset;		// �ʒu�̍���
	D3DXVECTOR3 m_rotOffset;		// �����̍���
};

#endif

