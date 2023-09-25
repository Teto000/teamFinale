//===================================================
//
// �A�C�e���ڈ�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _ITEMMARK_H_
#define _ITEMMARK_H_	//��d�C���N���[�h�h�~

//-------------------------
// �C���N���[�h
//-------------------------
#include "billboard.h"

//================================
// �A�C�e���ڈ�N���X
//================================
class CItemMark : public CBillBoard
{
public:
	CItemMark();			// �R���X�g���N�^
	~CItemMark() override;	// �f�X�g���N�^

	//----------------------
	// �����o�֐�
	//----------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetValue(int nValue);	// �l�̐ݒ�

	//----------------------
	// �ÓI�����o�֐�
	//----------------------
	static CItemMark* Create(D3DXVECTOR3 pos);

private:
	//----------------------
	// �����o�֐�
	//----------------------
	void ChangeTexture();	// �e�N�X�`���̐؂�ւ�

	//----------------------
	// �����o�ϐ�
	//----------------------
	int m_nValue;	// �l
};

#endif