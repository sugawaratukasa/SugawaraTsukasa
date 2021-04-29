//******************************************************************************
// ゲージ [gage.h]
// Author : 管原司
//******************************************************************************
#ifndef _GAGE_H_
#define _GAGE_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// クラス
//******************************************************************************
class CGage :public CScene
{
public:
	CGage(int nPriority = OBJTYPE_UI);
	~CGage();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetTexture(float tex_x, float tex_x2, float tex_y, float tex_y2);
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR color);
	void SetGageNum(int nGageNum);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXCOLOR GetColor(void) { return m_color; }
	void SetGage(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, int nGageNum);
private:
	LPDIRECT3DTEXTURE9		m_pTexture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	D3DXVECTOR3	m_pos;					// ポリゴンの位置
	D3DXVECTOR3	m_size;					// サイズ
	D3DXCOLOR m_color;					// カラー
	int m_nGageNum;						// ゲージの値
	float m_fMaxGageNum;				// ゲージの最大
	float m_fGageNum;					// ゲージの値
	float m_fTex_X;						// テクスチャX
	float m_fTex_X2;					// テクスチャX2
	float m_fTex_Y;						// テクスチャY
	float m_fTex_Y2;					// テクスチャY2
};

#endif
