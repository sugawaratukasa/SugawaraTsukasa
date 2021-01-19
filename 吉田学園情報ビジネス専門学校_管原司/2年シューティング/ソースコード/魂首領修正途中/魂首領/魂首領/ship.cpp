//******************************************************************************
// �D [ship.cpp]
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
#include "ship.h"
#include "ship_battery.h"
#include "warning.h"
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CShip::m_pTexture = NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CShip::CShip(int nPriority) : CScene2d(nPriority)
{
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CShip::~CShip()
{
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CShip::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Ship.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CShip::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CShip * CShip::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CShip�N���X�̃|�C���^
	CShip * pShip;

	// �������m��
	pShip = new CShip;

	// �ʒu���W�ݒ�
	pShip->SetPosition(pos);

	// �ʒu���W�ݒ�
	pShip->SetSize(size);

	// �����ݒ�
	pShip->SetRot(D3DXVECTOR3(0.0f,0.0f, D3DXToRadian(180.0f)));

	// �J���[�ݒ�
	pShip->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �e�N�X�`���󂯓n��
	pShip->BindTexture(m_pTexture);

	// �I�u�W�F�N�g�^�C�v�ݒ�
	pShip->SetObjType(OBJTYPE_SHIP);

	// ������
	pShip->Init();

	// �|�C���^��Ԃ�
	return pShip;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CShip::Init(void)
{
	// ������
	CScene2d::Init();

	// �C�䐶��
	CShip_Battery::Create(SHIP_BATTERY_POS1, SHIP_BATTERY_ROT,SHIP_BATTERY_SIZE,SHIP_BATTERY_LIFE,CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS2, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS3, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS4, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS5, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS6, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CShip::Uninit(void)
{
	// �I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CShip::Update(void)
{
	// �X�V
	CScene2d::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ��p�ϐ�
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,1.0f,0.0f);

	// �ړ�
	pos.y += move.y;

	// �ʒu���W�ݒ�
	SetPosition(pos);

	// ��ʊO�ɂł���
	if (pos.y - SHIP_SIZE.y / 2 >= SCREEN_HEIGHT)
	{
		// Warning����
		CWarning::Create(WARNING_POS, WARNING_SIZE);

		// �I��
		Uninit();
		return;
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CShip::Draw(void)
{
	// �`��
	CScene2d::Draw();
}