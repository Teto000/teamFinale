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

//------------------------
// 静的メンバ変数宣言
//------------------------
bool		CGame::m_bFinish = false;			//ゲーム終了フラグ
CCamera*	CGame::m_pCamera = nullptr;			//カメラ
CTime*		CGame::m_pTime = nullptr;			//タイマー
CSky*		CGame::m_pSky = nullptr;			//空
CMeshField*	CGame::m_pMeshField = nullptr;		//地面
CObjectX*	CGame::m_pObjectX[nMaxObject] = {};	//オブジェクト
CPlayer*	CGame::m_pPlayer[nMaxPlayer] = {};	//プレイヤー

//===========================
// コンストラクタ
//===========================
CGame::CGame()
{
	for (int i = 0; i < nMaxObjBG; i++)
	{
		m_pObj[i];
	}
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

		CCollision_Rectangle3D *pCollision = m_pPlayer[i]->GetCollision();
		pCollision->SetSize(D3DXVECTOR3(20.0f, 50.0f, 20.0f));
		pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	}

	m_pObjectX[0] = CItemObj::Create();
	m_pObjectX[0]->SetType(1);
	m_pObjectX[0]->SetPos(D3DXVECTOR3(0.0f, 0.0f, 100.0f));

	//-----------------------------------
	// オブジェクトの生成(時計)
	//-----------------------------------
	m_pObjectX[1] = CItemObj::Create();
	m_pObjectX[1]->SetType(17);
	m_pObjectX[1]->SetObjType(CObject::OBJTYPE_CLOCK);
	m_pObjectX[1]->SetPos(D3DXVECTOR3(0.0f, 0.0f, 200.0f));

	m_pObjectX[2] = CItemObj::Create();
	m_pObjectX[2]->SetType(17);
	m_pObjectX[2]->SetObjType(CObject::OBJTYPE_CLOCK);
	m_pObjectX[2]->SetPos(D3DXVECTOR3(1000.0f, 0.0f, 200.0f));

	//-----------------------------------
	// オブジェクトの生成(東屋)
	//-----------------------------------
	m_pObjectX[3] = CItemObj::Create();
	m_pObjectX[3]->SetType(18);
	m_pObjectX[3]->SetObjType(CObject::OBJTYPE_PAVILION);
	m_pObjectX[3]->SetPos(D3DXVECTOR3(1200.0f, 0.0f, 0.0f));

	m_pObjectX[4] = CItemObj::Create();
	m_pObjectX[4]->SetType(19);
	m_pObjectX[4]->SetObjType(CObject::OBJTYPE_PAVILION_BREAK);
	m_pObjectX[4]->SetPos(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));

	//-----------------------------------
	// オブジェクトの生成(ビル)
	//-----------------------------------
	{
		for (int i = 0; i < 4; i++)
		{
			//ビル*4
			m_pObj[i] = CObjectX::Create();
			m_pObj[i]->SetType(10);
			m_pObj[i]->SetPos(D3DXVECTOR3(-600.0f + (i * 400.0f), 0.0f, 800.0f));
		}
	}

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

	//-----------------------
	// 画面遷移
	//-----------------------
	if (!m_bFinish
		&& CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	{
		//ゲーム終了フラグを立てる
		m_bFinish = true;

		//リザルト画面に移行
		CApplication::GetFade()->SetFade(CApplication::MODE_RESULT);
	}

	if (CInputKeyboard::Trigger(DIK_M))
	{//Mキーを押したら
		//ミニゲームの生成
		CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_STICKROTATE);
	}
}