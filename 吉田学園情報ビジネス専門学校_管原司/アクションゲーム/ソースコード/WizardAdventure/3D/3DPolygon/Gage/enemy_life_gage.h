//******************************************************************************
// 敵のライフゲージ [enemy_life_gage.h]
// Author : 管原司
//******************************************************************************
#ifndef _ENEMY_LIFE_GAGE_H_
#define _ENEMY_LIFE_GAGE_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "3d_gage.h"
//******************************************************************************
// 前方宣言
//******************************************************************************
class CEnemy;
class C3D_Gage_Back;
//******************************************************************************
// クラス
//******************************************************************************
class CEnemy_Life_Gage : public C3D_Gage
{
public:
	CEnemy_Life_Gage(int nPriority = OBJTYPE_BILLBOARD_UI);
	~CEnemy_Life_Gage();
	static CEnemy_Life_Gage *Create(D3DXVECTOR3 pos, CEnemy *pEnemy);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CEnemy *m_pEnemy;				// CEnemyのポインタ
	C3D_Gage_Back *m_p3D_Gage_Back;	// C3D_Gage_Backのポインタ
};
#endif