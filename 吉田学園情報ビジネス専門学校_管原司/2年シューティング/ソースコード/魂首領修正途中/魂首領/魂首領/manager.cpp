//******************************************************************************
// manager [manager.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//*****************************************************************************
// �t�@�C���̃C���N���[�h
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
#include "boss.h"
#include "warning.h"
#include "tutrial.h"
#include "ship.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODE_SIZE (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT,0.0f))
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRenderer * CSceneManager::m_pRenderer = NULL;
CInputKeyboard * CSceneManager::m_pInputKeyboard = NULL;
CInputJoystick * CSceneManager::m_pInputJoystick = NULL;
CSound * CSceneManager::m_pSound = NULL;
CTitle * CSceneManager::m_pTitle = NULL;
CTutrial * CSceneManager::m_pTutrial = NULL;
CGame * CSceneManager::m_pGame = NULL;
CResult * CSceneManager::m_pResult = NULL;
CFade * CSceneManager::m_pFade = NULL;
CSceneManager::MODE CSceneManager::m_mode = MODE_NONE;
bool CSceneManager::m_bUseFade = false;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CSceneManager::CSceneManager()
{
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CSceneManager::~CSceneManager()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CSceneManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	// �����_���[�̐���
	if (m_pRenderer == NULL)
	{
		// �������m��
		m_pRenderer = new  CRenderer;
		// NULL�łȂ��ꍇ
		if (m_pRenderer != NULL)
		{
			// �����_���[����������
			m_pRenderer->Init(hWnd, TRUE);
		}
		// NULL�̏ꍇ
		else
		{
			return 0;
		}
	}
	// �L�[�{�[�h����
	if (m_pInputKeyboard == NULL)
	{
		// �������m��
		m_pInputKeyboard = new CInputKeyboard;
		// NULL�łȂ��Ƃ�
		if (m_pInputKeyboard != NULL)
		{
			// �L�[�{�[�h����������
			m_pInputKeyboard->Init(hInsitance, hWnd);
		}
		// NULL�̏ꍇ
		else
		{
			return 0;
		}
	}
	// �R���g���[���[����
	if (m_pInputJoystick == NULL)
	{
		// �������m��
		m_pInputJoystick = new CInputJoystick;
		// NULL�łȂ��Ƃ�
		if (m_pInputJoystick != NULL)
		{
			// �R���g���[���[����������
			m_pInputJoystick->Init(hInsitance, hWnd);
		}
		// NULL�̏ꍇ
		else
		{
			return 0;
		}
	}
	//�T�E���h����
	if (m_pSound == NULL)
	{
		// ������m��
		m_pSound = new CSound;

		// NULL�łȂ��Ƃ�
		if (m_pSound != NULL)
		{
			// �T�E���h����������
			m_pSound->Init(hWnd);
		}
		// NULL�̏ꍇ
		else
		{
			return 0;
		}
	}
	// �e�N�X�`���S�ǂݍ���
	LoadAll();

	// �^�C�g���ɐݒ�
	SetMode(MODE_TITLE);

	// NULL�łȂ��ꍇ
	if (m_pFade == NULL)
	{
		// �t�F�[�h����
		m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), FADE_SIZE, m_mode);
	}
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CSceneManager::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g��j��
	CScene::ReleaseAll();
	// �e�N�X�`���S�ǂݍ���
	UnloadAll();
	//�T�E���h�S��~
	m_pSound->StopSound();

	// NULL�łȂ��ꍇ
	if (m_pSound != NULL)
	{
		// �T�E���h�̏I������
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	// NULL�łȂ��ꍇ
	if (m_pInputJoystick != NULL)
	{
		// �R���g���[���[�̏I������
		m_pInputJoystick->Uninit();
		delete m_pInputJoystick;
		m_pInputJoystick = NULL;
	}
	// NULL�łȂ��ꍇ
	if (m_pInputKeyboard != NULL)
	{
		// �L�[�{�[�h�̏I������
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	// NULL�łȂ��ꍇ
	if (m_pRenderer != NULL)
	{
		// �����_���[�̏I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	// NULL�łȂ��ꍇ
	if (m_pFade != NULL)
	{
		// �t�F�[�h�I��
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}
}

//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CSceneManager::Update(void)
{
	// NULL�łȂ��ꍇ
	if (m_pRenderer != NULL)
	{
		// �����_���[�X�V
		m_pRenderer->Update();
	}
	// NULL�łȂ��ꍇ
	if (m_pInputKeyboard != NULL)
	{
		// �L�[�{�[�h�X�V
		m_pInputKeyboard->Update();
	}
	// NULL�łȂ��ꍇ
	if (m_pInputJoystick != NULL)
	{
		// �R���g���[���[�X�V
		m_pInputJoystick->Update();
	}
	// m_bUseFade��true�̏ꍇ
	if (m_bUseFade == true)
	{
		// NULL�łȂ��ꍇ
		if (m_pFade != NULL)
		{
			// �t�F�[�h�X�V
			m_pFade->Update();
		}
	}
}

//******************************************************************************
// �`��֐�
//******************************************************************************
void CSceneManager::Draw(void)
{
	//�`�揈��
	m_pRenderer->Draw(); 
}
//******************************************************************************
// ���[�h�ݒ�
//******************************************************************************
void CSceneManager::SetMode(MODE mode)
{
	// mode���
	m_mode = mode;

	// �S�I��
	CScene::ReleaseAll();

	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		m_pTitle = CTitle::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), MODE_SIZE);
		break;
		// �`���[�g���A��
	case MODE_TUTRIAL:
		m_pTutrial = CTutrial::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), MODE_SIZE);
		break;
		// �Q�[��
	case MODE_GAME:
		m_pGame = CGame::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), MODE_SIZE);
		break;
		// ���U���g
	case MODE_RESULT:
		m_pResult = CResult::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), MODE_SIZE);
		break;
		// ���̑��̏ꍇ
	default:
		break;
		return;
	}
	// �L�[�{�[�h�X�V
	m_pInputJoystick->Update();
}
//******************************************************************************
// �t�F�[�h�J�n
//******************************************************************************
void CSceneManager::StartFade(MODE mode)
{
	// mode����
	m_mode = mode;
	// true��
	m_bUseFade = true;
}
//******************************************************************************
// �t�F�[�h��~
//******************************************************************************
void CSceneManager::StopFade(void)
{
	// false��
	m_bUseFade = false;
}
//******************************************************************************
// �e�N�X�`���S�ǂݍ��݊֐�
//******************************************************************************
void CSceneManager::LoadAll(void)
{
	// �^�C�g��
	CTitle::Load();
	// ���U���g
	CResult::Load();
	// �w�i
	CBg::Load();
	// ���C�t
	CLife::Load();
	// ���@
	CPlayer::Load();
	// �G
	CEnemy::Load();
	// �e
	CBullet::Load();
	// ����
	CExplosion::Load();
	// �i���o�[
	CNumber::Load();
	// �A�C�e��
	CItem::Load();
	// �{��
	CBomUI::Load();
	// Ship
	CShip::Load();
	// �{�X
	CBoss::Load();
	// warning
	CWarning::Load();
	// �`���[�g���A��
	CTutrial::Load();
}
//******************************************************************************
// �e�N�X�`���S�j���֐�
//******************************************************************************
void CSceneManager::UnloadAll(void)
{
	// �e�N�X�`���j��
	// �`���[�g���A��
	CTutrial::Unload();
	// warning
	CWarning::Unload();
	// �{�X
	CBoss::Unload();
	// Ship
	CShip::Unload();
	// �{��
	CBomUI::Unload();
	// �A�C�e��
	CItem::Unload();
	// �i���o�[
	CNumber::Unload();
	// ����
	CExplosion::Unload();
	// �e
	CBullet::Unload();
	// �G
	CEnemy::Unload();
	// ���@
	CPlayer::Unload();
	// ���C�t
	CLife::Unload();
	// �w�i
	CBg::Unload();
	// Result
	CResult::Unload();
	// �^�C�g��
	CTitle::Unload();
}