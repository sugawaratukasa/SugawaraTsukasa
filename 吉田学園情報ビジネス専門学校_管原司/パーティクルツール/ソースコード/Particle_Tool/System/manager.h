//******************************************************************************
//	マネージャー[manager.h]
//	Author : 管原司
//******************************************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
//******************************************************************************
//前方宣言
//******************************************************************************
class CRenderer;
class CCamera;
class CLight;
class CInputKeyboard;
class CDebugProc;
class CMode;
class CTexture;
//******************************************************************************
//クラス
//******************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TOOL,
		MODE_MAX
	}MODE;
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadAll(void);
	void UnloadAll(void);
	static void CreateCamera(void);
	void SetNumFPS(int nCountFPS) { m_nCountFPS = nCountFPS; }
	void SetMode(MODE mode);

	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CTexture *GetTexture(void) { return m_pTexture; }
private:
	static CRenderer *m_pRenderer;			//レンダラー
	static CCamera *m_pCamera;				//カメラ
	static CMode *m_pMode;					// モード
	static CTexture *m_pTexture;			// テクスチャ
	int m_nCountFPS;						// FPSの値
	MODE m_Mode;							// モード
};
#endif // !_MANAGER_H_
