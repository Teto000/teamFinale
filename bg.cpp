//===================================================
//
// 背景の処理
// Author:Teruto Sato
//
//===================================================

//------------------------
// インクルード
//------------------------
#include "bg.h"
#include "renderer.h"
#include "texture.h"

//========================
// コンストラクタ
//========================
CBg::CBg() : CObject(1)
{
	m_pObject2D = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_fWidth = 0.0f;	//幅
	m_fHeight = 0.0f;	//高さ
}

//========================
// デストラクタ
//========================
CBg::~CBg()
{

}

//========================
// 初期化
//========================
HRESULT CBg::Init(D3DXVECTOR3 pos)
{
	//初期値の設定
	m_pos = pos;
	m_fWidth = SCREEN_WIDTH;
	m_fHeight = SCREEN_HEIGHT;

	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Init(m_pos);

		//-------------------------
		// 種類ごとの処理
		//-------------------------
		switch (m_type)
		{
		//タイトル画面の背景
		case BGTYPE_TITLE:
			m_pObject2D->SetTexture(CTexture::TEXTURE_TITLE);
			break;

		//リザルト画面の背景
		case BGTYPE_RESULT:
			m_pObject2D->SetTexture(CTexture::TEXTURE_RESULT);
			break;

		default:
			break;
		}

		m_pObject2D->SetSize(m_fWidth, m_fHeight);
	}

	return S_OK;
}

//========================
// 終了
//========================
void CBg::Uninit()
{

}

//========================
// 更新
//========================
void CBg::Update()
{
	
}

//========================
// 描画
//========================
void CBg::Draw()
{

}

//========================
// 生成
//========================
CBg* CBg::Create(D3DXVECTOR3 pos, BGTYPE type)
{
	CBg *pBg = nullptr;

	//----------------------------------
	// 背景の生成と初期化
	//----------------------------------
	pBg = new CBg;	//生成
	pBg->m_pObject2D = new CObject2D(1);

	if (pBg != nullptr)
	{//NULLチェック
		//変数に代入
		pBg->m_type = type;

		//初期化
		pBg->Init(pos);
	}

	return pBg;
}