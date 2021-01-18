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
#include "item.h"
LPDIRECT3DTEXTURE9 CItem::m_apTexture[MAX_ITEM_TEX] = {};
//------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------
CItem::CItem(int nPriority) : CScene2d(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bMove = false;
}
//------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------
CItem::~CItem()
{
}
//------------------------------------------------------------------
//����
//------------------------------------------------------------------
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int sizeX, int sizeY , TYPE type)
{
	//pItem�N���X�̃|�C���^
	CItem * pItem;
	//�������m��
	pItem = new CItem;
	//������
	pItem->Init(pos, rot, move, sizeX, sizeY, type);
	//pItem�|�C���^��Ԃ�
	return pItem;
}
//------------------------------------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------------------------------------
HRESULT CItem::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/star.png", &m_apTexture[TYPE_STAR]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bom3.png", &m_apTexture[TYPE_BOM]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Powerup.png", &m_apTexture[TYPE_POWER]);
	return S_OK;
}
//------------------------------------------------------------------
//�e�N�X�`���j��
//------------------------------------------------------------------
void CItem::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_ITEM_TEX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//------------------------------------------------------------------
//������
//------------------------------------------------------------------
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int sizeX, int sizeY , TYPE type)
{
	//move
	m_move = move;
	//�^�C�v
	m_type = type;
	//������
	CScene2d::Init(pos, rot, sizeX, sizeY);
	//�e�̏����ݒ�
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(m_apTexture[m_type]);
	SetObjType(CScene::OBJTYPE_ITEM);
	return S_OK;
}
//------------------------------------------------------------------
//�I��
//------------------------------------------------------------------
void CItem::Uninit(void)
{
	//�I��
	CScene2d::Uninit();
}
//------------------------------------------------------------------
//�X�V
//------------------------------------------------------------------
void CItem::Update(void)
{
	//�X�V
	CScene2d::Update();
	//�T�E���h�̎擾
	CSound * pSound = CSceneManager::GetSound();
	//�X�R�A�̎擾
	CScore * pScore = CGame::GetScore();
	CPlayer * pPlayer = CGame::GetPlayer();
	//���W�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();
	//�e�N�X�`���̃Z�b�g
	SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
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
				//�^�C�v
				switch (m_type)
				{
					//�^�C�v���X�^�[�̏ꍇ
				case TYPE_STAR:
					//�I�u�W�F�N�g��player�̏ꍇ
					if (objType == OBJTYPE_PLAYER)
					{
						//�G�ƒe����������
						if (pos.x - STAR_SIZE_X / 2 < (ScenePos.x + PLAYER_SIZE_X / 2)
							&& pos.x + STAR_SIZE_X / 2 > (ScenePos.x - PLAYER_SIZE_X / 2)
							&& pos.y - STAR_SIZE_Y / 2 < (ScenePos.y + PLAYER_SIZE_Y / 2)
							&& pos.y + STAR_SIZE_Y / 2 > (ScenePos.y - PLAYER_SIZE_Y / 2))
						{
							//�X�R�A���Z
							pScore->AddScore(100);
							//�I��
							Uninit();
							return;
						}
					}
				case TYPE_BOM:
					//�I�u�W�F�N�g��player�̏ꍇ
					if (objType == OBJTYPE_PLAYER)
					{
						//�G�ƒe����������
						if (pos.x - BOM_SIZE_X / 2 < (ScenePos.x + PLAYER_SIZE_X / 2)
							&& pos.x + BOM_SIZE_X / 2 > (ScenePos.x - PLAYER_SIZE_X / 2)
							&& pos.y - BOM_SIZE_Y / 2 < (ScenePos.y + PLAYER_SIZE_Y / 2)
							&& pos.y + BOM_SIZE_Y / 2 > (ScenePos.y - PLAYER_SIZE_Y / 2))
						{
							//�{���̏������̉��Z
							pPlayer->GetBom(1);
							//�I��
							Uninit();
							return;
						}
					}
				case TYPE_POWER:
					//�I�u�W�F�N�g��player�̏ꍇ
					if (objType == OBJTYPE_PLAYER)
					{
						//�G�ƒe����������
						if (pos.x - POWER_SIZE_X / 2 < (ScenePos.x + PLAYER_SIZE_X / 2)
							&& pos.x + POWER_SIZE_X / 2 > (ScenePos.x - PLAYER_SIZE_X / 2)
							&& pos.y - POWER_SIZE_Y / 2 < (ScenePos.y + PLAYER_SIZE_Y / 2)
							&& pos.y + POWER_SIZE_Y / 2 > (ScenePos.y - PLAYER_SIZE_Y / 2))
						{
							//�p���[�A�b�v
							pPlayer->GetPowerUp();
							//�I��
							Uninit();
							return;
						}
					}
				}
			}
		}
	}
	if (m_bMove == false)
	{
		m_move.y = 3;
	}
	//��ʂ̉E�ɓ���������
	if (pos.x + ITEM_SIZE_X / 2 > MAX_GAME_WIDTH)
	{
		m_bMove = true;
		//�^�񒆂��Ⴉ������
		if (pos.y + ITEM_SIZE_Y / 2 < SCREEN_HEIGHT / 2)
		{
			m_move.x = -3;
			m_move.y = 3;
		}
		////�^�񒆂�荂��������
		if (pos.y - ITEM_SIZE_Y / 2 > SCREEN_HEIGHT / 2)
		{
			m_move.x = -3;
			m_move.y = 3;
		}
	}
	//��ʍ��ɓ���������
	if (pos.x - ITEM_SIZE_X / 2 < MIN_GAME_WIDTH)
	{
		m_bMove = true;
		//�^�񒆂��Ⴉ������
		if (pos.y + ITEM_SIZE_Y / 2 < SCREEN_HEIGHT / 2)
		{
			m_move.x = 3;
			m_move.y = 3;
		}
		////�^�񒆂�荂��������
		if (pos.y - ITEM_SIZE_Y / 2 > SCREEN_HEIGHT / 2)
		{
			m_move.x = 3;
			m_move.y = -3;
		}
	}
	//��ʉ��ɓ���������
	if (pos.y - ITEM_SIZE_Y / 2 <= 0)
	{
		m_bMove = true;
		if (pos.x + ITEM_SIZE_X / 2 > SCREEN_WIDTH / 2)
		{
			m_move.x = 3;
			m_move.y = 3;
		}
		if (pos.x + ITEM_SIZE_X / 2 < SCREEN_WIDTH / 2)
		{
			m_move.x = -3;
			m_move.y = 3;
		}
	}
	//��ʏ�ɓ���������
	if (pos.y + ITEM_SIZE_Y / 2 > SCREEN_HEIGHT)
	{
		m_bMove = true;
		m_move.y = -3;
	}
	pos.x += m_move.x;
	pos.y += m_move.y;
	SetPosition(pos);
}
//------------------------------------------------------------------
//�`��
//------------------------------------------------------------------
void CItem::Draw(void)
{
	//�`��
	CScene2d::Draw();
}