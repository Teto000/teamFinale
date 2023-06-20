//===================================================
//
// ミニゲーム基盤処理
// Author : Kajita Hiromu
//
//===================================================

//----------------------
// インクルード
//----------------------
#include "mini_game_basis.h"
#include "application.h"
#include "renderer.h"

#include "mini_game_buttonpush.h"
#include "mg_buttonmash.h"
#include "mg_stickrotate.h"
#include "player.h"

//=======================
// コンストラクタ
//=======================
CMiniGameBasis::CMiniGameBasis() : CObject2D(1)
{
	m_bDraw = false;	//描画フラグ
}

//=======================
// デストラクタ
//=======================
CMiniGameBasis::~CMiniGameBasis()
{

}

//=======================
// 初期化
//=======================
HRESULT CMiniGameBasis::Init(D3DXVECTOR3 pos)
{
	//初期値の設定
	m_fWidth = 60.0f;
	m_fHeight = 80.0f;

	//オブジェクトの初期化
	CObject2D::Init(pos);

	//大きさの設定
	CObject2D::SetSize(m_fWidth, m_fHeight);

	//テクスチャの設定
	CObject2D::SetTexture(CTexture::TEXTURE_NONE);

	return S_OK;
}

//=======================
// 終了
//=======================
void CMiniGameBasis::Uninit()
{
	//オブジェクトの終了
	CObject2D::Uninit();
}

//=======================
// 更新
//=======================
void CMiniGameBasis::Update()
{
	//オブジェクトの更新
	CObject2D::Update();
}

//=======================
// 描画
//=======================
void CMiniGameBasis::Draw()
{
	if (!m_bDraw)
	{//描画しない状態なら
		return;
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//オブジェクトの描画
	CObject2D::Draw();

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=======================
// 生成
// 引数：位置、値、桁数
//=======================
CMiniGameBasis *CMiniGameBasis::Create(D3DXVECTOR3 pos, MiniGameType nType)
{
	CMiniGameBasis *pGameBasis = nullptr;

	//----------------------------------
	// ポリゴンの生成と初期化
	//----------------------------------
	//タイプごとに生成するものを決める
	switch (nType)
	{
	case TYPE_BUTTUNPUSH:
	{//ボタンプッシュゲーム
		pGameBasis = new CButtonPushGame;	//生成
	}

	break;

	case TYPE_BUTTONMASH:
	{//ボタン連打ゲーム
		pGameBasis = new CButtonMash;	//生成
	}
	break;

	case TYPE_STICKROTATE:
	{//スティック回転ゲーム
		pGameBasis = new CStickRotate;	//生成
	}
	break;

	default:
	{
	}

	break;

	}

	if (pGameBasis != nullptr)
	{//NULLチェック
	 //メンバ変数に代入
		pGameBasis->m_nType = nType;

		//初期化
		pGameBasis->Init(D3DXVECTOR3(pos));
		pGameBasis->SetObjType(OBJTYPE_MINIGAME);
	}

	return pGameBasis;
}

//=======================
// 拡縮
//=======================
void CMiniGameBasis::SetScaling(float fWidth, float fHeight)
{
	//幅と高さの設定
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	CObject2D::SetSize(m_fWidth, m_fHeight);
}