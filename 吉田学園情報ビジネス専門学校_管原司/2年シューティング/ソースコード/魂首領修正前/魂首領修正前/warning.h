//---------------------------------------------------
// warning
// warning.h
// Authur:	管原司
//---------------------------------------------------
#ifndef _WARNING_H_
#define _WARNING_H_
//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define WARNING_SIZE_X 500
#define WARNING_SIZE_Y 300
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CWarning : public CScene2d
{
public:
	CWarning(int nPriority = PRIORITY_TYPE_UI);
	~CWarning();
	static CWarning * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//texture
	D3DXCOLOR m_color;						//カラー
	bool m_bColor;							//カラー状態
	int m_nWarnigCount;						//カウント
};
#endif