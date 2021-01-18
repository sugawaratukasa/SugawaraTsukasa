//=============================================================================
//
// ‰æ–Ê‘JˆÚ
// tutrial.h
// Author : ŠÇŒ´Ži
//
//=============================================================================
#ifndef _TUTRIAL_H_
#define _TUTRIAL_H_
class CTutrial : public CScene2d
{
public:
	static CTutrial * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	static HRESULT Load(void);
	static void Unload(void);
	CTutrial(int nPriority = PRIORITY_TYPE_UI);
	~CTutrial();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	bool m_fade;
};
#endif