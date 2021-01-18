#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_
#define NUM_KEY_MAX 256
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetKeyboardPress(int nKey);
	bool GetKeyboardTrigger(int nKey);
	bool GetKeyboardRelease(int nKey);
private:
	BYTE m_aKeyState[NUM_KEY_MAX];		  //キーボードの入力情報ワーク
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //キーボードのトリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX]; //キーボードのリリース情報
};
#endif