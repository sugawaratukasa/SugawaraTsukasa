//******************************************************************************
// ���@ [player.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define PLAYER_SIZE				(D3DXVECTOR3(50.0f,50.0f,0.0f))
#define PLAYER_COLLISION_SIZE	(D3DXVECTOR3(5.0f,5.0f,0.0f))
#define PLAYER_WEPON_SIZE		(D3DXVECTOR3(25.0f,25.0f,0.0f))
#define PLAYER_MOVE				(D3DXVECTOR3(8.0f,8.0f,0.0f))
#define PLAYER_BEAM_MOVE		(D3DXVECTOR3(5.0f,5.0f,0.0f))
#define PLAYER_COLLISION_SIZE	(D3DXVECTOR3(5.0f,5.0f,0.0f))
#define RATE_MOVE				(0.4f)
#define MAX_PLAYER_TEX			(3)
#define MAX_PLAYER				(3)
#define DAMAGE_RESPAWN_COUNT	(30)
#define NODAMAGE_COUNT			(50)
#define DAMAGE_COUNT			(300)
#define BOM_LAUNCH_TIME			(200)
#define MAX_BOM_POSSESION		(5)
#define PLAYER_LIFE				(3)
#define PLAYER_CONTINUE			(1)
//******************************************************************************
// �N���X
//******************************************************************************
class CPlayer : public CScene
{
public:
	// �^�C�v�̗񋓌^
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_MAIN,
		TYPE_RIGHT,
		TYPE_LEFT,
		TYPE_MAX
	}TYPE;
	// ��ԗp�̗񋓌^
	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,
		STATE_RESPAWN,
		STATE_DAMAGE,
		STATE_DEAD,
		STATE_MAX
	}STATE;
	// Level�p�̗񋓌^
	typedef enum
	{
		LEVEL_NONE = -1,
		LEVEL_1,
		LEVEL_2,
		LEVEL_3,
		LEVEL_MAX
	}LEVEL;

	CPlayer(int nPriority = OBJTYPE_PLAYER);
	~CPlayer();
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitPlayer(void);
	void GetBom(int nBom);
	void GetPowerUp(void);
	void SetContinue(int Continue);
	void SavePlayer(void);
	void SetBossBom(bool bBoss);

	D3DXVECTOR3 GetPosition(void) { return m_MainPos; }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_Collision_Size; }
	int GetLevel(void) { return m_Level; }
	int GetPlayerState(void) { return m_nPlayerState; }
	
private:
	void Move(void);
	void Shot(void);
	void PlayerState(void);

	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];		// �e�N�X�`�����
	CScene2d * m_apScene2D[TYPE_MAX];						// Player�̏��
	D3DXVECTOR3 m_MainPos;									// ���S
	D3DXVECTOR3 m_RightPos;									// �E
	D3DXVECTOR3 m_LeftPos;									// ��
	D3DXVECTOR3 m_Size;										// �T�C�Y
	D3DXVECTOR3 m_Collision_Size;								// �����蔻��T�C�Y
	int m_nContinue;										// �R���e�B�j���[�J�E���g
	int m_nLife;											// �̗�
	int m_nCountAnim;										// �J�E���^�[
	int m_nCountAnimWepon;									// �J�E���^�[
	int m_nPatternAnim;										// �p�^�[��
	int m_nPatternAnimWepon;								// �E�p�^�[��
	int m_AttackCount;										// �e���˂̃J�E���g
	int m_nBeamCount;										// �r�[���̗��ߎ���
	int m_nDamageCount;										// �_���[�W�J�E���g
	int m_nRespawnCount;									// ���X�|�[���J�E���g
	int m_nNoDamageCount;									// ���G����
	int m_nBomCount;										// �{���̔��˃J�E���g
	int m_nBom_possession_count;							// �{���̏�����
	int m_nScore;											// �X�R�A
	int m_nPlayerState;										// �v���C���[��state
	int m_Level;											// �v���C���[�̃��x��
	bool m_bMove;											// �ړ��̏��
	bool m_bUseBeam;										// �r�[���̎g�p���
	bool m_bUseBom;											// �{���̎g�p���
	bool m_bBoss;											// �{�X
	bool m_bContinue;										// �R���e�B�j���[
};
#endif