//=============================================================================
//
// ��ʑJ��
// game.cpp
// Author : �ǌ��i
//
//=============================================================================

//-----------------------------------------------------------------------------
//�w�b�_�C���N���[�h
//-----------------------------------------------------------------------------
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
#include "number.h"
#include "score.h"
#include "life.h"
#include "title.h"
#include "game.h"
#include "fade.h"
#include "item.h"
#include "bomui.h"
#include "polygon.h"
#include "ship.h"
#include "boss.h"
#include "warning.h"
//------------------------------------------------
//�ÓI�����o�ϐ�
//------------------------------------------------
CScore * CGame::m_pScore = NULL;
CLife * CGame::m_pLife = NULL;
CPlayer * CGame::m_pPlayer = NULL;
CBom * CGame::m_pBom = NULL;
CShip * CGame::m_pShip = NULL;
CBoss * CGame::m_pBoss = NULL;
//-------------------------------------------------
//����
//-------------------------------------------------
CGame * CGame::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	CGame * pGame;
	pGame = new CGame;
	pGame->Init(pos, rot, sizeX, sizeY);
	return pGame;
}
//-------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------
CGame::CGame(int nPriority) : CScene(nPriority)
{
	m_bfade = false;
	m_nCount = 0;
	m_nRespawn_Count = 0;
	m_bUseBoss = false;
}
//-------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------
CGame::~CGame()
{
}
//-------------------------------------------------
//������
//-------------------------------------------------
HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//�T�E���h�擾
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;
	//pSound->PlaySound(CSound::SOUND_LABEL_BGM000);
	CPolygon::Create(D3DXVECTOR3(RIGHT_POS_X, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGON_SIZE_X, SCREEN_HEIGHT);
	CPolygon::Create(D3DXVECTOR3(LEFT_POS_X, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGON_SIZE_X, SCREEN_HEIGHT);
	//�w�i
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), SCREEN_WIDTH, SCREEN_HEIGHT);
	//�D
	m_pShip = CShip::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -1000, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), SHIP_SIZE_X , SHIP_SIZE_Y);
	//�{�X
	m_pBoss = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f), rot, BOSS_MAIN_SIZE_X, BOSS_MAIN_SIZE_Y);
	//���@
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(640.0f, 800, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), PLAYER_SIZE_X, PLAYER_SIZE_Y);
	//�X�R�A
	m_pScore = CScore::Create(D3DXVECTOR3(940.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), SCORE_SIZE_X, SCORE_SIZE_Y);
	m_pScore->SetScore(0);
	//���C�t
	m_pLife = CLife::Create(D3DXVECTOR3(350.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), LIFE_SIZE_X, LIFE_SIZE_Y);
	//�{��UI
	m_pBom = CBom::Create(D3DXVECTOR3(340.0f, 700.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), BOM_SIZE_X, BOM_SIZE_Y);
	return S_OK;
}
//-------------------------------------------------
//�I��
//-------------------------------------------------
void CGame::Uninit(void)
{
	//�I��
	Release();
}
//-------------------------------------------------
//�X�V
//-------------------------------------------------
void CGame::Update(void)
{
	//�v���C���[�擾
	CPlayer * pPlayer = GetPlayer();
	//�D
	CShip * pShip = GetShip();
	//State
	int nPlayerState = 0;
	//State�擾
	nPlayerState = pPlayer->GetPlayerState();
	/*if (m_nRespawn_Count == 50)
	{
		for (int nCount = 0; nCount < 20; nCount++)
		{
			CParticle::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),D3DXVECTOR3(0.0f,-2.0f,0.0f), 20, 20, OBJTYPE_EXPLOSION,CParticle::TEX_TYPE_1,CParticle::TYPE_SCALE);
		}
		m_nRespawn_Count = 0;
	}*/
	if (nPlayerState != CPlayer::STATE_DEAD)
	{
		if (m_bUseBoss == false)
		{
			m_nRespawn_Count++;
			if (m_nRespawn_Count % 150 == 0)
			{
				CEnemy::Create(D3DXVECTOR3(900.0f, -300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), ENEMY_SIZE_X, ENEMY_SIZE_X, 10, CEnemy::TYPE_TRAKING2, CEnemy::TEX_TYPE_NORMAL, CScene::OBJTYPE_ENEMY);
				CEnemy::Create(D3DXVECTOR3(540.0f, -150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), ENEMY_SIZE_X, ENEMY_SIZE_X, 10, CEnemy::TYPE_TRAKING2, CEnemy::TEX_TYPE_NORMAL, CScene::OBJTYPE_ENEMY);
				CEnemy::Create(D3DXVECTOR3(440.0f, -200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), ENEMY_SIZE_X, ENEMY_SIZE_X, 10, CEnemy::TYPE_TRAKING2, CEnemy::TEX_TYPE_NORMAL, CScene::OBJTYPE_ENEMY);
			}
			if (m_nRespawn_Count % 400 == 0)
			{
				CEnemy::Create(D3DXVECTOR3(840.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), ENEMY_SIZE_X, ENEMY_SIZE_X, 10, CEnemy::TYPE_TRAKING2, CEnemy::TEX_TYPE_NORMAL, CScene::OBJTYPE_ENEMY);
				CEnemy::Create(D3DXVECTOR3(740.0f, -50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), ENEMY_SIZE_X, ENEMY_SIZE_X, 10, CEnemy::TYPE_TRAKING2, CEnemy::TEX_TYPE_NORMAL, CScene::OBJTYPE_ENEMY);
				CEnemy::Create(D3DXVECTOR3(640.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), ENEMY_SIZE_X, ENEMY_SIZE_X, 10, CEnemy::TYPE_TRAKING2, CEnemy::TEX_TYPE_NORMAL, CScene::OBJTYPE_ENEMY);
			}
			if (m_nRespawn_Count % 300 == 0)
			{
				CEnemy::Create(D3DXVECTOR3(840.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), ENEMY_SIZE_X, ENEMY_SIZE_X, 50, CEnemy::TYPE_CIRCLE, CEnemy::TEX_TYPE_BLUE, CScene::OBJTYPE_ENEMY);
			}
			if (m_nRespawn_Count % 500 == 0)
			{
				CEnemy::Create(D3DXVECTOR3(600.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)), ENEMY_SIZE_X, ENEMY_SIZE_X, 50, CEnemy::TYPE_CIRCLE, CEnemy::TEX_TYPE_RED, CScene::OBJTYPE_ENEMY);
			}

			if (m_nRespawn_Count == 1500)
			{
				pShip->SetShip(1);
			}
			//�J�E���g��
			if (m_nRespawn_Count == 3300)
			{
				m_bUseBoss = true;
			}
		}
	}
}
//-------------------------------------------------
//�`��
//-------------------------------------------------
void CGame::Draw(void)
{
}