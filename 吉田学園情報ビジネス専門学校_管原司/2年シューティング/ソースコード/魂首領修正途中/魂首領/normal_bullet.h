//******************************************************************************
// 弾 [bullet.h]
// Author : 管原　司
//******************************************************************************
#ifndef _NORMAL_BULLET_H_
#define _NORMAL_BULLET_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "bullet.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BULLET_LEVEL1_SIZE	(D3DXVECTOR3(40.0f,40.0f,0.0f))	// レベル1の弾のサイズ
#define BULLET_LEVEL2_SIZE	(D3DXVECTOR3(50.0f,50.0f,0.0f))	// レベル2の弾のサイズ
#define BULLET_LEVEL3_SIZE	(D3DXVECTOR3(50.0f,50.0f,0.0f))	// レベル3の弾のサイズ
//******************************************************************************
// クラス
//******************************************************************************
class CNormal_Bullet : public CBullet
{
public:

	CNormal_Bullet(int nPriority = 10);
	~CNormal_Bullet();
	static CNormal_Bullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	bool Collision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
	D3DXVECTOR3 m_move;
};
#endif