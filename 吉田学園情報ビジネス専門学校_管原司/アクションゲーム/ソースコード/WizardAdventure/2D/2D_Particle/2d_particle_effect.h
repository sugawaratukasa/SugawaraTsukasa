//******************************************************************************
// 2D_パーティクルエフェクト [2d_particle_effect.h]
// Author : 管原　司
//******************************************************************************
#ifndef _2D_PARTICLE_EFFECT_H_
#define _2D_PARTICLE_EFFECT_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// クラス
//******************************************************************************
class C2D_Particle_Effect : public CScene
{
public:
	enum TYPE
	{
		TYPE_COLOR_BOM = 0,
	};
	C2D_Particle_Effect();
	~C2D_Particle_Effect();
	static C2D_Particle_Effect *Create(D3DXVECTOR3 pos, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Load(const char *cText);
	D3DXVECTOR3 m_pos;				// 位置座標
	int m_nCreate_TotalCount;		// 生成の総数
	char m_cText[MAX_TEXT];			// テキスト
	TYPE m_Type;					// 種類
};
#endif