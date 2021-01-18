//=============================================================================
//
// Manager 
// manager.cpp
// Author : �ǌ��i
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
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
#include "game.h"
#include "result.h"
#include "fade.h"
#include "item.h"
#include "bomui.h"
#include "polygon.h"
#include "ship.h"
#include "boss.h"
#include "warning.h"
#include "tutrial.h"
//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
CRenderer * CSceneManager::m_pRenderer = NULL;
CInputKeyboard * CSceneManager::m_pInputKeyboard = NULL;
CInputJoystick * CSceneManager::m_pInputJoystick = NULL;
CSound * CSceneManager::m_pSound = NULL;
CBullet * CSceneManager::m_pBullet = NULL;
CTitle * CSceneManager::m_pTitle = NULL;
CTutrial * CSceneManager::m_pTutrial = NULL;
CGame * CSceneManager::m_pGame = NULL;
CResult * CSceneManager::m_pResult = NULL;
CFade * CSceneManager::m_pFade = NULL;
CSceneManager::MODE CSceneManager::m_mode = MODE_NONE;
bool CSceneManager::m_bUseFade = false;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSceneManager::CSceneManager()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneManager::~CSceneManager()
{
}
//=============================================================================
// �������֐�
//=============================================================================
HRESULT CSceneManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	//�����_���[�̐���
	if (m_pRenderer == NULL)
	{
		//�������m��
		m_pRenderer = new  CRenderer;
		//NULL�łȂ��Ƃ�
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Init(hWnd, TRUE);
		}
		//NULL�̏ꍇ
		else
		{
			return 0;
		}
	}
	//�L�[�{�[�h����
	if (m_pInputKeyboard == NULL)
	{
		//�������m��
		m_pInputKeyboard = new CInputKeyboard;
		//NULL�łȂ��Ƃ�
		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInsitance, hWnd);
		}
		//NULL�̏ꍇ
		else
		{
			return 0;
		}
	}
	//�R���g���[���[����
	if (m_pInputJoystick == NULL)
	{
		//�������m��
		m_pInputJoystick = new CInputJoystick;
		//NULL�łȂ��Ƃ�
		if (m_pInputJoystick != NULL)
		{
			m_pInputJoystick->Init(hInsitance, hWnd);
		}
		//NULL�̏ꍇ
		else
		{
			return 0;
		}
	}
	//�T�E���h����
	if (m_pSound == NULL)
	{
		//������m��
		m_pSound = new CSound;
		//NULL�łȂ��Ƃ�
		if (m_pSound != NULL)
		{
			m_pSound->Init(hWnd);
		}
		//NULL�̏ꍇ
		else
		{
			return 0;
		}
	}
	//�e�N�X�`�����[�h
	CTitle::Load();
	//Result
	CResult::Load();
	//�w�i
	CBg::Load();
	//���C�t
	CLife::Load();
	//���@
	CPlayer::Load();
	//�G
	CEnemy::Load();
	//�e
	CBullet::Load();
	//����
	CExplosion::Load();
	//�i���o�[
	CNumber::Load();
	//�A�C�e��
	CItem::Load();
	//�{��
	CBom::Load();
	//Ship
	CShip::Load();
	//�{�X
	CBoss::Load();
	//warning
	CWarning::Load();
	//�`���[�g���A��
	CTutrial::Load();
	//�Z�b�g�^�C�g��
	SetMode(MODE_TITLE);
	if (m_pFade == NULL)
	{
		//�t�F�[�h����
		m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, m_mode);
	}
	return S_OK;
}
//=============================================================================
// �I���֐�
//=============================================================================
void CSceneManager::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g��Release
	//�e�N�X�`���j��
	//�G�t�F�N�g
	CScene::ReleaseAll();
	//�`���[�g���A��
	CTutrial::Unload();
	//warning
	CWarning::Unload();
	//�{�X
	CBoss::Unload();
	//Ship
	CShip::Unload();
	//�{��
	CBom::Unload();
	//�A�C�e��
	CItem::Unload();
	//�i���o�[
	CNumber::Unload();
	//����
	CExplosion::Unload();
	//�e
	CBullet::Unload();
	//�G
	CEnemy::Unload();
	//���@
	CPlayer::Unload();
	//���C�t
	CLife::Unload();
	//�w�i
	CBg::Unload();
	//Result
	CResult::Unload();
	//�^�C�g��
	CTitle::Unload();
	//�T�E���h�j��
	m_pSound->StopSound();
	//�T�E���h�̏I������
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	//�R���g���[���[�̏I������
	if (m_pInputJoystick != NULL)
	{
		m_pInputJoystick->Uninit();
		delete m_pInputJoystick;
		m_pInputJoystick = NULL;
	}
	//�L�[�{�[�h�̏I������
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	//�����_���[�̏I������
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	//�t�F�[�h�I��
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CSceneManager::Update(void)
{
	//�����_���[�X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();	// �X�V����
	}
	//�L�[�{�[�h�X�V
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	//�L�[�{�[�h�X�V
	if (m_pInputJoystick != NULL)
	{
		m_pInputJoystick->Update();
	}
	//�t�F�[�h�X�V
	if (m_bUseFade == true)
	{
		if (m_pFade != NULL)
		{
			m_pFade->Update();
		}
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CSceneManager::Draw(void)
{
	//�`�揈��
	m_pRenderer->Draw(); 
}
//----------------------------------------------------------------------------
//���[�h�̃Z�b�g
//----------------------------------------------------------------------------
void CSceneManager::SetMode(MODE mode)
{
	m_mode = mode;
	CScene::ReleaseAll();
	switch (m_mode)
	{
		//Title
	case MODE_TITLE:
		m_pTitle = CTitle::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT);
		break;
	case MODE_TUTRIAL:
		m_pTutrial = CTutrial::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT);
		break;
		//Game
	case MODE_GAME:
		m_pGame = CGame::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH , SCREEN_HEIGHT);
		break;
		//Result
	case MODE_RESULT:
		m_pResult = CResult::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 2 , SCREEN_HEIGHT);
		break;
	default:
		break;
		return;
	}
	m_pInputJoystick->Update();
}
//----------------------------------------------------
//�t�F�[�h�̊J�n
//----------------------------------------------------
void CSceneManager::StartFade(MODE mode)
{
	m_mode = mode;
	m_bUseFade = true;
}
//----------------------------------------------------
//
//----------------------------------------------------
void CSceneManager::StopFade(void)
{
	m_bUseFade = false;
}
