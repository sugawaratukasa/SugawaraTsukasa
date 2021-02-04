//******************************************************************************
// ビーム [player_beam.h]
// Author : 管原　司
//******************************************************************************
#ifndef _PLAYER_BEAM_H_
#define _PLAYER_BEAM_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "bullet.h"
//******************************************************************************
// クラス
//******************************************************************************
class CPlayer_Beam : public CBullet
{
public:

	CPlayer_Beam(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CPlayer_Beam();
	static CPlayer_Beam * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetUseBeam(bool bUseBeam);
private:
	void HitEnemy(void);

	D3DXVECTOR3 m_move;			// 移動量
	int m_nDeathCount;			// 死亡カウント
	bool m_bHit;				// 当たったか
	static bool m_bUseBeam;		// ビームの使用状態
};
#endif