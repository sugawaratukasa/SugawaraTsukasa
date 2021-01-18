//---------------------------------------------------
// Create
// scene2d.cpp
// Author:	�ǌ��i
//---------------------------------------------------
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "inputkeyboard.h"
//---------------------------------------------------
//�����֐�
//---------------------------------------------------
CScene2d * CScene2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	CScene2d * pScene2d;
	pScene2d = new CScene2d;
	pScene2d->Init(pos, rot, sizeX, sizeY);
	pScene2d->SetPosition(pos);
	return pScene2d;
}
//---------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------
CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nsizeX = 0;
	m_nsizeY = 0;
	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_fTexX = 0.0f;
	m_fTexY = 0.0f;
	m_fTexAnimX = 0.0f;
	m_fTexAnimY = 0;
	m_fScale = 0.0f;
	m_nCount = 0;
}
//---------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------
CScene2d::~CScene2d()
{
}
//---------------------------------------------------
//������
//---------------------------------------------------
HRESULT CScene2d::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//�ʒu���W
	m_pos = pos;
	//�T�C�Y
	m_nsizeX = sizeX;
	m_nsizeY = sizeY;
	m_rot = rot;
	m_fAngle = atan2f((m_nsizeY / 2), (m_nsizeX / 2));
	m_fLength = sqrtf((float)(((m_nsizeX / 2) * (m_nsizeX / 2)) + ((m_nsizeY / 2) * (m_nsizeY / 2))));
	m_fScale = 1.0f;
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//���_����ݒ�
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	//�e�N�X�`��
	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexAnimY);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexAnimY);

	pVtx += 4;
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	CScene::SetPosition(pos);
	return S_OK;
}
//---------------------------------------------------
//�I��
//---------------------------------------------------
void CScene2d::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�����[�X
	Release();
}
//---------------------------------------------------
//�X�V
//---------------------------------------------------
void CScene2d::Update(void)
{ 
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//���_����ݒ�
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexAnimY);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexAnimY);

	pVtx += 4;
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	CScene::SetPosition(m_pos);
}
//---------------------------------------------------
//�`��
//---------------------------------------------------
void CScene2d::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}
//----------------------------------------------------
//�Z�b�g
//----------------------------------------------------
void CScene2d::SetPosition(D3DXVECTOR3 pos)
{
	//���
	m_pos = pos;
}
//----------------------------------------------------
//�e�N�X�`���Z�b�g
//----------------------------------------------------
void CScene2d::SetTexture(float fTexX, float fTexY, float fTexAnimX ,float fTexAnimY)
{
	//���
	m_fTexX = fTexX;
	m_fTexY = fTexY;
	m_fTexAnimX = fTexAnimX;
	m_fTexAnimY = fTexAnimY;
}
//----------------------------------------------------
//RGBA�̃Z�b�g
//----------------------------------------------------
void CScene2d::SetRGBA(D3DXCOLOR col)
{
	m_col = col;
}
//----------------------------------------------------
//�����̐ݒ�
//----------------------------------------------------
void CScene2d::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//----------------------------------------------------
//�g��
//----------------------------------------------------
void CScene2d::SetScale(float fScale)
{
	m_fScale += fScale;
}
//----------------------------------------------------
//�e�N�X�`���̊��蓖��
//----------------------------------------------------
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//���蓖��
	m_pTexture = pTexture;
}
