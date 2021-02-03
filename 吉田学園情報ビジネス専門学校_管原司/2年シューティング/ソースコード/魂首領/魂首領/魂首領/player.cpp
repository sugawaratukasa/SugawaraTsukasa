//******************************************************************************
// ���@ [player.cpp]
// Author : �ǌ��@�i
//******************************************************************************
#define	_CRT_SECURE_NO_WARNINGS	//scanf�G���[
//******************************************************************************
// �C���N���[�h�t�@�C��
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
#include "player_wepon.h"
#include "bullet.h"
#include "normal_bullet.h"
#include "player_beam.h"
#include "sound.h"
#include "life.h"
#include "game.h"
#include "bomui.h"
#include "continue.h"
#include "bom.h"
#include "score.h"
#include "boss_bom.h"
#include "particle.h"
#include "particle_explosion.h"
#include <stdio.h>
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BULLET_NORMAL_MOVE_VALUE	(D3DXVECTOR3(0.0f,15.0f,0.0f))		// �ʏ�e�ړ���
#define BEAM_BULLET_MOVE_VALUE		(D3DXVECTOR3(0.0f,15.0f,0.0f))		// �r�[���ړ���
#define INIT_VARIABLE				(0)									// �ϐ�0������
#define COLOR						(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �J���[
#define JOYSTICK_DICISION			(500)								// �W���C�X�e�B�b�N����l
#define EXPLOSION_SIZE				(D3DXVECTOR3(3.0f,3.0f,0.0f))		// �����T�C�Y
#define PLAYER_SIZE					(D3DXVECTOR3(50.0f,50.0f,0.0f))	// �v���C���[�T�C�Y
#define PLAYER_COLLISION_SIZE		(D3DXVECTOR3(5.0f,5.0f,0.0f))	// �v���C���[����T�C�Y
#define PLAYER_MOVE					(D3DXVECTOR3(8.0f,8.0f,0.0f))	// �v���C���[�T�C�Y
#define PLAYER_BEAM_MOVE			(D3DXVECTOR3(5.0f,5.0f,0.0f))	// �v���C���[�r�[���T�C�Y
#define PLAYER_COLLISION_SIZE		(D3DXVECTOR3(5.0f,5.0f,0.0f))	// �v���C���[����T�C�Y
#define RATE_MOVE					(0.4f)							// �����̈ړ���
#define DAMAGE_RESPAWN_COUNT		(30)							// �_���[�W���X�|���J�E���g
#define NODAMAGE_COUNT				(50)							// ���G����
#define DAMAGE_COUNT				(300)							// �_���[�W�J�E���g
#define BOM_LAUNCH_TIME				(200)							// �{���̑ҋ@����
#define MAX_BOM_POSSESION			(5)								// �{���̍ő及����
#define PLAYER_LIFE					(3)								// �v���C���[���C�t
#define PLAYER_CONTINUE				(1)								// �v���C���[�̃R���e�B�j���[
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
//******************************************************************************
// �e�N�X�`���ǂݍ��݊֐�
//******************************************************************************
HRESULT CPlayer::Load(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Player/Player003.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j���֐�
//******************************************************************************
void CPlayer::Unload(void)
{
		// �e�N�X�`���̔j��
		if (m_pTexture != NULL)
		{
			// �e�N�X�`���̂�Release
			m_pTexture->Release();
			// �e�N�X�`���̂�NULL
			m_pTexture= NULL;
		}
}
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPlayer::CPlayer(int nPriority) : CScene2d(nPriority)
{
	m_nContinue				= INIT_VARIABLE;
	m_nLife					= INIT_VARIABLE;
	m_nCountAnim			= INIT_VARIABLE;
	m_nPatternAnim			= INIT_VARIABLE;
	m_AttackCount			= INIT_VARIABLE;
	m_nBeamCount			= INIT_VARIABLE;
	m_nDamageCount			= INIT_VARIABLE;
	m_nRespawnCount			= INIT_VARIABLE;
	m_nBomCount				= INIT_VARIABLE;
	m_nBom_possession_count = INIT_VARIABLE;
	m_nPlayerState			= STATE_NONE;
	m_Level					= LEVEL_NONE;
	m_bMove					= false;
	m_bUseShot				= false;
	m_bUseBeam				= false;
	m_bUseBom				= false;
	m_bBossBom				= false;
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
	pPlayer->SetPosition(pos);

	// �T�C�Y���
	pPlayer->SetSize(size);

	// �J���[�ݒ�
	pPlayer->SetRGBA(COLOR);

	// �e�N�X�`���ݒ�
	pPlayer->BindTexture(m_pTexture);

	// �I�u�W�F�N�g�^�C�v�ݒ�
	pPlayer->SetObjType(OBJTYPE_PLAYER);

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

	// ���퐶��
	// ��
	CPlayer_Wepon::Create(D3DXVECTOR3(-PLAYER_WEPON_POS.x, PLAYER_WEPON_POS.y, PLAYER_WEPON_POS.z), PLAYER_WEPON_SIZE, CPlayer_Wepon::TYPE_LEFT);

	// �E
	CPlayer_Wepon::Create(D3DXVECTOR3(PLAYER_WEPON_POS.x, PLAYER_WEPON_POS.y, PLAYER_WEPON_POS.z), PLAYER_WEPON_SIZE, CPlayer_Wepon::TYPE_RIGHT);

	// ������
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CPlayer::Uninit(void)
{
	// �I��
	CScene2d::Uninit();
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
	// �`��
	CScene2d::Draw();
}
//******************************************************************************
// �q�b�g�����֐�
//******************************************************************************
void CPlayer::HitPlayer(void)
{
	// ��Ԃ��m�[�}���̏ꍇ
	if (m_nPlayerState == STATE_NORMAL)
	{
		// �ʒu���W�擾
		D3DXVECTOR3 pos = GetPosition();

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
		CParticle_Explosion::CreateExplosionEffect(pos, EXPLOSION_SIZE, CParticle_Explosion::TYPE_PLAYER);

		// �ʒu���W�ݒ�
		SetPosition(D3DXVECTOR3(-100.0f, -100.0f, 0.0f));

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
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

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

	//���E�ړ����ĂȂ���
	if (m_bMove == false)
	{
		//�A�j���[�V�����p�^�[����2�ɂ���
		m_nPatternAnim = 2;
	}

	// ��
	if (g_lpDIDevice != NULL &&js.lY <= -JOYSTICK_DICISION || pInputKeyboard->GetKeyboardPress(DIK_W))
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
	if (g_lpDIDevice != NULL &&js.lY >= JOYSTICK_DICISION || pInputKeyboard->GetKeyboardPress(DIK_S))
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
	if (g_lpDIDevice != NULL &&js.lX <= -JOYSTICK_DICISION || pInputKeyboard->GetKeyboardPress(DIK_A))
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

		// �A�j���[�V������0��
		m_nPatternAnim = 0;
	}
	// ���Ɉړ����ĂȂ���
	else
	{
		m_bMove = false;
	}

	//�E
	if (g_lpDIDevice != NULL &&js.lX >= JOYSTICK_DICISION || pInputKeyboard->GetKeyboardPress(DIK_D))
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
	}
	// �E�Ɉړ����ĂȂ���
	else
	{
		m_bMove = false;
	}

	// �ʒu�X�V
	pos.x += move.x;
	pos.y += move.y;

	// ����
	move.x += (0.0f - move.x) * RATE_MOVE;
	move.y += (0.0f - move.y) * RATE_MOVE;

	// state��Normal�܂���Damage�̎�
	if (m_nPlayerState == STATE_NORMAL || m_nPlayerState == STATE_DAMAGE)
	{
		// ���ʊO�ɏo���Ƃ�
		if (pos.y - PLAYER_SIZE.y < 0)
		{
			// �v���C���[�̃T�C�Y�����炷
			pos.y = PLAYER_SIZE.y;
		}
		// �����v���C���[������ʊO�ɍs������
		if (pos.y + PLAYER_SIZE.y > SCREEN_HEIGHT)
		{
			// �v���C���[�̃T�C�Y�����炷
			pos.y = SCREEN_HEIGHT - PLAYER_SIZE.y;
		}
		// �����v���C���[������ʊO�ɍs������
		if (pos.x - PLAYER_SIZE.x - PLAYER_WEPON_SIZE.x / 2 < MIN_GAME_WIDTH)
		{
			// �v���C���[�ƕ���̃T�C�Y�����炷
			pos.x = MIN_GAME_WIDTH + PLAYER_SIZE.x + PLAYER_WEPON_SIZE.x / 2;
		}
		// �����v���C���[���E��ʊO�ɍs������
		if (pos.x + PLAYER_SIZE.x + PLAYER_WEPON_SIZE.x / 2 > MAX_GAME_WIDTH)
		{
			// �v���C���[�ƕ���̃T�C�Y�����炷
			pos.x = MAX_GAME_WIDTH - PLAYER_SIZE.x - PLAYER_WEPON_SIZE.x / 2;
		}
	}
	// �ʒu�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �e���ˏ����֐�
//******************************************************************************
void CPlayer::Shot(void)
{

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �L�[�{�[�h�擾
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();

	// �R���g���[���[�擾
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
			// SPACE�܂��̓R���g���[���[A�{�^��
			if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_SPACE))
			{
				// �V���b�g���g�p��Ԃ�
				m_bUseShot = true;
				// �V���b�g��
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

				// �v���C���[���x����1�̏ꍇ
				if (m_Level == LEVEL_1)
				{
					// �e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(pos),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
						BULLET_LEVEL1_SIZE, 
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
						, CBullet::TEX_TYPE_NORMAL);
				}
				// �v���C���[���x����2�̏ꍇ
				if (m_Level == LEVEL_2)
				{
					// �e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(pos),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL2_SIZE, 
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_NORMAL);
				}
				// �v���C���[���x����3�̏ꍇ
				if (m_Level == LEVEL_3)
				{
					// �e�̐���
					CNormal_Bullet::Create(D3DXVECTOR3(pos),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL3_SIZE,
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_NORMAL);
				}

			}
			// �R���g���[���[A�{�^���܂��̓L�[�{�[�hSPACE�𗣂����ꍇ
			if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickRelease(JS_A) || pInputKeyboard->GetKeyboardRelease(DIK_SPACE))
			{
				// �ʏ�e�̕s�g�p��Ԃ�
				m_bUseShot = false;
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
			//�J�E���g��2���܂�0�̎�
			if (m_AttackCount % 2 == 0)
			{
				// �V���b�g������
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
				// player���x����1�̎�
				if (m_Level == LEVEL_1)
				{
					// �e����
					CPlayer_Beam::Create(D3DXVECTOR3(pos.x, pos.y - 45, pos.z),
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
					CPlayer_Beam::Create(D3DXVECTOR3(pos.x, pos.y - 45, pos.z),
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
					CPlayer_Beam::Create(D3DXVECTOR3(pos.x, pos.y - 45, pos.z),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL3_BEAM_SIZE,
						D3DXVECTOR3(BEAM_BULLET_MOVE_VALUE.x, -BEAM_BULLET_MOVE_VALUE.y, BEAM_BULLET_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_BEAM);
				}
			}
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

			// �{�X��p�̃{�����g�p��Ԃ�
			m_bBossBom = true;

			// 2���܂�0�̎�
			if (m_nBomCount % 2 == 0)
			{
				// �r�[��������
				//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
				// �e�̐���
				CBoss_Bom::Create(D3DXVECTOR3(pos.x, pos.y - 45, pos.z),
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
		CScene2d::Update();

		//���@�̒��S
		D3DXVECTOR3 pos = GetPosition();

		//�e�N�X�`���X�V
		SetTexture(m_nPatternAnim * 0.2f, 0.0f, 0.2f, 1.0f);
	
		//�X�R�A�擾
		CScore * pScore = CGame::GetScore();
		m_nScore = pScore->GetScore();

		// �v���C���[�̏����O���t�@�C���ɏ�������
		SavePlayer();

		// �ړ�����
		Move();

		// �e���ˏ���
		Shot();

		//�ʏ���
		if (m_nPlayerState == STATE_NORMAL)
		{
			//�J���[�ݒ�
			SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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
				SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f));

				// �J�E���g��0��
				m_nRespawnCount = 0;
			}
		}
		// �_���[�W���
		if (m_nPlayerState == STATE_DAMAGE)
		{
			// �J�E���g�C���N�������g
			m_nDamageCount++;
			// �_���[�W�̃J�E���g��5���܂�0�ɂȂ�����
			if (m_nDamageCount % 5 == 0)
			{
				// �J���[�ݒ�
				SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			// �_���[�W�̃J�E���g��6���܂�0�ɂȂ�����
			if (m_nDamageCount % 6 == 0)
			{
				// �J���[�ݒ�
				SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

			}
			// ���G���Ԃ��I��������
			if (m_nDamageCount == DAMAGE_COUNT)
			{
				// �J���[�ݒ�
				SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

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
		SetPosition(D3DXVECTOR3(-100.0f, -100.0f, 0.0f));
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