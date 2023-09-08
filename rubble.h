//=============================================================================
//
// ¢âINX(rubble.h)
// Author : ú±l
// Tv : ¢âI¶¬ðs¤
//
//=============================================================================
#ifndef _RUBBLE_H_			// ±Ì}Nè`ª³êÄÈ©Á½ç
#define _RUBBLE_H_			// ñdCN[hh~Ì}Nè`

//*****************************************************************************
// CN[h
//*****************************************************************************
#include <vector>
#include "objectX.h"
#include "itemObj.h"
#include "texture.h"

//--------------------------------
// Oûé¾
//--------------------------------
class CLine;
class CItemMark;

//=============================================================================
// fIuWFNgNX
// Author : ú±l
// Tv : fIuWFNg¶¬ðs¤NX
//=============================================================================
class CRubble : public CObjectX
{
public:
	//--------------------------------------------------------------------
	// ÃIoÖ
	//--------------------------------------------------------------------
	static CRubble *Create();	// fIuWFNgÌ¶¬

	//--------------------------------------------------------------------
	// RXgN^ÆfXgN^
	//--------------------------------------------------------------------
	CRubble();
	~CRubble();

	//--------------------------------------------------------------------
	// ACeÌíÞÌñ^
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
	// C
	//--------------------------------------------------------------------
	struct REPAIR
	{
		CItemObj::EItemType type;			// ACe^Cv
		int nRequired;						// Kv
		int nCutRequired;					// KvJEg
		bool bCompletion;					// ®¹
	};

	//--------------------------------------------------------------------
	// oÖ
	//--------------------------------------------------------------------
	HRESULT Init(D3DXVECTOR3 pos) override;										// ú»
	void Uninit() override;														// I¹
	void Update() override;														// XV
	void Draw() override;														// `æ
	void Repair(CItemObj *pItem);
	void SetRepair(std::vector<REPAIR> repair) { m_repair = repair; }
	void SetRequired(int nRequired) { m_nRequired = nRequired; }
	void SetBuildType(EBuildType buildType);
	void SetMark(D3DXVECTOR3 pos, CTexture::NUM_TEXTURE tex);	// «oµÌ¶¬
	int GetRequired() { return m_nRequired; }

private:
	//--------------------------------------------------------------------
	// oÖ
	//--------------------------------------------------------------------
	void Complete();
	void SetLine();

	//--------------------------------------------------------------------
	// oÏ
	//--------------------------------------------------------------------
	std::vector<REPAIR> m_repair;			// C
	CLine **m_pLine;						// Cîñ
	D3DXCOLOR m_lineCol;					// CÌF
	EBuildType m_buildType;					// ¨Ì^Cv
	CItemMark* m_pItemMark;					// «oµ
	int m_nRequired;						// C
	int m_nCntRequired;						// CJEg
	bool m_bComplete;						// ®¹Flag
};

#endif



