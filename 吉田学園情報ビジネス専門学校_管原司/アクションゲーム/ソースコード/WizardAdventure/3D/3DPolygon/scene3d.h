//******************************************************************************
// 3D[scene3d.h]
// Author : 管原司
//******************************************************************************
#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// クラス
//******************************************************************************
class CScene3d :public CScene
{
public:
	CScene3d(int nPriority = OBJTYPE_DEFAULT);
	~CScene3d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR col);
	void SetScale(float scale);
	void SetTexture(float tex_x, float tex_x2, float tex_y, float tex_y2);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXCOLOR GetColor(void) { return m_col; }
	float GetScale(void) { return m_fScale; }
private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						// 位置座標
	D3DXVECTOR3 m_size;						// サイズ
	D3DXVECTOR3 m_rot;						// 向き
	D3DXCOLOR m_col;						// 色
	D3DXMATRIX m_mtxWorld;					// ワールド座標
	float m_fTex_X;							// テクスチャX
	float m_fTex_X2;						// テクスチャX2
	float m_fTex_Y;							// テクスチャY
	float m_fTex_Y2;						// テクスチャY2
	float m_fScale;							// 拡大率
	bool m_bDraw;							// 描画判定
};
#endif