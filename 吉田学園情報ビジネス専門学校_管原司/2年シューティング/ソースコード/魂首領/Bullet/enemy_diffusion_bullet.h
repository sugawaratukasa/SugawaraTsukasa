//******************************************************************************
// 敵の弾 [enemy_diffusionl_bullet.h]
// Author : 管原　司
//******************************************************************************
#ifndef _ENEMY_DIFFUSIONL_BULLET_H_
#define _ENEMY_DIFFUSIONL_BULLET_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CEnemy_Diffusion_Bullet : public CBullet
{
public:

	CEnemy_Diffusion_Bullet(int nPriority = OBJTYPE_ENEMY_BULLET);
	~CEnemy_Diffusion_Bullet();
	static CEnemy_Diffusion_Bullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3 m_move;	// 移動
	int m_nDifCount;	// カウント
	
};
#endif