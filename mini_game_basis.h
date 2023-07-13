//===================================================
//
// �~�j�Q�[����Ճw�b�_�[
// Author : Kajita Hiromu
//
//===================================================
#ifndef _MINI_GAME_BASIS_H_
#define _MINI_GAME_BASIS_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "object2d.h"
#include "itemObj.h"

//-------------------------------
// �O���錾
//-------------------------------
class CGameCenter;

//================================
// �~�j�Q�[����ՃN���X
//================================
class CMiniGameBasis : public CObject2D
{
public:

	enum MiniGameType		//�~�j�Q�[���̎��
	{
		TYPE_NULL = -1,
		TYPE_BUTTUNPUSH = 0,
		TYPE_BUTTONMASH,
		TYPE_STICKROTATE,
		TYPE_MAX
	};

	CMiniGameBasis();				//�R���X�g���N�^
	~CMiniGameBasis() override;		//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// �Z�b�^�[
	//------------------
	void SetScaling(float fWidth, float fHeight);		//�g�k
	void SetEnable(bool bEnable) { m_bDraw = bEnable; }	//�`�悷�邩�ǂ���
	void SetParent(CGameCenter *pParent) { m_pParent = pParent; }
	void SetItemType(CItemObj::EItemType type) { m_ItemType = type; }
	void SetGame(bool bGame) { m_bGame = bGame; }
	CItemObj::EItemType GetItemType() { return m_ItemType; }

	//------------------
	// �Q�b�^�[
	//------------------
	MiniGameType GetGameType() { return m_nType; }
	CGameCenter *GetParent() { return m_pParent; }
	bool GetGame() { return m_bGame; }

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CMiniGameBasis* Create(D3DXVECTOR3 pos, int nType);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	MiniGameType m_nType;					// �~�j�Q�[���̎��
	CGameCenter *m_pParent;					// �e�I�u�W�F�N�g
	CItemObj::EItemType m_ItemType;
	bool m_bDraw;							// �`��t���O
	bool m_bGame;							// �Q�[�������ۂ�
};

#endif
