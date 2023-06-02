//===================================================
//
// スティック回転ゲーム処理
// Author : Kajita Hiromu
//
//===================================================

//----------------------
// インクルード
//----------------------
#include "mg_stickrotate.h"
#include "application.h"
#include "renderer.h"

#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "object2D.h"
#include "game.h"

#include "itemObj.h"
#include "player.h"

//=======================
// コンストラクタ
//=======================
CStickRotate::CStickRotate()
{

}

//=======================
// デストラクタ
//=======================
CStickRotate::~CStickRotate()
{

}

//=======================
// 初期化
//=======================
HRESULT CStickRotate::Init(D3DXVECTOR3 pos)
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//カラー変数
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	

	//ボタン連打画像
	pObj2D = CObject2D::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	pObj2D->SetSize(500.0f, 300.0f);
	pObj2D->SetTexture(CTexture::TEXTURE_JOYPAD);
	pObj2D->SetColor(m_col);
	pObj2D->SetSplitTex(1.0f, 1.0f, 2.0f, (float)m_nPatternAnim);

	//アニメーション用変数
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	//数字カウント用変数
	m_nStickCount = 0;		//カウント数

	m_bStick = false;

	return S_OK;
}

//=======================
// 終了
//=======================
void CStickRotate::Uninit()
{

}

//=======================
// 更新
//=======================
void CStickRotate::Update()
{
	CInputJoypad *pJoypad = CInput::GetJoypad();

	if (pObj2D != nullptr)
	{
		//カウンターを加算
		m_nCounterAnim++;

		if ((m_nCounterAnim % 10) == 0)
		{//10フレーム経過
		 //テクスチャのアニメーション
			pObj2D->SetSplitTex(1.0f, 1.0f, 2.0f, (float)m_nPatternAnim);

			//パターンNo.を更新する
			m_nPatternAnim++;
		}

		//移動量と目的の角度の計算
		if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).y < -0.3f)
		{//Wキーが押された場合
			if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
			{//Aキーも押された場合
				m_stick = STICK_UPLEFT;

				if (m_stickold != STICK_UPLEFT)
				{
					m_nStickCount++;
				}
			}
			else if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
			{//Dキーも押された場合
				m_stick = STICK_UPRIGHT;

				if (m_stickold != STICK_UPRIGHT)
				{
					m_nStickCount++;
				}
			}
			else
			{//Wキーだけが押された場合
				m_stick = STICK_UP;

				if (m_stickold != STICK_UP)
				{
					m_nStickCount++;
				}
			}
		}
		else if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).y > 0.3f)
		{//Sキーが押された場合
			if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
			{//Aキーも押された場合
				m_stick = STICK_DOWNLEFT;

				if (m_stickold != STICK_DOWNLEFT)
				{
					m_nStickCount++;
				}
			}
			else if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).x > 0.5f)
			{//Dキーも押された場合
				m_stick = STICK_DOWNRIGHT;

				if (m_stickold != STICK_DOWNRIGHT)
				{
					m_nStickCount++;
				}
			}
			else
			{//Sキーだけが押された場合
				m_stick = STICK_DOWN;

				if (m_stickold != STICK_DOWN)
				{
					m_nStickCount++;
				}
			}
		}
		else if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
		{//Dキーだけ押された場合
			m_stick = STICK_RIGHT;

			if (m_stickold != STICK_RIGHT)
			{
				m_nStickCount++;
			}
		}
		else if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
		{//Aキーだけ押された場合
			m_stick = STICK_LEFT;

			if (m_stickold != STICK_LEFT)
			{
				m_nStickCount++;
			}
		}

#ifdef _DEBUG
		if (CInputKeyboard::Trigger(DIK_N))
		{//Nキー押されたら終了
			m_nStickCount = 45;
		}
#endif // !_DEBUG

		m_stickold = m_stick;

		if (m_nStickCount >= 45)
		{
			m_nStickCount = 0;
			m_stick = STICK_UP;
			m_stickold = STICK_UP;

			//オブジェクト破棄
			pObj2D->Uninit();
			pObj2D = nullptr;
		}
	}
}

//=======================
// 描画
//=======================
void CStickRotate::Draw()
{

}

//=======================
// 生成
// 引数：位置
//=======================
CStickRotate *CStickRotate::Create(D3DXVECTOR3 pos)
{
	CStickRotate *pStickGame = nullptr;

	//----------------------------------
	// ポリゴンの生成と初期化
	//----------------------------------
	pStickGame = new CStickRotate;	//生成

	if (pStickGame != nullptr)
	{//NULLチェック

	 //初期化
		pStickGame->Init(D3DXVECTOR3(pos));
		pStickGame->SetObjType(OBJTYPE_MINIGAME);
	}

	return pStickGame;
}
