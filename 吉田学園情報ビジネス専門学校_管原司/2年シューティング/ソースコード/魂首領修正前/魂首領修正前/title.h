//=============================================================================
//
// âÊñ ëJà⁄
// title.h
// Author : ä«å¥éi
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#define TITLE_WAIT_COUNT 10
#define MAX_TITLE_TEX 2
#define MAX_TITLE 2
class CTitle : public CScene
{
public:
	static CTitle * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	static HRESULT Load(void);
	static void Unload(void);
	CTitle(int nPriority = PRIORITY_TYPE_UI);
	~CTitle();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TITLE_TEX];
	CScene2d * m_apScene2D[MAX_TITLE];	//ResultÇÃèÓïÒ
	D3DXCOLOR m_color;					//ÉJÉâÅ[
	bool m_bColor;
	bool m_bfade;
};
#endif