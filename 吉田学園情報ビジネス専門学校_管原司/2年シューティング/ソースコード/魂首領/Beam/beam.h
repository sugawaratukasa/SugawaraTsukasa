//******************************************************************************
// ビーム [beam.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BEAM_H_
#define _BEAM_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "beam_base.h"
//******************************************************************************
// クラス
//******************************************************************************
class CBeam : public CBeam_Base
{
public:
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_01,
		TEX_TYPE_02,
		TEX_TYPE_MAX
	}TEX_TYPE;

	CBeam(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CBeam();
	static HRESULT Load(void);
	static void Unload(void);
	static CBeam * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DCOLOR col, TEX_TYPE tex_type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_TYPE_MAX];		// テクスチャ
};
#endif