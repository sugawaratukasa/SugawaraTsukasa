//******************************************************************************
// チュートリアル [tutrial.h]
// Author : 管原 司
//******************************************************************************
#ifndef _TUTRIAL_H_
#define _TUTRIAL_H_
//******************************************************************************
// クラス
//******************************************************************************
class CTutrial : public CScene2d
{
public:
	static CTutrial * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
	CTutrial(int nPriority = 10);
	~CTutrial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャ
	bool m_bfade;							// フェード
};
#endif