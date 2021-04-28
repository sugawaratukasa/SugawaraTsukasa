//******************************************************************************
// パーティクルエミッター [particle_emitter.h]
// Author : 管原　司
//******************************************************************************
#ifndef _PARTICLE_EMITTER_H_
#define _PARTICLE_EMITTER_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../System/scene.h"
//******************************************************************************
// クラス
//******************************************************************************
class CParticle_Emitter : public CScene
{
public:
	CParticle_Emitter();
	virtual ~CParticle_Emitter();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void);
	virtual void Draw(void) = 0;

	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	int GetCount(void) { return m_nCount; }
private:
	D3DXVECTOR3 m_pos;	// 位置座標
	int m_nCount;		// カウント
};
#endif