//-----------------------------------------------------------------
// Continue
// continue.cpp
// Author �ǌ� �i
//-----------------------------------------------------------------
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
#include "fade.h"
#include "item.h"
#include "bomui.h"
#include "polygon.h"
#include "ship.h"
#include "continue.h"
//-----------------------------------------------------------------
//�R���g���N�^
//-----------------------------------------------------------------
CContinue::CContinue(int nPriority)
{
	m_pNumber = NULL;
	m_nContinueCount = 0;
	m_nContinueNum = 0;
}
//-----------------------------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------------------------
CContinue::~CContinue()
{
}
//-----------------------------------------------------------------
//�����֐�
//-----------------------------------------------------------------
CContinue * CContinue::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayer�N���X�̃|�C���^
	CContinue * pContinue;
	//�������m��
	pContinue = new CContinue;
	//������
	pContinue->Init(pos, rot, sizeX, sizeY);
	return pContinue;
}
//-----------------------------------------------------------------
//����������
//-----------------------------------------------------------------
HRESULT CContinue::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//������
	m_pNumber = CNumber::Create(pos, sizeX, sizeY);
	m_nContinueNum = 9;
	m_pNumber->SetNumber(m_nContinueNum);
	
	return S_OK;
}
//-----------------------------------------------------------------
//�I������
//-----------------------------------------------------------------
void CContinue::Uninit(void)
{
	if (m_pNumber != NULL)
	{
		m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = NULL;
	}
	//�����[�X
	Release();
}
//-----------------------------------------------------------------
//�X�V����
//-----------------------------------------------------------------
void CContinue::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();
	//�R���g���[���[�擾
	DIJOYSTATE js;
	//�C���v�b�g�W���C�X�e�B�b�N
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	//�f�o�C�X�擾
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();
	//�T�E���h�擾
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;
	//�R���e�B�j���[�^�C���̃C���N�������g
	m_nContinueCount++;
	//1�b��������
	if (m_nContinueCount % 60 == 0)
	{
		//�i���o�[�̃f�N�������g
		m_nContinueNum--;
		//�i���o�[�̐ݒ�
		m_pNumber->SetNumber(m_nContinueNum);
	}
	//�i���o�[��0�̏ꍇ
	if (m_nContinueNum <= 0)
	{
		//���U���g�ɑJ��
		CSceneManager::StartFade(CSceneManager::MODE_RESULT);
	}
	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(11) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		//�R���e�B�j���[�̔���
		pPlayer->SetContinue(PLAYER_CONTINUE);
		Uninit();
		return;
	}
	
}
//-----------------------------------------------------------------
//�`�揈��
//-----------------------------------------------------------------
void CContinue::Draw(void)
{
	m_pNumber->Draw();
}
