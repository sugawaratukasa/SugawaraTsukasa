//******************************************************************************
// 2D [scene2d.h]
// Author : 管原司
//******************************************************************************
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// クラス
//******************************************************************************
class CScene2D :public CScene
{
public:
	CScene2D(int nPriority = OBJTYPE_DEFAULT);
	~CScene2D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR color);
	void SetRotation(D3DXVECTOR3 rot);
	void SetScale(float fScale);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR color);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXCOLOR GetColor(void) { return m_color; }
	float GetScale(void) { return m_fScale; }
private:
	LPDIRECT3DTEXTURE9		m_pTexture;				// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;					// ポリゴンの位置
	D3DXVECTOR3				m_size;					// サイズ
	D3DXVECTOR3				m_rot;					// 向き
	D3DXCOLOR				m_color;				// カラー
	float					m_fAngle;				// 角度
	float					m_fLength;				// 半径
	float					m_fScale;				// 拡大率
};

#endif // !_SCENE2D_H_
