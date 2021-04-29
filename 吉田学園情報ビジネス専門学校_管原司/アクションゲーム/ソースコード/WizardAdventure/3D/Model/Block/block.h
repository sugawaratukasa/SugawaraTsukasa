//******************************************************************************
// ブロック [block.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BLOCK_H_
#define _BLOCK_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
#include "../3D/Model/Object/3d_obj.h"
#include "../3D/Model/model.h"
//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 前方宣言
//******************************************************************************
class CFrame;
class CParticle_Emitter;
//******************************************************************************
// プレイヤークラス
//******************************************************************************
class CBlock :public C3D_Obj
{
public:
	CBlock(int nPriority = OBJTYPE_BLOCK);
	~CBlock();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Move(void);
	void Create_Move(void);
	void ReleaseBlock(void);
	void SetFrame(void);
	void Selecting(void);
	void UnSelected(void);
	void PlayerSelection(void);
	void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type, CBlock *pBlock);
	void SetbMove(bool bMove);
	void SetbEmitter(bool bEmitter);
private:
	void Collision(D3DXVECTOR3 posOld, D3DXVECTOR3 size);
	D3DXVECTOR3 m_posOld;					// 古い位置
	D3DXVECTOR3 m_move;						// 移動
	CBlock *m_pBlock;						// ポインタ
	CFrame *m_pFrame;						// 枠のポインタ
	CParticle_Emitter *m_pParticleEmitter;	// CParticle_Emitterのポインタ
	bool m_bMove;							// 移動の判定
	bool m_bParticleEmitter;					// 放射体の判定
};

#endif