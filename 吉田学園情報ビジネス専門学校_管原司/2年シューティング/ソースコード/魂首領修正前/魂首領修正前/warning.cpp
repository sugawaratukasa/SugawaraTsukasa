//---------------------------------------------------
// Warning
// warning.cpp
// Author:	�ǌ��i
//---------------------------------------------------
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
#include "sound.h"
#include "life.h"
#include "game.h"
#include "explosion.h"
#include "bomui.h"
#include "continue.h"
#include "score.h"
#include "boss.h"
#include "enemy.h"
#include "warning.h"
LPDIRECT3DTEXTURE9 CWarning::m_pTexture = NULL;
//------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------
CWarning::CWarning(int nPriority) : CScene2d(nPriority)
{
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_bColor = false;
	m_nWarnigCount = 0;
}
//------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------
CWarning::~CWarning()
{
}
//------------------------------------------------
//�����֐�
//------------------------------------------------
CWarning * CWarning::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CWarning�N���X�̃|�C���^
	CWarning * pWarning;
	//�������m��
	pWarning = new CWarning;
	//������
	pWarning->Init(pos, rot, sizeX, sizeY);
	return nullptr;
}
//------------------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------------------
HRESULT CWarning::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/warning.png", &m_pTexture);
	return S_OK;
}
//------------------------------------------------
//�e�N�X�`���j��
//------------------------------------------------
void CWarning::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//------------------------------------------------
//�������֐�
//------------------------------------------------
HRESULT CWarning::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//������
	CScene2d::Init(pos, rot, sizeX, sizeY);
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(m_pTexture);
	SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	return S_OK;
}
//------------------------------------------------
//�I���֐�
//------------------------------------------------
void CWarning::Uninit(void)
{
	//�I��
	CScene2d::Uninit();
}
//------------------------------------------------
//�X�V�֐�
//------------------------------------------------
void CWarning::Update(void)
{
	//�X�V
	CScene2d::Update();
	//false�̏ꍇ
	if (m_bColor == false)
	{
		m_color.a -= 0.05f;
		if (m_color.a <= 0.1f)
		{
			m_bColor = true;
		}
	}
	//true�̏ꍇ
	else
	{
		m_color.a += 0.05f;
		if (m_color.a >= 1.0f)
		{
			m_bColor = false;
		}
		m_nWarnigCount++;
	}
	if (m_nWarnigCount == 50)
	{
		//�{�X�擾
		CBoss *pBoss = CGame::GetBoss();
		pBoss->SetBoss(1);
		//�I��
		Uninit();
		//���̏�����ʂ�Ȃ��悤��
		return;
	}
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_color.a));
}
//------------------------------------------------
//�`��֐�
//------------------------------------------------
void CWarning::Draw(void)
{
	//�`��
	CScene2d::Draw();
}