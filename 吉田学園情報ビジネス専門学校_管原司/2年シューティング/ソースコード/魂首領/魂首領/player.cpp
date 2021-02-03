//******************************************************************************
// ���@ [player.cpp]
// Author : �ǌ��@�i
//******************************************************************************
#define	_CRT_SECURE_NO_WARNINGS	//scanf�G���[
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
#include "normal_bullet.h"
#include "player_beam.h"
#include "sound.h"
#include "life.h"
#include "game.h"
#include "explosion.h"
#include "bomui.h"
#include "continue.h"
#include "bom.h"
#include "score.h"
#include "boss_bom.h"
#include <stdio.h>
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BULLET_NORMAL_MOVE_VALUE		(D3DXVECTOR3(0.0f,15.0f,0.0f))
#define WEPON_BULLET_NORMAL_MOVE_VALUE	(D3DXVECTOR3(7.5f,15.0f,0.0f))
#define BEAM_BULLET_MOVE_VALUE			(D3DXVECTOR3(0.0f,15.0f,0.0f))
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[TYPE_MAX] = {};
//******************************************************************************
// �e�N�X�`���ǂݍ��݊֐�
//******************************************************************************
HRESULT CPlayer::Load(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Player003.png", &m_apTexture[TYPE_MAIN]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Player002.png", &m_apTexture[TYPE_RIGHT]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Player002.png", &m_apTexture[TYPE_LEFT]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j���֐�
//******************************************************************************
void CPlayer::Unload(void)
{
	// �ő吔���J��Ԃ�
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			// m_apTexture��Release
			m_apTexture[nCnt]->Release();
			// m_apTexture��NULL
			m_apTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_MainPos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RightPos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LeftPos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Collision_Size		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nContinue				= 0;
	m_nLife					= 0;
	m_nCountAnim			= 0;
	m_nCountAnimWepon		= 0;
	m_nPatternAnim			= 0;
	m_nPatternAnimWepon		= 0;
	m_AttackCount			= 0;
	m_nBeamCount			= 0;
	m_nDamageCount			= 0;
	m_nRespawnCount			= 0;
	m_nNoDamageCount		= 0;
	m_nBomCount				= 0;
	m_nBom_possession_count	= 0;
	m_nPlayerState			= STATE_NONE;
	m_Level					= LEVEL_NONE;
	m_bMove					= false;
	m_bUseBeam				= false;
	m_bUseBom				= false;
	m_bBoss					= false;
	m_bContinue				= false;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CPlayer::~CPlayer()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPlayer�N���X�̃|�C���^
	CPlayer * pPlayer;

	// �������m��
	pPlayer = new CPlayer;

	// pos���
	pPlayer->m_MainPos = pos;

	// �T�C�Y���
	pPlayer->m_Size = size;

	// ������
	pPlayer->Init();

	// pPlayer��Ԃ�
	return pPlayer;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CPlayer::Init(void)
{
	// �v���C���[�̃X�e�[�g�m�[�}��
	m_nPlayerState = STATE_NORMAL;
	// �����蔻��T�C�Y
	m_Collision_Size = PLAYER_COLLISION_SIZE;
	// ���x��1
	m_Level = LEVEL_1;
	// �̗�
	m_nLife = PLAYER_LIFE;

	// �������m��
	m_apScene2D[TYPE_MAIN] = new CScene2d;
	m_apScene2D[TYPE_RIGHT] = new CScene2d;
	m_apScene2D[TYPE_LEFT] = new CScene2d;

	// �ʒu���W�ݒ�
	m_apScene2D[TYPE_MAIN]->SetPosition(m_MainPos);
	m_apScene2D[TYPE_RIGHT]->SetPosition(D3DXVECTOR3(m_MainPos.x + 40, m_MainPos.y + 40, m_MainPos.z));
	m_apScene2D[TYPE_LEFT]->SetPosition(D3DXVECTOR3(m_MainPos.x - 40, m_MainPos.y + 40, m_MainPos.z));

	// �ʒu���W�ݒ�
	m_apScene2D[TYPE_MAIN]->SetSize(m_Size);
	m_apScene2D[TYPE_RIGHT]->SetSize(PLAYER_WEPON_SIZE);
	m_apScene2D[TYPE_LEFT]->SetSize(PLAYER_WEPON_SIZE);

	// RGBA�̐ݒ�
	m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �e�N�X�`���̎󂯓n��
	m_apScene2D[TYPE_MAIN]->BindTexture(m_apTexture[TYPE_MAIN]);
	m_apScene2D[TYPE_RIGHT]->BindTexture(m_apTexture[TYPE_RIGHT]);
	m_apScene2D[TYPE_LEFT]->BindTexture(m_apTexture[TYPE_LEFT]);

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	m_apScene2D[TYPE_MAIN]->SetObjType(OBJTYPE_PLAYER);
	m_apScene2D[TYPE_RIGHT]->SetObjType(OBJTYPE_PLAYER_WEPON);
	m_apScene2D[TYPE_LEFT]->SetObjType(OBJTYPE_PLAYER_WEPON);

	// ������
	m_apScene2D[TYPE_MAIN]->Init();
	m_apScene2D[TYPE_RIGHT]->Init();
	m_apScene2D[TYPE_LEFT]->Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CPlayer::Uninit(void)
{
	// �I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CPlayer::Update(void)
{
	// State���֌W���Ă��鏈��
	PlayerState();
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CPlayer::Draw(void)
{
}
//******************************************************************************
// �q�b�g�����֐�
//******************************************************************************
void CPlayer::HitPlayer(void)
{
	// ��Ԃ��m�[�}���̏ꍇ
	if (m_nPlayerState == STATE_NORMAL)
	{
		// �T�E���h�擾
		CSound * pSound = CSceneManager::GetSound();
		CSound::SOUND_LABEL type;
		type = CSound::SOUND_LABEL_SE_SHOT;

		// ����������
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

		// ���C�t�̎擾
		CLife * pLife = CGame::GetLife();

		// ���C�t���Z
		m_nLife--;

		// ���C�tUI�̌��Z
		pLife->HitDamage(1);

		// �����̐���
		CExplosion::Create(m_MainPos, EXPLOSION_SIZE);

		// �ʒu���W�ݒ�
		m_apScene2D[TYPE_MAIN]->SetPosition(D3DXVECTOR3(-100.0f, -100.0f, 0.0f));

		// State��Respawn��
		m_nPlayerState = STATE_RESPAWN;
	}
}
//******************************************************************************
// �{�����菈���֐�
//******************************************************************************
void CPlayer::GetBom(int nBom)
{
	// �{���擾
	CBomUI * pBom = CGame::GetBomUI();
	// �X�R�A�擾
	CScore * pScore = CGame::GetScore();

	// �{���̏������̉��Z���Z
	if (m_nBom_possession_count >= 0 && m_nBom_possession_count <= MAX_BOM_POSSESION)
	{
		m_nBom_possession_count += nBom;
		pBom->SetBomUI(m_nBom_possession_count);
	}

	// �{���̏�������MAX�̏ꍇ
	if (m_nBom_possession_count >= MAX_BOM_POSSESION)
	{
		// �X�R�A���Z
		pScore->AddScore(5000);
	}
}
//******************************************************************************
// �p���[�A�b�v�����֐�
//******************************************************************************
void CPlayer::GetPowerUp(void)
{
	CScore * pScore = CGame::GetScore();
	// ���x����3���Ⴂ�ꍇ
	if (m_Level < LEVEL_3)
	{
		// ���x���A�b�v
		m_Level++;
	}
	// ���x����3�̏ꍇ
	if (m_Level == LEVEL_3)
	{
		// �X�R�A���Z
		pScore->AddScore(3000);
	}
}
//******************************************************************************
// �R���e�B�j���[�����֐�
//******************************************************************************
void CPlayer::SetContinue(int Continue)
{
	m_nContinue = Continue;
}
//******************************************************************************
// �v���C���[��񏑂����݊֐�
//******************************************************************************
void CPlayer::SavePlayer(void)
{
	FILE * pFile;
	// �t�@�C���̏����o��
	pFile = fopen("player.txt", "w");
	// �t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		// �X�R�A��������
		fprintf(pFile, "%d\n", m_nScore);
		// �t�@�C�������
		fclose(pFile);
	}
}
//******************************************************************************
// �{�X��p�{�������֐�
//******************************************************************************
void CPlayer::SetBossBom(bool bBoss)
{
	m_bBoss = bBoss;
}
//******************************************************************************
// �ړ������֐�
//******************************************************************************
void CPlayer::Move(void)
{
	// �ړ�
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	// �L�[�{�[�h�擾
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();
	// �R���g���[���[�擾
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// ��
	if (g_lpDIDevice != NULL &&js.lY <= -500 || pInputKeyboard->GetKeyboardPress(DIK_W))
	{
		//false��
		m_bMove = false;

		// �r�[���𔭎˂��Ă鎞
		if (m_bUseBeam == true)
		{
			// �ړ�
			move.y = -PLAYER_BEAM_MOVE.y;
		}
		// �r�[���𔭎˂��ĂȂ���
		else
		{
			// �ړ�
			move.y = -PLAYER_MOVE.y;
		}
	}
	// ��
	if (g_lpDIDevice != NULL &&js.lY >= 500 || pInputKeyboard->GetKeyboardPress(DIK_S))
	{
		// false��
		m_bMove = false;

		// �r�[���𔭎˂��Ă鎞
		if (m_bUseBeam == true)
		{
			// �ړ�
			move.y = PLAYER_BEAM_MOVE.y;
		}
		// �r�[���𔭎˂��ĂȂ���
		else
		{
			// �ړ�
			move.y = PLAYER_MOVE.y;
		}
	}
	// ��
	if (g_lpDIDevice != NULL &&js.lX <= -500 || pInputKeyboard->GetKeyboardPress(DIK_A))
	{
		// true��
		m_bMove = true;

		// �r�[���𔭎˂��Ă���ꍇ
		if (m_bUseBeam == true)
		{
			// �ړ�
			move.x = -PLAYER_BEAM_MOVE.x;
		}
		// �r�[���𔭎˂��ĂȂ��ꍇ
		else
		{
			// �ړ�
			move.x = -PLAYER_MOVE.x;
		}
		// �A�j���[�V������1��
		m_nPatternAnim = 1;
		// �J�E���g��10���傫���ꍇ
		if (m_nCountAnim > 10)
		{
			// �A�j���[�V������0��
			m_nPatternAnim = 0;
		}
	}
	// ���Ɉړ����ĂȂ���
	else
	{
		m_bMove = false;
	}
	//�E
	if (g_lpDIDevice != NULL &&js.lX >= 500 || pInputKeyboard->GetKeyboardPress(DIK_D))
	{
		// m_bMove��true��
		m_bMove = true;

		// �r�[���𔭎˂��Ă���ꍇ
		if (m_bUseBeam == true)
		{
			move.x = PLAYER_BEAM_MOVE.x;
		}
		// �r�[���𔭎˂��Ă��Ȃ��ꍇ
		else
		{
			move.x = PLAYER_MOVE.x;
		}
		// �A�j���[�V����
		m_nPatternAnim = 4;
		if (m_nCountAnim > 10)
		{
			m_nPatternAnim = 5;
		}
	}
	// �E�Ɉړ����ĂȂ���
	else
	{
		m_bMove = false;
	}

	// �ʒu�X�V
	m_MainPos.x += move.x;
	m_MainPos.y += move.y;

	// ����
	move.x += (0.0f - move.x) * RATE_MOVE;
	move.y += (0.0f - move.y) * RATE_MOVE;

	// state��Normal�܂���Damage�̎�
	if (m_nPlayerState == STATE_NORMAL || m_nPlayerState == STATE_DAMAGE)
	{
		// ���ʊO�ɏo���Ƃ�
		if (m_MainPos.y - PLAYER_SIZE.y < 0)
		{
			// �v���C���[�̃T�C�Y�����炷
			m_MainPos.y = PLAYER_SIZE.y;
		}
		// �����v���C���[������ʊO�ɍs������
		if (m_MainPos.y + PLAYER_SIZE.y > SCREEN_HEIGHT)
		{
			// �v���C���[�̃T�C�Y�����炷
			m_MainPos.y = SCREEN_HEIGHT - PLAYER_SIZE.y;
		}
		// �����v���C���[������ʊO�ɍs������
		if (m_MainPos.x - PLAYER_SIZE.x - PLAYER_WEPON_SIZE.x / 2 < MIN_GAME_WIDTH)
		{
			// �v���C���[�ƕ���̃T�C�Y�����炷
			m_MainPos.x = MIN_GAME_WIDTH + PLAYER_SIZE.x + PLAYER_WEPON_SIZE.x / 2;
		}
		// �����v���C���[���E��ʊO�ɍs������
		if (m_MainPos.x + PLAYER_SIZE.x + PLAYER_WEPON_SIZE.x / 2 > MAX_GAME_WIDTH)
		{
			// �v���C���[�ƕ���̃T�C�Y�����炷
			m_MainPos.x = MAX_GAME_WIDTH - PLAYER_SIZE.x - PLAYER_WEPON_SIZE.x / 2;
		}
	}
	// �ʒu�ݒ�
	m_apScene2D[TYPE_MAIN]->SetPosition(m_MainPos);
}
//******************************************************************************
// �e���ˏ����֐�
//******************************************************************************
void CPlayer::Shot(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();
	// �R���g���[���[�擾
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	// �T�E���h�擾
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;

	//*****************************************************************
	// �m�[�}���e�̏���
	//*****************************************************************

	// �{�����g�p���ĂȂ��ꍇ
	if (m_bUseBom == false)
	{
		// �r�[�����g�p���ĂȂ��ꍇ
		if (m_bUseBeam == false)
		{
			// �r�[��
			// SPACE�������܂��̓R���g���[���[A�{�^��
			if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_SPACE))
			{
				// �V���b�g��
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

				// �v���C���[���x����1�̏ꍇ
				if (m_Level == LEVEL_1)
				{
					// �e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(m_MainPos), 
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
						BULLET_LEVEL1_SIZE, 
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
						, CBullet::TEX_TYPE_NORMAL);

					CNormal_Bullet::Create(D3DXVECTOR3(m_RightPos),
						D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-30.0f)),
						BULLET_LEVEL1_SIZE, 
						D3DXVECTOR3(WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_NORMAL);

					CNormal_Bullet::Create(D3DXVECTOR3(m_LeftPos),
						D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)),
						BULLET_LEVEL1_SIZE,
						D3DXVECTOR3(-WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
						, CBullet::TEX_TYPE_NORMAL);
				}
				// �v���C���[���x����2�̏ꍇ
				if (m_Level == LEVEL_2)
				{
					// �e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(m_MainPos),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL2_SIZE, 
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_NORMAL);

					CNormal_Bullet::Create(D3DXVECTOR3(m_RightPos),
						D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-30.0f)),
						BULLET_LEVEL2_SIZE,
						D3DXVECTOR3(WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_NORMAL);

					CNormal_Bullet::Create(D3DXVECTOR3(m_LeftPos),
						D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)),
						BULLET_LEVEL2_SIZE, 
						D3DXVECTOR3(-WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_NORMAL);
				}
				// �v���C���[���x����3�̏ꍇ
				if (m_Level == LEVEL_3)
				{
					// �e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(m_MainPos),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL3_SIZE,
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_NORMAL);

					CNormal_Bullet::Create(D3DXVECTOR3(m_RightPos),
						D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-30.0f)),
						BULLET_LEVEL3_SIZE,
						D3DXVECTOR3(WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_NORMAL);

					CNormal_Bullet::Create(D3DXVECTOR3(m_LeftPos),
						D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)),
						BULLET_LEVEL3_SIZE, 
						D3DXVECTOR3(-WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_NORMAL);
				}
			}
		}

		//*****************************************************************
		// �r�[�����˂̏���
		//*****************************************************************

		//�r�[��
		//SPACE�������܂��̓R���g���[���[A�{�^��
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickPress(JS_A) || pInputKeyboard->GetKeyboardPress(DIK_SPACE))
		{
			//�r�[���J�E���g�C���N�������g
			m_nBeamCount++;
			//�J�E���g��20�ȏ�̎�
			if (m_nBeamCount >= 20)
			{
				//�r�[����bool��true��
				m_bUseBeam = true;
			}
		}
		// SPACE�܂��̓R���g���[��A�{�^���𗣂����Ƃ�
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickRelease(JS_A) || pInputKeyboard->GetKeyboardRelease(DIK_SPACE))
		{
			// �J�E���g��0��
			m_nBeamCount = 0;
			// �r�[��bool��false��
			m_bUseBeam = false;
			// �r�[���̎g�p��Ԃ�ݒ�
			CPlayer_Beam::SetUseBeam(m_bUseBeam);
		}
		// �r�[����bool��true�̎�
		if (m_bUseBeam == true)
		{
			// �J�E���g�C���N�������g
			m_AttackCount++;
			// �����pos�����@�̑O��
			m_apScene2D[TYPE_RIGHT]->SetPosition(D3DXVECTOR3(m_MainPos.x + 15, m_MainPos.y - 40, m_MainPos.z));
			m_apScene2D[TYPE_LEFT]->SetPosition(D3DXVECTOR3(m_MainPos.x - 15, m_MainPos.y - 40, m_MainPos.z));
			//�J�E���g��2���܂�0�̎�
			if (m_AttackCount % 2 == 0)
			{
				// �V���b�g������
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
				// player���x����1�̎�
				if (m_Level == LEVEL_1)
				{
					// �e����
					CPlayer_Beam::Create(D3DXVECTOR3(m_MainPos.x, m_MainPos.y - 45, m_MainPos.z), 
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL1_BEAM_SIZE,
						D3DXVECTOR3(BEAM_BULLET_MOVE_VALUE.x, -BEAM_BULLET_MOVE_VALUE.y, BEAM_BULLET_MOVE_VALUE.z),
						D3DXCOLOR (1.0f,1.0f,1.0f,1.0f),
						CBullet::TEX_TYPE_BEAM);
				}
				// player���x����2�̎�
				if (m_Level == LEVEL_2)
				{
					// �e����
					CPlayer_Beam::Create(D3DXVECTOR3(m_MainPos.x, m_MainPos.y - 45, m_MainPos.z),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL2_BEAM_SIZE,
						D3DXVECTOR3(BEAM_BULLET_MOVE_VALUE.x, -BEAM_BULLET_MOVE_VALUE.y, BEAM_BULLET_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_BEAM);
				}
				// player���x����3�̎�
				if (m_Level == LEVEL_3)
				{
					// �e����
					CPlayer_Beam::Create(D3DXVECTOR3(m_MainPos.x, m_MainPos.y - 45, m_MainPos.z),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL3_BEAM_SIZE,
						D3DXVECTOR3(BEAM_BULLET_MOVE_VALUE.x, -BEAM_BULLET_MOVE_VALUE.y, BEAM_BULLET_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_BEAM);
				}
			}
		}
		// �r�[�����g�p���ĂȂ���
		else
		{
			// �ʒu�ݒ�
			m_apScene2D[TYPE_RIGHT]->SetPosition(D3DXVECTOR3(m_MainPos.x + 40, m_MainPos.y + 40, m_MainPos.z));
			m_apScene2D[TYPE_LEFT]->SetPosition(D3DXVECTOR3(m_MainPos.x - 40, m_MainPos.y + 40, m_MainPos.z));
		}
		// �L�[�{�[�h��B�܂��̓R���g���[����B�{�^�����������ꍇ
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_B) || pInputKeyboard->GetKeyboardTrigger(DIK_B))
		{
			// �{����������0��葽���ꍇ
			if (m_nBom_possession_count > 0)
			{
				// �{��bool��true��
				m_bUseBom = true;
			}
		}
	}

	// �{�����g�p���̏ꍇ
	if (m_bUseBom == true)
	{
		// �{���̏��������Z
		GetBom(-1);
		// �{�X��łȂ���
		if (m_bBoss == false)
		{
			// ����������
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BOM);
			// �{������
			CBom::Create(BOM_POS, BOM_ROT, BOM_SIZE,CBullet::TEX_TYPE_BOM);
			m_bUseBom = false;
		}
		// �{�X��̎�
		if (m_bBoss == true)
		{
			// �{���̃J�E���g���C���N�������g
			m_nBomCount++;

			// �����pos�����@�̑O��
			m_apScene2D[TYPE_RIGHT]->SetPosition(D3DXVECTOR3(m_MainPos.x + 15, m_MainPos.y - 40, m_MainPos.z));
			m_apScene2D[TYPE_LEFT]->SetPosition(D3DXVECTOR3(m_MainPos.x - 15, m_MainPos.y - 40, m_MainPos.z));

			// 2���܂�0�̎�
			if (m_nBomCount % 2 == 0)
			{
				// �r�[��������
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
				// �e�̐���
				CBoss_Bom::Create(D3DXVECTOR3(m_MainPos.x, m_MainPos.y - 45, m_MainPos.z),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					BOSS_BOM_SIZE,
					D3DXVECTOR3(BEAM_BULLET_MOVE_VALUE.x, -BEAM_BULLET_MOVE_VALUE.y, BEAM_BULLET_MOVE_VALUE.z),
					CBullet::TEX_TYPE_BEAM);
			}
			// �J�E���g��200�ȏ�ɂȂ�����
			if (m_nBomCount >= BOM_LAUNCH_TIME)
			{
				// �{���̎g�p��Ԃ�false��
				m_bUseBom = false;
				// �{���̎g�p��Ԃ�ݒ�
				CBoss_Bom::SetUseBoss_Bom(m_bUseBom);
				// �{���̃J�E���g��0��
				m_nBomCount = 0;
			}
		}
	}
}

//******************************************************************************
// �v���C���[�̏�ԏ����֐�
//******************************************************************************
void CPlayer::PlayerState(void)
{
	//���S��ԂłȂ���
	if (m_nPlayerState != STATE_DEAD)
	{
		// �X�V
		m_apScene2D[TYPE_MAIN]->Update();
		m_apScene2D[TYPE_RIGHT]->Update();
		m_apScene2D[TYPE_LEFT]->Update();

		//���@�̒��S
		m_MainPos = m_apScene2D[TYPE_MAIN]->GetPosition();
		//���@�̉E
		m_RightPos = m_apScene2D[TYPE_RIGHT]->GetPosition();
		//���@�̍�
		m_LeftPos = m_apScene2D[TYPE_LEFT]->GetPosition();

		//�ʒu�ݒ�
		m_apScene2D[TYPE_RIGHT]->SetPosition(D3DXVECTOR3(m_MainPos.x + 40, m_MainPos.y + 40, m_MainPos.z));
		m_apScene2D[TYPE_LEFT]->SetPosition(D3DXVECTOR3(m_MainPos.x - 40, m_MainPos.y + 40, m_MainPos.z));

		//�e�N�X�`���X�V
		m_apScene2D[TYPE_MAIN]->SetTexture(m_nPatternAnim * 0.2f, 0.0f, 0.2f, 1.0f);
		m_apScene2D[TYPE_RIGHT]->SetTexture(m_nPatternAnimWepon * 0.25f, 0.0f, 0.25f, 1.0f);
		m_apScene2D[TYPE_LEFT]->SetTexture(m_nPatternAnimWepon * 0.25f, 0.0f, 0.25f, 1.0f);
	
		//�X�R�A�擾
		CScore * pScore = CGame::GetScore();
		m_nScore = pScore->GetScore();

		// �v���C���[�̏����O���t�@�C���ɏ�������
		SavePlayer();

		// �ړ�����
		Move();

		// �e���ˏ���
		Shot();

		//�J�E���g�C���N�������g
		m_nCountAnimWepon++;

		//�J�E���g��25�ȏ�ɂȂ����ꍇ
		if (m_nCountAnimWepon > 7)
		{
			m_nCountAnimWepon = 0;
			//�p�^�[����0�ȏ�̏ꍇ
			if (m_nPatternAnim >= 0)
			{
				//�p�^�[�����C���N�������g
				m_nPatternAnimWepon++;
			}
		}
		//���E�ړ����ĂȂ���
		if (m_bMove == false)
		{
			//�A�j���[�V�����p�^�[����2�ɂ���
			m_nPatternAnim = 2;
		}

		//�ʏ���
		if (m_nPlayerState == STATE_NORMAL)
		{
			//�J���[�ݒ�
			m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		//���X�|�[�����
		if (m_nPlayerState == STATE_RESPAWN)
		{
			//�J�E���g�C���N�������g
			m_nRespawnCount++;
			//�J�E���g��30�ɂȂ����Ƃ�
			if (m_nRespawnCount == DAMAGE_RESPAWN_COUNT)
			{
				// �_���[�W��Ԃ�
				m_nPlayerState = STATE_DAMAGE;

				// ���X�|���ʒu�ݒ�
				m_apScene2D[TYPE_MAIN]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f));

				// �J�E���g��0��
				m_nRespawnCount = 0;
			}
		}
		// �_���[�W���
		if (m_nPlayerState == STATE_DAMAGE)
		{
			// �J�E���g�C���N�������g
			m_nDamageCount++;
			// �_���[�W�̃J�E���g��10�ɂȂ�����
			if (m_nDamageCount % 5 == 0)
			{
				// �J���[�ݒ�
				m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			// �_���[�W�̃J�E���g��20�ɂȂ�����
			if (m_nDamageCount % 6 == 0)
			{
				// �J���[�ݒ�
				m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_nNoDamageCount = 0;
			}
			// ���G���Ԃ��I��������
			if (m_nDamageCount == DAMAGE_COUNT)
			{
				m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				// state��Normal��
				m_nPlayerState = STATE_NORMAL;
				// �J�E���g��0��
				m_nDamageCount = 0;
			}
		}
		// �R���e�B�j���[��Ԃ�false�̎�
		if (m_bContinue == false)
		{
			// ���C�t��0�ȉ��̎�
			if (m_nLife <= 0)
			{
				// �R���e�B�j���[��Ԃ�true��
				m_bContinue = true;
			}
		}
		// �R���e�B�j���[��Ԃ�true��
		if (m_bContinue == true)
		{
			// ���S��Ԃ�
			m_nPlayerState = STATE_DEAD;
			// �R���e�B�j���[���� 
			CContinue::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CONTINUE_SIZE);
		}
	}
	// ���S��Ԃ̏ꍇ
	if (m_nPlayerState == STATE_DEAD)
	{
		// ��ʊO�Ɉړ�������
		m_apScene2D[TYPE_MAIN]->SetPosition(D3DXVECTOR3(-100.0f, -100.0f, 0.0f));
		// �R���e�B�j���[�����ꍇ
		if (m_nContinue == PLAYER_CONTINUE)
		{
			// �X�R�A�擾
			CScore * pScore = CGame::GetScore();
			pScore->AddScore(-3000);

			// ���C�t�̎擾
			CLife * pLife = CGame::GetLife();

			//���C�t��3��
			m_nLife = PLAYER_LIFE;

			//���C�t��ݒ�
			pLife->AddLife(m_nLife);

			//�{���̏�������3��
			GetBom(3);

			//�R���e�B�j���[��Ԃ�false��
			m_bContinue = false;
			m_nContinue = 0;
			m_nPlayerState = STATE_RESPAWN;
		}
	}
}