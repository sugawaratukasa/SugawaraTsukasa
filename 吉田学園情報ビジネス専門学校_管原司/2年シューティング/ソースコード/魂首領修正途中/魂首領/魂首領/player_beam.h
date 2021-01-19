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
// �}�N����`
//******************************************************************************
#define BULLET_LEVEL1_BEAM_SIZE (D3DXVECTOR3(40.0f,40.0f,0.0f))//�r�[���̃T�C�Y
#define BULLET_LEVEL2_BEAM_SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))//�r�[���̃T�C�Y
#define BULLET_LEVEL3_BEAM_SIZE (D3DXVECTOR3(60.0f,60.0f,0.0f))//�r�[���̃T�C�Y
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
	D3DXVECTOR3 m_move;			// �ړ�
	static bool m_bUseBeam;		//�r�[���̎g�p���
};
#endif