//===================================================
//
// �{�^���v�b�V���Q�[���w�b�_�[
// Author : Kajita Hiromu
//
//===================================================
#ifndef _MINI_GAME_BUTTONPUSH_H_
#define _MINI_GAME_BUTTONPUSH_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "mini_game_basis.h"

//================================
// �~�j�Q�[����ՃN���X
//================================
class CButtonPushGame : public CMiniGameBasis
{
public:

	enum FLASH
	{
		FLASH_NONE = 0,	//�t���b�V�����Ă��Ȃ����
		FLASH_IN,		//�t���b�V�����
		FLASH_OUT,		//�t���b�V���A�E�g���
		FADE_MAX
	};

	CButtonPushGame();				//�R���X�g���N�^
	~CButtonPushGame() override;	//�f�X�g���N�^

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
	static CButtonPushGame* Create(D3DXVECTOR3 pos);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	CObject2D *pObj2D[2];
	D3DXCOLOR m_col[2];
	FLASH m_flash;			//�t���b�V�����
};

#endif

