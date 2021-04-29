//******************************************************************************
// 幽霊[ghost.h]
// Author : 管原　司
//******************************************************************************
#ifndef _GHOST_H_
#define _GHOST_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "enemy.h"
//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 前方宣言
//******************************************************************************
class CModel;
class CParticle_Emitter;
//******************************************************************************
// プレイヤークラス
//******************************************************************************
class CGhost :public CEnemy
{
public:
	enum TYPE
	{
		TYPE_NONE = -1,
		TYPE_FIRE,
		TYPE_ICE,
		TYPE_MAX
	};
	enum ROT
	{
		ROT_RIGHT = 0,
		ROT_LEFT
	};
	CGhost(int nPriority = OBJTYPE_ENEMY);
	~CGhost();
	static CGhost *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	TYPE GetType(void) { return m_Type; }
private:
	void Attack(void);
	void Rot(void);

	CParticle_Emitter *m_pParticleEmitter;	// CParticle_Emitter1のポインタ
	TYPE m_Type;							// 種類
	int m_nAttackCount;						// 攻撃カウント
	ROT m_Rot;								// 向きの列挙
};
#endif