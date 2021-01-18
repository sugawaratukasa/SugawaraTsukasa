//=============================================================================
//
// Manager 
// manager.h
// Author : 管原司
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
//-----------------------------------------------------------------------------
//前方宣言
//-----------------------------------------------------------------------------
class CRenderer;
class CInputKeyboard;
class CInputJoystick;
class CSound;
class CBullet;
class CTitle;
class CGame;
class CResult;
class CFade;
class CTutrial;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSceneManager
{
public:
	//モードのタイプ
	typedef enum
	{
		MODE_NONE = 0,
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
	static CBullet * GetBullet(void) { return m_pBullet; }
	static CFade * GetFade(void) { return m_pFade; }
	static CGame *GetGame(void) { return m_pGame; }
	static void StartFade(MODE mode);
	static void StopFade(void);
private:
	static MODE m_mode;	//モード 
	static CTitle * m_pTitle;	//タイトルの情報
	static CTutrial * m_pTutrial;	//チュートリアル
	static CGame * m_pGame; //ゲームの情報
	static CResult * m_pResult;	//Resultの情報
	static CRenderer * m_pRenderer;	//レンダラー情報
	static CInputKeyboard * m_pInputKeyboard;	//キーボード情報
	static CInputJoystick * m_pInputJoystick;	//ジョイスティックの情報
	static CSound * m_pSound;	//サウンドの情報
	static CBullet * m_pBullet;	//弾の情報
	static CFade * m_pFade;	//フェードの情報
	static bool m_bUseFade;	//フェードの使用
};
#endif