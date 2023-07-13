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

//--------------------------------
// �O���錾
//--------------------------------
class CMove;

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
	// �A�C�e���̎�ނ̗񋓌^
	//--------------------------------------------------------------------
	enum EItemType
	{
		TYPE_NONE = 0,
		TYPE_WOOD,
		TYPE_STONE,
		TYPE_METAL,
		MAX_TYPE,
	};

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init(D3DXVECTOR3 pos) override;											// ������
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��
	void Stack(CItemObj *pTarget);													// �ςݏd��
	CItemObj* SearchChild();																// �q���̌���
	void SetParent(CModel3D *pParent);												// �e�̐ݒ�
	void SetParent();																// �e�̐ݒ����
	void SetParentItem(CObject *pParentItem) { m_pParentItem = pParentItem; }		// �e�̐ݒ�
	void SetParentItem() { m_pParentItem = nullptr; }								// �e�̐ݒ�
	void SetChildItem(CObject *pChildItem) { m_pChildItem = pChildItem; }			// �q���̐ݒ�
	void SetChildItem() { m_pChildItem = nullptr; }								 	// �q���̐ݒ�
	void SetPosOffset(D3DXVECTOR3 posOffset) { m_posOffset = posOffset; }			// �ʒu�̍����̐ݒ�
	void SetRotOffset(D3DXVECTOR3 rotOffset) { m_rotOffset = rotOffset; }			// �����̍����̐ݒ�
	void SetItemType(EItemType type) { m_Type = type; }								// 
	CModel3D *GetParent() { return m_pParent; }										// �e���̎擾
	CObject *GetParentItem() { return m_pParentItem; }								// �e�̐ݒ�
	CObject *GetChildItem() { return m_pChildItem; }								// �q���̐ݒ�
	EItemType GetItemType() { return m_Type; }										// ��ʂ̎擾
private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Stack();			// �ςݏd��

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CObject *m_pParentItem;			// �e�I�u�W�F�̏��
	CObject *m_pChildItem;			// �q���I�u�W�F�̏��
	CModel3D *m_pParent;			// �e���f���̏��
	EItemType m_Type;				// �A�C�e���̎��
	D3DXVECTOR3 m_posOffset;		// �ʒu�̍���
	D3DXVECTOR3 m_rotOffset;		// �����̍���
};

#endif


