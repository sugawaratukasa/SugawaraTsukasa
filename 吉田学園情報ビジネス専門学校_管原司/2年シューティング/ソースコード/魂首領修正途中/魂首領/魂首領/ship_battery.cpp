//******************************************************************************
// �D�̖C�� [ship_battery_enemy.cpp]
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
#include "player.h"
#include "bullet.h"
#include "enemy_traking_bullet.h"
#include "game.h"
#include "ship.h"
#include "ship_battery.h"
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CShip_Battery::CShip_Battery(int nPriority) : CEnemy(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nAttackCount = 0;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CShip_Battery::~CShip_Battery()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CShip_Battery * CShip_Battery::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type)
{
	// CShip_Battery�N���X�̃|�C���^
	CShip_Battery * pShip_Battery;

	// �������m��
	pShip_Battery = new CShip_Battery;

	// �G�̏��ݒ�
	pShip_Battery->SetEnemy(pos, rot, size, nLife, tex_type, CScene::OBJTYPE_ENEMY);

	// �ʒu���W���
	pShip_Battery->m_pos = pos;

	// ������
	pShip_Battery->Init();

	// �|�C���^��Ԃ�
	return pShip_Battery;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CShip_Battery::Init(void)
{
	// ������
	CEnemy::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CShip_Battery::Uninit(void)
{
	// �I��
	CEnemy::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CShip_Battery::Update(void)
{
	// �X�V
	CEnemy::Update();

	// �D�̎擾
	CShip * pShip = CGame::GetShip();

	// �D�̍��W�擾
	D3DXVECTOR3 ShipPos;
	ShipPos = pShip->GetPosition();

	// �ʒu���W�ݒ�
	SetPosition(ShipPos + m_pos);

	// �U������
	Attack();
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CShip_Battery::Draw(void)
{
	// �`��
	CEnemy::Draw();
}
//******************************************************************************
// �U�������֐�
//******************************************************************************
void CShip_Battery::Attack(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();

	// �v���C���[�̍��W�擾
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPosition();

	// �v���C���[�̏��擾
	int nPlayerState = 0;
	nPlayerState = pPlayer->GetPlayerState();

	if (nPlayerState == CPlayer::STATE_NORMAL || nPlayerState == CPlayer::STATE_DAMAGE)
	{
		// �v���C���[�ւ̊p�x
		float fAngle = atan2f(PlayerPos.x - pos.x, PlayerPos.y - pos.y);

		// �e���ւ̔��a
		float fLength = SHIP_BATTERY_SIZE.y / 2;

		// �e����pos
		D3DXVECTOR3 Battery_Muzle_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ����
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f);

		// �U���J�E���g�C���N�������g
		m_nAttackCount++;

		//���W�����߂�
		Battery_Muzle_Pos.x = pos.x - cosf(fAngle + D3DXToRadian(90.0f)) * fLength;
		Battery_Muzle_Pos.y = pos.y + sinf(fAngle + D3DXToRadian(90.0f)) * fLength;

		//rot�Ɋp�x����
		rot.z = fAngle;

		//�����̐ݒ�
		SetRot(rot);

		//�U������
		if (m_nAttackCount % 100 == 0)
		{
			for (int nCount = 0; nCount < 4; nCount++)
			{
				// 4���_�������e����
				CEnemy_Traking_Bullet::Create(D3DXVECTOR3(Battery_Muzle_Pos.x, Battery_Muzle_Pos.y, Battery_Muzle_Pos.z)
					, D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_TRAKING_BULLET_SIZE,
					D3DXVECTOR3(5.0f + nCount, 5.0f + nCount, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);
			}
		}
	}
}