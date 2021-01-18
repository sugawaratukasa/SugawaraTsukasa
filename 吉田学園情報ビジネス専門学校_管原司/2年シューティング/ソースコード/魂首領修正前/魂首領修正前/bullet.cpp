//---------------------------------------------------
// Bullet
// Bullet.cpp
// Author:	�ǌ��i
//---------------------------------------------------

//---------------------------------------------------
//�C���N���[�h�t�@�C��
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
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "game.h"
#include "ship.h"
#include "boss.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//-------------------------------------------------
//�ÓI�����o�ϐ�
//-------------------------------------------------
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[MAX_BULLET_TEX] = {};
bool CBullet::m_bUseBeam = true;
bool CBullet::m_bUseBom = true;
//--------------------------------------------------
//�e�N�X�`���̃��[�h
//--------------------------------------------------
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Playerbullet001.png", &m_apTexture[TEX_TYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/PlayerBeam001.png", &m_apTexture[TEX_TYPE_BEAM]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bom.png", &m_apTexture[TEX_TYPE_BOM]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/EnemyBullet.png", &m_apTexture[TEX_TYPE_ENEMY_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Bullet003test.png", &m_apTexture[TEX_TYPE_ENEMY_WAVE]);
	return S_OK;
}
//-------------------------------------------------
//�e�N�X�`���̔j��
//-------------------------------------------------
void CBullet::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_BULLET_TEX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//---------------------------------------------------
//�����֐�
//---------------------------------------------------
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int sizeX, int sizeY, TYPE type, PATTERN_TYPE pattern , TEX_TYPE texType , OBJTYPE objtype)
{
	//CPlayer�N���X�̃|�C���^
	CBullet * pBullet;
	//�������m��
	pBullet = new CBullet;
	//������
	pBullet->Init(pos, rot, move, sizeX, sizeY, type, pattern, texType, objtype);
	return pBullet;
}
//---------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------
CBullet::CBullet(int nPriority) : CScene2d(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_textype = TEX_TYPE_NONE;
	m_objtype = OBJTYPE_NONE;
	m_PatternType = PATTERN_TYPE_NONE;
	m_bUseBeam = true;
	m_bUseBom = true;
	m_nEffectCount = 0;
	m_nDifCount = 0;
	m_nBom_Anim_Count = 0;
	m_nPattern_Bom_Anim = 0;
	m_nAddMove = 0;
	m_nMinMove = 0.0f;
	m_rad = 0.0f;
	m_fAngle = 0.0f;
	m_fMoveX = 0.0f;
	m_fMoveY = 0.0f;
	m_bWavemove = false;
}
//---------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------
CBullet::~CBullet()
{
}
//---------------------------------------------------
//������
//---------------------------------------------------
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int sizeX, int sizeY, TYPE type, PATTERN_TYPE pattern , TEX_TYPE texType , OBJTYPE objtype)
{
	//move
	m_move = move;
	//����
	m_rot = rot;
	//�^�C�v
	m_type = type;
	//�p�^�[���̃^�C�v
	m_PatternType = pattern;
	//�e�N�X�`���^�C�v
	m_textype = texType;
	//������
	CScene2d::Init(pos, rot, sizeX, sizeY);
	//�e�̏����ݒ�
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(m_apTexture[texType]);
	SetObjType(objtype);
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();
	//�v���C���[�̍��W�擾
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPosition();
	/*m_fAngle = atan2f(1000 - pos.y, 100 - pos.x);*/
	m_fAngle = atan2f(PlayerPos.y - pos.y, PlayerPos.x - pos.x);
	return S_OK;
}
//---------------------------------------------------
//�I��
//---------------------------------------------------
void CBullet::Uninit(void)
{
	//�I��
	CScene2d::Uninit();
}
//---------------------------------------------------
//�X�V
//---------------------------------------------------
void CBullet::Update(void)
{
	//�X�V
	CScene2d::Update();
	//�T�E���h�̎擾
	CSound * pSound = CSceneManager::GetSound();
	//�X�R�A�̎擾
	CScore * pScore = CGame::GetScore();
	//�Q�[���擾
	CGame * pGame = CSceneManager::GetGame();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();
	//�{�X�̎擾
	CBoss * pBoss = CGame::GetBoss();
	//�D�̎擾
	CShip * pShip = CGame::GetShip();
	//�v���C���[�̍��W�擾
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPosition();
	//�v���C���[�̏�Ԏ擾
	int nPlayerState = 0;
	nPlayerState = pPlayer->GetPlayerState();
	//�v���C���[�̃��x���擾
	int PlayerLevel = 0;
	PlayerLevel = pPlayer->GetLevel();
	//���W�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();
	for (int nCntPriority = 0; nCntPriority < PRIORITY_TYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//�V�[���̎擾
			CScene * pScene = GetScene(nCntPriority, nCntScene);
			if (pScene != NULL)
			{
				//�I�u�W�F�N�g�̃^�C�v�擾
				OBJTYPE objType;
				objType = pScene->GetObjType();
				//���W�̎擾
				D3DXVECTOR3 ScenePos;
				ScenePos = pScene->GetPosition();
				//�G�̎擾
				CEnemy * pEnemy = (CEnemy*)(pScene);
				//�^�C�v
				switch (m_type)
				{
					//Player�̏ꍇ
				case TYPE_PLAYER:
					//�ʏ�e�̏ꍇ
					if (m_PatternType == PATTERN_TYPE_NORMAL)
					{
						//�I�u�W�F�N�g���G�̏ꍇ
						if (objType == OBJTYPE_ENEMY)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									////������
									//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
									//�����̐���
									CExplosion::Create(ScenePos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
									//�X�R�A���Z
									pScore->AddScore(100);
									pEnemy->HitEnemy(20);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									////������
									//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
									//�����̐���
									CExplosion::Create(ScenePos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
									//�X�R�A���Z
									pScore->AddScore(100);
									//�_���[�W
									pEnemy->HitEnemy(20);
									//�I��
									Uninit();
									return;
								}
							}
							//���x��3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									////������
									//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
									//�����̐���
									CExplosion::Create(ScenePos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
									//�X�R�A���Z
									pScore->AddScore(100);
									//�_���[�W
									pEnemy->HitEnemy(20);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//�^�C�v���I�u�W�F�N�g
						if (objType == OBJTYPE_BOSS)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + BOSS_MAIN_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - BOSS_MAIN_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2 - 80)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2))
								{
									//�X�R�A���Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(40);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + BOSS_MAIN_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - BOSS_MAIN_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2 - 80)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2))
								{
									//�X�R�A���Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(40);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + BOSS_MAIN_SIZE_X / 2 )
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - BOSS_MAIN_SIZE_X / 2 )
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2 - 80)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2 ))
								{
									//�X�R�A���Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(40);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//�{�X�̉E
						if (objType == OBJTYPE_BOSS_RIGHT)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2 - 30)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
								{
									//�X�R�A���Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(20);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2 - 30)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
								{
									//�X�R�A���Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(20);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2 - 30)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
								{
									//�X�R�A���Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(20);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//�{�X�̍�
						if (objType == OBJTYPE_BOSS_LEFT)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
								{
									//�X�R�A���Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(20);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
								{
									//�X�R�A���Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(20);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
								{
									//�X�R�A���Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(20);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//�^�C�v��SHIPWEPON1�̏ꍇ
						if (objType == OBJTYPE_SHIP_WEPON1)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon1(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon1(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon1(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//�^�C�v��SHIPWEPON2�̏ꍇ
						if (objType == OBJTYPE_SHIP_WEPON2)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon2(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon2(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon2(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//�^�C�v��SHIPWEPON3�̏ꍇ
						if (objType == OBJTYPE_SHIP_WEPON3)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon3(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon3(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon3(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//SHIP_WEPON_4
						if (objType == OBJTYPE_SHIP_WEPON4)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon4(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon4(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon4(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//SHIP_WEPON_4
						if (objType == OBJTYPE_SHIP_WEPON5)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon5(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon5(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon5(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//SHIP_WEPON_6
						if (objType == OBJTYPE_SHIP_WEPON6)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon6(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon6(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon6(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
					}
					//�r�[���̏ꍇ
					if (m_PatternType == PATTERN_TYPE_BEAM)
					{
						pos.x = PlayerPos.x;
						//�I�u�W�F�N�g���{�X�̏ꍇ
						if (objType == OBJTYPE_BOSS)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if ((pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_MAIN_SIZE_X / 2 )
									&& (pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_MAIN_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2 - 80)
									&& (pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2))
								{
									//�X�R�A�̉��Z
									pScore->AddScore(100);
									//�G�̏I������
									pBoss->HitBoss(20);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if ((pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_MAIN_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_MAIN_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2 - 80)
									&& (pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2))
								{
									//�X�R�A�̉��Z
									pScore->AddScore(100);
									//�G�̏I������
									pBoss->HitBoss(20);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if ((pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_MAIN_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_MAIN_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2 - 80)
									&& (pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2))
								{
									//�X�R�A�̉��Z
									pScore->AddScore(100);
									//�G�̏I������
									pBoss->HitBoss(20);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//�{�X�̉E
						if (objType == OBJTYPE_BOSS_RIGHT)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if ((pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2 - 30)
									&& (pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
								{
									//�X�R�A�̉��Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if ((pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2 - 30)
									&& (pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
								{
									//�X�R�A�̉��Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if ((pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2 - 30)
									&& (pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
								{
									//�X�R�A�̉��Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//�{�X�̍�
						if (objType == OBJTYPE_BOSS_LEFT)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if ((pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2 - 30)
									&& (pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
								{
									//�X�R�A�̉��Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if ((pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2 - 30)
									&& (pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
								{
									//�X�R�A�̉��Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if ((pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2 - 30)
									&& (pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
								{
									//�X�R�A�̉��Z
									pScore->AddScore(100);
									//�_���[�W
									pBoss->HitBoss(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//�I�u�W�F�N�g���G�̏ꍇ
						if (objType == OBJTYPE_ENEMY)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if ((pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2) < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2) > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2) < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& (pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2) > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									//�T�E���h����
									/*pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);*/
									//��������
									CExplosion::Create(ScenePos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
									//�X�R�A�̉��Z
									pScore->AddScore(100);
									//�G�̏I������
									pEnemy->HitEnemy(5);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if ((pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2) < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2) > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2) < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& (pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2) > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									//�T�E���h����
									/*pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);*/
									//��������
									CExplosion::Create(ScenePos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
									//�X�R�A�̉��Z
									pScore->AddScore(100);
									//�G�̏I������
									pEnemy->HitEnemy(5);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if ((pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2) < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2) > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2) < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& (pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2) > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									//�T�E���h����
									/*pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);*/
									//��������
									CExplosion::Create(ScenePos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
									//�X�R�A�̉��Z
									pScore->AddScore(100);
									//�G�̏I������
									pEnemy->HitEnemy(5);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//�^�C�v��SHIPWEPON1�̏ꍇ
						if (objType == OBJTYPE_SHIP_WEPON1)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon1(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon1(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon1(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
					}
						//�^�C�v��SHIPWEPON2�̏ꍇ
						if (objType == OBJTYPE_SHIP_WEPON2)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon2(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon2(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon2(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//�^�C�v��SHIPWEPON3�̏ꍇ
						if (objType == OBJTYPE_SHIP_WEPON3)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon3(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon3(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon3(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//SHIP_WEPON_4
						if (objType == OBJTYPE_SHIP_WEPON4)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon4(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon4(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon4(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//SHIP_WEPON_4
						if (objType == OBJTYPE_SHIP_WEPON5)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon5(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon5(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon5(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//SHIP_WEPON_6
						if (objType == OBJTYPE_SHIP_WEPON6)
						{
							//���x����1�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon6(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����2�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon6(10);
									//�I��
									Uninit();
									return;
								}
							}
							//���x����3�̏ꍇ
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//�G�ƒe����������
								if (pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon6(10);
									//�I��
									Uninit();
									return;
								}
							}
						}
						//�{��
						if (m_PatternType == PATTERN_TYPE_BOM)
						{
							//�G�̒e
							if (objType == OBJTYPE_ENEMY_BULLET)
							{
								//�G�ƒe����������
								if ((pos.x - MAX_GAME_WIDTH / 2) < (ScenePos.x + ENEMY_BULLET_SIZE_X / 2)
									&& (pos.x + MAX_GAME_WIDTH / 2) > (ScenePos.x - ENEMY_BULLET_SIZE_X / 2)
									&& (pos.y - SCREEN_HEIGHT / 2) < (ScenePos.y + ENEMY_BULLET_SIZE_Y / 2)
									&& (pos.y + SCREEN_HEIGHT / 2) > (ScenePos.y - ENEMY_BULLET_SIZE_Y / 2))
								{
									//�G�̒e�̏I��
									pScene->Uninit();
								}
							}

							//�I�u�W�F�N�g���G�̏ꍇ
							if (objType == OBJTYPE_ENEMY)
							{
								//�G�ƒe����������
								if ((pos.x - MAX_GAME_WIDTH / 2) < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& (pos.x + MAX_GAME_WIDTH / 2) > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& (pos.y - SCREEN_HEIGHT / 2) < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& (pos.y + SCREEN_HEIGHT / 2) > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									//�_���[�W
									pEnemy->HitEnemy(50);
								}
							}
							//�^�C�v��SHIPWEPON1�̏ꍇ
							if (objType == OBJTYPE_SHIP_WEPON1)
							{
								//�G�ƒe����������
								if (pos.x - MAX_GAME_WIDTH / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + MAX_GAME_WIDTH / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - SCREEN_HEIGHT / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + SCREEN_HEIGHT / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon1(50);
								}
							}
							//�^�C�v��SHIPWEPON2�̏ꍇ
							if (objType == OBJTYPE_SHIP_WEPON2)
							{
								//�G�ƒe����������
								if (pos.x - MAX_GAME_WIDTH / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + MAX_GAME_WIDTH / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - SCREEN_HEIGHT / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + SCREEN_HEIGHT / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon2(50);
								}
							}
							//�^�C�v��SHIPWEPON3�̏ꍇ
							if (objType == OBJTYPE_SHIP_WEPON3)
							{
								//�G�ƒe����������
								if (pos.x - MAX_GAME_WIDTH / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + MAX_GAME_WIDTH / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - SCREEN_HEIGHT / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + SCREEN_HEIGHT / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon3(50);
								}
							}
							//�^�C�v��SHIPWEPON4�̏ꍇ
							if (objType == OBJTYPE_SHIP_WEPON4)
							{
								//�G�ƒe����������
								if (pos.x - MAX_GAME_WIDTH / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + MAX_GAME_WIDTH / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - SCREEN_HEIGHT / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + SCREEN_HEIGHT / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon4(50);
								}
							}
							//�^�C�v��SHIPWEPON5�̏ꍇ
							if (objType == OBJTYPE_SHIP_WEPON5)
							{
								//�G�ƒe����������
								if (pos.x - MAX_GAME_WIDTH / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + MAX_GAME_WIDTH / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - SCREEN_HEIGHT / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + SCREEN_HEIGHT / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon5(50);
								}
							}
							//�^�C�v��SHIPWEPON6�̏ꍇ
							if (objType == OBJTYPE_SHIP_WEPON6)
							{
								//�G�ƒe����������
								if (pos.x - MAX_GAME_WIDTH / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + MAX_GAME_WIDTH / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - SCREEN_HEIGHT / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + SCREEN_HEIGHT / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//�_���[�W
									pShip->HitWepon6(50);
								}
							}
						}
					//�r�[���̏ꍇ
					if (m_PatternType == PATTERN_TYPE_BOSS_BOM)
					{
						pos.x = PlayerPos.x;
						//�I�u�W�F�N�g���G�̏ꍇ
						if (objType == OBJTYPE_BOSS)
						{
							//�G�ƒe����������
							if ((pos.x - BULLET_BOSS_BOM_SIZE_X / 2) < (ScenePos.x + BOSS_MAIN_SIZE_X / 2)
								&& (pos.x + BULLET_BOM_SIZE_X / 2) > (ScenePos.x - BOSS_MAIN_SIZE_X / 2)
								&& (pos.y - BULLET_BOSS_BOM_SIZE_Y / 2) < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2)
								&& (pos.y + BULLET_BOSS_BOM_SIZE_Y / 2) > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2))
							{
								//��������
								CExplosion::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
								//�X�R�A�̉��Z
								pScore->AddScore(10);
								//�{�X�Ƀ_���[�W
								pBoss->HitBoss(30);
								//�I��
								Uninit();
								return;
							}
						}
						if (objType == OBJTYPE_BOSS_RIGHT)
						{
							//�G�ƒe����������
							if ((pos.x - BULLET_BOSS_BOM_SIZE_X / 2) < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
								&& (pos.x + BULLET_BOM_SIZE_X / 2) > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
								&& (pos.y - BULLET_BOSS_BOM_SIZE_Y / 2) < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2)
								&& (pos.y + BULLET_BOSS_BOM_SIZE_Y / 2) > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
							{
								//�X�R�A�̉��Z
								pScore->AddScore(10);
								//�{�X�Ƀ_���[�W
								pBoss->HitBoss(20);
								//�I��
								Uninit();
								return;
							}
						}
						if (objType == OBJTYPE_BOSS_LEFT)
						{
							//�G�ƒe����������
							if ((pos.x - BULLET_BOSS_BOM_SIZE_X / 2) < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
								&& (pos.x + BULLET_BOM_SIZE_X / 2) > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
								&& (pos.y - BULLET_BOSS_BOM_SIZE_Y / 2) < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2)
								&& (pos.y + BULLET_BOSS_BOM_SIZE_Y / 2) > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
							{
								//�X�R�A�̉��Z
								pScore->AddScore(10);
								//�{�X�Ƀ_���[�W
								pBoss->HitBoss(20);
								//�I��
								Uninit();
								return;
							}
						}
						if (objType == OBJTYPE_ENEMY_BULLET)
						{
							//�G�ƒe����������
							if ((pos.x - BULLET_BOSS_BOM_SIZE_X / 2) < (ScenePos.x + ENEMY_BULLET_SIZE_X / 2)
								&& (pos.x + BULLET_BOSS_BOM_SIZE_X / 2) > (ScenePos.x - ENEMY_BULLET_SIZE_X / 2)
								&& (pos.y - BULLET_BOSS_BOM_SIZE_Y / 2) < (ScenePos.y + ENEMY_BULLET_SIZE_Y / 2)
								&& (pos.y + BULLET_BOSS_BOM_SIZE_Y / 2) > (ScenePos.y - ENEMY_BULLET_SIZE_Y / 2))
							{
								//�G�̒e�̏I��
								pScene->Uninit();
								//�I��
								Uninit();
								return;
							}
						}
					}
					break;
					//�G
				case TYPE_ENEMY:
					//�e�N�X�`���̃Z�b�g
					SetTexture(0.0f, 0.0f, 1.0f,1.0f);
					//�ʏ�e�̏ꍇ
					if (m_PatternType == PATTERN_TYPE_ENEMY_NORMAL)
					{
						//�I�u�W�F�N�g���G�̏ꍇ
						if (objType == OBJTYPE_PLAYER)
						{
							//�G�ƒe����������
							if ((pos.x - BULLET_ENEMY_COLLISION_X / 2) < (ScenePos.x + PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.x + BULLET_ENEMY_COLLISION_X / 2) > (ScenePos.x - PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.y - BULLET_ENEMY_COLLISION_Y / 2) < (ScenePos.y + PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.y + BULLET_ENEMY_COLLISION_Y / 2) > (ScenePos.y - PLAYER_COLLISION_SIZE_X / 2))
							{
								pPlayer->HitPlayer();
								//�I��
								Uninit();
								return;
							}
						}
					}
					//�_������
					if (m_PatternType == PATTERN_TYPE_ENEMY_TRAKING)
					{
						//�I�u�W�F�N�g���G�̏ꍇ
						if (objType == OBJTYPE_PLAYER)
						{
							//�G�ƒe����������
							if ((pos.x - BULLET_ENEMY_COLLISION_X / 2) < (ScenePos.x + PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.x + BULLET_ENEMY_COLLISION_X / 2) > (ScenePos.x - PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.y - BULLET_ENEMY_COLLISION_Y / 2) < (ScenePos.y + PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.y + BULLET_ENEMY_COLLISION_Y / 2) > (ScenePos.y - PLAYER_COLLISION_SIZE_X / 2))
							{
								//�v���C���[�_���[�W
								pPlayer->HitPlayer();
								//�I��
								Uninit();
								return;
							}
						}
					}
					//�g��
					if (m_PatternType == PATTERN_TYPE_ENEMY_WAVE)
					{
						//�I�u�W�F�N�g���G�̏ꍇ
						if (objType == OBJTYPE_PLAYER)
						{
							//�G�ƒe����������
							if ((pos.x - BULLET_ENEMY_COLLISION_X / 2) < (ScenePos.x + PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.x + BULLET_ENEMY_COLLISION_X / 2) > (ScenePos.x - PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.y - BULLET_ENEMY_COLLISION_Y / 2) < (ScenePos.y + PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.y + BULLET_ENEMY_COLLISION_Y / 2) > (ScenePos.y - PLAYER_COLLISION_SIZE_X / 2))
							{
								//�v���C���[�_���[�W
								pPlayer->HitPlayer();
								//�I��
								Uninit();
								return;
							}
						}
					}
					break;
					//��O�̏ꍇ
				default:
					break;
					return;
				}
			}
		}
	}
	//�ǔ�
	if (m_PatternType == PATTERN_TYPE_ENEMY_TRAKING)
	{
		m_rad = m_fAngle;
	}
	//�g�U�e
	if (m_PatternType == PATTERN_TYPE_ENEMY_DIFFUSION)
	{
		m_nDifCount++;
		if (m_nDifCount >= 80)
		{
			for (int nCount = 0; nCount < 20; nCount++)
			{
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(cosf(D3DXToRadian(nCount * (360 / 20)))*5.0f, sinf(D3DXToRadian(nCount * (360 / 20)))*5.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_NORMAL, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
			}
			//�I��
			Uninit();
			return;
		}
	}

	//�r�[���̏ꍇ
	if (m_PatternType == PATTERN_TYPE_BEAM)
	{
		//false�̏ꍇ
		if (m_bUseBeam == false)
		{
			//�I��
			Uninit();
			return;
		}
	}
	//�{���̏ꍇ
	if (m_PatternType == PATTERN_TYPE_BOSS_BOM)
	{
		//false�̏ꍇ
		if (m_bUseBom == false)
		{
			//�I��
			Uninit();
			return;
		}
	}
	//�v���C���[�A�����_���A�m�[�}���̏ꍇ
	if (m_type == TYPE_PLAYER || m_PatternType == PATTERN_TYPE_ENEMY_DIFFUSION || m_PatternType == PATTERN_TYPE_ENEMY_NORMAL)
	{
		//�ʒu�X�V
		pos.x += m_move.x;
		pos.y += m_move.y;
	}
	//�����_��2
	if (m_PatternType == PATTERN_TYPE_ENEMY_TRAKING)
	{
		//�ʒu�X�V
		pos.x += m_move.x * cosf(m_rad);
		pos.y += m_move.y * sinf(m_rad);
	}
	//�g��
	if (m_PatternType == PATTERN_TYPE_ENEMY_WAVE)
	{
		//false�̏ꍇ
		if (m_bWavemove == false)
		{
			m_nMinMove -= 0.5f;
		}
		//
		if (m_nMinMove == -7.0f)
		{
			m_bWavemove = true;
			m_nMinMove = 0;
		}
		if (m_bWavemove == true)
		{
			m_nMinMove += 0.5f;
		}
		if (m_nMinMove == 7.0f)
		{
			m_bWavemove = false;
			m_nMinMove = 0;
		}
		//�ʒu�X�V
		pos.x += m_move.x + m_nMinMove;
		pos.y += m_move.y;
	}
	//�e�N�X�`��
	if (m_textype == TEX_TYPE_BEAM || m_textype == TEX_TYPE_NORMAL || m_type == TYPE_ENEMY)
	{
		//�e�N�X�`���̐ݒ�
		SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
	}
	//�{���̏ꍇ
	if (m_PatternType == PATTERN_TYPE_BOM)
	{
		m_nBom_Anim_Count++;
		//�J�E���g��4�ȏ�ɂȂ�����
		if (m_nBom_Anim_Count > 4)
		{
			m_nBom_Anim_Count = 0;
			//�p�^�[����4�ȉ��̏ꍇ
			if (m_nPattern_Bom_Anim <= 4)
			{
				//�e�N�X�`���ݒ�
				SetTexture(m_nPattern_Bom_Anim * 0.2f, 0.0, 0.2f, 0.5f);
			}
			//�p�^�[����5�ȏ�̏ꍇ
			if (m_nPattern_Bom_Anim >= 5)
			{
				//�e�N�X�`���̐ݒ�
				SetTexture(m_nPattern_Bom_Anim * 0.2f, 0.5, 0.2f, 1.0f);

			}
			//�p�^�[���̃C���N�������g
			m_nPattern_Bom_Anim++;
		}
		//�p�^�[����10�ȏ�ɂȂ�����
		if (m_nPattern_Bom_Anim >= 10)
		{
			//�I������
			Uninit();
			return;
		}
	}
	if (nPlayerState == CPlayer::STATE_DEAD)
	{
		Uninit();
		return;
	}
	//�ʒu�X�V
	SetPosition(pos);
	//��ʊO
	if (pos.x > MAX_GAME_WIDTH || pos.x < MIN_GAME_WIDTH || pos.y > SCREEN_HEIGHT || pos.y < 0)
	{
		//�I��
		Uninit();
		return;
	}
}
//---------------------------------------------------
//�`��
//---------------------------------------------------
void CBullet::Draw(void)
{
	//�`��
	CScene2d::Draw();
}
//---------------------------------------------------
//�r�[���̎g�p��Ԃ̎擾
//---------------------------------------------------
void CBullet::SetUseBeam(bool bUseBeam)
{
	m_bUseBeam = bUseBeam;
}
//---------------------------------------------------
//�{���̎g�p��Ԃ̎擾
//---------------------------------------------------
void CBullet::SetUseBom(bool bUseBom)
{
	m_bUseBom = bUseBom;
}