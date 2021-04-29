//******************************************************************************
// ビルボードUI[billboard_ui.h]
// Author : 管原司
//******************************************************************************
#ifndef _BILLBOARD_UI_H_
#define _BILLBOARD_UI_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "billboard.h"
//******************************************************************************
// 前方宣言
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CBillboard_UI : public CBillboard
{
public:
	enum TEX_TYPE
	{
		TEX_TYPE_NONE = 0,
		TEX_TYPE_FIREBALL,
		TEX_TYPE_ICEBALL,
		TEX_TYPE_MAX
	};
	CBillboard_UI(int nPriority = OBJTYPE_BILLBOARD_UI);
	~CBillboard_UI();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE Textype);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_TYPE_MAX];		// テクスチャへのポインタ
	TEX_TYPE m_Textype;											// テクスチャの種類
};
#endif