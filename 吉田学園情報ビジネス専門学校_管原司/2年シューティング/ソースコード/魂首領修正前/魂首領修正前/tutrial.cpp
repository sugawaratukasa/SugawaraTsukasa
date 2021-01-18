//=============================================================================
//
// ��ʑJ��
// title.cpp
// Author : �ǌ��i
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "player.h"
#include "bullet.h"
#include "bg.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "title.h"
#include "fade.h"
#include "polygon.h"
#include "tutrial.h"
LPDIRECT3DTEXTURE9 CTutrial::m_pTexture = NULL;
//--------------------------------------------------
//�e�N�X�`���̃��[�h
//--------------------------------------------------
HRESULT CTutrial::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Tutrial.png", &m_pTexture);
	return S_OK;
}
//-------------------------------------------------
//�e�N�X�`���̔j��
//-------------------------------------------------
void CTutrial::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//---------------------------------------------------
//�����֐�
//---------------------------------------------------
CTutrial * CTutrial::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayer�N���X�̃|�C���^
	CTutrial * pTitle;
	//�������m��
	pTitle = new CTutrial;
	//������
	pTitle->Init(pos, rot, sizeX, sizeY);
	return pTitle;
}
//---------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------
CTutrial::CTutrial(int nPriority) : CScene2d(nPriority)
{
	m_fade = false;
}
//---------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------
CTutrial::~CTutrial()
{
}
//---------------------------------------------------
//������
//---------------------------------------------------
HRESULT CTutrial::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//������
	CScene2d::Init(pos, rot, sizeX, sizeY);
	//RGB�̐ݒ�
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//�e�N�X�`���̎󂯓n��
	BindTexture(m_pTexture);
	//�e�N�X�`���Z�b�g
	SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
	CPolygon::Create(D3DXVECTOR3(RIGHT_POS_X, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGON_SIZE_X, SCREEN_HEIGHT);
	CPolygon::Create(D3DXVECTOR3(LEFT_POS_X, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGON_SIZE_X, SCREEN_HEIGHT);
	return S_OK;
}
//---------------------------------------------------
//�I��
//---------------------------------------------------
void CTutrial::Uninit(void)
{
	//�I��
	CScene2d::Uninit();
}
//---------------------------------------------------
//�X�V
//---------------------------------------------------
void CTutrial::Update(void)
{
	int nWaitnCnt = 0;
	//�X�V
	CScene2d::Update();
	//�T�E���h�擾
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;
	//�L�[�{�[�h�擾
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();
	//�R���g���[���[�擾
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();
	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	if (m_fade == false)
	{
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			m_fade = true;
		}
	}
	if (m_fade == true)
	{
		CSceneManager::StartFade(CSceneManager::MODE_GAME);
	}
}
//---------------------------------------------------
//�`��
//---------------------------------------------------
void CTutrial::Draw(void)
{
	//�`��
	CScene2d::Draw();
}