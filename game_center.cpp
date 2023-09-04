//=============================================================================
//
// ゲームセンタークラス(game_center.h)
// Author : 唐﨑結斗
// 概要 : ゲームセンター生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>
#include <stdio.h>

#include "game_center.h"
#include "application.h"
#include "renderer.h"
#include "model3D.h"
#include "collision_rectangle3D.h"
#include "player.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : インスタンスを生成する
//=============================================================================
CGameCenter * CGameCenter::Create()
{
	// オブジェクトインスタンス
	CGameCenter *pGameCenter = nullptr;

	// メモリの解放
	pGameCenter = new CGameCenter;

	// メモリの確保ができなかった
	assert(pGameCenter != nullptr);

	// 数値の初期化
	pGameCenter->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// インスタンスを返す
	return pGameCenter;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CGameCenter::CGameCenter() : m_EMiniGameType(CMiniGameBasis::TYPE_NULL),
m_pPlayer(nullptr),
m_pMiniGameBasis(nullptr),
m_bGame(false)
{
	// オブジェクトタイプ
	SetObjType(OBJTYPE_MINIGAME);
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CGameCenter::~CGameCenter()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CGameCenter::Init(D3DXVECTOR3 pos)
{
	// モデルオブジェクトの初期化
	CObjectX::Init(pos);

	return E_NOTIMPL;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CGameCenter::Uninit()
{
	// モデルオブジェクトの終了
	CObjectX::Uninit();

	// オブジェクトの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 更新を行う
//=============================================================================
void CGameCenter::Update()
{
	// モデルオブジェクトの更新
	CObjectX::Update();
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CGameCenter::Draw()
{
	// モデルオブジェクトの描画
	CObjectX::Draw();
}

void CGameCenter::SetGame(bool bGame)
{
	m_bGame = bGame;

	if (m_bGame && m_EMiniGameType != CMiniGameBasis::TYPE_NULL)
	{//ゲーム中 & ミニゲームがnullじゃないなら
		m_pMiniGameBasis = CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), m_EMiniGameType);
		m_pMiniGameBasis->SetParent(this);
		m_pMiniGameBasis->SetGame(true);
		m_pMiniGameBasis->SetItemType(m_ItemType);
		m_pMiniGameBasis->SetPlayer(m_pPlayer);

		m_pPlayer->SetUpdate(true);
	}
}
