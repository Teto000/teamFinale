//===================================================
//
// アプリケーションヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_	

//------------------------------
// インクルード
//------------------------------
#include <d3dx9.h>

//------------------------------
// 前方宣言
//------------------------------
class CRenderer;	//レンダラー
class CInput;		//インプット
class CTexture;		//テクスチャ
class CSound;		//サウンド
class CLight;		//ライト
class CDebugProc;	//デバッグ用文字

//================================
// アプリケーションクラスの定義
//================================
class CApplication
{
public:
	//--------------------------------
	// ゲームモードの列挙型の定義
	//--------------------------------
	enum GAMEMODE
	{
		GAMEMODE_TIME = 0,
		GAMEMODE_SCORE,
		GAMEMODE_MAX
	};

	CApplication();		//コンストラクタ
	~CApplication();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	void Draw();

	//------------------
	// 静的メンバ関数
	//------------------
	static CRenderer*		GetRenderer()	{ return m_pRenderer; }		//レンダラーの取得
	static CInput*			GetInput()		{ return m_pInput; }		//インプットの取得
	static CTexture*		GetTexture()	{ return m_pTexture; }		//テクスチャの取得
	static CSound*			GetSound()		{ return m_pSound; }		//サウンドの取得
	static CLight*			GetLight()		{ return m_pLight; }		//ライトの取得

	//------------------
	// セッター
	//------------------
	static void AddStageScore(int nNum, int nValue) { m_nStageScore[nNum] += nValue; }	//ステージごとのスコアを加算
	static void ResetStageScore(int nNum) { m_nStageScore[nNum] = 0; }					//ステージのごとのスコアをリセット
	static void SetMaxScore(int nNum, int nValue) { m_nMaxScore[nNum] = nValue; }		//ステージごとのスコアの最大数を設定

	//------------------
	// ゲッター
	//------------------
	static const int GetMaxStage() { return nMaxStage; }	//ステージの最大数を取得
	static int GetStageScore(int nNum) { return m_nStageScore[nNum]; }	//ステージごとのスコアを取得
	static int GetMaxScore(int nNum) { return m_nMaxScore[nNum]; }		//ステージごとのスコアの最大数を取得

private:
	//------------------
	// 定数
	//------------------
	static const int nMaxStage = 2;		//ステージの最大数

	//------------------
	// 静的メンバ変数
	//------------------
	static GAMEMODE			m_gameMode;		//ゲームモード

	static CRenderer*		m_pRenderer;	//レンダラー
	static CInput*			m_pInput;		//インプット
	static CTexture*		m_pTexture;		//テクスチャ
	static CSound*			m_pSound;		//サウンド
	static CLight*			m_pLight;		//ライト
	static CDebugProc*		m_pDebugproc;	//デバッグ用文字

	static int m_nStageScore[nMaxStage];	//ステージごとのスコアを保存
	static int m_nMaxScore[nMaxStage];		//スコアの最大値を保存
};

#endif // !_APPLICATION_H_