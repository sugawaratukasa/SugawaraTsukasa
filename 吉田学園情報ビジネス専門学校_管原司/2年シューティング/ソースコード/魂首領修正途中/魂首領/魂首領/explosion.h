//******************************************************************************
// 爆発 [explosion.h]
// Author : 管原　司
//******************************************************************************
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define EXPLOSION_SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))	// 爆発サイズ
//******************************************************************************
// クラス
//******************************************************************************
class CExplosion : public CScene2d
{
public:
	CExplosion(int nPriority = 10);
	~CExplosion();
	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャ
	int m_nCountAnim;						// カウンター
	int m_nPatternAnim;						// パターン
};
#endif