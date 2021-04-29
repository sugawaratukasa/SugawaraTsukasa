//******************************************************************************
// 狙い撃ち弾 [enemy_traking_bullet.h]
// Author : 管原　司
//******************************************************************************
#ifndef _ENEMY_TRAKING_BULLET_H_
#define _ENEMY_TRAKING_BULLET_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CEnemy_Traking_Bullet : public CBullet
{
public:

	CEnemy_Traking_Bullet(int nPriority = OBJTYPE_ENEMY_BULLET);
	~CEnemy_Traking_Bullet();
	static CEnemy_Traking_Bullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void HitPlayer(void);
	D3DXVECTOR3 m_move;	// 移動
	float m_fAngle;		// 角度
};
#endif