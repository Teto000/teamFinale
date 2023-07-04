//=============================================================================
//
// �v���C���[�N���X(player.h)
// Author : �������l
// �T�v : �v���C���[�������s��
//
//=============================================================================
#ifndef _PLAYER_H_			// ���̃}�N����`������ĂȂ�������
#define _PLAYER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "motion_model3D.h"

//--------------------------------
// �O���錾
//--------------------------------
class CMove;
class CObjectX;
class CObject2D;
class CItemObj;
class CLine;

//=============================================================================
// �v���C���[�N���X
// Author : �������l
// �T�v : �v���C���[�������s���N���X
//=============================================================================
class CPlayer : public CMotionModel3D
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CPlayer *Create();			// �v���C���[�̐���

	//--------------------------------------------------------------------
	// �ÓI�����o�ϐ�
	//--------------------------------------------------------------------
	static const UPDATE_FUNC m_UpdateFunc[];

	//--------------------------------------------------------------------
	// �v���C���[�̃A�N�V�����̗񋓌^
	//--------------------------------------------------------------------
	enum ACTION_TYPE
	{
		// �ʏ�
		NEUTRAL_ACTION = 0,		// �j���[�g����
		MOVE_ACTION,			// �ړ�
		ATTACK_ACTION,			// �U��
		ATTACK_JUMP,			// �W�����v
		ATTACK_LANDING,			// ���n 
		MAX_ACTION,				// �ő吔
	};

	//--------------------------------------------------------------------
	// �v���C���[�̏�Ԃ̗񋓌^
	//--------------------------------------------------------------------
	enum EState
	{
		STATE_IDEl = 0,
		STATE_WALK,
		STATE_JUMP,
		STATE_MAX,
		STATE_INVALID,
	};

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CPlayer();
	~CPlayer();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init(D3DXVECTOR3 pos) override;		// ������
	void Uninit() override;						// �I��
	void Update() override;						// �X�V
	void Draw() override;						// �`��
	void Retention(CItemObj *pItem);			// �A�C�e���ێ�
	void Drop();								// �A�C�e���̕ێ�����

	// �X�V
	void Update_Idel();
	void Update_Walk();
	void Update_Jump();

	// �Z�b�^�[
	void SetNumber(int nNum) { m_nNumber = nNum; }				// �v���C���[�ԍ��̐ݒ�
	void SetMiniGame(bool bMiniGame);							// �~�j�Q�[�������ǂ����̐ݒ�
	
	// �Q�b�^�[
	CItemObj* GetMyItem() { return m_pMyItem; }					// �擾�A�C�e���̃Q�b�^�[
	int GetParentParts() { return m_nParentParts; }				// �e�p�[�c�̃Q�b�^�[
	bool GetMiniGame() { return m_bMiniGame; }					// �~�j�Q�[�������ǂ����̎擾

private:
	//--------------------------------------------------------------------
	// �萔
	//--------------------------------------------------------------------
	static const int nMaxGetTime = 20;	//�A�C�e���擾�̃��L���X�g�^�C��

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	D3DXVECTOR3 Move(int nUpKey, int nDownKey
					, int nLeftKey, int nRightKey);		// �ړ�
	void Rotate();							// ��]
	D3DXVECTOR3 Warp(D3DXVECTOR3 pos);		// ���[�v
	void Collision();						// �����蔻��
	void LimitMove(D3DXVECTOR3 pos);		// �ړ��̌��E

	/* �� �I�u�W�F�N�g���Ƃ̓����蔻�� �� */
	void Coll_Pavilion(D3DXVECTOR3 size, CObjectX* pObject);	// ����
	void Coll_Item(D3DXVECTOR3 size, CObjectX* pObject);		// �A�C�e��
	void Coll_Clock(D3DXVECTOR3 size, CObjectX* pObject);		// ���v

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CMove *m_pMove;				// �ړ����
	CItemObj *m_pMyItem;		// �����A�C�e��
	ACTION_TYPE m_EAction;		// �A�N�V�����^�C�v
	ACTION_TYPE m_EActionOld;	// �A�N�V�����^�C�v�̃o�b�N�A�b�v
	D3DXVECTOR3 m_rotDest;		// �ړI�̌���
	int m_nNumMotion;			// ���݂̃��[�V�����ԍ�
	int m_nCntGetTime;			// �A�C�e�����擾�ł��鎞�Ԃ𐔂���
	int m_nCntRimit;			// �ߋ��Ɏc��鎞�Ԃ𐔂���
	int m_nParentParts;			// �e�p�[�c�̔ԍ�
	int m_nNumber;				// �v���C���[�ԍ�
	bool m_bMiniGame;			// �~�j�Q�[�������ǂ���
	bool m_bGetItem;			// �A�C�e�����擾�ł�����

	//--------------------------------------------------------------------
	// �ÓI�����o�ϐ�
	//--------------------------------------------------------------------
	static bool m_bPast;		// �ߋ��ɂ��邩�ǂ���
	CLine **m_pLine;			// ���C���̏��
	D3DXCOLOR lineCol;			// ���C���̐F
	bool m_bCrate;				// �r������������
	static bool m_bWarp;		// ���[�v�����Ԃ��ǂ���
};

#endif
