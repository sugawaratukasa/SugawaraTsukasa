//******************************************************************************
// 2dパーティクルエミッター [2d_particle_emitter.h]
// Author : 管原　司
//******************************************************************************
#ifndef _2D_PARTICLE_EMITTER_H_
#define _2D_PARTICLE_EMITTER_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
//******************************************************************************
// 前方宣言
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class C2D_Particle_Emitter : public CScene
{
public:
	typedef enum
	{
		TYPE_GREEN,
		TYPE_FIRE,
		TYPE_ICE
	}TYPE;
	C2D_Particle_Emitter();
	~C2D_Particle_Emitter();
	static C2D_Particle_Emitter *Create(D3DXVECTOR3 pos, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	void SetPos(D3DXVECTOR3 pos);
private:
	void CreateParticle(void);
	void Load(const char *cText);
	D3DXVECTOR3 m_pos;		// 位置座標
	int m_nCount;			// 間隔
	int m_nCreateCount;		// 生成カウント
	char m_cText[MAX_TEXT];	// テキスト
	TYPE m_Type;			// タイプ
};
#endif