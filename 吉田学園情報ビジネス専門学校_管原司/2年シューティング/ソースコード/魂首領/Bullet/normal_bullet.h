//******************************************************************************
// 弾 [bullet.h]
// Author : 管原　司
//******************************************************************************
#ifndef _NORMAL_BULLET_H_
#define _NORMAL_BULLET_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CNormal_Bullet : public CBullet
{
public:

	CNormal_Bullet(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CNormal_Bullet();
	static CNormal_Bullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void HitEnemy(void);
	D3DXVECTOR3 m_move;
};
#endif