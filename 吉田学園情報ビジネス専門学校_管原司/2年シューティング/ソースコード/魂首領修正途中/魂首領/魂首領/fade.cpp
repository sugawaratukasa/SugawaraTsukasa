//******************************************************************************
// �t�F�[�h [fade.cpp]
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
#include "fade.h"
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CFade::CFade()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fade = FADE_NONE;
	m_ModeNext = CSceneManager::MODE_NONE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CFade::~CFade()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CFade * CFade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CSceneManager::MODE mode)
{
	// CFade�N���X�̃|�C���^
	CFade * pFade;

	//�������m��
	pFade = new CFade;

	// �ʒu���W���
	pFade->m_pos = pos;

	// �T�C�Y���
	pFade->m_size = size;

	// ���[�h���
	pFade->m_ModeNext = mode;

	//������
	pFade->Init();

	// �|�C���^��Ԃ�
	return pFade;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CFade::Init(void)
{
	// �t�F�[�h�C����Ԃ�
	m_fade = FADE_IN;
	//������
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//���_����ݒ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ� 
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CFade::Uninit(void)
{
	//�I��
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CFade::Update(void)
{
	//���_����ݒ�
	VERTEX_2D *pVtx;
	//���[�h
	m_ModeNext = CSceneManager::GetMode();
	//�X�V
	if (m_fade != FADE_NONE)
	{
		//�t�F�[�h�C��
		if (m_fade == FADE_IN)
		{
			//a�l�����Z
			m_colorFade.a += FADE_RATE;	
			//��ʂ������Ȃ�����
			if (m_colorFade.a >= 1.0f)
			{
				//�J��
				CSceneManager::SetMode(m_ModeNext);
				//�t�F�[�h�I������
				m_colorFade.a = 1.0f;
				m_fade = FADE_OUT;
			}
		}
		//�t�F�[�h�A�E�g
		if (m_fade == FADE_OUT)
		{
			//���l�����Z
			m_colorFade.a -= FADE_RATE;
			//��ʂ̓���
			if (m_colorFade.a <= 0.0f)
			{
				//�t�F�[�h�����؂�ւ�
				m_colorFade.a = 0.0f;
				//���[�h�ݒ�
				m_fade = FADE_IN;
				CSceneManager::StopFade();
			}
		}
		//���_�o�b�t�@�����b�N
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		//���_�J���[�̐ݒ� 
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;
		//���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CFade::Draw(void)
{
	//�`��
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}
