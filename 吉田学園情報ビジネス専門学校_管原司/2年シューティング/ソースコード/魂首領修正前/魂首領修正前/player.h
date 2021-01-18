//---------------------------------------------------
// Player
// player.h
// Authur:	�ǌ��i
//---------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define PLAYER_SIZE_X 50
#define PLAYER_SIZE_Y 50
#define PLAYER_COLLISION_SIZE_X 5
#define PLAYER_COLLISION_SIZE_Y 5
#define PLAYER_WEPON_SIZE_X 25
#define PLAYER_WEPON_SIZE_Y 25
#define PLAYER_MOVE_Y 8
#define PLAYER_MOVE_X 8
#define PLAYER_BEAM_MOVE_Y 5
#define PLAYER_BEAM_MOVE_X 5
#define RATE_MOVE 0.4f
#define MAX_PLAYER_TEX 3
#define MAX_PLAYER 3
#define DAMAGE_RESPAWN_COUNT 30
#define NODAMAGE_COUNT 50
#define DAMAGE_COUNT 300
#define BOM_LAUNCH_TIME 200
#define MAX_BOM_POSSESION	5
#define PLAYER_LIFE	3
#define PLAYER_CONTINUE	1
//---------------------------------------------------
//�N���X
//---------------------------------------------------
class CPlayer : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_MAIN,
		TYPE_RIGHT,
		TYPE_LEFT,
		TYPE_MAX
	}TYPE;
	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,
		STATE_RESPAWN,
		STATE_DAMAGE,
		STATE_DEAD,
		STATE_MAX
	}STATE;
	typedef enum
	{
		LEVEL_NONE = -1,
		LEVEL_1,
		LEVEL_2,
		LEVEL_3,
		LEVEL_MAX
	}LEVEL;
	CPlayer(int nPriority = PRIORITY_TYPE_PLAYER);
	~CPlayer();
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void) { return m_Mainpos; }
	void HitPlayer(void);
	void GetBom(int nBom);
	void GetPowerUp(void);
	void SetContinue(int Continue);
	int GetLevel(void) { return m_Level; }
	int GetPlayerState(void) { return m_nPlayerState; }
	void SavePlayer(void);
	void SetBossBom(bool bBoss);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_PLAYER_TEX];	//�e�N�X�`�����
	CScene2d * m_apScene2D[MAX_PLAYER];						//Player�̏��
	D3DXVECTOR3 m_Mainpos;									//���S
	D3DXVECTOR3 m_WeponRightpos;							//�E
	D3DXVECTOR3 m_WeponLeftpos;								//��
	D3DXVECTOR3 m_move;										//�ړ�
	int m_nContinue;									//
	int m_nLife;											//�̗�
	int m_nCountAnim;										//�J�E���^�[
	int m_nCountAnimWepon;									//�J�E���^�[
	int m_nPatternAnim;										//�p�^�[��
	int m_nPatternAnimWepon;								//�E�p�^�[��
	int m_AttackCount;										//�e���˂̃J�E���g
	int m_nBeamCount;										//�r�[���̗��ߎ���
	int m_nDamageCount;										//�_���[�W�J�E���g
	int m_nRespawnCount;									//���X�|�[���J�E���g
	int m_nNoDamageCount;									//���G����
	int m_nBomCount;										//�{���̔��˃J�E���g
	int m_nBom_possession_count;							//�{���̏�����
	int m_nScore;											//�X�R�A
	int m_nPlayerState;									//�v���C���[��state
	int m_Level;											//�v���C���[�̃��x��
	bool m_bMove;											//�ړ��̏��
	bool m_bUseBeam;										//�r�[���̎g�p���
	bool m_bUseBom;											//�{���̎g�p���
	bool m_bBoss;											//�{�X
	bool m_bContinue;										//�R���e�B�j���[
};
#endif