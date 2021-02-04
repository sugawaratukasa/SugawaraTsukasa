//******************************************************************************
// �{�X��p�̃{�� [boss_bom.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BOSS_BOM_H_
#define _BOSS_BOM_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "bullet.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CBoss_Bom : public CBullet
{
public:

	CBoss_Bom(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CBoss_Bom();
	static CBoss_Bom * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetUseBoss_Bom(bool bUseBoss_Bom);
private:
	void HitBoss(void);
	D3DXVECTOR3 m_move;				// �ړ�
	static bool m_bUseBoss_Bom;		// �g�p���
};
#endif