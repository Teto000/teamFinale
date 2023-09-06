//===================================================
//
// ���b�Z�[�W�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _MESSAGE_H_
#define _MESSAGE_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "object2d.h"

//================================
// ���b�Z�[�W�N���X
//================================
class CMessage : public CObject2D
{
public:
	CMessage();		//�R���X�g���N�^
	~CMessage();	//�f�X�g���N�^

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
	static CMessage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
};

#endif