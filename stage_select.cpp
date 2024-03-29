//===================================================
//
// ステージ選択処理
// Author : Sato Teruto
//
//===================================================

//----------------------------------
// インクルード
//----------------------------------
#include "stage_select.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "fade.h"
#include "camera.h"
#include "meshfield.h"
#include "objectX.h"
#include "player.h"
#include "object2D.h"
#include "score.h"
#include "sky.h"

//----------------------------------
// 静的メンバ変数宣言
//----------------------------------
int CStageSelect::m_nNumStage = 0;			//現在のステージ番号
bool CStageSelect::m_bViewMap = false;		//マップを表示する状態
bool CStageSelect::m_bStart = false;		//ゲームを開始する状態

//==================================
// コンストラクタ
//==================================
CStageSelect::CStageSelect()
{
	m_pCamera = nullptr;	//カメラ
	m_pMeshField = nullptr;	//メッシュフィールド(地面)
	m_pPlayer = nullptr;	//プレイヤー
	m_pObject2D = nullptr;	//オブジェクト2D
	m_pNumber = nullptr;	//数字
	m_pSky = nullptr;		//空

	//オブジェクトX
	for (int i = 0; i < nMaxStage; i++)
	{
		m_pObjectX[i] = nullptr;
	}
}

//=================================
// デストラクタ
//=================================
CStageSelect::~CStageSelect()
{
}

//==================================
// 初期化処理
//==================================
HRESULT CStageSelect::Init()
{
	//------------------------
	// カメラの生成
	//------------------------
	m_pCamera = CCamera::Create();

	//------------------------
	// 地面の生成
	//------------------------
	m_pMeshField = CMeshField::Create(12.0f,5500.0f);

	//------------------------
	// 空の生成
	//------------------------
	m_pSky = CSky::Create(CTexture::TEXTURE_SKY);

	//------------------------
	// プレイヤーの生成
	//------------------------
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetMotion("data/MOTION/motion.txt");

	//------------------------
	// オブジェクトの生成(旗)
	//------------------------
	m_pObjectX[0] = CObjectX::Create();
	m_pObjectX[0]->SetType(1);

	m_pObjectX[1] = CObjectX::Create();
	m_pObjectX[1]->SetType(1);
	m_pObjectX[1]->SetPos(D3DXVECTOR3(200.0f, 0.0f, 0.0f));

	//------------------------
	// 画像の生成
	//------------------------
	{
		D3DXVECTOR3 pos((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f);	//位置
		m_pObject2D = CObject2D::Create(pos);							//生成
		m_pObject2D->SetSize(0.0f, 0.0f);								//大きさ
		m_pObject2D->SetTexture(CTexture::TEXTURE_STATE1);				//テクスチャ
	}

	//------------------------
	// 数字の生成
	//------------------------
	{
		D3DXVECTOR3 pos(560.0f, 460.0f, 0.0f);
		m_pNumber = CScore::Create(pos);
	}

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CStageSelect::Uninit()
{
	//-----------------------
	// カメラの終了
	//-----------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//==================================
// 更新処理
//==================================
void CStageSelect::Update()
{
	//-----------------------
	// カメラの更新処理
	//-----------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	//-----------------------
	// 画像表示の切り替え
	// 備考::ステージ番号でテクスチャを切り替える
	//-----------------------
	if (m_bViewMap == true)
	{//マップを表示する状態なら
		//画像を拡大する(表示)
		m_pObject2D->SetSize(300.0f, 300.0f);

		//ステージに応じた処理
		switch (m_nNumStage)
		{
		case 0:
			m_pObject2D->SetTexture(CTexture::TEXTURE_STATE1);
			break;
		case 1:
			m_pObject2D->SetTexture(CTexture::TEXTURE_STATE2);
			break;
		default:
			break;
		}

		//ステージ番号に対応したスコアの最大値を取得
		int nScore = CApplication::GetMaxScore(m_nNumStage);

		//数字を描画する
		m_pNumber->SetDraw(true);
		m_pNumber->SetScore(nScore);
	}
	else
	{
		//画像を縮小する(非表示)
		m_pObject2D->SetSize(0.0f, 0.0f);

		//数字を描画しない
		m_pNumber->SetDraw(false);
	}

	// ジョイパッドでの操作
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// 画面遷移
	//-----------------------
	if (m_bStart &&
		CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	{//ゲームを開始する状態 & キーが押されたら
		//ゲーム画面に移行
		CMode::GetFade()->SetFade(CMode::MODE_GAME);
	}
}