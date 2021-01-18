//******************************************************************************
// �`���[�g���A�� [tutrial.cpp]
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
#include "fade.h"
#include "polygon.h"
#include "sound.h"
#include "tutrial.h"
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CTutrial::m_pTexture = NULL;
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CTutrial::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Tutrial.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CTutrial::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CTutrial * CTutrial::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CTutrial�N���X�̃|�C���^
	CTutrial * pTitle;

	// �������m��
	pTitle = new CTutrial;

	// �ʒu���W�ݒ�
	pTitle->SetPosition(pos);

	// �T�C�Y�ݒ�
	pTitle->SetSize(size);

	// ������
	pTitle->Init();

	// �|�C���^��Ԃ�
	return pTitle;
}
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************-
CTutrial::CTutrial(int nPriority) : CScene2d(nPriority)
{
	m_bfade = false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CTutrial::~CTutrial()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CTutrial::Init()
{
	//������
	CScene2d::Init();

	//RGB�̐ݒ�
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�e�N�X�`���̎󂯓n��
	BindTexture(m_pTexture);

	// ���|���S������
	CPolygon::Create(POLYGON_RIGHT_POS, POLYGON_SIZE);
	CPolygon::Create(POLYGON_LEFT_POS, POLYGON_SIZE);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CTutrial::Uninit(void)
{
	//�I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CTutrial::Update(void)
{
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

	// false�̏ꍇ
	if (m_bfade == false)
	{
		// �R���g���[���[A�{�^���܂���ENTER
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
		{
			// �T�E���h�Đ�
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			// true��
			m_bfade = true;
		}
	}
	// true�̏ꍇ
	if (m_bfade == true)
	{
		// �t�F�[�h�J�n
		CSceneManager::StartFade(CSceneManager::MODE_GAME);
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CTutrial::Draw(void)
{
	//�`��
	CScene2d::Draw();
}