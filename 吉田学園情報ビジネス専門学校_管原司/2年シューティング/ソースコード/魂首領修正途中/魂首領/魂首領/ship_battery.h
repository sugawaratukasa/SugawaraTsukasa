//******************************************************************************
// 船の砲台 [ship_battery_enemy.h]
// Author : 管原　司
//******************************************************************************
#ifndef _SHIP_BATTERY_H_
#define _SHIP_BATTERY_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "enemy.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define SHIP_BATTERY_SIZE	(D3DXVECTOR3(100.0f,200.0f,0.0f))	// 船の砲台のサイズ
#define SHIP_BATTERY_ROT	(D3DXVECTOR3(0.0f,0.0f,0.0f))		// 船の砲台の向き
#define SHIP_BATTERY_LIFE	(50)								// 船の砲台のライフ
//******************************************************************************
// クラス
//******************************************************************************
class CShip_Battery : public CEnemy
{
public:

	CShip_Battery(int nPriority = OBJTYPE_ENEMY);
	~CShip_Battery();
	static CShip_Battery * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Attack(void);
	D3DXVECTOR3 m_pos;	// 位置座標
	int m_nAttackCount;	// 攻撃カウント
};
#endif