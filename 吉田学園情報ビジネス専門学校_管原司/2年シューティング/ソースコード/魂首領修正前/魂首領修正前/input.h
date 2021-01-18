//=============================================================================
// Keyboard
// Keyboard.h
// Author : ŠÇŒ´Ži
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#define NUM_KEY_MAX 256
//---------------------------------------------------
//ƒNƒ‰ƒX
//---------------------------------------------------
class CInput
{
public:
	CInput();
	virtual~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;
	static LPDIRECTINPUT8 m_pDInput;
};
#endif
