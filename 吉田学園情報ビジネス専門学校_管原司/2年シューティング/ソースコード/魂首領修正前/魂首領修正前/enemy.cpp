//---------------------------------------
//
//	enemy
//	enemy.cpp
//	Author �ǌ��i
//
//---------------------------------------
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
#include "enemy.h"
#include "game.h"
#include "item.h"
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[MAX_ENEMY_TEX] = {};
//-------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------
CEnemy::CEnemy(int nPriority) : CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nAttackCount = 0;
	m_Type = TYPE_NONE;
	m_TexType = TEX_TYPE_NONE;
	m_state = STATE_NONE;
	m_nLife = 0;
	m_nBossAttackCount = 0;
	m_nDamageCount = 0;
	m_nCircleCount = 0;
	m_fAddPosX = 0.0;
}
//-------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------
CEnemy::~CEnemy()
{
}
//-------------------------------------------------
//�e�N�X�`���̓ǂݍ���
//-------------------------------------------------
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/enemy1.png", &m_apTexture[TEX_TYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/enemy2.png", &m_apTexture[TEX_TYPE_BLUE]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/enemy3.png", &m_apTexture[TEX_TYPE_RED]);
	return S_OK;
}
//------------------------------------------------
//�e�N�X�`���̔j��
//------------------------------------------------
void CEnemy::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY_TEX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//-----------------------------------------------
//����
//-----------------------------------------------
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY, int nLife, TYPE type, TEX_TYPE tex_type, CScene::OBJTYPE objtype)
{
	//CPlayer�N���X�̃|�C���^
	CEnemy * pEnemy;
	//�������m��
	pEnemy = new CEnemy;
	//������
	pEnemy->Init(pos, rot, sizeX, sizeY, nLife, type, tex_type, objtype);
	return pEnemy;
}
//---------------------------------------------
//������
//---------------------------------------------
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY, int nLife, TYPE type, TEX_TYPE tex_type, CScene::OBJTYPE objtype)
{
	//�^�C�v
	m_Type = type;
	//�ʒu
	m_pos = pos;
	//���C�t
	m_nLife = nLife;
	//�e�N�X�`���^�C�v
	m_TexType = tex_type;
	//������
	CScene2d::Init(pos, rot, sizeX, sizeY);
	//�J���[�ݒ�
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//�e�N�X�`���̎󂯓n��
	BindTexture(m_apTexture[m_TexType]);
	//�I�u�W�F�N�g�̐ݒ�
	SetObjType(objtype);
	return S_OK;
}
//---------------------------------------------
//�I��
//---------------------------------------------
void CEnemy::Uninit(void)
{
	//�I��
	CScene2d::Uninit();
}
//---------------------------------------------
//�X�V
//---------------------------------------------
void CEnemy::Update(void)
{
	//�X�V
	CScene2d::Update();
	//�L�[�{�[�h�擾
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();
	//�R���g���[���[�擾
	DIJOYSTATE js;
	//�C���v�b�g�W���C�X�e�B�b�N
	CInputJoystick * pInputJoystick = NULL;
	pInputJoystick = CSceneManager::GetInputJoystick();
	//�f�o�C�X�擾
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = NULL;
	g_lpDIDevice = CInputJoystick::GetDevice();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();
	//�v���C���[�̍��W�擾
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPosition();
	int nPlayerState = 0;
	nPlayerState = pPlayer->GetPlayerState();
	if (nPlayerState != CPlayer::STATE_DEAD)
	{
		//�^�C�v
		switch (m_Type)
		{
			//N_Way�̃^�C�v�̏ꍇ
		case TYPE_NWAY:
			m_nAttackCount++;
			if (m_nAttackCount == 50)
			{
				//5������
				for (int nCount = 0; nCount < 5; nCount++)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(0.0f + nCount * 1, 6.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::CBullet::PATTERN_TYPE_ENEMY_NORMAL, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(0.0f + nCount * -1, 6.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::CBullet::PATTERN_TYPE_ENEMY_NORMAL, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
			}
			if (m_nAttackCount == 100)
			{
				for (int nCount = 0; nCount < 9; nCount++)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(-3.5f + nCount * 1, 6.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::CBullet::PATTERN_TYPE_ENEMY_NORMAL, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
				m_nAttackCount = 0;
			}
			break;
		case TYPE_TRAKING_NWAY:
			m_nAttackCount++;
			if (m_nAttackCount % 60 == 0)
			{
				//5������
				for (int nCount = 0; nCount < 3; nCount++)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(5.0f + nCount * 1, 6.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
				m_nAttackCount = 0;
			}
			break;
		case TYPE_TRAKING2:
			m_nAttackCount++;
			if (m_nAttackCount % 60 == 0)
			{
				for (int nCount = 0; nCount < 2; nCount++)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(5.0f + nCount, 5.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
				m_nAttackCount = 0;
			}
			break;
		case TYPE_TRAKING3:
			m_nAttackCount++;
			if (m_nAttackCount % 60 == 0)
			{
				for (int nCount = 0; nCount < 4; nCount++)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(2.0f + nCount, 2.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
				m_nAttackCount = 0;
			}
			break;
		case TYPE_TRAKING4:
			m_nAttackCount++;
			if (m_nAttackCount % 60 == 0)
			{
				for (int nCount = 0; nCount < 5; nCount++)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(2.0f + nCount, 2.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
				m_nAttackCount = 0;
			}
			break;
		case TYPE_WAVE:
			m_nAttackCount++;
			if (m_nAttackCount % 60 == 0)
			{
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(0.0f, 6.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::CBullet::PATTERN_TYPE_ENEMY_WAVE, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				m_nAttackCount = 0;
			}
			break;
		case TYPE_CIRCLE:
			m_nAttackCount++;
			if (m_nAttackCount == 100)
			{
				for (int nCount = 0; nCount < 20; nCount++)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(cosf(D3DXToRadian(nCount * (360 / 20)))*5.0f, sinf(D3DXToRadian(nCount * (360 / 20)))*5.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_NORMAL, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
				m_nAttackCount = 0;
			}
			break;
		case TYPE_RIGHT_CIRCLE:
			m_nAttackCount++;
			m_nCircleCount++;
			if (m_nAttackCount >= 100)
			{
				if (m_nCircleCount % 3 == 0)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(cosf(D3DXToRadian(m_nCircleCount / 3 * (360 / 30)))*5.0f, sinf(D3DXToRadian(m_nCircleCount / 3 * (360 / 30)))*5.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_NORMAL, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
				m_nAttackCount = 0;
			}
			break;
		default:
			break;
			return;
		}

		//State���m�[�}���̏ꍇ
		if (m_state == STATE_NORMAL)
		{
			SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (m_state == STATE_DAMAGE)
		{
			m_nDamageCount++;
			if (m_nDamageCount % 2 == 0)
			{
				SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}

			if (m_nDamageCount % 1 == 0)
			{
				SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
			}
			if (m_nDamageCount == 10)
			{
				m_state = STATE_NORMAL;
				m_nDamageCount = 0;
			}
		}
		m_move.y = 2.0f;
		if (PlayerPos.x >= SCREEN_WIDTH / 2 && PlayerPos.x <= 880)
		{
			m_pos.x -= 0.1f;
		}
		if (PlayerPos.x <= SCREEN_WIDTH / 2 && PlayerPos.x >= 400)
		{
			m_pos.x += 0.1f;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_A))
		{
			m_pos.x += 2.0f;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_D))
		{
			m_pos.x -= 2.0f;
		}
		if (PlayerPos.x < 400 && pInputKeyboard->GetKeyboardPress(DIK_A))
		{
			m_pos.x -= 2.0f;
		}
		if (PlayerPos.x > 880 && pInputKeyboard->GetKeyboardPress(DIK_D))
		{
			m_pos.x += 2.0f;
		}

		//�ʒu�X�V
		m_pos.x += m_fAddPosX;
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;
		//�ʒu�X�V
		SetPosition(m_pos);
		//�e�N�X�`���Z�b�g
		SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
		//���C�t��0�ɂȂ�����
		if (m_TexType == TEX_TYPE_NORMAL)
		{
			//���C�t���Z����
			if (m_nLife <= 0)
			{
				//�����̐���
				CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_SIZE_X, ENEMY_SIZE_Y);
				//�I��
				Uninit();
				return;
			}
		}
		if (m_TexType == TEX_TYPE_BLUE)
		{
			if (m_nLife <= 0)
			{
				//�����̐���
				CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_SIZE_X, ENEMY_SIZE_Y);
				CItem::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POWER_SIZE_X, POWER_SIZE_Y, CItem::TYPE_POWER);
				Uninit();
				return;
			}
		}
		if (m_TexType == TEX_TYPE_RED)
		{
			if (m_nLife <= 0)
			{
				//�����̐���
				CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_SIZE_X, ENEMY_SIZE_Y);
				CItem::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BOM_SIZE_X, BOM_SIZE_Y, CItem::TYPE_BOM);
				Uninit();
				return;
			}
		}
	}
}
//---------------------------------------------
//�`��
//---------------------------------------------
void CEnemy::Draw(void)
{
	//�`��
	CScene2d::Draw();
}
//--------------------------------------------
//�e�Ɠ���������
//--------------------------------------------
void CEnemy::HitEnemy(int nDamage)
{
	//�_���[�W���Z
	m_nLife -= nDamage;
	//state���_���[�W��
	m_state = STATE_DAMAGE;
}
