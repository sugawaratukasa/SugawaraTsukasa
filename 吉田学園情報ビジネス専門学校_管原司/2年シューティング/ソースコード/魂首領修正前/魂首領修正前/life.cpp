//---------------------------------------------------
// life
// life.cpp
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
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;
//-----------------------------------------
//�R���X�g���N�^
//-----------------------------------------
CLife::CLife(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumLife = 0;
}
//-----------------------------------------
//�f�X�g���N�^
//-----------------------------------------
CLife::~CLife()
{
}
//-----------------------------------------
//�C���X�^���X����
//-----------------------------------------
CLife * CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayer�N���X�̃|�C���^
	CLife * pLife;
	//�������m��
	pLife = new CLife;
	//������
	pLife->Init(pos, rot, sizeX, sizeY);
	return pLife;
}
//-----------------------------------------
//�e�N�X�`���ǂݍ���
//-----------------------------------------
HRESULT CLife::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/PlayerLife.png", &m_pTexture);
	return S_OK;
}
//-----------------------------------------
//�e�N�X�`���j��
//-----------------------------------------
void CLife::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}
//-----------------------------------------
//������
//-----------------------------------------
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	m_pos = pos;
	m_nNumLife = PLAYER_LIFE;
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2d;
		m_apScene2D[nCnt]->Init(pos, rot, sizeX, sizeY);
		m_apScene2D[nCnt]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[nCnt]->BindTexture(m_pTexture);
		m_apScene2D[nCnt]->SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
		m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3((m_pos.x + 50 * nCnt), m_pos.y, m_pos.z));
		//�I�u�W�F�N�g�^�C�v�̐ݒ�
		m_apScene2D[nCnt]->SetObjType(CScene::OBJTYPE_LIFE);
	}
	return S_OK;
}
//-----------------------------------------
//�I��
//-----------------------------------------
void CLife::Uninit(void)
{
	Release();
}
//-----------------------------------------
//�X�V
//-----------------------------------------
void CLife::Update(void)
{
	SetLife();
}
//-----------------------------------------
//�`��
//-----------------------------------------
void CLife::Draw(void)
{
}
//-----------------------------------------
//���C�t���Z
//-----------------------------------------
void CLife::AddLife(int nLife)
{
	m_nNumLife = nLife;
}
//-----------------------------------------
//���C�t�̌��Z
//-----------------------------------------
void CLife::HitDamage(int Damage)
{
	m_nNumLife -= Damage;
}
//-----------------------------------------
//���C�t�Z�b�g
//-----------------------------------------
void CLife::SetLife(void)
{
	//���C�t��3�̏ꍇ
	if (m_nNumLife == 3)
	{
		m_apScene2D[0]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[1]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[2]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	//���C�t��2�̏ꍇ
	if (m_nNumLife == 2)
	{
		m_apScene2D[2]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	//���C�t��1�̏ꍇ
	if (m_nNumLife == 1)
	{
		m_apScene2D[1]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	//���C�t��0�̏ꍇ
	if (m_nNumLife == 0)
	{
		m_apScene2D[0]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
}
