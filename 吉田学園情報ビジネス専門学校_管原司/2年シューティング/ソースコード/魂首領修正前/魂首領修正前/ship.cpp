#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "sound.h"
#include "ship.h"
#include "player.h"
#include "game.h"
#include "bullet.h"
#include "explosion.h"
#include "boss.h"
#include "warning.h"
//-------------------------------------------------
//�ÓI�����o�ϐ�
//-------------------------------------------------
LPDIRECT3DTEXTURE9 CShip::m_apTexture[MAX_SHIP_TEX] = {};
//------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------
CShip::CShip(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_Ship_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Wepon1_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Wepon2_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Wepon3_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Wepon4_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Wepon5_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Wepon6_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Wepon1_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Wepon2_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Wepon3_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Wepon4_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Wepon5_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Wepon6_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Type = TYPE_NONE;
	m_fWepon1Angle = 0.0f;
	m_fWepon2Angle = 0.0f;
	m_fWepon3Angle = 0.0f;
	m_fWepon4Angle = 0.0f;
	m_fWepon5Angle = 0.0f;
	m_fWepon6Angle = 0.0f;
	m_fLength = 0.0f;
	m_nWeponAttackCount = 0;
	m_nWepon1_Life = 0;
	m_nWepon2_Life = 0;
	m_nWepon3_Life = 0;
	m_nWepon4_Life = 0;
	m_nWepon5_Life = 0;
	m_nWepon6_Life = 0;
	m_Wepon1State = STATE_NONE;
	m_Wepon2State = STATE_NONE;
	m_Wepon3State = STATE_NONE;
	m_Wepon4State = STATE_NONE;
	m_Wepon5State = STATE_NONE;
	m_Wepon6State = STATE_NONE;
	m_nWepon1_DamageCount = 0;
	m_nWepon2_DamageCount = 0;
	m_nWepon3_DamageCount = 0;
	m_nWepon4_DamageCount = 0;
	m_nWepon5_DamageCount = 0;
	m_nWepon6_DamageCount = 0;
	m_nShipCount = 0;
	m_fAddPosX = 0.0f;
}

//------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------
CShip::~CShip()
{
}

//------------------------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------------------------
HRESULT CShip::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,"data/Texture/Ship.png", &m_apTexture[TEX_TYPE_SHIP]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Wepon1.png", &m_apTexture[TEX_TYPE_WEPON1]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Wepon2.png", &m_apTexture[TEX_TYPE_WEPON2]);
	return S_OK;
}

//------------------------------------------------------
//�e�N�X�`���j��
//------------------------------------------------------
void CShip::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_SHIP_TEX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//------------------------------------------------------
//����
//------------------------------------------------------
CShip * CShip::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CShip�N���X�̃|�C���^
	CShip * pShip;
	//�������m��
	pShip = new CShip;
	//������
	pShip->Init(pos, rot, sizeX, sizeY);
	return pShip;
}

//------------------------------------------------------
//������
//------------------------------------------------------
HRESULT CShip::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	m_Ship_pos = pos;
	//�������m��
	m_apScene2D[TYPE_SHIP] = new CScene2d;
	m_apScene2D[TYPE_WEPON1] = new CScene2d;
	m_apScene2D[TYPE_WEPON2] = new CScene2d;
	m_apScene2D[TYPE_WEPON3] = new CScene2d;
	m_apScene2D[TYPE_WEPON4] = new CScene2d;
	m_apScene2D[TYPE_WEPON5] = new CScene2d;
	m_apScene2D[TYPE_WEPON6] = new CScene2d;
	//RGBA�̐ݒ�
	m_apScene2D[TYPE_SHIP]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_WEPON1]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_WEPON2]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_WEPON3]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_WEPON4]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_WEPON5]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_WEPON6]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//�e�N�X�`���̎󂯓n��
	m_apScene2D[TYPE_SHIP]->BindTexture(m_apTexture[TEX_TYPE_SHIP]);
	m_apScene2D[TYPE_WEPON1]->BindTexture(m_apTexture[TEX_TYPE_WEPON1]);
	m_apScene2D[TYPE_WEPON2]->BindTexture(m_apTexture[TEX_TYPE_WEPON1]);
	m_apScene2D[TYPE_WEPON3]->BindTexture(m_apTexture[TEX_TYPE_WEPON2]);
	m_apScene2D[TYPE_WEPON4]->BindTexture(m_apTexture[TEX_TYPE_WEPON2]);
	m_apScene2D[TYPE_WEPON5]->BindTexture(m_apTexture[TEX_TYPE_WEPON2]);
	m_apScene2D[TYPE_WEPON6]->BindTexture(m_apTexture[TEX_TYPE_WEPON2]);
	//������
	m_apScene2D[TYPE_SHIP]->Init(pos, rot, sizeX, sizeY);
	m_apScene2D[TYPE_WEPON1]->Init(D3DXVECTOR3(m_Ship_pos.x + 150, m_Ship_pos.y + 400, m_Ship_pos.z), D3DXVECTOR3(0.0f, 0.0f,0.0f), SHIP_WEPON_SIZE_X, SHIP_WEPON_SIZE_Y);
	m_apScene2D[TYPE_WEPON2]->Init(D3DXVECTOR3(m_Ship_pos.x - 150, m_Ship_pos.y + 400, m_Ship_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SHIP_WEPON_SIZE_X, SHIP_WEPON_SIZE_Y);
	m_apScene2D[TYPE_WEPON3]->Init(D3DXVECTOR3(m_Ship_pos.x + 280, m_Ship_pos.y - 20, m_Ship_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SHIP_WEPON_SIZE_X, SHIP_WEPON_SIZE_Y);
	m_apScene2D[TYPE_WEPON4]->Init(D3DXVECTOR3(m_Ship_pos.x - 280, m_Ship_pos.y - 20, m_Ship_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SHIP_WEPON_SIZE_X, SHIP_WEPON_SIZE_Y);
	m_apScene2D[TYPE_WEPON5]->Init(D3DXVECTOR3(m_Ship_pos.x - 280, m_Ship_pos.y - 550, m_Ship_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SHIP_WEPON_SIZE_X, SHIP_WEPON_SIZE_Y);
	m_apScene2D[TYPE_WEPON6]->Init(D3DXVECTOR3(m_Ship_pos.x + 280, m_Ship_pos.y - 550, m_Ship_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SHIP_WEPON_SIZE_X, SHIP_WEPON_SIZE_Y);
	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	m_apScene2D[TYPE_SHIP]->SetObjType(OBJTYPE_SHIP);
	m_apScene2D[TYPE_WEPON1]->SetObjType(OBJTYPE_SHIP_WEPON1);
	m_apScene2D[TYPE_WEPON2]->SetObjType(OBJTYPE_SHIP_WEPON2);
	m_apScene2D[TYPE_WEPON3]->SetObjType(OBJTYPE_SHIP_WEPON3);
	m_apScene2D[TYPE_WEPON4]->SetObjType(OBJTYPE_SHIP_WEPON4);
	m_apScene2D[TYPE_WEPON5]->SetObjType(OBJTYPE_SHIP_WEPON5);
	m_apScene2D[TYPE_WEPON6]->SetObjType(OBJTYPE_SHIP_WEPON6);

	//�e�N�X�`���̃Z�b�g
	m_apScene2D[TYPE_SHIP]->SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
	m_apScene2D[TYPE_WEPON1]->SetTexture(0.0f, 0.0f, 1.0f,1.0f);
	m_apScene2D[TYPE_WEPON2]->SetTexture(0.0f, 0.0f, 1.0f,1.0f);
	m_apScene2D[TYPE_WEPON3]->SetTexture(0.0f, 0.0f, 1.0f,1.0f);
	m_apScene2D[TYPE_WEPON4]->SetTexture(0.0f, 0.0f, 1.0f,1.0f);
	m_apScene2D[TYPE_WEPON5]->SetTexture(0.0f, 0.0f, 1.0f,1.0f);
	m_apScene2D[TYPE_WEPON6]->SetTexture(0.0f, 0.0f, 1.0f,1.0f);

	//���C�t�ݒ�
	m_nWepon1_Life = 80;
	m_nWepon2_Life = 80;
	m_nWepon3_Life = 80;
	m_nWepon4_Life = 80;
	m_nWepon5_Life = 80;
	m_nWepon6_Life = 80;

	//State
	m_Wepon1State = STATE_NORMAL;
	m_Wepon2State = STATE_NORMAL;
	m_Wepon3State = STATE_NORMAL;
	m_Wepon4State = STATE_NORMAL;
	m_Wepon5State = STATE_NORMAL;
	m_Wepon6State = STATE_NORMAL;

	return S_OK;
}

//------------------------------------------------------
//�I��
//------------------------------------------------------
void CShip::Uninit(void)
{
	//�I��
	Release();
}

//------------------------------------------------------
//�X�V
//------------------------------------------------------
void CShip::Update(void)
{
	if (m_nShipCount == 1)
	{
		//�X�V
		m_apScene2D[TYPE_SHIP]->Update();
		m_apScene2D[TYPE_WEPON1]->Update();
		m_apScene2D[TYPE_WEPON2]->Update();
		m_apScene2D[TYPE_WEPON3]->Update();
		m_apScene2D[TYPE_WEPON4]->Update();
		m_apScene2D[TYPE_WEPON5]->Update();
		m_apScene2D[TYPE_WEPON6]->Update();
		//�L�[�{�[�h�擾
		CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();

		//�R���g���[���[�擾
		DIJOYSTATE js;
		CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
		LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

		//�T�E���h�擾
		CSound * pSound = CSceneManager::GetSound();

		//�ʒu���W�̎擾
		m_Wepon1_pos = m_apScene2D[TYPE_WEPON1]->GetPosition();
		m_Wepon2_pos = m_apScene2D[TYPE_WEPON2]->GetPosition();
		m_Wepon3_pos = m_apScene2D[TYPE_WEPON3]->GetPosition();
		m_Wepon4_pos = m_apScene2D[TYPE_WEPON4]->GetPosition();
		m_Wepon5_pos = m_apScene2D[TYPE_WEPON5]->GetPosition();
		m_Wepon6_pos = m_apScene2D[TYPE_WEPON6]->GetPosition();

		//�ʒu���W�̐ݒ�
		m_apScene2D[TYPE_WEPON1]->SetPosition(D3DXVECTOR3(m_Ship_pos.x + 150, m_Ship_pos.y + 400, m_Ship_pos.z));
		m_apScene2D[TYPE_WEPON2]->SetPosition(D3DXVECTOR3(m_Ship_pos.x - 150, m_Ship_pos.y + 400, m_Ship_pos.z));
		m_apScene2D[TYPE_WEPON3]->SetPosition(D3DXVECTOR3(m_Ship_pos.x + 280, m_Ship_pos.y - 20, m_Ship_pos.z));
		m_apScene2D[TYPE_WEPON4]->SetPosition(D3DXVECTOR3(m_Ship_pos.x - 280, m_Ship_pos.y - 20, m_Ship_pos.z));
		m_apScene2D[TYPE_WEPON5]->SetPosition(D3DXVECTOR3(m_Ship_pos.x - 280, m_Ship_pos.y - 550, m_Ship_pos.z));
		m_apScene2D[TYPE_WEPON6]->SetPosition(D3DXVECTOR3(m_Ship_pos.x + 280, m_Ship_pos.y - 550, m_Ship_pos.z));

		//�v���C���[�̎擾
		CPlayer * pPlayer = CGame::GetPlayer();

		//�v���C���[�̍��W�擾
		D3DXVECTOR3 PlayerPos;
		PlayerPos = pPlayer->GetPosition();
		int nPlayerState = 0;
		nPlayerState = pPlayer->GetPlayerState();
		
		if (nPlayerState == CPlayer::STATE_NORMAL || nPlayerState == CPlayer::STATE_DAMAGE)
		{
			//�U���J�E���g�C���N�������g
			m_nWeponAttackCount++;
			//wepon1
			//�v���C���[�ւ̊p�x
			m_fWepon1Angle = atan2f(PlayerPos.x - m_Wepon1_pos.x, PlayerPos.y - m_Wepon1_pos.y);
			//�e���ւ̔��a
			m_fLength = 100.0f;
			//�e����pos
			D3DXVECTOR3 m_Wepon1_Bullet_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//���W�����߂�
			m_Wepon1_Bullet_pos.x = m_Wepon1_pos.x - cosf(m_fWepon1Angle + D3DXToRadian(90.0f)) * m_fLength;
			m_Wepon1_Bullet_pos.y = m_Wepon1_pos.y + sinf(m_fWepon1Angle + D3DXToRadian(90.0f)) * m_fLength;

			//rot�Ɋp�x����
			m_Wepon1_rot.z = m_fWepon1Angle;

			//�����̐ݒ�
			m_apScene2D[TYPE_WEPON1]->SetRot(m_Wepon1_rot);

			//�U������
			if (m_nWeponAttackCount % 100 == 0)
			{
				for (int nCount = 0; nCount < 4; nCount++)
				{
					CBullet::Create((m_Wepon1_Bullet_pos), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(4.0f + nCount, 4.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
			}

			//wepon2

			//�v���C���[�ւ̊p�x
			m_fWepon2Angle = atan2f(PlayerPos.x - m_Wepon2_pos.x, PlayerPos.y - m_Wepon2_pos.y);

			//rot�Ɋp�x����
			m_Wepon2_rot.z = m_fWepon2Angle;

			//�����̐ݒ�
			m_apScene2D[TYPE_WEPON2]->SetRot(m_Wepon2_rot);

			//�e����pos
			D3DXVECTOR3 m_Wepon2_Bullet_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//���W�����߂�
			m_Wepon2_Bullet_pos.x = m_Wepon2_pos.x - cosf(m_fWepon2Angle + D3DXToRadian(90.0f)) * m_fLength;
			m_Wepon2_Bullet_pos.y = m_Wepon2_pos.y + sinf(m_fWepon2Angle + D3DXToRadian(90.0f)) * m_fLength;

			//�U������
			if (m_nWeponAttackCount % 100 == 0)
			{
				for (int nCount = 0; nCount < 4; nCount++)
				{
					CBullet::Create(m_Wepon2_Bullet_pos, D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(4.0f + nCount, 4.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
			}



			//wepon3
			//�v���C���[�ւ̊p�x
			m_fWepon3Angle = atan2f(PlayerPos.x - m_Wepon3_pos.x, PlayerPos.y - m_Wepon3_pos.y);

			//rot�Ɋp�x����
			m_Wepon3_rot.z = m_fWepon3Angle;

			//�����̐ݒ�
			m_apScene2D[TYPE_WEPON3]->SetRot(m_Wepon3_rot);
			//�e����pos
			D3DXVECTOR3 m_Wepon3_Bullet_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//���W�����߂�
			m_Wepon3_Bullet_pos.x = m_Wepon3_pos.x - cosf(m_fWepon3Angle + D3DXToRadian(90.0f)) * m_fLength;
			m_Wepon3_Bullet_pos.y = m_Wepon3_pos.y + sinf(m_fWepon3Angle + D3DXToRadian(90.0f)) * m_fLength;

			//�U������
			if (m_nWeponAttackCount % 100 == 0)
			{
				for (int nCount = 0; nCount < 4; nCount++)
				{
					CBullet::Create(D3DXVECTOR3(m_Wepon3_Bullet_pos.x + 20, m_Wepon3_Bullet_pos.y, m_Wepon3_Bullet_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(4.0f + nCount, 4.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
					CBullet::Create(D3DXVECTOR3(m_Wepon3_Bullet_pos.x - 20, m_Wepon3_Bullet_pos.y, m_Wepon3_Bullet_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(4.0f + nCount, 4.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
			}

			//wepon4

			//�v���C���[�ւ̊p�x
			m_fWepon4Angle = atan2f(PlayerPos.x - m_Wepon4_pos.x, PlayerPos.y - m_Wepon4_pos.y);

			//rot�Ɋp�x����
			m_Wepon4_rot.z = m_fWepon4Angle;

			//�����̐ݒ�
			m_apScene2D[TYPE_WEPON4]->SetRot(m_Wepon4_rot);
			//�e����pos
			D3DXVECTOR3 m_Wepon4_Bullet_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//���W�����߂�
			m_Wepon4_Bullet_pos.x = m_Wepon4_pos.x - cosf(m_fWepon4Angle + D3DXToRadian(90.0f)) * m_fLength;
			m_Wepon4_Bullet_pos.y = m_Wepon4_pos.y + sinf(m_fWepon4Angle + D3DXToRadian(90.0f)) * m_fLength;

			//�U������
			if (m_nWeponAttackCount % 100 == 0)
			{
				for (int nCount = 0; nCount < 4; nCount++)
				{
					CBullet::Create(D3DXVECTOR3(m_Wepon4_Bullet_pos.x + 20, m_Wepon4_Bullet_pos.y, m_Wepon4_Bullet_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(4.0f + nCount, 4.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
					CBullet::Create(D3DXVECTOR3(m_Wepon4_Bullet_pos.x - 20, m_Wepon4_Bullet_pos.y, m_Wepon4_Bullet_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(4.0f + nCount, 4.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
			}
			//wepon5

			//�v���C���[�ւ̊p�x
			m_fWepon5Angle = atan2f(PlayerPos.x - m_Wepon5_pos.x, PlayerPos.y - m_Wepon5_pos.y);

			//rot�Ɋp�x����
			m_Wepon5_rot.z = m_fWepon5Angle;

			//�����̐ݒ�
			m_apScene2D[TYPE_WEPON5]->SetRot(m_Wepon5_rot);
			//�e����pos
			D3DXVECTOR3 m_Wepon5_Bullet_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//���W�����߂�
			m_Wepon5_Bullet_pos.x = m_Wepon5_pos.x - cosf(m_fWepon5Angle + D3DXToRadian(90.0f)) * m_fLength;
			m_Wepon5_Bullet_pos.y = m_Wepon5_pos.y + sinf(m_fWepon5Angle + D3DXToRadian(90.0f)) * m_fLength;

			//�U������
			if (m_nWeponAttackCount % 100 == 0)
			{
				for (int nCount = 0; nCount < 4; nCount++)
				{
					CBullet::Create(D3DXVECTOR3(m_Wepon5_Bullet_pos.x + 20, m_Wepon5_Bullet_pos.y, m_Wepon5_Bullet_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(4.0f + nCount, 4.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
					CBullet::Create(D3DXVECTOR3(m_Wepon5_Bullet_pos.x - 20, m_Wepon5_Bullet_pos.y, m_Wepon5_Bullet_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(4.0f + nCount, 4.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
			}
			//wepon6

			//�v���C���[�ւ̊p�x
			m_fWepon6Angle = atan2f(PlayerPos.x - m_Wepon6_pos.x, PlayerPos.y - m_Wepon6_pos.y);

			//rot�Ɋp�x����
			m_Wepon6_rot.z = m_fWepon6Angle;

			//�����̐ݒ�
			m_apScene2D[TYPE_WEPON6]->SetRot(m_Wepon6_rot);
			//�e����pos
			D3DXVECTOR3 m_Wepon6_Bullet_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//���W�����߂�
			m_Wepon6_Bullet_pos.x = m_Wepon6_pos.x - cosf(m_fWepon6Angle + D3DXToRadian(90.0f)) * m_fLength;
			m_Wepon6_Bullet_pos.y = m_Wepon6_pos.y + sinf(m_fWepon6Angle + D3DXToRadian(90.0f)) * m_fLength;

			//�U������
			if (m_nWeponAttackCount % 100 == 0)
			{
				for (int nCount = 0; nCount < 4; nCount++)
				{
					CBullet::Create(D3DXVECTOR3(m_Wepon6_Bullet_pos.x + 20, m_Wepon6_Bullet_pos.y, m_Wepon6_Bullet_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(4.0f + nCount, 4.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
					CBullet::Create(D3DXVECTOR3(m_Wepon6_Bullet_pos.x - 20, m_Wepon6_Bullet_pos.y, m_Wepon6_Bullet_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(4.0f + nCount, 4.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
			}
			//STATE_NORMAL�̏ꍇ
			if (m_Wepon1State == STATE_NORMAL)
			{
				m_apScene2D[TYPE_WEPON1]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			//Wepon2
			if (m_Wepon2State == STATE_NORMAL)
			{
				m_apScene2D[TYPE_WEPON2]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			//Wepon3
			if (m_Wepon3State == STATE_NORMAL)
			{
				m_apScene2D[TYPE_WEPON3]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			//Wepon4
			if (m_Wepon4State == STATE_NORMAL)
			{
				m_apScene2D[TYPE_WEPON4]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			//Wepon5
			if (m_Wepon5State == STATE_NORMAL)
			{
				m_apScene2D[TYPE_WEPON5]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			//Wepon6
			if (m_Wepon6State == STATE_NORMAL)
			{
				m_apScene2D[TYPE_WEPON6]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			//state��DAMAGE�̏ꍇ
			//Wepon1
			if (m_Wepon1State == STATE_DAMAGE)
			{
				m_nWepon1_DamageCount++;
				if (m_nWepon1_DamageCount % 2 == 0)
				{
					m_apScene2D[TYPE_WEPON1]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
				}
				if (m_nWepon1_DamageCount % 3 == 0)
				{
					m_apScene2D[TYPE_WEPON1]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				if (m_nWepon1_DamageCount == 10)
				{
					m_Wepon1State = STATE_NORMAL;
					m_nWepon1_DamageCount = 0;
				}
			}
			//Wepon2
			if (m_Wepon2State == STATE_DAMAGE)
			{
				m_nWepon2_DamageCount++;
				if (m_nWepon2_DamageCount % 1 == 0)
				{
					m_apScene2D[TYPE_WEPON2]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
				}
				if (m_nWepon2_DamageCount % 2 == 0)
				{
					m_apScene2D[TYPE_WEPON2]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				if (m_nWepon2_DamageCount == 10)
				{
					m_Wepon2State = STATE_NORMAL;
					m_nWepon2_DamageCount = 0;
				}
			}
			//Wepon3
			if (m_Wepon3State == STATE_DAMAGE)
			{
				m_nWepon3_DamageCount++;
				if (m_nWepon3_DamageCount % 1 == 0)
				{
					m_apScene2D[TYPE_WEPON3]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
				}
				if (m_nWepon3_DamageCount % 2 == 0)
				{
					m_apScene2D[TYPE_WEPON3]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				if (m_nWepon3_DamageCount == 10)
				{
					m_Wepon3State = STATE_NORMAL;
					m_nWepon3_DamageCount = 0;
				}
			}
			//Wepon4
			if (m_Wepon4State == STATE_DAMAGE)
			{
				m_nWepon4_DamageCount++;
				if (m_nWepon4_DamageCount % 1 == 0)
				{
					m_apScene2D[TYPE_WEPON4]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
				}
				if (m_nWepon4_DamageCount % 2 == 0)
				{
					m_apScene2D[TYPE_WEPON4]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				if (m_nWepon4_DamageCount == 10)
				{
					m_Wepon4State = STATE_NORMAL;
					m_nWepon4_DamageCount = 0;
				}
			}
			//Wepon5
			if (m_Wepon5State == STATE_DAMAGE)
			{
				m_nWepon5_DamageCount++;
				if (m_nWepon5_DamageCount % 1 == 0)
				{
					m_apScene2D[TYPE_WEPON5]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
				}
				if (m_nWepon5_DamageCount % 2 == 0)
				{
					m_apScene2D[TYPE_WEPON5]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				if (m_nWepon5_DamageCount == 10)
				{
					m_Wepon5State = STATE_NORMAL;
					m_nWepon5_DamageCount = 0;
				}
			}
			//Wepon6
			if (m_Wepon6State == STATE_DAMAGE)
			{
				m_nWepon6_DamageCount++;
				if (m_nWepon6_DamageCount % 1 == 0)
				{
					m_apScene2D[TYPE_WEPON6]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
				}
				if (m_nWepon6_DamageCount % 2 == 0)
				{
					m_apScene2D[TYPE_WEPON6]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				if (m_nWepon6_DamageCount == 10)
				{
					m_Wepon6State = STATE_NORMAL;
					m_nWepon6_DamageCount = 0;
				}
			}
			if (PlayerPos.x >= SCREEN_WIDTH / 2 && PlayerPos.x <= 880)
			{
				m_Ship_pos.x -= 0.1f;
			}
			if (PlayerPos.x <= SCREEN_WIDTH / 2 && PlayerPos.x >= 400)
			{
				m_Ship_pos.x += 0.1f;
			}
			//�X�N���[��
			if (pInputKeyboard->GetKeyboardPress(DIK_A))
			{
				m_Ship_pos.x += 2.0f;
			}
			if ( pInputKeyboard->GetKeyboardPress(DIK_D))
			{
				m_Ship_pos.x -= 2.0f;
			}
			if (PlayerPos.x < 400 && pInputKeyboard->GetKeyboardPress(DIK_A))
			{
				m_Ship_pos.x -= 2.0f;
			}
			if (PlayerPos.x > 880 && pInputKeyboard->GetKeyboardPress(DIK_D))
			{
				m_Ship_pos.x += 2.0f;
			}
			//���Ɉړ�
			m_move.y = 1.0f;
			//pos�ɉ��Z
			m_Ship_pos.x += m_move.x;
			m_Ship_pos.y += m_move.y;
			//�ʒu�X�V
			m_apScene2D[TYPE_SHIP]->SetPosition(m_Ship_pos);
		}
		//���C�t��0�ɂȂ����ꍇ
		if (m_nWepon1_Life <= 0)
		{
			//���j����
			CExplosion::Create(m_Wepon1_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SHIP_WEPON_SIZE_X, SHIP_WEPON_SIZE_Y);
			m_apScene2D[TYPE_WEPON1]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		if (m_nWepon2_Life <= 0)
		{
			//���j����
			CExplosion::Create(m_Wepon2_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SHIP_WEPON_SIZE_X, SHIP_WEPON_SIZE_Y);
			m_apScene2D[TYPE_WEPON2]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		if (m_nWepon3_Life <= 0)
		{
			//���j����
			CExplosion::Create(m_Wepon3_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SHIP_WEPON_SIZE_X, SHIP_WEPON_SIZE_Y);
			m_apScene2D[TYPE_WEPON3]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		if (m_nWepon4_Life <= 0)
		{
			//���j����
			CExplosion::Create(m_Wepon4_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SHIP_WEPON_SIZE_X, SHIP_WEPON_SIZE_Y);
			m_apScene2D[TYPE_WEPON4]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		if (m_nWepon5_Life <= 0)
		{
			//���j����
			CExplosion::Create(m_Wepon5_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SHIP_WEPON_SIZE_X, SHIP_WEPON_SIZE_Y);
			m_apScene2D[TYPE_WEPON5]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		if (m_nWepon6_Life <= 0)
		{
			//���j����
			CExplosion::Create(m_Wepon6_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SHIP_WEPON_SIZE_X, SHIP_WEPON_SIZE_Y);
			m_apScene2D[TYPE_WEPON6]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		if (m_Ship_pos.y - SHIP_SIZE_Y / 2 >= SCREEN_HEIGHT)
		{
			//Warning
			CWarning::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WARNING_SIZE_X, WARNING_SIZE_Y);
			Uninit();
			return;
		}
	}
}
//------------------------------------------------------
//�`��
//------------------------------------------------------
void CShip::Draw(void)
{
}
//------------------------------------------------------
//Wepon1Life���Z����
//------------------------------------------------------
void CShip::HitWepon1(int nLife)
{
	m_nWepon1_Life -= nLife;
	m_Wepon1State = STATE_DAMAGE;
}
//------------------------------------------------------
//Wepon2Life���Z����
//------------------------------------------------------
void CShip::HitWepon2(int nLife)
{
	m_nWepon2_Life -= nLife;
	m_Wepon2State = STATE_DAMAGE;
}
//------------------------------------------------------
//Wepon3Life���Z����
//------------------------------------------------------
void CShip::HitWepon3(int nLife)
{
	m_nWepon3_Life -= nLife;
	m_Wepon3State = STATE_DAMAGE;
}
//------------------------------------------------------
//Wepon4Life���Z����
//------------------------------------------------------
void CShip::HitWepon4(int nLife)
{
	m_nWepon4_Life -= nLife;
	m_Wepon4State = STATE_DAMAGE;
}
//------------------------------------------------------
//Wepon5Life���Z����
//------------------------------------------------------
void CShip::HitWepon5(int nLife)
{
	m_nWepon5_Life -= nLife;
	m_Wepon5State = STATE_DAMAGE;
}
//------------------------------------------------------
//Wepon6Life���Z����
//------------------------------------------------------
void CShip::HitWepon6(int nLife)
{
	m_nWepon6_Life -= nLife;
	m_Wepon6State = STATE_DAMAGE;
}
//------------------------------------------------------
//�J�E���g�Z�b�g
//------------------------------------------------------
void CShip::SetShip(int nShip)
{
	//���
	m_nShipCount = nShip;
}
