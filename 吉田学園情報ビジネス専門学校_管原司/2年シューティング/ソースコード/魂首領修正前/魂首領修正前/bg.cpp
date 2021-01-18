//---------------------------------------------------
// BG
// bg.cpp
// Author:	�ǌ��i
//---------------------------------------------------
//---------------------------------------------------
//�C���N���[�h�t�@�C��
//---------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "bg.h"
#include "player.h"
#include "game.h"
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};
//--------------------------------------------------
//�e�N�X�`���ǂݍ���
//--------------------------------------------------
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bg2.png", &m_apTexture[TYPE_FARST_BG]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bg101.png", &m_apTexture[TYPE_SECOUND_BG]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bg102.png", &m_apTexture[TYPE_THIRD_BG]);
	return S_OK;
}
//--------------------------------------------------
//�e�N�X�`���̔j��
//--------------------------------------------------
void CBg::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
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
CBg * CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//�|�C���^
	CBg * pBg;
	//�������m��
	pBg = new CBg;
	//������
	pBg->Init(pos, rot, sizeX, sizeY);
	return pBg;
}
//---------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------
CBg::CBg(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_type = TYPE_NONE;
	m_Farstpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Secoundpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Thirdpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_texsizeX = 0.0f;
	m_texsizeY = 0.0f;
	m_fFastMove = 0.0f;
	m_fSlowMove = 0.0f;
	m_fmove = 0.0f;
}
//---------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------
CBg::~CBg()
{
}
//---------------------------------------------------
//������
//---------------------------------------------------
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//�������m��
	m_apScene2D[TYPE_FARST_BG] = new CScene2d;
	m_apScene2D[TYPE_SECOUND_BG] = new CScene2d;
	m_apScene2D[TYPE_THIRD_BG] = new CScene2d;
	//������
	m_apScene2D[TYPE_FARST_BG]->Init(pos, rot, sizeX, sizeY);
	m_apScene2D[TYPE_SECOUND_BG]->Init(pos, rot, sizeX, sizeY);
	m_apScene2D[TYPE_THIRD_BG]->Init(pos, rot, sizeX, sizeY);
	//�J���[�ݒ�
	m_apScene2D[TYPE_FARST_BG]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_SECOUND_BG]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_THIRD_BG]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//�e�N�X�`���̎󂯓n��
	m_apScene2D[TYPE_FARST_BG]->BindTexture(m_apTexture[TYPE_FARST_BG]);
	m_apScene2D[TYPE_SECOUND_BG]->BindTexture(m_apTexture[TYPE_SECOUND_BG]);
	m_apScene2D[TYPE_THIRD_BG]->BindTexture(m_apTexture[TYPE_THIRD_BG]);
	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	m_apScene2D[TYPE_FARST_BG]->SetObjType(CScene::OBJTYPE_BG);
	m_apScene2D[TYPE_SECOUND_BG]->SetObjType(CScene::OBJTYPE_BG);
	m_apScene2D[TYPE_THIRD_BG]->SetObjType(CScene::OBJTYPE_BG);

	return S_OK;
}
//---------------------------------------------------
//�I��
//---------------------------------------------------
void CBg::Uninit(void)
{
	//�I��
	Release();
}
//---------------------------------------------------
//�X�V
//---------------------------------------------------
void CBg::Update(void)
{
	//�X�V
	m_apScene2D[TYPE_FARST_BG]->Update();
	m_apScene2D[TYPE_SECOUND_BG]->Update();
	m_apScene2D[TYPE_THIRD_BG]->Update();
	//
	//�L�[�{�[�h�擾
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();
	//�R���g���[���[�擾
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();
	//�v���C���[�̍��W�擾
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPosition();
	int nPlayerState = 0;
	nPlayerState = pPlayer->GetPlayerState();
	//���W�̎擾
	m_Farstpos = m_apScene2D[TYPE_FARST_BG]->GetPosition();
	m_Secoundpos = m_apScene2D[TYPE_SECOUND_BG]->GetPosition();
	m_Thirdpos = m_apScene2D[TYPE_THIRD_BG]->GetPosition();
	//����
	m_fmove += 0.005f;
	//�x��
	m_fSlowMove += 0.0005f;
	if (m_fFastMove >= 1.0f)
	{
		m_fFastMove = 0.0f;
	}
	if (m_fmove >= 1.0f)
	{
		m_fmove = 0.0f;
	}
	if (m_fSlowMove >= 1.0f)
	{
		m_fSlowMove = 0.0f;
	}
	m_apScene2D[TYPE_FARST_BG]->SetTexture(m_texsizeX, m_texsizeY + +m_fFastMove, 1.0f , 1.0f);
	m_apScene2D[TYPE_SECOUND_BG]->SetTexture(m_texsizeX, m_texsizeY + +m_fmove, 1.0f , 1.0f);
	m_apScene2D[TYPE_THIRD_BG]->SetTexture(m_texsizeX, m_texsizeY + +m_fSlowMove, 1.0f , 1.0f);
	if (nPlayerState == CPlayer::STATE_NORMAL || nPlayerState == CPlayer::STATE_DAMAGE)
	{
		if (PlayerPos.x >= SCREEN_WIDTH / 2 && PlayerPos.x <= 880)
		{
			m_Farstpos.x -= 0.1f;
		}
		if (PlayerPos.x <= SCREEN_WIDTH / 2 && PlayerPos.x >= 400)
		{
			m_Farstpos.x += 0.1f;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_A))
		{
			m_move.x = 2.0f;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_D))
		{
			m_move.x = -2.0f;
		}
		if (pInputKeyboard->GetKeyboardRelease(DIK_A))
		{
			m_move.x = 0.0f;
		}
		if (pInputKeyboard->GetKeyboardRelease(DIK_D))
		{
			m_move.x = 0.0f;
		}
		if (PlayerPos.x >= 880)
		{
			m_move.x = 0.0f;
		}
		if (PlayerPos.x <= 400)
		{
			m_move.x = 0.0f;
		}
	}
	if (nPlayerState == CPlayer::STATE_RESPAWN || nPlayerState == CPlayer::STATE_DEAD)
	{
		m_move.x = 0.0f;
	}
	//�ꖇ�ڂ̔w�i�̈ʒu�X�V
	m_Farstpos.x += m_move.x;
	m_Farstpos.y += m_move.y;
	//�񖇖ڂ̔w�i�̈ʒu�X�V
	m_Secoundpos.x += m_move.x;
	m_Secoundpos.y += m_move.y;
	//�O���ڂ̔w�i�̈ʒu�X�V
	m_Thirdpos.x += m_move.x;
	m_Thirdpos.y += m_move.y;
	//�ʒu�X�V
	m_apScene2D[TYPE_FARST_BG]->SetPosition(m_Farstpos);
	//�ʒu�X�V
	m_apScene2D[TYPE_SECOUND_BG]->SetPosition(m_Secoundpos);
	//�ʒu�X�V
	m_apScene2D[TYPE_THIRD_BG]->SetPosition(m_Thirdpos);
}
//---------------------------------------------------
//�`��
//---------------------------------------------------
void CBg::Draw(void)
{
}
