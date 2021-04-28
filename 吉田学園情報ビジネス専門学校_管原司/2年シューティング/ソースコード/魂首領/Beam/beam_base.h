//******************************************************************************
// beam [beam.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BEAM_BASE_H_
#define _BEAM_BASE_H_
//******************************************************************************
// クラス
//******************************************************************************
class CBeam_Base : public CScene
{
public:

	CBeam_Base(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CBeam_Base();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBeam(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);
	void SetPosition(D3DXVECTOR3 pos);
	void SetTexture(float fTexX, float fTexY, float fTexAnimX, float fTexAnimY);
	void SetRGBA(D3DXCOLOR col);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetSizeY(float sizeY);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXCOLOR GetRGBA(void) { return m_col; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	float GetSizeY(void) { return m_fSizeY; }
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// バッファ
	D3DXVECTOR3 m_pos;					// 位置座標
	D3DXVECTOR3 m_rot;					// 向き
	D3DXVECTOR3 m_size;					// サイズ
	D3DXCOLOR m_col;					// カラー
	float m_fSizeY;						// サイズ
	float m_fAddSize;					// サイズ加算
	float m_fTexX;						// テクスチャX
	float m_fTexY;						// テクスチャY
	float m_fTexAnimX;					// テクスチャアニメーション
	float m_fTexAnimY;					// テクスチャアニメーション
	bool m_bAddSize_Stop;				// サイズ加算停止
};
#endif