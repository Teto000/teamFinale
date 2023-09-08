//=============================================================================
//
// ���I�N���X(rubble.h)
// Author : �������l
// �T�v : ���I�������s��
//
//=============================================================================
#ifndef _RUBBLE_H_			// ���̃}�N����`������ĂȂ�������
#define _RUBBLE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <vector>
#include "objectX.h"
#include "itemObj.h"
#include "texture.h"

//--------------------------------
// �O���錾
//--------------------------------
class CLine;
class CItemMark;

//=============================================================================
// ���f���I�u�W�F�N�g�N���X
// Author : �������l
// �T�v : ���f���I�u�W�F�N�g�������s���N���X
//=============================================================================
class CRubble : public CObjectX
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CRubble *Create();	// ���f���I�u�W�F�N�g�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CRubble();
	~CRubble();

	//--------------------------------------------------------------------
	// �A�C�e���̎�ނ̗񋓌^
	//--------------------------------------------------------------------
	enum EBuildType
	{
		TYPE_NONE = 0,
		TYPE_PAVILION,
		TYPE_FOUNTAIN,
		TYPE_SLIDE,
		TYPE_SWING,
		TYPE_SEESAW,
		MAX_TYPE,
	};

	//--------------------------------------------------------------------
	// �C��
	//--------------------------------------------------------------------
	struct REPAIR
	{
		CItemObj::EItemType type;			// �A�C�e���^�C�v
		int nRequired;						// �K�v��
		int nCutRequired;					// �K�v���J�E���g
		bool bCompletion;					// ����
	};

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init(D3DXVECTOR3 pos) override;										// ������
	void Uninit() override;														// �I��
	void Update() override;														// �X�V
	void Draw() override;														// �`��
	void Repair(CItemObj *pItem);
	void SetRepair(std::vector<REPAIR> repair) { m_repair = repair; }
	void SetRequired(int nRequired) { m_nRequired = nRequired; }
	void SetBuildType(EBuildType buildType);
	void SetMark(D3DXVECTOR3 pos, CTexture::NUM_TEXTURE tex);	// �����o���̐���
	int GetRequired() { return m_nRequired; }

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Complete();
	void SetLine();

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	std::vector<REPAIR> m_repair;			// �C��
	CLine **m_pLine;						// ���C�����
	D3DXCOLOR m_lineCol;					// ���C���̐F
	EBuildType m_buildType;					// �����̃^�C�v
	CItemMark* m_pItemMark;					// �����o��
	int m_nRequired;						// �C����
	int m_nCntRequired;						// �C�����J�E���g
	bool m_bComplete;						// ����Flag
};

#endif



