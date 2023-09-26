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
	enum MESSAGETYPE
	{
		MESSAGETYPE_NONE = 0,
		MESSAGE_TYPE_FINISH,
		MESSAGE_TYPE_COMPLETE
	};

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
	static CMessage* Create(D3DXVECTOR3 pos, MESSAGETYPE m_type);

private:
	MESSAGETYPE m_type;
	int m_nTime;
};

#endif