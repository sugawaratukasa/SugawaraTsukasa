//******************************************************************************
// manager [manager.h]
// Author : 管原　司
//******************************************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_
//******************************************************************************
// 前方宣言
//******************************************************************************
class CRenderer;
class CInputKeyboard;
class CInputJoystick;
class CSound;
class CMode;
class CFade;
class CTutrial;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSceneManager
{
public:
	//モードの列挙型
	typedef enum
	{
		MODE_NONE = -1,
		MODE_TITLE,
		MODE_TUTRIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_END
	}MODE;

	CSceneManager();
	~CSceneManager();
	HRESULT Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }
	static CRenderer * GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard * GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CInputJoystick * GetInputJoystick(void) { return m_pInputJoystick; }
	static CSound * GetSound(void) { return m_pSound; }

	//static void CreateFade(MODE mode);
	void LoadAll(void);
	void UnloadAll(void);
private:
	static MODE m_mode;							// モード 
	static CMode *m_pMode;						// モード情報
	static CRenderer * m_pRenderer;				// レンダラー情報
	static CInputKeyboard * m_pInputKeyboard;	// キーボード情報
	static CInputJoystick * m_pInputJoystick;	// ジョイスティックの情報
	static CSound * m_pSound;					// サウンドの情報
};
#endif