//===================================================
//
// オブジェクトXヘッダー
// Author:Teruto Sato
//
//===================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_	//二重インクルード防止

//--------------------------------
// インクルード
//--------------------------------
#include "object.h"

//--------------------------------
// 前方宣言
//--------------------------------
class CModel3D;

//================================
// オブジェクトXクラスの定義
//================================
class CObjectX : public CObject
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CObjectX *Create();			// モデルの生成

	CObjectX();
	explicit CObjectX(int nPriority);	//コンストラクタ
	virtual ~CObjectX() override;		//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	virtual HRESULT Init(D3DXVECTOR3 pos) override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	//----------------
	// セッター
	//----------------
	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }					//位置の設定
	void SetPosOld(D3DXVECTOR3 posOld) { m_posOld = posOld; }				//
	void SetRot(D3DXVECTOR3 rot);											//向きの設定

	//----------------
	// ゲッター
	//----------------
	D3DXVECTOR3 GetPosition() override;										//位置の取得
	D3DXVECTOR3 GetPosOld() override { return m_posOld; }					//位置の取得
	D3DXVECTOR3 GetRot() { return m_rot; }									//向きのゲッター
	float GetWidth() override;												//幅の取得
	float GetHeight() override;												//高さの取得
	void SetType(const int nType);											// タイプの設定
	void SetMtx(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }
	D3DXMATRIX GetMtx() { return m_mtxWorld; }
	CModel3D *GetModel() { return m_pModel; }

private:
	//----------------
	// メンバ変数
	//----------------
	CModel3D *m_pModel;					//モデル情報
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_posOld;				//過去位置
	D3DXVECTOR3 m_rot;					//向き
	int m_nType;						//モデルのタイプ
};

#endif