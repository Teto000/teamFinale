//=============================================================================
//
// アイテムクラス(itemObj.h)
// Author : 唐﨑結斗
// 概要 : アイテム生成を行う
//
//=============================================================================
#ifndef _ITEMOBJ_H_			// このマクロ定義がされてなかったら
#define _ITEMOBJ_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "objectX.h"

//--------------------------------
// 前方宣言
//--------------------------------
class CMove;

//=============================================================================
// モデルオブジェクトクラス
// Author : 唐﨑結斗
// 概要 : モデルオブジェクト生成を行うクラス
//=============================================================================
class CItemObj : public CObjectX
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CItemObj *Create();	// モデルオブジェクトの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CItemObj();
	~CItemObj();

	//--------------------------------------------------------------------
	// アイテムの種類の列挙型
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
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init(D3DXVECTOR3 pos) override;											// 初期化
	void Uninit() override;															// 終了
	void Update() override;															// 更新
	void Draw() override;															// 描画
	void Stack(CItemObj *pTarget);													// 積み重ね
	CItemObj* SearchChild();																// 子供の検索
	void SetParent(CModel3D *pParent);												// 親の設定
	void SetParent();																// 親の設定解除
	void SetParentItem(CObject *pParentItem) { m_pParentItem = pParentItem; }		// 親の設定
	void SetParentItem() { m_pParentItem = nullptr; }								// 親の設定
	void SetChildItem(CObject *pChildItem) { m_pChildItem = pChildItem; }			// 子供の設定
	void SetChildItem() { m_pChildItem = nullptr; }								 	// 子供の設定
	void SetPosOffset(D3DXVECTOR3 posOffset) { m_posOffset = posOffset; }			// 位置の差分の設定
	void SetRotOffset(D3DXVECTOR3 rotOffset) { m_rotOffset = rotOffset; }			// 向きの差分の設定
	void SetItemType(EItemType type) { m_Type = type; }								// 
	CModel3D *GetParent() { return m_pParent; }										// 親情報の取得
	CObject *GetParentItem() { return m_pParentItem; }								// 親の設定
	CObject *GetChildItem() { return m_pChildItem; }								// 子供の設定
	EItemType GetItemType() { return m_Type; }										// 種別の取得
private:
	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	void Stack();			// 積み重ね

	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	CObject *m_pParentItem;			// 親オブジェの情報
	CObject *m_pChildItem;			// 子供オブジェの情報
	CModel3D *m_pParent;			// 親モデルの情報
	EItemType m_Type;				// アイテムの種別
	D3DXVECTOR3 m_posOffset;		// 位置の差分
	D3DXVECTOR3 m_rotOffset;		// 向きの差分
};

#endif


