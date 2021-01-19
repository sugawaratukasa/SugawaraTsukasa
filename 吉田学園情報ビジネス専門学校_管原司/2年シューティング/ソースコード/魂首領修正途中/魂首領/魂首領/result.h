//******************************************************************************
// リザルト [result.h]
// Author : 管原 司
//******************************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_
//******************************************************************************
// 前方宣言
//******************************************************************************
class CScene2d;
class CPlayerdata;
//******************************************************************************
// クラス
//******************************************************************************
class CResult : public CScene
{
public:
	CResult(int nPriority = 10);
	~CResult();
	static CResult * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayerdata * GetPlayerData(void) { return m_pPlayerData; }
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャの情報
	static CPlayerdata * m_pPlayerData;		// プレイヤーデータ
	CScene2d * m_pScene2D;					// Resultの情報
	D3DXVECTOR3 m_pos;						// 位置座標
	D3DXVECTOR3 m_size;						// サイズ
	bool m_bfade;							// フェード用のbool変数
};
#endif