//******************************************************************************
// �r�[�� [player_beam.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PLAYER_BEAM_H_
#define _PLAYER_BEAM_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "bullet.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CPlayer_Beam : public CBullet
{
public:

	CPlayer_Beam(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CPlayer_Beam();
	static CPlayer_Beam * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetUseBeam(bool bUseBeam);
private:
	void HitEnemy(void);

	D3DXVECTOR3 m_move;			// �ړ���
	int m_nDeathCount;			// ���S�J�E���g
	bool m_bHit;				// ����������
	static bool m_bUseBeam;		// �r�[���̎g�p���
};
#endif