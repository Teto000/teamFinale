//===================================================
//
// アイテムの目印を表示する処理
// Author : Sato Teruto
//
//===================================================

//---------------------------
// インクルード
//---------------------------
#include "ItemMark.h"

//======================================
// コンストラクタ
//======================================
CItemMark::CItemMark()
{
}

//======================================
// デストラクタ
//======================================
CItemMark::~CItemMark()
{
}

//======================================
// 初期化
//======================================
HRESULT CItemMark::Init(D3DXVECTOR3 pos)
{
	CBillBoard::Init(pos);

	return S_OK;
}

//======================================
// 終了
//======================================
void CItemMark::Uninit()
{
	CBillBoard::Uninit();
}

//======================================
// 更新
//======================================
void CItemMark::Update()
{
	CBillBoard::Update();

	//テクスチャの切り替え
	ChangeTexture();
}

//======================================
// 描画
//======================================
void CItemMark::Draw()
{
	CBillBoard::Draw();
}

//======================================
// 生成
//======================================
CItemMark* CItemMark::Create(D3DXVECTOR3 pos)
{
	CItemMark* pItemMark = nullptr;

	//----------------------------------
	// ポリゴンの生成と初期化
	//----------------------------------
	pItemMark = new CItemMark;	//生成

	if (pItemMark != nullptr)
	{//NULLチェック
		//初期化
		pItemMark->Init(D3DXVECTOR3(pos));
	}

	return pItemMark;
}

//======================================
// 値の設定
//======================================
void CItemMark::SetValue(int nValue)
{
	m_nValue = nValue;
}

//======================================
// テクスチャの切り替え
//======================================
void CItemMark::ChangeTexture()
{
	switch (m_nValue)
	{
	case 4:
		SetTexture(CTexture::TEXTURE_FUKIDASI4);
		break;

	case 3:
		SetTexture(CTexture::TEXTURE_FUKIDASI3);
		break;

	case 2:
		SetTexture(CTexture::TEXTURE_FUKIDASI2);
		break;

	case 1:
		SetTexture(CTexture::TEXTURE_FUKIDASI);
		break;

	default:
		break;
	}
}