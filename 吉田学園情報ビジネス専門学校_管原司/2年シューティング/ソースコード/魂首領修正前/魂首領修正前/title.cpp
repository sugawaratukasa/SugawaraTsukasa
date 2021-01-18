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
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[MAX_TITLE_TEX] = {};
//--------------------------------------------------
//�e�N�X�`���̃��[�h
//--------------------------------------------------
HRESULT CTitle::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Title.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/PressEnter.png", &m_apTexture[1]);
	return S_OK;
}
//-------------------------------------------------
//�e�N�X�`���̔j��
//-------------------------------------------------
void CTitle::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//---------------------------------------------------
//�����֐�
//---------------------------------------------------
CTitle * CTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayer�N���X�̃|�C���^
	CTitle * pTitle;
	//�������m��
	pTitle = new CTitle;
	//������
	pTitle->Init(pos, rot, sizeX, sizeY);
	return pTitle;
}
//---------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------
CTitle::CTitle(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_bfade = false;
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bColor = false;
}
//---------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------
CTitle::~CTitle()
{
}
//---------------------------------------------------
//������
//---------------------------------------------------
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//������
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		//�������m��
		m_apScene2D[nCnt] = new CScene2d;
		//RGB�̐ݒ�
		m_apScene2D[nCnt]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		//�e�N�X�`���̎󂯓n��
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
		//�e�N�X�`���Z�b�g
		m_apScene2D[nCnt]->SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
	}
	m_apScene2D[0]->Init(pos, rot, sizeX, sizeY);
	m_apScene2D[1]->Init(D3DXVECTOR3(pos.x, 600, 0.0f), rot, 200, 200);
	CPolygon::Create(D3DXVECTOR3(RIGHT_POS_X, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGON_SIZE_X, SCREEN_HEIGHT);
	CPolygon::Create(D3DXVECTOR3(LEFT_POS_X, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGON_SIZE_X, SCREEN_HEIGHT);
	return S_OK;
}
//---------------------------------------------------
//�I��
//---------------------------------------------------
void CTitle::Uninit(void)
{
	//�j��
	Release();
}
//---------------------------------------------------
//�X�V
//---------------------------------------------------
void CTitle::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		m_apScene2D[nCnt]->Update();
	}
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
	if (m_bColor == false)
	{
		m_color.a -= 0.05f;
		if (m_color.a <= 0.1f)
		{
			m_bColor = true;
		}
	}
	else
	{
		m_color.a += 0.05f;
		if (m_color.a >= 1.0f)
		{
			m_bColor = false;
		}
	}
	m_apScene2D[1]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_color.a));
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_bfade = true;
	}
	//true�̏ꍇ
	if (m_bfade == true)
	{
		CSceneManager::StartFade(CSceneManager::MODE_TUTRIAL);
	}
}
//---------------------------------------------------
//�`��
//---------------------------------------------------
void CTitle::Draw(void)
{
}