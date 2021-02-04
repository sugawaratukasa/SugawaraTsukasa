//******************************************************************************
// 入力処理 [input.h]
// Author : 管原　司
//******************************************************************************
#ifndef _INPUT_H_
#define _INPUT_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define NUM_KEY_MAX (256)
//******************************************************************************
// クラス
//******************************************************************************
class CInput
{
public:
	CInput();
	virtual~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;		// Device
	static LPDIRECTINPUT8 m_pDInput;	// DInput
};
#endif
