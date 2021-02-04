//******************************************************************************
// ポリゴン [polygon.h]
// Author : 管原　司
//******************************************************************************
#ifndef _POLYGON_H_
#define _POLYGON_H_

//******************************************************************************
// クラス
//******************************************************************************
class CPolygon : public CScene2d
{
public:
	// テクスチャ種類
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_TITLE,			// タイトル用画像
		TEX_TYPE_PRESS_ENTER,	// タイトル用画像
		TEX_TYPE_TUTRIAL,		// チュートリアル画像
		TEX_TYPE_RANKING,		// リザルト用画像
		TEX_TYPE_CONTINUE,		// コンティニュー用画像
		TEX_TYPE_MAX
	}TEX_TYPE;

	CPolygon(int nPriority = OBJTYPE::OBJTYPE_UI);
	~CPolygon();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_TYPE_MAX];		// テクスチャ
	TEX_TYPE m_TexType;											// テクスチャの種類
};
#endif