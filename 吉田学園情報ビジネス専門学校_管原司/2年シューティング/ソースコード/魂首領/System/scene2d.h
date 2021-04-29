//******************************************************************************
// scene2d [scene2d.h]
// Author : 管原　司
//******************************************************************************
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//******************************************************************************
// クラス
//******************************************************************************
class CScene2d : public CScene
{
public:

	CScene2d(int nPriority = OBJTYPE_DEFAULT);
	~CScene2d();
	static CScene2d*Create();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetTexture(float fTexX, float fTexY, float fTexAnimX , float fTexAnimY);
	void SetRGBA(D3DXCOLOR col);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetScale(float fScale);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXCOLOR GetRGBA(void) { return m_col; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	float GetScale(void) { return m_fScale; }
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// バッファ
	D3DXVECTOR3 m_pos;					// 位置座標
	D3DXVECTOR3 m_rot;					// 向き
	D3DXVECTOR3 m_size;					// サイズ
	D3DXCOLOR m_col;					// カラー
	float m_fAngle;						// 角度
	float m_fLength;					// 対角線
	float m_fTexX;						// テクスチャX
	float m_fTexY;						// テクスチャY
	float m_fTexAnimX;					// テクスチャアニメーション
	float m_fTexAnimY;					// テクスチャアニメーション
	float m_fScale;						// 拡大
};
#endif