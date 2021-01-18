#ifndef _FADE_H_
#define _FADE_H_
#define FADE_RATE 0.05f
//---------------------------------------
//前方宣言
//---------------------------------------
class CSceneManager;
//---------------------------------------
//クラス
//---------------------------------------
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
	static CFade * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int sizeX, int sizeY,CSceneManager::MODE mode);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY, CSceneManager::MODE mode);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//バッファ
	D3DXVECTOR3 m_pos;
	int m_nSizeX;
	int m_nSizeY;
	FADE m_fade;	//フェード
	CSceneManager::MODE m_ModeNext;
	D3DXCOLOR m_colorFade;	//カラー
};
#endif