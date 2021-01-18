//---------------------------------------------------
// Create
// scene2d.h
// Authur:	管原司
//---------------------------------------------------
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
#include "d3dx9.h"
//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE| D3DFVF_TEX1)
#define NUM_VERTEX	4

#define NUM_POLYGON 2
//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換用紙係数
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ
}VERTEX_2D;
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CScene2d : public CScene
{
public:
	CScene2d(int nPriority = 3);
	~CScene2d();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);
	void SetTexture(float fTexX, float fTexY, float fTexAnimX , float fTexAnimY);
	void SetRGBA(D3DXCOLOR col);
	void SetRot(D3DXVECTOR3 rot);
	void SetScale(float fScale);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	static CScene2d * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//バッファ
	D3DXVECTOR3 m_pos;	//位置座標
	D3DXVECTOR3 m_rot; //向き
	D3DXCOLOR m_col;	//カラー
	int m_nsizeX;	//サイズX
	int m_nsizeY;	//サイズY
	float m_fAngle;	//角度
	float m_fLength;	//対角線
	float m_fTexX;	//テクスチャX
	float m_fTexY;	//テクスチャY
	float m_fTexAnimX;	//テクスチャアニメーション
	float m_fTexAnimY;	//テクスチャアニメーション
	float m_fScale;		//拡大
	int m_nCount;	//
};
#endif