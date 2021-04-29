//******************************************************************************
// パーティクルエフェクト [particle_effect.h]
// Author : 管原　司
//******************************************************************************
#ifndef _PARTICLE_EFFECT_H_
#define _PARTICLE_EFFECT_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// クラス
//******************************************************************************
class CParticle_Effect : public CScene
{
public:
	enum TYPE
	{
		TYPE_FIRE_EXPLOSION = 0,
		TYPE_ICE_EXPLOSION,
		TYPE_FIRE_EXPLOSION_2,
		TYPE_ICE_EXPLOSION_2,
		TYPE_ENEMY_FIRE_EXPLOSION,
		TYPE_ENEMY_FIRE_EXPLOSION_2,
		TYPE_WOOD_EFFECT,
		TYPE_WOOD_EFFECT_2,
		TYPE_BLOCK_EFFECT,
		TYPE_STAR_EFFECT,
		TYPE_STAR_EFFECT2
	};
	CParticle_Effect();
	~CParticle_Effect();
	static CParticle_Effect *Create(D3DXVECTOR3 pos, TYPE type);
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