//******************************************************************************
// ボス戦用のボム [boss_bom.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BOSS_BOM_H_
#define _BOSS_BOM_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "bullet.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BOSS_BOM_SIZE		(D3DXVECTOR3(100.0f,100.0f,0.0f))	// サイズ
#define BOSS_BOM_ROT		(D3DXVECTOR3(0.0f,0.0f,0.0f))		// ボムの向き
//******************************************************************************
// クラス
//******************************************************************************
class CBoss_Bom : public CBullet
{
public:

	CBoss_Bom(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CBoss_Bom();
	static CBoss_Bom * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetUseBoss_Bom(bool bUseBoss_Bom);
private:
	void HitBoss(void);
	D3DXVECTOR3 m_move;				// 移動
	static bool m_bUseBoss_Bom;		// 使用状態
};
#endif