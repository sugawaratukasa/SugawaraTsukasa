//******************************************************************************
// îöî≠èàóù [particle_circle.h]
// Author : ä«å¥Å@éi
//******************************************************************************
#ifndef _PARTICLE_CIRCLE_H_
#define _PARTICLE_CIRCLE_H_
//******************************************************************************
// ÉNÉâÉX
//******************************************************************************
class CParticle_Circle : public CParticle
{
public:

	CParticle_Circle(int nPrirority = OBJTYPE_PARTICLE);
	~CParticle_Circle();
	static CParticle_Circle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void CreateParticleEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nCreateCount);
	static void PlayerDeathEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nCreateCount);
private:
	D3DXVECTOR3	m_move;		// à⁄ìÆó 
};
#endif