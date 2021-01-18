//---------------------------------------------------
// bom
// bom.cpp
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
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "bomui.h"
LPDIRECT3DTEXTURE9 CBom::m_pTexture = NULL;
//-----------------------------------------
//�R���X�g���N�^
//-----------------------------------------
CBom::CBom(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nBom_Posession = 0;
}
//-----------------------------------------
//�f�X�g���N�^
//-----------------------------------------
CBom::~CBom()
{
}
//-----------------------------------------
//�C���X�^���X����
//-----------------------------------------
CBom * CBom::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayer�N���X�̃|�C���^
	CBom * pBom;
	//�������m��
	pBom = new CBom;
	//������
	pBom->Init(pos, rot, sizeX, sizeY);
	return pBom;
}
//-----------------------------------------
//�e�N�X�`���ǂݍ���
//-----------------------------------------
HRESULT CBom::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bom3.png", &m_pTexture);
	return S_OK;
}
//-----------------------------------------
//�e�N�X�`���j��
//-----------------------------------------
void CBom::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}
//-----------------------------------------
//������
//-----------------------------------------
HRESULT CBom::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	m_pos = pos;
	m_nBom_Posession = MAX_BOM;
	for (int nCnt = 0; nCnt < MAX_BOM; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2d;
		m_apScene2D[nCnt]->Init(pos, rot, sizeX, sizeY);
		m_apScene2D[nCnt]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_apScene2D[nCnt]->BindTexture(m_pTexture);
		m_apScene2D[nCnt]->SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
		m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3((m_pos.x + 40 * nCnt), m_pos.y, m_pos.z));
		//�I�u�W�F�N�g�^�C�v�̐ݒ�
		m_apScene2D[nCnt]->SetObjType(CScene::OBJTYPE_LIFE);
	}
	return S_OK;
}
//-----------------------------------------
//�I��
//-----------------------------------------
void CBom::Uninit(void)
{
	Release();
}
//-----------------------------------------
//�X�V
//-----------------------------------------
void CBom::Update(void)
{

}
//-----------------------------------------
//�`��
//-----------------------------------------
void CBom::Draw(void)
{
}
//-----------------------------------------
//�{���̃Z�b�g
//-----------------------------------------
void CBom::SetBomUI(int mBomPossesion)
{
	//�{���̏��������擾
	m_nBom_Posession = mBomPossesion;
	
	if (m_nBom_Posession == MAX_BOM)
	{
		for (int nCount = 0; nCount < MAX_BOM; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	if (m_nBom_Posession == 4)
	{
		for (int nCount = 0; nCount < 4; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_apScene2D[4]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	if (m_nBom_Posession == 3)
	{
		for (int nCount = 0; nCount < 3; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_apScene2D[3]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_apScene2D[4]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
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
	if (m_nBom_Posession == 0)
	{
		for (int nCount = 0; nCount < MAX_BOM; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		}
	}
}