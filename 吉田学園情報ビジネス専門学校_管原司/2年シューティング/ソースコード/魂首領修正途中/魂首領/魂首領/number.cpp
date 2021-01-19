//******************************************************************************
// �i���o�[���� [number.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �t�@�C���C���N���[�h
//******************************************************************************
#include "main.h"
#include "renderer.h"
#include "number.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumber = 0;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CNumber::~CNumber()
{

}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CNumber::Load(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/number000.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CNumber::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		//�e�N�X�`�������[�X
		m_pTexture->Release();
		//m_pTexture��NULL��
		m_pTexture = NULL;
	}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CNumber�̃|�C���^
	CNumber * pNumber;

	// �������m��
	pNumber = new CNumber;

	// �ʒu���W�ݒ�
	pNumber->SetPosition(pos);

	// �T�C�Y�ݒ�
	pNumber->SetSize(size);

	//������
	pNumber->Init();

	// pNumber��Ԃ�
	return pNumber;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CNumber::Init()
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_size.x/ 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	// rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ� �������̂��
	pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	// �e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(m_nNumber * 0.10f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber * 0.10f + 0.10f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber * 0.10f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber * 0.10f + 0.10f, 1.0f);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}
//******************************************************************************
//�I���֐�
//******************************************************************************
void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		// m_pVtxBuff�����[�X
		m_pVtxBuff->Release();
		// m_pVtxBuff��NULL
		m_pVtxBuff = NULL;
	}
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CNumber::Update(void)
{
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CNumber::Draw(void)
{
	//�����_���[�擾
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
//******************************************************************************
// �i���o�[�ݒ�
//******************************************************************************
void CNumber::SetNumber(int nNumber)
{
	// nNumber���
	m_nNumber = nNumber;

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(m_nNumber * 0.10f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber * 0.10f + 0.10f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber * 0.10f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber * 0.10f + 0.10f, 1.0f);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//******************************************************************************
// �ʒu���W�ݒ�
//******************************************************************************
void CNumber::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// �T�C�Y�ݒ�
//******************************************************************************
void CNumber::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}