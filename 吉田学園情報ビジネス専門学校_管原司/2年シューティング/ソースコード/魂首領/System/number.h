//******************************************************************************
// ナンバー処理 [number.h]
// Author : 管原　司
//******************************************************************************
#ifndef NUMBER_H_
#define NUMBER_H_
//******************************************************************************
// クラス
//******************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();
	static HRESULT Load(void);
	static void Unload(void);
	static CNumber * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR col);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXCOLOR GetColor(void) { return m_col; }
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// バッファ
	D3DXVECTOR3 m_pos;							// 位置座標
	D3DXVECTOR3 m_size;							// サイズ
	D3DXCOLOR m_col;							// 色
	int m_nNumber;								// ナンバー
};
#endif