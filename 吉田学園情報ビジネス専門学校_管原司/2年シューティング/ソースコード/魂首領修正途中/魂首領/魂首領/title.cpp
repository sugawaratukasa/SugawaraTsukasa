//******************************************************************************
// �^�C�g�� [title.cpp]
// Author : �ǌ� �i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "sound.h"
#include "title.h"
#include "fade.h"
#include "polygon.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define TITLE_WAIT_COUNT (10)								// �Q�[���֑J�ڂ���J�E���g
#define PRESS_ENTER_SIZE (D3DXVECTOR3(200.0f,200.0f,0.0f))	// �v���X�G���^�[�T�C�Y
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[MAX_TITLE_TEX] = {};

//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CTitle::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Title.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/PressEnter.png", &m_apTexture[1]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
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
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CTitle::CTitle(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos		= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size		= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_color		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bColor	= false;
	m_bfade		= false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CTitle::~CTitle()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CTitle * CTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�@CTitle�N���X�̃|�C���^
	CTitle * pTitle;

	//�@�������m��
	pTitle = new CTitle;

	// �ʒu���W���
	pTitle->m_pos = pos;

	// �T�C�Y���
	pTitle->m_size = size;

	// ������
	pTitle->Init();

	// �|�C���^��Ԃ�
	return pTitle;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CTitle::Init()
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
	}
	// �ʒu���W�ݒ�
	m_apScene2D[0]->SetPosition(m_pos);
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(m_pos.x, 600.0f, 0.0f));

	// �T�C�Y�ݒ�
	m_apScene2D[0]->SetSize(m_size);
	m_apScene2D[1]->SetSize(PRESS_ENTER_SIZE);

	// ������
	m_apScene2D[0]->Init();
	m_apScene2D[1]->Init();

	// ���|���S������
	CPolygon::Create(POLYGON_RIGHT_POS, POLYGON_SIZE);
	CPolygon::Create(POLYGON_LEFT_POS, POLYGON_SIZE);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CTitle::Uninit(void)
{
	//�I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CTitle::Update(void)
{
	// �ő吔���J��Ԃ�
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		// �X�V
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

	// false�̏ꍇ
	if (m_bColor == false)
	{
		// ���l���Z
		m_color.a -= 0.05f;
		// 0.1�ȉ��̏ꍇ
		if (m_color.a <= 0.1f)
		{
			// true�ɂ���
			m_bColor = true;
		}
	}
	else
	{
		// ���l���Z
		m_color.a += 0.05f;
		// 1.0f�ȏ�̏ꍇ
		if (m_color.a >= 1.0f)
		{
			// false�ɂ���
			m_bColor = false;
		}
	}
	// �J���[�ݒ�
	m_apScene2D[1]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_color.a));

	// A�{�^���܂���ENTER����������
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// �T�E���h�Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

		// true��
		m_bfade = true;
	}
	//true�̏ꍇ
	if (m_bfade == true)
	{
		// �t�F�[�h�J�n
		CSceneManager::StartFade(CSceneManager::MODE_TUTRIAL);
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CTitle::Draw(void)
{
}