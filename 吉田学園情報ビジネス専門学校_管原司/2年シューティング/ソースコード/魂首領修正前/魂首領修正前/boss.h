//---------------------------------------------------
// Player
// player.h
// Authur:	�ǌ��i
//---------------------------------------------------
#ifndef _BOSS_H_
#define _BOSS_H_
//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define MAX_BOSS 3
#define BOSS_MAIN_SIZE_X 150
#define BOSS_MAIN_SIZE_Y 150
#define BOSS_RIGHT_SIZE_X 150
#define BOSS_RIGHT_SIZE_Y 150
#define BOSS_LEFT_SIZE_X 150
#define BOSS_LEFT_SIZE_Y 150
//---------------------------------------------------
//�N���X
//---------------------------------------------------
class CBoss : public CScene
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
		STATE_MOVE,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_DEAD,
		STATE_MAX
	}STATE;
	CBoss(int nPriority = PRIORITY_TYPE_BOSS);
	~CBoss();
	static HRESULT Load(void);
	static void Unload(void);
	static CBoss * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitBoss(int nDamage);
	void SetBoss(int nSetCount);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOSS];		//�e�N�X�`�����
	CScene2d * m_apScene2D[MAX_BOSS];						//Boss�̏��
	D3DXVECTOR3 m_Mainpos;									//���S
	D3DXVECTOR3 m_Rightpos;							//�E
	D3DXVECTOR3 m_Leftpos;								//��
	D3DXVECTOR3 m_move;										//�ړ�
	int m_nLife;											//�̗�
	int m_nAttackCount;										//�U��
	int m_nAttackCount2;									//�U��
	int m_nDamageCount;										//�_���[�W
	int m_nSetCount;										//�{�X�Z�b�g�J�E���g
	STATE m_State;											//State
	bool m_bMove;											//move
};
#endif