//******************************************************************************
// ワーニング [warning.h]
// Author : 管原 司
//******************************************************************************
#ifndef _WARNING_H_
#define _WARNING_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define WARNING_SIZE (D3DXVECTOR3(500.0f,300.0f,0.0f))

//******************************************************************************
// クラス
//******************************************************************************
class CWarning : public CScene2d
{
public:
	CWarning(int nPriority = 20);
	~CWarning();
	static CWarning * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//texture
	bool m_bColor;							//カラー状態
	int m_nWarnigCount;						//カウント
};
#endif