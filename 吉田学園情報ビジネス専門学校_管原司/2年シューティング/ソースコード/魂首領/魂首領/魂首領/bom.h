//******************************************************************************
// ボム [bom.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BOM_H_
#define _BOM_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "bullet.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BOM_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	// ボムの位置
#define BOM_SIZE	(D3DXVECTOR3(800.0f,800.0f,0.0f))						// ボムのサイズ
#define BOM_ROT		(D3DXVECTOR3(0.0f,0.0f,0.0f))							// ボムの向き
//******************************************************************************
// クラス
//******************************************************************************
class CBom : public CBullet
{
public:

	CBom(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CBom();
	static CBom * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void HitEnemy(void);
	int m_nPatternCount;	// パターンカウント
	int m_nAnimCount;		// アニメーションカウント

};
#endif