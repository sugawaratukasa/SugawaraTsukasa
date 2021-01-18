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
#include "result.h"
#include "fade.h"
#include "ranking.h"
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;
CPlayerdata *CResult::m_pPlayerData = NULL;
//--------------------------------------------------
//�e�N�X�`���̃��[�h
//--------------------------------------------------
HRESULT CResult::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Ranking.png", &m_pTexture);
	return S_OK;
}
//-------------------------------------------------
//�e�N�X�`���̔j��
//-------------------------------------------------
void CResult::Unload(void)
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
CResult * CResult::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayer�N���X�̃|�C���^
	CResult * pResult;
	//�������m��
	pResult = new CResult;
	//������
	pResult->Init(pos, rot, sizeX, sizeY);
	return pResult;
}
//---------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------
CResult::CResult(int nPriority) : CScene(nPriority)
{
	m_pScene2D = NULL;
}
//---------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------
CResult::~CResult()
{
	m_bfade = false;
}
//---------------------------------------------------
//������
//---------------------------------------------------
HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//�������m��
	m_pScene2D = new CScene2d;
	m_pScene2D->Init(pos, rot, sizeX, sizeY);
	//RGB�̐ݒ�
	m_pScene2D->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//�e�N�X�`���̎󂯓n��
	m_pScene2D->BindTexture(m_pTexture);
	//�e�N�X�`���Z�b�g
	m_pScene2D->SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
	//�����L���O����
	CRanking::Create(D3DXVECTOR3(700.0f, 300.0f, 0.0f), rot, 30, 30);
	return S_OK;
}
//---------------------------------------------------
//�I��
//---------------------------------------------------
void CResult::Uninit(void)
{
	//�j��
	Release();
}
//---------------------------------------------------
//�X�V
//---------------------------------------------------
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
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		m_bfade = true;
	}
	//true�̏ꍇ
	if (m_bfade == true)
	{
		CSceneManager::StartFade(CSceneManager::MODE_TITLE);
	}
}
//---------------------------------------------------
//�`��
//---------------------------------------------------
void CResult::Draw(void)
{
}