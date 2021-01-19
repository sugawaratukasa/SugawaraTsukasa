//******************************************************************************
// �Q�[�� [game.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
// �t�@�C���C���N���[�h
//******************************************************************************
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
#include "bg.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "normal_enemy.h"
#include "circle_bullet_enemy.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "game.h"
#include "fade.h"
#include "item.h"
#include "bomui.h"
#include "polygon.h"
#include "ship.h"
#include "boss.h"
#include "warning.h"
#include "ship_battery.h"
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
CScore * CGame::m_pScore = NULL;
CLife * CGame::m_pLife = NULL;
CPlayer * CGame::m_pPlayer = NULL;
CBomUI * CGame::m_pBom = NULL;
CShip * CGame::m_pShip = NULL;
CBoss * CGame::m_pBoss = NULL;
//******************************************************************************
// �����֐�
//******************************************************************************
CGame * CGame::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CGame�N���X�̃|�C���^
	CGame * pGame;

	// �������m��
	pGame = new CGame;

	// �ʒu���W���
	pGame->m_pos = pos;

	// �T�C�Y���
	pGame->m_size = size;

	// ������
	pGame->Init();

	// �|�C���^��Ԃ�
	return pGame;
 }
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CGame::CGame(int nPriority) : CScene(nPriority)
{
	m_pos				= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size				= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nCount			= 0;
	m_nRespawn_Count	= 0;
	m_bfade				= false;
	m_bUseBoss			= false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CGame::~CGame()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CGame::Init(void)
{
	//�T�E���h�擾
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;
	//pSound->PlaySound(CSound::SOUND_LABEL_BGM000);
	CPolygon::Create(POLYGON_RIGHT_POS, POLYGON_SIZE);
	CPolygon::Create(POLYGON_LEFT_POS, POLYGON_SIZE);
	//�w�i
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), BG_SIZE);
	//�{�X
	m_pBoss = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f), BOSS_MAIN_SIZE);
	//���@
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(640.0f, 800, 0.0f), PLAYER_SIZE);
	//�X�R�A
	m_pScore = CScore::Create(D3DXVECTOR3(940.0f, 50.0f, 0.0f), SCORE_SIZE);
	m_pScore->SetScore(0);
	//���C�t
	m_pLife = CLife::Create(D3DXVECTOR3(350.0f, 50.0f, 0.0f), LIFE_SIZE);
	//�{��UI
	m_pBom = CBomUI::Create(D3DXVECTOR3(340.0f, 700.0f, 0.0f), BOM_UI_SIZE);

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CGame::Uninit(void)
{
	//�I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CGame::Update(void)
{
	//�v���C���[�擾
	CPlayer * pPlayer = GetPlayer();
	//State
	int nPlayerState = 0;
	//State�擾
	nPlayerState = pPlayer->GetPlayerState();

	// �v���C���[�����S��ԂłȂ��ꍇ
	if (nPlayerState != CPlayer::STATE_DEAD)
	{
		// false�̏ꍇ
		if (m_bUseBoss == false)
		{
			// �C���N�������g
			m_nRespawn_Count++;

			// 150���܂�0�̂Ƃ�
			if (m_nRespawn_Count % 150 == 0)
			{
				// �G����
				CNormal_Enemy::Create(D3DXVECTOR3(900.0f, -300.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					NORMAL_ENEMY_SIZE,
					NORMAL_ENEMY_LIFE,
					CEnemy::TEX_TYPE_NORMAL);

				CNormal_Enemy::Create(D3DXVECTOR3(540.0f, -150.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					NORMAL_ENEMY_SIZE,
					NORMAL_ENEMY_LIFE,
					CEnemy::TEX_TYPE_NORMAL);

				CNormal_Enemy::Create(D3DXVECTOR3(440.0f, -200.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					NORMAL_ENEMY_SIZE,
					NORMAL_ENEMY_LIFE,
					CEnemy::TEX_TYPE_NORMAL);
			}
			// 400���܂�0�̂Ƃ�
			if (m_nRespawn_Count % 400 == 0)
			{
				CNormal_Enemy::Create(D3DXVECTOR3(840.0f, -100.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					NORMAL_ENEMY_SIZE,
					NORMAL_ENEMY_LIFE,
					CEnemy::TEX_TYPE_NORMAL);

				CNormal_Enemy::Create(D3DXVECTOR3(740.0f, -50.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					NORMAL_ENEMY_SIZE,
					NORMAL_ENEMY_LIFE,
					CEnemy::TEX_TYPE_NORMAL);

				CNormal_Enemy::Create(D3DXVECTOR3(640.0f, -100.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					NORMAL_ENEMY_SIZE,
					NORMAL_ENEMY_LIFE,
					CEnemy::TEX_TYPE_NORMAL);

			}
			// 300���܂�0�̂Ƃ�
			if (m_nRespawn_Count % 300 == 0)
			{
				// �G����
				CCirecle_Bullet_Enemy::Create(D3DXVECTOR3(480.0f, -100.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					CIRCLE_BULLET_ENEMY_SIZE,
					CIRCLE_BULLET_ENEMY_LIFE,
					CEnemy::TEX_TYPE_BLUE,
					CCirecle_Bullet_Enemy::DROP_ITEM_BOM);
			}
			// 500���܂�0�̂Ƃ�
			if (m_nRespawn_Count % 500 == 0)
			{
				// �G����
				CCirecle_Bullet_Enemy::Create(D3DXVECTOR3(600.0f, -100.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					CIRCLE_BULLET_ENEMY_SIZE,
					CIRCLE_BULLET_ENEMY_LIFE,
					CEnemy::TEX_TYPE_RED,
					CCirecle_Bullet_Enemy::DROP_ITEM_POWERUP);
			}
			// 1500�J�E���g
			if (m_nRespawn_Count == 1500)
			{
				// �D����
				m_pShip = CShip::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -1000.0f, 0.0f), SHIP_SIZE);
			}
			//�J�E���g��
			if (m_nRespawn_Count == 3300)
			{
				m_bUseBoss = true;
			}
		}
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CGame::Draw(void)
{
}