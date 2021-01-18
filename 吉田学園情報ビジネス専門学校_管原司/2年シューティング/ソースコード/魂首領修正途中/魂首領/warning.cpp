//******************************************************************************
// ���[�j���O [warning.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
// �t�@�C���C���N���[�h
//******************************************************************************
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
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CWarning::m_pTexture = NULL;
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CWarning::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/warning.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CWarning::Unload(void)
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
CWarning::CWarning(int nPriority) : CScene2d(nPriority)
{
	m_bColor		= false;
	m_nWarnigCount	= 0;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CWarning::~CWarning()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CWarning * CWarning::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CWarning�N���X�̃|�C���^
	CWarning * pWarning;

	// �������m��
	pWarning = new CWarning;

	// �ʒu���W�ݒ�
	pWarning->SetPosition(pos);

	// �ʒu���W�ݒ�
	pWarning->SetSize(size);

	// ������
	pWarning->Init();

	// �|�C���^��Ԃ�
	return nullptr;
}

//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CWarning::Init(void)
{
	// �J���[�ݒ�
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �e�N�X�`���󂯓n��
	BindTexture(m_pTexture);

	// ������
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CWarning::Uninit(void)
{
	//�I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CWarning::Update(void)
{
	// �X�V
	CScene2d::Update();

	// �J���[�擾
	D3DXCOLOR col = GetRGBA();

	// false�̏ꍇ
	if (m_bColor == false)
	{
		// ���l���Z
		col.a -= 0.05f;
		// 0.1�ȉ��ɂȂ����ꍇ
		if (col.a <= 0.1f)
		{
			// true�ɂ���
			m_bColor = true;
		}
	}
	// true�̏ꍇ
	else
	{
		// ���l���Z
		col.a += 0.05f;
		// 1.0f�ȏ�̏ꍇ
		if (col.a >= 1.0f)
		{
			// false�ɂ���
			m_bColor = false;
		}
		// �C���N�������g
		m_nWarnigCount++;
	}
	// 50�̏ꍇ
	if (m_nWarnigCount == 50)
	{
		// �{�X�擾
		CBoss *pBoss = CGame::GetBoss();
		// �{�X�X�V�J�n
		pBoss->SetBoss(1);
		//�I��
		Uninit();
		// ���̏�����ʂ�Ȃ��悤��
		return;
	}

	// �J���[�ݒ�
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a));
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CWarning::Draw(void)
{
	// �`��
	CScene2d::Draw();
}