//===================================================
//
// 便利なやつヘッダー
// Author:Teruto Sato
//
//===================================================
#ifndef _UTILITY_H_
#define _UTILITY_H_	//二重インクルード防止

//--------------------------
// インクルード
//--------------------------
#include "object.h"
#include "camera.h"

//================================
// ユーティリティクラスの定義
//================================
class CUtility
{
public:
	//--------------------------
	// 当たり判定の向き
	//--------------------------
	enum COLLISION
	{
		COLLISION_NONE = 0,	//当たっていない
		COLLISION_FRONT,	//前から当たった
		COLLISION_BACK,		//後ろから
		COLLISION_LEFT,		//左から
		COLLISION_RIGHT,	//右から
		COLLISION_MAX
	};

	CUtility();		//コンストラクタ
	~CUtility();	//デストラクタ

	//-----------------------
	// 静的メンバ関数
	//-----------------------
	//押し戻された位置を返す当たり判定処理
	static bool Collision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size,
									D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize);

	//角度の正規化
	static float GetNorRot(float rot);

	static D3DXVECTOR3 ScreenCastWorld(const D3DXVECTOR3 &pos ,CCamera *pCamera);
	static D3DXVECTOR3 WorldCastScreen(const D3DXVECTOR3 &pos,CCamera *pCamera);
};

#endif _UTILITY_H_