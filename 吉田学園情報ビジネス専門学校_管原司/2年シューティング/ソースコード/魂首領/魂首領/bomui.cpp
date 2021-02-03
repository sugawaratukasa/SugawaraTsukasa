//******************************************************************************
// �{����UI [bomui.cpp]
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
#include "bomui.h"
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CBomUI::m_pTexture = NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBomUI::CBomUI(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nBom_Posession	= 0;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBomUI::~CBomUI()
{
}

//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CBomUI::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bom3.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CBomUI::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}
//******************************************************************************
// �����֐�
//******************************************************************************
CBomUI * CBomUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBomUI�N���X�̃|�C���^
	CBomUI * pBomUI;

	// �������m��
	pBomUI = new CBomUI;

	// �ʒu���W���
	pBomUI->m_pos = pos;

	// �T�C�Y���
	pBomUI->m_size = size;

	// ������
	pBomUI->Init();

	// �|�C���^��Ԃ�
	return pBomUI;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBomUI::Init()
{
	// �ő吔���J��Ԃ�
	for (int nCnt = 0; nCnt < MAX_BOM; nCnt++)
	{
		// �������m��
		m_apScene2D[nCnt] = new CScene2d;

		// �J���[�ݒ�
		m_apScene2D[nCnt]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));

		// �e�N�X�`���󂯓n��
		m_apScene2D[nCnt]->BindTexture(m_pTexture);

		// �ʒu�ݒ�
		m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3((m_pos.x + BOM_UI_SIZE.x * nCnt), m_pos.y, m_pos.z));

		// �T�C�Y�ݒ�
		m_apScene2D[nCnt]->SetSize(m_size);

		// �I�u�W�F�N�g�^�C�v�̐ݒ�
		m_apScene2D[nCnt]->SetObjType(CScene::OBJTYPE_UI);

		// ������
		m_apScene2D[nCnt]->Init();
	}
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBomUI::Uninit(void)
{
	// �I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBomUI::Update(void)
{

}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBomUI::Draw(void)
{
}
//******************************************************************************
// �{���̏������ݒ�
//******************************************************************************
void CBomUI::SetBomUI(int mBomPossesion)
{
	// �{���̏��������擾
	m_nBom_Posession = mBomPossesion;
	
	// ��������5�̏ꍇ
	if (m_nBom_Posession == MAX_BOM)
	{
		for (int nCount = 0; nCount < MAX_BOM; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	// ��������4�̏ꍇ
	if (m_nBom_Posession == 4)
	{
		for (int nCount = 0; nCount < 4; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_apScene2D[4]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	// ��������3�̏ꍇ
	if (m_nBom_Posession == 3)
	{
		for (int nCount = 0; nCount < 3; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_apScene2D[3]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_apScene2D[4]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	// ��������2�̏ꍇ
	if (m_nBom_Posession == 2)
	{
		for (int nCount = 0; nCount < 2; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_apScene2D[2]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_apScene2D[3]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_apScene2D[4]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	// ��������1�̏ꍇ
	if (m_nBom_Posession == 1)
	{
			m_apScene2D[0]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			for (int nCount = 1; nCount < MAX_BOM; nCount++)
			{
				m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
				m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
				m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
				m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
			}
	}
	// ��������0�̏ꍇ
	if (m_nBom_Posession == 0)
	{
		for (int nCount = 0; nCount < MAX_BOM; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		}
	}
}