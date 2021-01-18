//=============================================================================
//
// ��ʑJ��
// game.h
// Author : �ǌ��i
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
// ----------------------------------------------------------------------------
//�}�N��
//----------------------------------------------------------------------------7
#define MAX_GAME_WIDTH 960
#define MIN_GAME_WIDTH 320
//----------------------------------------------------------------------------
//�O���錾
//----------------------------------------------------------------------------
class CPlayer;
class CScore;
class CLife;
class CEnemy;
class CBom;
class CShip;
class CBoss;
//---------------------------------------------------------------------------
//�N���X
//---------------------------------------------------------------------------
class CGame : public CScene
{
public:
	static CGame * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	CGame(int nPriority = PRIORITY_TYPE_UI);
	~CGame();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore * GetScore(void) { return m_pScore; }
	static CLife * GetLife(void) { return m_pLife; }
	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CBom * GetBomUI(void) { return m_pBom; }
	static CShip * GetShip(void) { return m_pShip; }
	static CBoss * GetBoss(void) { return m_pBoss; }
private:
	static CScore * m_pScore;
	static CLife * m_pLife;
	static CPlayer * m_pPlayer;	//�v���C���[���
	static CBom * m_pBom;		//�{��
	static CShip * m_pShip;		//�D
	static CBoss * m_pBoss;		//�{�X
	bool m_bfade;				//�t�F�[�h
	int m_nCount;				//�J�E���g
	int m_nRespawn_Count;		//Respawn�J�E���g
	int m_nShipSpawnCount;		//�D�̐���
	bool m_bUseBoss;				//�{�X�킩
};
#endif