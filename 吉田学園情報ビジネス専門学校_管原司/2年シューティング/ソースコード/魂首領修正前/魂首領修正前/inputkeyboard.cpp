//---------------------------------------------------
// inputkeyboard
// inputkeyboard.cpp
// Author:	管原司
//---------------------------------------------------
#include "main.h"
#include "input.h"
#include "inputkeyboard.h"
//---------------------------------------------------
//コンストラクタ
//---------------------------------------------------
CInputKeyboard::CInputKeyboard()
{
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
}
//---------------------------------------------------
//デストラクタ
//---------------------------------------------------
CInputKeyboard::~CInputKeyboard()
{
}
//---------------------------------------------------
//初期化
//---------------------------------------------------
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	m_pDevice->Acquire();
	return S_OK;
}
//---------------------------------------------------
//終了
//---------------------------------------------------
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}
//---------------------------------------------------
//更新
//---------------------------------------------------
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyState[nCntKey] = m_aKeyState[nCntKey]; //キープレス情報保存
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}
//---------------------------------------------------
//プレス
//---------------------------------------------------
bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return m_aKeyState[nKey] & 0x80 ? true : false;
}
//---------------------------------------------------
//トリガー
//---------------------------------------------------
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return m_aKeyStateTrigger[nKey] & 0x80 ? true : false;
}
//---------------------------------------------------
//リリース
//---------------------------------------------------
bool CInputKeyboard::GetKeyboardRelease(int nKey)
{
	return m_aKeyStateRelease[nKey] & 0x80 ? true : false;
}
