//******************************************************************************
// タイトル [title.h]
// Author : 管原 司
//******************************************************************************
#ifndef _TITLE_H_
#define _TITLE_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define TITLE_WAIT_COUNT	(10)	// タイトルカウント
#define MAX_TITLE_TEX		(2)		// タイトルテクスチャ
#define MAX_TITLE			(2)		// タイトル最大数
//******************************************************************************
// クラス
//******************************************************************************
class CTitle : public CScene
{
public:
	
	CTitle(int nPriority = 10);
	~CTitle();
	static HRESULT Load(void);
	static void Unload(void);
	static CTitle * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TITLE_TEX];	// テクスチャ
	CScene2d * m_apScene2D[MAX_TITLE];						// タイトルの情報
	D3DXVECTOR3 m_pos;										// 位置座標
	D3DXVECTOR3 m_size;										// サイズ
	D3DXCOLOR m_color;										// カラー
	bool m_bColor;											// カラー用のbool変数
	bool m_bfade;											// フェード用のbool変数
};
#endif