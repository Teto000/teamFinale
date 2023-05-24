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

//-------------------------------
// �}�N����`
//-------------------------------
#define MAX_SPEED			(3.0f)	//���x
#define MAX_BUTTONPOLYGON	(3)		//�|���S���̐�

//================================
// �~�j�Q�[����ՃN���X
//================================
class CButtonPushGame : public CMiniGameBasis
{
public:

	enum CLEAR
	{
		CLEAR_NONE = 0,	//�����ɓ����Ă��Ȃ����
		CLEAR_IN,		//�������
		CLEAR_OUT,		//��������Ȃ����
		CLEAR_MAX
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
	CObject2D *pObj2D[MAX_OBJECT];
	D3DXCOLOR m_col[MAX_OBJECT];
	D3DXVECTOR3 m_move;		//�ړ�
	CLEAR m_flash;			//�t���b�V�����
	int m_nCount;			//�J�E���g
	bool m_bStop;			//�~�܂邩�ǂ���
	bool m_bEdge;			//�[�ɂ��ǂ蒅�������ǂ���
};

#endif