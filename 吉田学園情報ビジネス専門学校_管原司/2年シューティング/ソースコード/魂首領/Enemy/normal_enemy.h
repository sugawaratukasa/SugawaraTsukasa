//******************************************************************************
// 通常の敵 [normal_enemy.h]
// Author : 管原　司
//******************************************************************************
#ifndef _NORMAL_ENEMY_H_
#define _NORMAL_ENEMY_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "enemy.h"
//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CNormal_Enemy : public CEnemy
{
public:

	CNormal_Enemy(int nPriority = OBJTYPE_ENEMY);
	~CNormal_Enemy();
	static CNormal_Enemy * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Attack(void);
	int m_nAttackCount;	// 攻撃カウント
};
#endif