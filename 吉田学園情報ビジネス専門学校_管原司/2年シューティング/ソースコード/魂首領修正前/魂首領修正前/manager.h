//=============================================================================
//
// Manager 
// manager.h
// Author : �ǌ��i
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
//-----------------------------------------------------------------------------
//�O���錾
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
// �N���X��`
//*****************************************************************************
class CSceneManager
{
public:
	//���[�h�̃^�C�v
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
	static MODE m_mode;	//���[�h 
	static CTitle * m_pTitle;	//�^�C�g���̏��
	static CTutrial * m_pTutrial;	//�`���[�g���A��
	static CGame * m_pGame; //�Q�[���̏��
	static CResult * m_pResult;	//Result�̏��
	static CRenderer * m_pRenderer;	//�����_���[���
	static CInputKeyboard * m_pInputKeyboard;	//�L�[�{�[�h���
	static CInputJoystick * m_pInputJoystick;	//�W���C�X�e�B�b�N�̏��
	static CSound * m_pSound;	//�T�E���h�̏��
	static CBullet * m_pBullet;	//�e�̏��
	static CFade * m_pFade;	//�t�F�[�h�̏��
	static bool m_bUseFade;	//�t�F�[�h�̎g�p
};
#endif