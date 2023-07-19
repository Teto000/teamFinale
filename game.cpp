//===================================================
//
// ゲームの処理
// Author : Sato Teruto
//
//===================================================

//------------------------
// インクルード
//------------------------
#include <time.h>
#include "game.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "debug_proc.h"
#include "sound.h"
#include "camera.h"
#include "fade.h"
#include "time.h"
#include "sky.h"
#include "meshfield.h"
#include "player.h"
#include "mini_game_basis.h"
#include "objectX.h"
#include "itemObj.h"
#include "collision.h"
#include "collision_rectangle3D.h"
#include "game_center.h"
#include "rubble.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CGame::fPastPosX = 2000.0f;			//過去移動時のX座標の変化量
bool		CGame::m_bFinish = false;			//ゲーム終了フラグ
CCamera*	CGame::m_pCamera = nullptr;			//カメラ
CTime*		CGame::m_pTime = nullptr;			//タイマー
CSky*		CGame::m_pSky = nullptr;			//空
CMeshField*	CGame::m_pMeshField = nullptr;		//地面
CObjectX*	CGame::m_pObjectX[nMaxObject] = {};	//オブジェクト
CObjectX*	CGame::m_pObjBG[nMaxBG];
CPlayer*	CGame::m_pPlayer[nMaxPlayer] = {};	//プレイヤー

//===========================
// コンストラクタ
//===========================
CGame::CGame()
{

}

//===========================
// デストラクタ
//===========================
CGame::~CGame()
{

}

//===========================
// 初期化
//===========================
HRESULT CGame::Init()
{
	// 変数宣言
	CCollision_Rectangle3D *pCollision = nullptr;

	//初期値の設定
	m_bFinish = false;	//ゲームが終了していない状態

	//------------------------
	// カメラの生成
	//------------------------
	m_pCamera = CCamera::Create((DWORD)0.0f, (DWORD)0.0f
								, (DWORD)SCREEN_WIDTH
								, (DWORD)SCREEN_HEIGHT);

	//メッシュフィールドの生成
	m_pMeshField = CMeshField::Create();

	//空の生成
	m_pSky = CSky::Create(CTexture::TEXTURE_SKY);

	//タイマーの生成
	m_pTime = CTime::Create(D3DXVECTOR3(1088.0f, 592.0f, 0.0f));
	m_pTime->SetCntTime(true);

	// プレイヤーの設定
	for (int i = 0; i < nMaxPlayer; i++)
	{
		m_pPlayer[i] = CPlayer::Create();
		m_pPlayer[i]->SetMotion("data/MOTION/motion.txt");
		m_pPlayer[i]->SetNumber(i);		//プレイヤー番号の設定

		pCollision = m_pPlayer[i]->GetCollision();
		pCollision->SetSize(D3DXVECTOR3(20.0f, 50.0f, 20.0f));
		pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	}

	//オブジェクトの生成関数
	CreateObj();

	//BGMの再生
	//CSound::PlaySound(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//===========================
// 終了
//===========================
void CGame::Uninit()
{
	//BGMの停止
	//CSound::StopSound();

	//---------------------
	// カメラの終了
	//---------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//===========================
// 更新
//===========================
void CGame::Update()
{
	//----------------------------
	// カメラの更新
	//----------------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	// ジョイパッドでの操作
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

#ifdef _DEBUG
	//-----------------------
	// 画面遷移
	//-----------------------
	if (!m_bFinish
		&& CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	{
		//ゲーム終了フラグを立てる
		m_bFinish = true;

		//リザルト画面に移行
		CMode::GetFade()->SetFade(CMode::MODE_RESULT);
	}

	if (CInputKeyboard::Trigger(DIK_L))
	{//Lキーを押したら
	 //ミニゲームの生成
		CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_BUTTONMASH);
	}

	if (CInputKeyboard::Trigger(DIK_M))
	{//Mキーを押したら
	 //ミニゲームの生成
		CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_STICKROTATE);
	}
#endif // DEBUG
}

//===========================
// オブジェクトの生成関数
//===========================
void CGame::CreateObj()
{
	// 変数宣言
	CCollision_Rectangle3D *pCollision = nullptr;

	/*m_pObjectX[0] = CItemObj::Create();
	m_pObjectX[0]->SetType(1);
	m_pObjectX[0]->SetPos(D3DXVECTOR3(0.0f, 0.0f, 100.0f));*/

	//-----------------------------------
	// オブジェクトの生成(時計)
	//-----------------------------------
	m_pObjectX[0] = CItemObj::Create();
	m_pObjectX[0]->SetType(17);
	m_pObjectX[0]->SetObjType(CObject::OBJTYPE_CLOCK);
	m_pObjectX[0]->SetPos(D3DXVECTOR3(0.0f, 0.0f, 200.0f));
	pCollision = m_pObjectX[0]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 60.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(50.0f, 120.0f, 50.0f));

	m_pObjectX[1] = CItemObj::Create();
	m_pObjectX[1]->SetType(17);
	m_pObjectX[1]->SetObjType(CObject::OBJTYPE_CLOCK);
	m_pObjectX[1]->SetPos(D3DXVECTOR3(fPastPosX, 0.0f, 200.0f));
	pCollision = m_pObjectX[1]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 60.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(50.0f, 120.0f, 50.0f));

	//-----------------------------------
	// ゲームセンターの設定
	//-----------------------------------
	CGameCenter* pGameCenter = CGameCenter::Create();
	pGameCenter->SetType(1);
	pGameCenter->SetGameType(CMiniGameBasis::TYPE_BUTTUNPUSH);
	pGameCenter->SetItemType(CItemObj::TYPE_WOOD);
	pGameCenter->SetPos(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(50.0f, 50.0f, 50.0f));

	//-----------------------------------
	// オブジェクトの生成(東屋)
	//-----------------------------------
	//綺麗な東屋
	pGameCenter = CGameCenter::Create();
	pGameCenter->SetType(18);
	pGameCenter->SetGameType(CMiniGameBasis::TYPE_BUTTUNPUSH);
	pGameCenter->SetPos(D3DXVECTOR3(1200.0f, 0.0f, 0.0f));
	pGameCenter->SetItemType(CItemObj::TYPE_WOOD);
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(90.0f, 90.0f, 90.0f));

	//壊れた東屋
	m_pObjectX[2] = CItemObj::Create();
	m_pObjectX[2]->SetType(19);
	m_pObjectX[2]->SetObjType(CObject::OBJTYPE_PAVILION_BREAK);
	m_pObjectX[2]->SetPos(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));

	/*pGameCenter = CGameCenter::Create();
	pGameCenter->SetType(19);
	pGameCenter->SetObjType(CObject::OBJTYPE_PAVILION_BREAK);
	pGameCenter->SetGameType(CMiniGameBasis::TYPE_NULL);
	pGameCenter->SetPos(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(90.0f, 90.0f, 90.0f));*/

	//-----------------------------------
	// オブジェクトの生成(噴水)
	//-----------------------------------
	//綺麗な噴水
	pGameCenter = CGameCenter::Create();
	pGameCenter->SetType(20);
	pGameCenter->SetGameType(CMiniGameBasis::TYPE_BUTTONMASH);
	pGameCenter->SetPos(D3DXVECTOR3(200.0f + fPastPosX, 0.0f, 400.0f));
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(150.0f, 100.0f, 150.0f));

	CRubble *pRubble = CRubble::Create();
	pRubble->SetPos(D3DXVECTOR3(200.0f, 0.0f, 200.0f));
	pRubble->SetBuildType(CRubble::TYPE_FOUNTAIN);
	pCollision = pRubble->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(150.0f, 100.0f, 150.0f));
	pRubble->SetRequired(1);
	std::vector<CRubble::REPAIR> repair;
	repair.clear();
	repair.resize(pRubble->GetRequired());
	repair.at(0).type = CItemObj::TYPE_WOOD;
	repair.at(0).nRequired = 4;
	pRubble->SetRepair(repair);

	//壊れた噴水
	m_pObjectX[3] = CItemObj::Create();
	m_pObjectX[3]->SetType(21);
	m_pObjectX[3]->SetObjType(CObject::OBJTYPE_FOUNTAIN_BREAK);
	m_pObjectX[3]->SetPos(D3DXVECTOR3(200.0f, 0.0f, -100.0f));

	//木の生成
	CreateWood();
}

//================================
// 背景オブジェクト(木)の生成
//================================
void CGame::CreateWood()
{
	for (int i = 0; i < nMaxBG; i++)
	{
		if (i < 12)
		{//左の木
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-450.0f, 0.0f, 500.0f - (100.0f * i)));
		}
		else if (i < 25)
		{//右の木
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(450.0f, 0.0f, 500.0f - (100.0f * (i - 13))));
		}
		else if (i < 38)
		{//上の木
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + (100.0f * (i - 26)), 0.0f, 450.0f));
		}
		else if (i < 51)
		{//下の木
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + (100.0f * (i - 39)), 0.0f, -450.0f));
		}
	}
}