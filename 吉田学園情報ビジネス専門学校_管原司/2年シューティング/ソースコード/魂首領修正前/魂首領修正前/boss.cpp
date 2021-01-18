//---------------------------------------------------
// Boss
// boss.cpp
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
#include "sound.h"
#include "life.h"
#include "game.h"
#include "explosion.h"
#include "bomui.h"
#include "continue.h"
#include "score.h"
#include "boss.h"
#include "enemy.h"
LPDIRECT3DTEXTURE9 CBoss::m_apTexture[MAX_BOSS] = {};
//---------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------
CBoss::CBoss(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_Mainpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rightpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Leftpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nAttackCount = 0;
	m_nAttackCount2 = 0;
	m_nDamageCount = 0;
	m_nSetCount = 0;
	m_State = STATE_NONE;
	m_bMove = false;
}
//---------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------
CBoss::~CBoss()
{
}
//---------------------------------------------------------------
//�e�N�X�`���ǂݍ���
//---------------------------------------------------------------
HRESULT CBoss::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/BossMain2.png", &m_apTexture[TYPE_MAIN]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/BossRight2.png", &m_apTexture[TYPE_RIGHT]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/BossLeft2.png", &m_apTexture[TYPE_LEFT]);
	return S_OK;
}
//---------------------------------------------------------------
//�e�N�X�`���j��
//---------------------------------------------------------------
void CBoss::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BOSS; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//---------------------------------------------------------------
//�����֐�
//---------------------------------------------------------------
CBoss * CBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//�{�X�|�C���^
	CBoss * pBoss;
	//�������m��
	pBoss = new CBoss;
	pBoss->Init(pos, rot, sizeX, sizeY);
	return pBoss;
}
//---------------------------------------------------------------
//�������֐�
//---------------------------------------------------------------
HRESULT CBoss::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//�̗�
	m_nLife = BOSS_LIFE;
	m_State = STATE_MOVE;

	//�������m��
	m_apScene2D[TYPE_MAIN] = new CScene2d;
	m_apScene2D[TYPE_RIGHT] = new CScene2d;
	m_apScene2D[TYPE_LEFT] = new CScene2d;

	//RGBA�̐ݒ�
	m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�e�N�X�`���̎󂯓n��
	m_apScene2D[TYPE_MAIN]->BindTexture(m_apTexture[TYPE_MAIN]);
	m_apScene2D[TYPE_RIGHT]->BindTexture(m_apTexture[TYPE_RIGHT]);
	m_apScene2D[TYPE_LEFT]->BindTexture(m_apTexture[TYPE_LEFT]);
	//������
	m_apScene2D[TYPE_MAIN]->Init(pos, rot, sizeX, sizeY);
	m_apScene2D[TYPE_RIGHT]->Init(D3DXVECTOR3(pos.x + BOSS_RIGHT_SIZE_X, pos.y, pos.z), rot, BOSS_RIGHT_SIZE_X, BOSS_RIGHT_SIZE_Y);
	m_apScene2D[TYPE_LEFT]->Init(D3DXVECTOR3(pos.x - BOSS_LEFT_SIZE_X, pos.y, pos.z), rot, BOSS_LEFT_SIZE_X, BOSS_LEFT_SIZE_Y);
	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	m_apScene2D[TYPE_MAIN]->SetObjType(OBJTYPE_BOSS);
	m_apScene2D[TYPE_RIGHT]->SetObjType(OBJTYPE_BOSS_RIGHT);
	m_apScene2D[TYPE_LEFT]->SetObjType(OBJTYPE_BOSS_LEFT);
	
	return S_OK;
}
//---------------------------------------------------------------
//�I���֐�
//---------------------------------------------------------------
void CBoss::Uninit(void)
{
	//�I��
	Release();
}
//---------------------------------------------------------------
//�X�V�֐�
//---------------------------------------------------------------
void CBoss::Update(void)
{
	if (m_nSetCount == 1)
	{
		//�X�V
		m_apScene2D[TYPE_MAIN]->Update();
		m_apScene2D[TYPE_RIGHT]->Update();
		m_apScene2D[TYPE_LEFT]->Update();

		//���@�̒��S
		m_Mainpos = m_apScene2D[TYPE_MAIN]->GetPosition();
		//���@�̉E
		m_Rightpos = m_apScene2D[TYPE_RIGHT]->GetPosition();
		//���@�̍�
		m_Leftpos = m_apScene2D[TYPE_LEFT]->GetPosition();
		//���W�ݒ�
		m_apScene2D[TYPE_RIGHT]->SetPosition(D3DXVECTOR3(m_Mainpos.x + BOSS_RIGHT_SIZE_X, m_Mainpos.y, m_Mainpos.z));
		m_apScene2D[TYPE_LEFT]->SetPosition(D3DXVECTOR3(m_Mainpos.x - BOSS_LEFT_SIZE_X, m_Mainpos.y, m_Mainpos.z));
		//�e�N�X�`���ݒ�
		m_apScene2D[TYPE_MAIN]->SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
		m_apScene2D[TYPE_RIGHT]->SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
		m_apScene2D[TYPE_LEFT]->SetTexture(0.0f, 0.0f, 1.0f, 1.0f);

		//�ŏ��̈ړ�
		if (m_State == STATE_MOVE)
		{
			m_move.y = 2;
			if (m_Mainpos.y == 200.0f)
			{
				m_move.y = 0;
				m_State = STATE_NORMAL;
			}
		}
		//State���m�[�}���̏ꍇ
		if (m_State == STATE_NORMAL)
		{
			//�J���[��ʏ�ɂ���
			m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		//�{�X���ړ�����������
		if (m_State != STATE_MOVE)
		{
			//�v���C���[�擾
			CPlayer * pPlayer = CGame::GetPlayer();
			//�v���C���[��bom���{�X��p�ɕύX
			pPlayer->SetBossBom(true);
			if (m_nLife >= BOSS_LIFE / 2)
			{
				m_nAttackCount++;
				//60���܂�0�̏ꍇ
				if (m_nAttackCount % 60 == 0)
				{
					//5������
					for (int nCount = 0; nCount < 2; nCount++)
					{
						CBullet::Create(D3DXVECTOR3(m_Rightpos.x + BOSS_RIGHT_SIZE_X / 2, m_Rightpos.y + BOSS_RIGHT_SIZE_Y / 2, m_Rightpos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(-2.0f - nCount, 6.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::CBullet::PATTERN_TYPE_ENEMY_NORMAL, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
						CBullet::Create(D3DXVECTOR3(m_Leftpos.x - BOSS_LEFT_SIZE_X / 2, m_Leftpos.y + BOSS_LEFT_SIZE_Y / 2, m_Leftpos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(2.0f + nCount, 6.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::CBullet::PATTERN_TYPE_ENEMY_NORMAL, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
					}
				}
				//100���܂�0�̏ꍇ
				if (m_nAttackCount % 100 == 0)
				{
					for (int nCount = 0; nCount < 3; nCount++)
					{
						CBullet::Create(D3DXVECTOR3(m_Mainpos.x, m_Mainpos.y, m_Mainpos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(6.0f + nCount, 6.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
					}
				}
				//�g�U�e
				if (m_nAttackCount % 250 == 0)
				{
					CBullet::Create(D3DXVECTOR3(m_Mainpos.x, m_Mainpos.y, m_Mainpos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(0.0f, 2.0f, 0.0f), FIFFUSION_BULLET_SIZE_X, FIFFUSION_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_DIFFUSION, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
				}
				if (m_bMove == false)
				{
					m_move.x = 3;
				}
				//���E�ړ�
				if (m_Rightpos.x + BOSS_RIGHT_SIZE_X / 2 >= MAX_GAME_WIDTH)
				{
					m_move.x = -3;
					m_bMove = true;
				}
				if (m_Leftpos.x - BOSS_LEFT_SIZE_X / 2 <= MIN_GAME_WIDTH)
				{
					m_move.x = 3;
					m_bMove = true;
				}
			}
			if (m_nLife <= BOSS_LIFE / 2)
			{
				m_nAttackCount2++;
				//100���܂�0�̏ꍇ
				if (m_nAttackCount2 % 60 == 0)
				{
					for (int nCount = 0; nCount < 4; nCount++)
					{
						CBullet::Create(D3DXVECTOR3(m_Mainpos.x, m_Mainpos.y, m_Mainpos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(6.0f + nCount, 6.0f + nCount, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_TRAKING, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
					}
				}
				if (m_nAttackCount2 >= 100)
				{
					if (m_nAttackCount2 % 3 == 0)
					{
						CBullet::Create(D3DXVECTOR3(m_Rightpos.x + BOSS_RIGHT_SIZE_X / 2, m_Rightpos.y + BOSS_RIGHT_SIZE_X / 2, m_Rightpos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(cosf(D3DXToRadian(m_nAttackCount2 / 3 * (360 / 20)))*3.0f, sinf(D3DXToRadian(m_nAttackCount2 / 3 * (360 / 20)))*3.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_NORMAL, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
						CBullet::Create(D3DXVECTOR3(m_Leftpos.x - BOSS_LEFT_SIZE_X / 2, m_Leftpos.y + BOSS_LEFT_SIZE_Y / 2, m_Leftpos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(cosf(D3DXToRadian(m_nAttackCount2 / 3 * (360 / 20)))* -3.0f, sinf(D3DXToRadian(m_nAttackCount2 / 3 * (360 / 20)))* -3.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_NORMAL, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
					}
				}
				//���E�ړ�
				if (m_Rightpos.x + BOSS_RIGHT_SIZE_X / 2 >= MAX_GAME_WIDTH)
				{
					m_move.x = -3;
					m_bMove = true;
				}
				if (m_Leftpos.x - BOSS_LEFT_SIZE_X / 2 <= MIN_GAME_WIDTH)
				{
					m_move.x = 3;
					m_bMove = true;
				}
			}
		}
		//State��Damage�̏ꍇ
		if (m_State == STATE_DAMAGE)
		{
			//�_���[�W�J�E���g�̃C���N�������g
			m_nDamageCount++;
			//�J�E���g��1���܂�0�̎�
			if (m_nDamageCount % 1 == 0)
			{
				//�Ԃ�����
				m_apScene2D[TYPE_MAIN]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
				m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
				m_apScene2D[TYPE_LEFT]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
			}
			//�J�E���g��2���܂�0�̎�
			if (m_nDamageCount % 2 == 0)
			{
				//�J���[��ʏ�ɖ߂�
				m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}

			//�J�E���g��10�ɂȂ�����
			if (m_nDamageCount == 10)
			{
				//State���m�[�}����
				m_State = STATE_NORMAL;
				//�J�E���g��0�ɂȂ�����
				m_nDamageCount = 0;
			}
		}
		//���C�t��0�ɂȂ����ꍇ
		if (m_nLife <= 0)
		{
			CExplosion::Create(m_Mainpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), BOSS_MAIN_SIZE_X, BOSS_MAIN_SIZE_Y);
			CExplosion::Create(m_Rightpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), BOSS_RIGHT_SIZE_X, BOSS_RIGHT_SIZE_Y);
			CExplosion::Create(m_Leftpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), BOSS_LEFT_SIZE_X, BOSS_LEFT_SIZE_Y);
			m_State = STATE_DEAD;
			if (m_State == STATE_DEAD)
			{
				CSceneManager::StartFade(CSceneManager::MODE_RESULT);
				//�I��
				Uninit();
				return;
			}
		}
		//�ʒu�X�V
		m_Mainpos.x += m_move.x;
		m_Mainpos.y += m_move.y;
		m_Rightpos.x += m_move.x;
		m_Rightpos.y += m_move.y;
		m_Leftpos.x += m_move.x;
		m_Leftpos.y += m_move.y;
		m_apScene2D[TYPE_MAIN]->SetPosition(m_Mainpos);
		m_apScene2D[TYPE_RIGHT]->SetPosition(m_Rightpos);
		m_apScene2D[TYPE_LEFT]->SetPosition(m_Leftpos);
	}
}
//---------------------------------------------------------------
//�`��֐�
//---------------------------------------------------------------
void CBoss::Draw(void)
{
}
//---------------------------------------------------------------
//Damage����
//---------------------------------------------------------------
void CBoss::HitBoss(int nDamage)
{
	if (m_State != STATE_MOVE)
	{
		//�̗͌��Z
		m_nLife -= nDamage;
		//State��Damage��
		m_State = STATE_DAMAGE;
	}
}
//---------------------------------------------------------------
//�{�X�X�V�J�n
//---------------------------------------------------------------
void CBoss::SetBoss(int nSetCount)
{
	m_nSetCount = nSetCount;
}
