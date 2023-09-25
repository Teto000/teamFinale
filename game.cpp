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
#include "ItemMark.h"
#include "score.h"
#include "model3D.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CGame::fPastPosX = 3000.0f;				//過去移動時のX座標の変化量
bool		CGame::m_bFinish = false;				//ゲーム終了フラグ
CCamera*	CGame::m_pCamera = nullptr;				//カメラ
CTime*		CGame::m_pTime = nullptr;				//タイマー
CSky*		CGame::m_pSky = nullptr;				//空
CMeshField*	CGame::m_pMeshField = nullptr;			//地面
CMeshField* CGame::m_pMeshField2 = nullptr;			//地面2
CMeshField* CGame::m_pCityField = nullptr;			//町のフィールド
CObjectX*	CGame::m_pObjectX[nMaxObject] = {};		//オブジェクト
CObjectX*	CGame::m_pObjBG[nMaxBG];				//背景オブジェクト
CPlayer*	CGame::m_pPlayer[nMaxPlayer] = {};		//プレイヤー
CRubble*	CGame::m_pRubble[nMaxRubble] = {};
CScore*		CGame::m_pScore = nullptr;				//スコア
CObject2D*	CGame::m_pObjUI = nullptr;

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
	m_pCamera = CCamera::Create();

	m_pMeshField2 = CMeshField::Create(12.0f, 5500.0f);
	m_pMeshField2->SetPos(D3DXVECTOR3(500.0f, -5.0f, 0.0f));
	m_pMeshField2->SetTexture(CTexture::TEXTURE_GROUND);
	//メッシュフィールドの生成
	m_pMeshField = CMeshField::Create(12.0f, 1000.0f);
	m_pMeshField->SetTexture(CTexture::TEXTURE_GROUND);

	m_pCityField = CMeshField::Create(12.0f, 2500.0f);
	m_pCityField->SetPos(D3DXVECTOR3(fPastPosX, 0.0f, 0.0f));
	m_pCityField->SetTexture(CTexture::TEXTURE_GROUND_DART);

	//空の生成
	m_pSky = CSky::Create(CTexture::TEXTURE_SKY);

	//タイマーの生成
	m_pTime = CTime::Create(
		D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f));
	m_pTime->SetCntTime(true);

	//スコアの生成
	{
		D3DXVECTOR3 pos(1000.0f, 630.0f, 0.0f);
		m_pScore = CScore::Create(pos);
	}

	//操作方法の表示
	m_pObjUI = new CObject2D(1);

	if (m_pObjUI)
	{
		m_pObjUI->Init(D3DXVECTOR3(200.0f, 600.0f, 0.0f));
		m_pObjUI->SetSize(300.0f, 200.0f);
		m_pObjUI->SetTexture(CTexture::TEXTURE_UI_MANUAL);
	}

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
	//if (!m_bFinish
	//	&& CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	//{
	//	//ゲーム終了フラグを立てる
	//	m_bFinish = true;

	//	//リザルト画面に移行
	//	CMode::GetFade()->SetFade(CMode::MODE_RESULT);
	//}

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
	int size = 1.25f;
	D3DXVECTOR3 dSize = D3DXVECTOR3(size, size, size);

	//-----------------------------------
	// オブジェクトの生成(時計)
	//-----------------------------------
	m_pObjectX[0] = CItemObj::Create();
	m_pObjectX[0]->SetType(17);
	m_pObjectX[0]->SetObjType(CObject::OBJTYPE_CLOCK);
	m_pObjectX[0]->SetPos(D3DXVECTOR3(0.0f, 0.0f, 200.0f));
	m_pObjectX[0]->GetModel()->SetSize(dSize);
	pCollision = m_pObjectX[0]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 60.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(50.0f, 120.0f, 50.0f));

	m_pObjectX[1] = CItemObj::Create();
	m_pObjectX[1]->SetType(17);
	m_pObjectX[1]->SetObjType(CObject::OBJTYPE_CLOCK);
	m_pObjectX[1]->SetPos(D3DXVECTOR3(fPastPosX, 0.0f, 200.0f));
	m_pObjectX[1]->GetModel()->SetSize(dSize);
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
	pGameCenter->SetPos(D3DXVECTOR3(200.0f + fPastPosX, 0.0f, 0.0f));
	pGameCenter->SetItemType(CItemObj::TYPE_WOOD);
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(90.0f, 90.0f, 90.0f));

	//壊れた東屋
	m_pRubble[0] = CRubble::Create();
	m_pRubble[0]->SetPos(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));
	m_pRubble[0]->SetBuildType(CRubble::TYPE_PAVILION);
	pCollision = m_pRubble[0]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(90.0f, 90.0f, 90.0f));
	m_pRubble[0]->SetRequired(1);
	std::vector<CRubble::REPAIR> repair;
	repair.clear();
	repair.resize(m_pRubble[0]->GetRequired());
	repair.at(0).type = CItemObj::TYPE_WOOD;
	repair.at(0).nRequired = 1;
	m_pRubble[0]->SetRepair(repair);

	//東屋を直すのに必要なアイテムの目印
	m_pRubble[0]->SetMark(D3DXVECTOR3(-200.0f, 130.0f, 0.0f), CTexture::TEXTURE_FUKIDASI);

	//m_pObjectX[2] = CItemObj::Create();
	//m_pObjectX[2]->SetType(19);
	//m_pObjectX[2]->SetObjType(CObject::OBJTYPE_PAVILION_BREAK);
	//m_pObjectX[2]->SetPos(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));

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
	pGameCenter->GetModel()->SetSize(dSize);
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(150.0f, 100.0f, 150.0f));

	//壊れた噴水
	m_pRubble[1] = CRubble::Create();
	m_pRubble[1]->SetPos(D3DXVECTOR3(200.0f, 0.0f, 200.0f));
	m_pRubble[1]->SetBuildType(CRubble::TYPE_FOUNTAIN);
	pCollision = m_pRubble[1]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(150.0f, 100.0f, 150.0f));
	m_pRubble[1]->SetRequired(1);
	repair.clear();
	repair.resize(m_pRubble[1]->GetRequired());
	repair.at(0).type = CItemObj::TYPE_WOOD;
	repair.at(0).nRequired = 4;
	m_pRubble[1]->SetRepair(repair);

	//噴水を直すのに必要なアイテムの目印
	m_pRubble[1]->SetMark(D3DXVECTOR3(200.0f, 130.0f, 200.0f), CTexture::TEXTURE_FUKIDASI4);

	//壊れた噴水
	/*m_pObjectX[3] = CItemObj::Create();
	m_pObjectX[3]->SetType(21);
	m_pObjectX[3]->SetObjType(CObject::OBJTYPE_FOUNTAIN_BREAK);
	m_pObjectX[3]->SetPos(D3DXVECTOR3(200.0f, 0.0f, -100.0f));*/

	//-----------------------------------
	// オブジェクトの生成(滑り台)
	//-----------------------------------
	//綺麗な滑り台
	pGameCenter = CGameCenter::Create();
	pGameCenter->SetType(26);
	pGameCenter->SetGameType(CMiniGameBasis::TYPE_BUTTUNPUSH);
	pGameCenter->SetPos(D3DXVECTOR3(-200.0f + fPastPosX, 0.0f, 0.0f));
	pGameCenter->SetItemType(CItemObj::TYPE_WOOD);
	pGameCenter->GetModel()->SetSize(dSize);
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(140.0f, 90.0f, 50.0f));

	//壊れた滑り台
	m_pRubble[2] = CRubble::Create();
	m_pRubble[2]->SetPos(D3DXVECTOR3(200.0f, 0.0f, 0.0f));
	m_pRubble[2]->SetBuildType(CRubble::TYPE_SLIDE);
	pCollision = m_pRubble[2]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 30.0f));
	pCollision->SetSize(D3DXVECTOR3(140.0f, 90.0f, 50.0f));
	m_pRubble[2]->SetRequired(1);
	repair.clear();
	repair.resize(m_pRubble[2]->GetRequired());
	repair.at(0).type = CItemObj::TYPE_WOOD;
	repair.at(0).nRequired = 1;
	m_pRubble[2]->SetRepair(repair);

	//滑り台を直すのに必要なアイテムの目印
	m_pRubble[2]->SetMark(D3DXVECTOR3(200.0f, 130.0f, 0.0f), CTexture::TEXTURE_FUKIDASI);

	//m_pObjectX[4] = CItemObj::Create();
	//m_pObjectX[4]->SetType(27);
	//m_pObjectX[4]->SetObjType(CObject::OBJTYPE_SLIDE_BREAK);
	//m_pObjectX[4]->SetPos(D3DXVECTOR3(200.0f, 0.0f, -50.0f));

	//滑り台を直すのに必要なアイテムの目印
	//m_pItemMark[2] = CItemMark::Create(D3DXVECTOR3(-200.0f, 130.0f, 0.0f));
	//m_pItemMark[2]->SetSize(100.0f, 100.0f);
	//m_pItemMark[2]->SetTexture(CTexture::TEXTURE_FUKIDASI);

	//-----------------------------------
	// オブジェクトの生成(ブランコ)
	//-----------------------------------
	//綺麗なブランコ
	pGameCenter = CGameCenter::Create();
	pGameCenter->SetType(28);
	pGameCenter->SetGameType(CMiniGameBasis::TYPE_BUTTUNPUSH);
	pGameCenter->SetPos(D3DXVECTOR3(-200.0f + fPastPosX, 0.0f, 400.0f));
	pGameCenter->SetItemType(CItemObj::TYPE_WOOD);
	pGameCenter->GetModel()->SetSize(dSize);
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(-5.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(165.0f, 90.0f, 130.0f));

	//壊れたブランコ
	m_pRubble[3] = CRubble::Create();
	m_pRubble[3]->SetPos(D3DXVECTOR3(-300.0f, 0.0f, 300.0f));
	m_pRubble[3]->SetBuildType(CRubble::TYPE_SWING);
	pCollision = m_pRubble[3]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 30.0f));
	pCollision->SetSize(D3DXVECTOR3(165.0f, 90.0f, 130.0f));
	m_pRubble[3]->SetRequired(1);
	repair.clear();
	repair.resize(m_pRubble[3]->GetRequired());
	repair.at(0).type = CItemObj::TYPE_WOOD;
	repair.at(0).nRequired = 1;
	m_pRubble[3]->SetRepair(repair);

	//ブランコを直すのに必要なアイテムの目印
	m_pRubble[3]->SetMark(D3DXVECTOR3(-300.0f, 130.0f, 300.0f), CTexture::TEXTURE_FUKIDASI);

	//m_pObjectX[5] = CItemObj::Create();
	//m_pObjectX[5]->SetType(29);
	//m_pObjectX[5]->SetObjType(CObject::OBJTYPE_SWING_BREAK);
	//m_pObjectX[5]->SetPos(D3DXVECTOR3(-300.0f, 0.0f, 300.0f));

	//ブランコを直すのに必要なアイテムの目印
	//m_pItemMark[2] = CItemMark::Create(D3DXVECTOR3(-200.0f, 130.0f, 0.0f));
	//m_pItemMark[2]->SetSize(100.0f, 100.0f);
	//m_pItemMark[2]->SetTexture(CTexture::TEXTURE_FUKIDASI);

	//-----------------------------------
	// オブジェクトの生成(シーソー)
	//-----------------------------------
	//綺麗なシーソー
	//pGameCenter = CGameCenter::Create();
	//pGameCenter->SetType(30);
	//pGameCenter->SetGameType(CMiniGameBasis::TYPE_BUTTUNPUSH);
	//pGameCenter->SetPos(D3DXVECTOR3(-250.0f + fPastPosX, 0.0f, 200.0f));
	//pGameCenter->SetItemType(CItemObj::TYPE_WOOD);
	//pCollision = pGameCenter->GetCollision();
	//pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	//pCollision->SetSize(D3DXVECTOR3(270.0f, 90.0f, 30.0f));

	////壊れたシーソー
	//m_pRubble[4] = CRubble::Create();
	//m_pRubble[4]->SetPos(D3DXVECTOR3(-200.0f, 0.0f, -250.0f));
	//m_pRubble[4]->SetBuildType(CRubble::TYPE_SEESAW);
	//pCollision = m_pRubble[4]->GetCollision();
	//pCollision->SetPos(D3DXVECTOR3(5.0f, 25.0f, 0.0f));
	//pCollision->SetSize(D3DXVECTOR3(280.0f, 90.0f, 80.0f));
	//m_pRubble[4]->SetRequired(1);
	//repair.clear();
	//repair.resize(m_pRubble[4]->GetRequired());
	//repair.at(0).type = CItemObj::TYPE_WOOD;
	//repair.at(0).nRequired = 1;
	//m_pRubble[4]->SetRepair(repair);

	//m_pObjectX[6] = CItemObj::Create();
	//m_pObjectX[6]->SetType(31);
	//m_pObjectX[6]->SetObjType(CObject::OBJTYPE_SEESAW_BREAK);
	//m_pObjectX[6]->SetPos(D3DXVECTOR3(-200.0f, 0.0f, -250.0f));

	//シーソーを直すのに必要なアイテムの目印
	//m_pItemMark[2] = CItemMark::Create(D3DXVECTOR3(-200.0f, 130.0f, 0.0f));
	//m_pItemMark[2]->SetSize(100.0f, 100.0f);
	//m_pItemMark[2]->SetTexture(CTexture::TEXTURE_FUKIDASI);

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
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f, 0.0f, 500.0f - (100.0f * i)));
		}
		else if (i < 25)
		{//右の木
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(550.0f, 0.0f, 500.0f - (100.0f * (i - 13))));
		}
		else if (i < 38)
		{//上の木
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + (100.0f * (i - 26)), 0.0f, 550.0f));
		}
		else if (i < 51)
		{//下の木
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + (100.0f * (i - 39)), 0.0f, -550.0f));
		}

		//何かあった未来の生成
		else if (i < 64)
		{//左の木
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(32);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + fPastPosX, 0.0f, 500.0f - (100.0f * (i - 51))));
		}
		else if (i < 77)
		{//右の木
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(32);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(550.0f + fPastPosX, 0.0f, 500.0f - (100.0f * (i - 64))));
		}
		else if (i < 90)
		{//上の木
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(32);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + fPastPosX + (100.0f * (i - 77)), 0.0f, 550.0f));
		}
		else if (i < 103)
		{//下の木
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(32);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + fPastPosX +(100.0f * (i - 90)), 0.0f, -550.0f));
		}
	}
}