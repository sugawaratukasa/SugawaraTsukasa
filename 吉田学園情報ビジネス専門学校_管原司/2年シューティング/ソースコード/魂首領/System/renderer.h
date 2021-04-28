//******************************************************************************
// 描画 [renderer.h]
// Author : 管原　司
//******************************************************************************
#ifndef _RENERER_H_
#define _RENDERER_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <dinput.h>
#include "d3dx9.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define WINDOW_POS_X	(0)		// サイズ
#define WINDOW_POS_Y	(0)		// サイズ
#define SCREEN_WIDTH	(1280)	// サイズ
#define SCREEN_HEIGHT	(720)	// サイズ
//#undef _DEBUG
//******************************************************************************
// クラス
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
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3Decvice; }
private:
	void DrawFPS(void);
	LPDIRECT3D9 m_pD3D;				//LPDIRECT3D9
	LPDIRECT3DDEVICE9 m_pD3Decvice;	//デバイス
	LPD3DXFONT m_pFont;				//フォント
};
#endif