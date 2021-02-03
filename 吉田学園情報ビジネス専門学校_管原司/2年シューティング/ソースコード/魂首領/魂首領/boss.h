//******************************************************************************
// �{�X [boss.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BOSS_H_
#define _BOSS_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_BOSS		(3)									// �{�X�̕��ʐ�
#define BOSS_LIFE		(4000)								// �{�X�̃��C�t
#define BOSS_MAIN_SIZE	(D3DXVECTOR3(150.0f,150.0f,0.0f))	// �{�X�̒����̃T�C�Y
#define BOSS_RIGHT_SIZE	(D3DXVECTOR3(150.0f,150.0f,0.0f))	// �{�X�̉E�̃T�C�Y
#define BOSS_LEFT_SIZE	(D3DXVECTOR3(150.0f,150.0f,0.0f))	// �{�X�̍��̃T�C�Y
//******************************************************************************
// �N���X
//******************************************************************************
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
	CBoss(int nPriority = OBJTYPE_BOSS);
	~CBoss();
	static HRESULT Load(void);
	static void Unload(void);
	static CBoss * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitBoss(int nDamage);
	void SetBoss(int nSetCount);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRightPosition(void) { return m_Rightpos; }
	D3DXVECTOR3 GetLeftPosition(void) { return m_Leftpos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
private:
	void Attack(void);
	void State(void);
	void Move(void);
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOSS];		// �e�N�X�`�����
	CScene2d * m_apScene2D[MAX_BOSS];						// Boss�̏��
	D3DXVECTOR3 m_pos;										// �ʒu���W
	D3DXVECTOR3 m_Rightpos;									// �E�ʒu���W
	D3DXVECTOR3 m_Leftpos;									// ���ʒu���W
	D3DXVECTOR3 m_size;										// �T�C�Y
	D3DXVECTOR3 m_move;										// �ړ�
	int m_nLife;											// �̗�
	int m_nAttackCount;										// �U��
	int m_nAttackCount2;									// �U��
	int m_nDamageCount;										// �_���[�W
	int m_nSetCount;										// �{�X�Z�b�g�J�E���g
	STATE m_State;											// State
	bool m_bMove;											// move
};
#endif