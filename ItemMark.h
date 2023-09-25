//===================================================
//
// アイテム目印ヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _ITEMMARK_H_
#define _ITEMMARK_H_	//二重インクルード防止

//-------------------------
// インクルード
//-------------------------
#include "billboard.h"

//================================
// アイテム目印クラス
//================================
class CItemMark : public CBillBoard
{
public:
	CItemMark();			// コンストラクタ
	~CItemMark() override;	// デストラクタ

	//----------------------
	// メンバ関数
	//----------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetValue(int nValue);	// 値の設定

	//----------------------
	// 静的メンバ関数
	//----------------------
	static CItemMark* Create(D3DXVECTOR3 pos);

private:
	//----------------------
	// メンバ関数
	//----------------------
	void ChangeTexture();	// テクスチャの切り替え

	//----------------------
	// メンバ変数
	//----------------------
	int m_nValue;	// 値
};

#endif