//******************************************************************************
// îöî≠èàóù [particle_explosion.h]
// Author : ä«å¥Å@éi
//******************************************************************************
#ifndef _PARTICLE_EXPLOSION_H_
#define _PARTICLE_EXPLOSION_H_
//******************************************************************************
// ÉNÉâÉX
//******************************************************************************
class CParticle_Explosion : public CParticle
{
public:
	// éÌóﬁ
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_ENEMY,
		TYPE_PLAYER,
		TYPE_MAX
	}TYPE;

	CParticle_Explosion(int nPrirority = OBJTYPE_EXPLOSION);
	~CParticle_Explosion();
	static CParticle_Explosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void CreateExplosionEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
private:
	D3DXVECTOR3	m_move;		// à⁄ìÆó 
};
#endif