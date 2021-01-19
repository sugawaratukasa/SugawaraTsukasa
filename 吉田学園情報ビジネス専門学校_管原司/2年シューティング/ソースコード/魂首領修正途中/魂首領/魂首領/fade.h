//******************************************************************************
// フェード [fade.h]
// Author : 管原　司
//******************************************************************************
#ifndef _FADE_H_
#define _FADE_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define FADE_RATE (0.05f)											// フェード移動量
#define FADE_SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))	// サイズ
//******************************************************************************
// 前方宣言
//******************************************************************************
class CSceneManager;
//******************************************************************************
// クラス
//******************************************************************************
class CFade 
{
public:
	typedef enum
	{
		FADE_NONE = -1,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;
	CFade();
	~CFade();
	static CFade * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CSceneManager::MODE mode);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// バッファ
	D3DXVECTOR3 m_pos;						// 位置座標
	D3DXVECTOR3 m_size;						// サイズ
	FADE m_fade;							// フェード
	CSceneManager::MODE m_ModeNext;			// モード
	D3DXCOLOR m_colorFade;					// カラー
};
#endif