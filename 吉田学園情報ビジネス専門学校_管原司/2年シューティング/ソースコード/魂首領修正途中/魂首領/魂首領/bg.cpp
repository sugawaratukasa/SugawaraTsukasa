//******************************************************************************
// �w�i [bg.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "bg.h"

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bg2.png", &m_apTexture[TYPE_FARST_BG]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bg101.png", &m_apTexture[TYPE_SECOUND_BG]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bg102.png", &m_apTexture[TYPE_THIRD_BG]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
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

//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBg::CBg(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_type		= TYPE_NONE;
	m_pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_texsizeX	= 0.0f;
	m_texsizeY	= 0.0f;
	m_fFastMove = 0.0f;
	m_fSlowMove = 0.0f;
	m_fmove		= 0.0f;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBg::~CBg()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CBg * CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �|�C���^
	CBg * pBg;

	// �������m��
	pBg = new CBg;

	// �ʒu���W���
	pBg->m_pos = pos;

	// �T�C�Y���
	pBg->m_size = size;

	// ������
	pBg->Init();

	// �|�C���^��Ԃ�
	return pBg;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBg::Init(void)
{
	// �������m��
	m_apScene2D[TYPE_FARST_BG] = new CScene2d;
	m_apScene2D[TYPE_SECOUND_BG] = new CScene2d;
	m_apScene2D[TYPE_THIRD_BG] = new CScene2d;

	// �ʒu���W�ݒ�
	m_apScene2D[TYPE_FARST_BG]->SetPosition(m_pos);
	m_apScene2D[TYPE_SECOUND_BG]->SetPosition(m_pos);
	m_apScene2D[TYPE_THIRD_BG]->SetPosition(m_pos);

	// �ʒu���W�ݒ�
	m_apScene2D[TYPE_FARST_BG]->SetSize(m_size);
	m_apScene2D[TYPE_SECOUND_BG]->SetSize(m_size);
	m_apScene2D[TYPE_THIRD_BG]->SetSize(m_size);

	// �J���[�ݒ�
	m_apScene2D[TYPE_FARST_BG]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_SECOUND_BG]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_THIRD_BG]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �e�N�X�`���̎󂯓n��
	m_apScene2D[TYPE_FARST_BG]->BindTexture(m_apTexture[TYPE_FARST_BG]);
	m_apScene2D[TYPE_SECOUND_BG]->BindTexture(m_apTexture[TYPE_SECOUND_BG]);
	m_apScene2D[TYPE_THIRD_BG]->BindTexture(m_apTexture[TYPE_THIRD_BG]);

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	m_apScene2D[TYPE_FARST_BG]->SetObjType(CScene::OBJTYPE_BG);
	m_apScene2D[TYPE_SECOUND_BG]->SetObjType(CScene::OBJTYPE_BG);
	m_apScene2D[TYPE_THIRD_BG]->SetObjType(CScene::OBJTYPE_BG);

	// ������
	m_apScene2D[TYPE_FARST_BG]->Init();
	m_apScene2D[TYPE_SECOUND_BG]->Init();
	m_apScene2D[TYPE_THIRD_BG]->Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBg::Uninit(void)
{
	//�I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBg::Update(void)
{
	// �X�V
	m_apScene2D[TYPE_FARST_BG]->Update();
	m_apScene2D[TYPE_SECOUND_BG]->Update();
	m_apScene2D[TYPE_THIRD_BG]->Update();

	// ����
	m_fmove += 0.005f;

	// �x��
	m_fSlowMove += 0.0005f;

	// �e�N�X�`���ړ�
	if (m_fFastMove >= 1.0f)
	{
		m_fFastMove = 0.0f;
	}
	// �e�N�X�`���ړ�
	if (m_fmove >= 1.0f)
	{
		m_fmove = 0.0f;
	}
	// �e�N�X�`���ړ�
	if (m_fSlowMove >= 1.0f)
	{
		m_fSlowMove = 0.0f;
	}

	// �e�N�X�`���X�V
	m_apScene2D[TYPE_FARST_BG]->SetTexture(m_texsizeX, m_texsizeY + +m_fFastMove, 1.0f , 1.0f);
	m_apScene2D[TYPE_SECOUND_BG]->SetTexture(m_texsizeX, m_texsizeY + +m_fmove, 1.0f , 1.0f);
	m_apScene2D[TYPE_THIRD_BG]->SetTexture(m_texsizeX, m_texsizeY + +m_fSlowMove, 1.0f , 1.0f);

}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBg::Draw(void)
{
}
