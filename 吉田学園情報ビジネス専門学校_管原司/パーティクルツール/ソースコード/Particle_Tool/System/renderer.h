//******************************************************************************
// レンダラー[renderer.h]
// Author : 管原司
//******************************************************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
//******************************************************************************
//レンダリングクラス
//******************************************************************************
class CRenderer
{
public:
	CRenderer();	
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void SetNumFPS(int nCountFPS) { m_nCountFPS = nCountFPS; }
#endif
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
private:
	void DrawFPS(void);
	LPDIRECT3D9				m_pD3D = NULL;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)

#ifdef _DEBUG
	LPD3DXFONT				m_pFont = NULL;			// フォントへのポインタ
	int						m_nCountFPS;			// FPSカウンタ
#endif
};
#endif // !_RENDERER_H_
