//=============================================================================
//
// 3Dモーションキャラクタークラス(motion_model3D.h)
// Author : 唐�ｱ結斗
// 概要 : 3Dプレイヤー生成を行う
//
//=============================================================================
#ifndef _MOTION_MODEL3D_H_			// このマクロ定義がされてなかったら
#define _MOTION_MODEL3D_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CMotion;
class CCollision_Rectangle3D;

//=============================================================================
// 3Dプレイヤークラス
// Author : 唐�ｱ結斗
// 概要 : 3Dプレイヤー生成を行うクラス
//=============================================================================
class CMotionModel3D : public CObject
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CMotionModel3D *Create();			// 3Dプレイヤーの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CMotionModel3D();
	explicit CMotionModel3D(int nPriority);
	~CMotionModel3D();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init(D3DXVECTOR3 pos) override;											// 初期化
	void Uninit() override;															// 終了
	void Update() override;															// 更新
	void Draw() override;															// 描画
	void SetPosOld(const D3DXVECTOR3 &posOld) { m_posOld = posOld; }				// 過去位置のセッター
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; };							// 向きのセッター
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }						// 大きさのセッター
	D3DXVECTOR3 GetPos() { return m_pos; }											// 位置のゲッター
	D3DXVECTOR3 GetRot() { return m_rot; }											// 向きのゲッター
	D3DXVECTOR3 GetSize() { return m_size; }										// 大きさのゲッター
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }				// ワールドマトリックスのセッター
	D3DXMATRIX *GetMtxWorld() { return &m_mtxWorld; }								// ワールドマトリックスのゲッター
	void SetMotion(const char *pName);												// モーション情報の設定
	void SetMotion(const char *pName, const int nNumMotion);						// モーション情報の設定(オーバーロード)
	CMotion *GetMotion() { return m_pMotion; }										// モーション情報の取得
	CCollision_Rectangle3D* GetCollision() { return m_pCollision; }					// 
	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }							//位置の設定
	D3DXVECTOR3 GetPosOld() override { return m_posOld; }							//位置の取得
	D3DXVECTOR3 GetPosition() override;												//位置の取得
	float GetWidth() override;														//幅の取得
	float GetHeight() override;														//高さの取得

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	CMotion						*m_pMotion;				// モーションインスタンス
	CCollision_Rectangle3D		*m_pCollision;			// 当たり判定
	D3DXMATRIX					m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3					m_pos;					// 位置
	D3DXVECTOR3					m_posOld;				// 過去位置
	D3DXVECTOR3					m_rot;					// 向き
	D3DXVECTOR3					m_size;					// 大きさ
};

#endif