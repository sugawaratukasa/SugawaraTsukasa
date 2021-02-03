//******************************************************************************
// ���@�̕��� [player_wepon.cpp]
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
#include "normal_bullet.h"
#include "game.h"
#include "player_wepon.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include <stdio.h>
//******************************************************************************
// �}�N����`
//******************************************************************************
#define WEPON_BULLET_NORMAL_MOVE_VALUE	(D3DXVECTOR3(7.5f,15.0f,0.0f))
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CPlayer_Wepon::m_pTexture= NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPlayer_Wepon::CPlayer_Wepon(int nPriority)
{
	m_Type			= TYPE_NONE;
	m_nCountAnim	= 0;
	m_nPatternAnim	= 0;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CPlayer_Wepon::~CPlayer_Wepon()
{
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CPlayer_Wepon::Load(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Player/Player002.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CPlayer_Wepon::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		// m_pTexture��Release
		m_pTexture->Release();
		// m_pTexture��NULL
		m_pTexture = NULL;
	}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CPlayer_Wepon * CPlayer_Wepon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// CPlayer_Wepon�N���X�̃|�C���^
	CPlayer_Wepon * pPlayer_Wepon;

	// �������m��
	pPlayer_Wepon = new CPlayer_Wepon;

	// �ʒu���W�ݒ�
	pPlayer_Wepon->SetPosition(pos);

	// �T�C�Y�ݒ�
	pPlayer_Wepon->SetSize(size);

	// �J���[�ݒ�
	pPlayer_Wepon->SetRGBA(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	// �I�u�W�F�^�C�v�ݒ�
	pPlayer_Wepon->SetObjType(OBJTYPE_PLAYER_WEPON);

	// �^�C�v�ݒ�
	pPlayer_Wepon->m_Type = type;

	// �e�N�X�`���󂯓n��
	pPlayer_Wepon->BindTexture(m_pTexture);

	// ������
	pPlayer_Wepon->Init();

	// �|�C���^��Ԃ�
	return pPlayer_Wepon;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CPlayer_Wepon::Init(void)
{
	// ������
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CPlayer_Wepon::Uninit(void)
{
	// �I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CPlayer_Wepon::Update(void)
{
	// �X�V
	CScene2d::Update();

	// �ړ�����
	Move();

	// �e���ˏ���
	Shot();

	// �C���N�������g
	m_nCountAnim++;

	//�J�E���g�� 7�ȏ�ɂȂ����ꍇ
	if (m_nCountAnim > 7)
	{
		m_nCountAnim = 0;
		//�p�^�[����0�ȏ�̏ꍇ
		if (m_nPatternAnim >= 0)
		{
			//�p�^�[�����C���N�������g
			m_nPatternAnim++;
		}
	}

	// �e�N�X�`���ݒ�
	SetTexture(m_nPatternAnim * 0.25f, 0.0f, 0.25f, 1.0f);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CPlayer_Wepon::Draw(void)
{
	// �`��
	CScene2d::Draw();
}
//******************************************************************************
// �ړ������֐�
//******************************************************************************
void CPlayer_Wepon::Move(void)
{

	// �v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();

	// �v���C���[�̍��W�擾
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPosition();

	// �v���C���[���r�[�����g�p���Ă��邩���擾
	bool bPlayer_Use_Beam = pPlayer->GetUseBeam();

	// �v���C���[���{�X��p�̃{�����g�p���Ă��邩���擾
	bool bPlayer_Use_BossBom = pPlayer->GetUseBossBom();

	// �r�[�����g�p���̏ꍇ
	if (bPlayer_Use_Beam == true || bPlayer_Use_BossBom == true)
	{
		// �^�C�v�����̏ꍇ
  		if (m_Type == TYPE_LEFT)
		{
			// �����pos�����@�̑O��
          	SetPosition(D3DXVECTOR3(PlayerPos.x - 15, PlayerPos.y - 40, PlayerPos.z));
		}
		// �^�C�v���E�̏ꍇ
		if (m_Type == TYPE_RIGHT)
		{
			// �����pos�����@�̑O��
			SetPosition(D3DXVECTOR3(PlayerPos.x + 15, PlayerPos.y - 40, PlayerPos.z));
		}
	}
	// �r�[�����g�p���̏ꍇ
	else if (bPlayer_Use_Beam == false)
	{
		// �^�C�v�����̏ꍇ
		if (m_Type == TYPE_LEFT)
		{
			// �ʒu���W�ݒ�
			SetPosition(D3DXVECTOR3(PlayerPos.x - 40, PlayerPos.y + 40, PlayerPos.z));
		}
		// �^�C�v���E�̏ꍇ
		if (m_Type == TYPE_RIGHT)
		{
			// �ʒu���W�ݒ�
			SetPosition(D3DXVECTOR3(PlayerPos.x + 40, PlayerPos.y + 40, PlayerPos.z));
		}
	}
}
//******************************************************************************
// �e���ˏ����֐�
//******************************************************************************
void CPlayer_Wepon::Shot(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();

	// �L�[�{�[�h�擾
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();

	// �R���g���[���[�擾
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	// �v���C���[���r�[�����g�p���Ă��邩���擾
	bool bPlayer_Use_Shot = pPlayer->GetUseShot();

	// �v���C���[���x���擾
	int nPlayerLevel = pPlayer->GetLevel();

	// �v���C���[���ʏ�e���g�p���̏ꍇ
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_SPACE))
	{
		// ���x����1�̏ꍇ
		if (nPlayerLevel == CPlayer::LEVEL_1)
		{
			// �^�C�v�����̏ꍇ
			if (m_Type == TYPE_LEFT)
			{
				// �e����
				CNormal_Bullet::Create(D3DXVECTOR3(pos),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)),
					BULLET_LEVEL1_SIZE,
					D3DXVECTOR3(-WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
					, CBullet::TEX_TYPE_NORMAL);
			}
			// �^�C�v���E�̏ꍇ
			if (m_Type == TYPE_RIGHT)
			{
				CNormal_Bullet::Create(D3DXVECTOR3(pos),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-30.0f)),
					BULLET_LEVEL1_SIZE,
					D3DXVECTOR3(WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_NORMAL);
			}
		}

		// ���x����2�̏ꍇ
		if (nPlayerLevel == CPlayer::LEVEL_2)
		{
			// �^�C�v�����̏ꍇ
			if (m_Type == TYPE_LEFT)
			{
				CNormal_Bullet::Create(D3DXVECTOR3(pos),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)),
					BULLET_LEVEL2_SIZE,
					D3DXVECTOR3(-WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_NORMAL);
			}
			// �^�C�v���E�̏ꍇ
			if (m_Type == TYPE_RIGHT)
			{
				CNormal_Bullet::Create(D3DXVECTOR3(pos),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-30.0f)),
					BULLET_LEVEL2_SIZE,
					D3DXVECTOR3(WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_NORMAL);
			}
		}
		// �v���C���[���x����3�̏ꍇ
		if (nPlayerLevel == CPlayer::LEVEL_3)
		{
			// �^�C�v�����̏ꍇ
			if (m_Type == TYPE_LEFT)
			{
				CNormal_Bullet::Create(D3DXVECTOR3(pos),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)),
					BULLET_LEVEL3_SIZE,
					D3DXVECTOR3(-WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_NORMAL);
			}
			// �^�C�v���E�̏ꍇ
			if (m_Type == TYPE_RIGHT)
			{
				CNormal_Bullet::Create(D3DXVECTOR3(pos),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-30.0f)),
					BULLET_LEVEL3_SIZE,
					D3DXVECTOR3(WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_NORMAL);
			}
		}
	}
}