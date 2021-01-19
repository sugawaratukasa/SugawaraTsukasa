//******************************************************************************
// �{�� [bom.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BOM_H_
#define _BOM_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "bullet.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BOM_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	// �{���̈ʒu
#define BOM_SIZE	(D3DXVECTOR3(800.0f,800.0f,0.0f))						// �{���̃T�C�Y
#define BOM_ROT		(D3DXVECTOR3(0.0f,0.0f,0.0f))							// �{���̌���
//******************************************************************************
// �N���X
//******************************************************************************
class CBom : public CBullet
{
public:

	CBom(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CBom();
	static CBom * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void HitEnemy(void);
	int m_nPatternCount;	// �p�^�[���J�E���g
	int m_nAnimCount;		// �A�j���[�V�����J�E���g

};
#endif