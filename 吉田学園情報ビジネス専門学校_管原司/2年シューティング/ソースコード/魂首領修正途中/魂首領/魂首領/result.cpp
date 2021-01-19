//******************************************************************************
// ���U���g [result.cpp]
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
#include "result.h"
#include "fade.h"
#include "score.h"
#include "ranking.h"
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;
CPlayerdata *CResult::m_pPlayerData = NULL;
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CResult::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Ranking.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CResult::Unload(void)
{
		// �e�N�X�`���̔j��
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CResult::CResult(int nPriority) : CScene(nPriority)
{
	m_pScene2D	= NULL;
	m_pos		= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size		= D3DXVECTOR3(0.0f,0.0f,0.0f);
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CResult::~CResult()
{
	m_bfade = false;
}
//******************************************************************************
// �����֐�
//******************************************************************************
CResult * CResult::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CResult�N���X�̃|�C���^
	CResult * pResult;

	// �������m��
	pResult = new CResult;

	// �ʒu���W���
	pResult->m_pos = pos;

	// �T�C�Y���
	pResult->m_size = size;

	// ������
	pResult->Init();

	// �|�C���^��Ԃ�
	return pResult;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CResult::Init()
{
	//�������m��
	m_pScene2D = new CScene2d;

	// �ʒu���W�ݒ�
	m_pScene2D->SetPosition(m_pos);

	// �T�C�Y�ݒ�
	m_pScene2D->SetSize(m_size);

	//RGB�̐ݒ�
	m_pScene2D->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�e�N�X�`���̎󂯓n��
	m_pScene2D->BindTexture(m_pTexture);

	// ������
	m_pScene2D->Init();

	//�����L���O����
	CRanking::Create(D3DXVECTOR3(700.0f, 300.0f, 0.0f), SCORE_SIZE);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CResult::Uninit(void)
{
	// �I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CResult::Update(void)
{
	//�X�V
	m_pScene2D->Update();

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

	// A�{�^���܂���ENTER���������ꍇ
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// true�ɂ���
		m_bfade = true;
	}
	//true�̏ꍇ
	if (m_bfade == true)
	{
		// �t�F�[�h�J�n
		CSceneManager::StartFade(CSceneManager::MODE_TITLE);
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CResult::Draw(void)
{
}