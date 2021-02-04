//******************************************************************************
// フェード [fade.h]
// Author : 管原　司
//******************************************************************************
#ifndef _FADE_H_
#define _FADE_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "polygon.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define FADE_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 ,0.0f))	// フェード位置座標
#define FADE_SIZE	(D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))				// サイズ
//******************************************************************************
// 前方宣言
//******************************************************************************
class CSceneManager;
//******************************************************************************
// クラス
//******************************************************************************
class CFade : public CPolygon 
{
public:
	// フェード列挙型
	typedef enum
	{
		FADE_NONE = -1,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;

	CFade(int nPriority = CScene::OBJTYPE_FADE);
	~CFade();
	static CFade * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CSceneManager::MODE mode);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	FADE m_fade;							// フェード
	CSceneManager::MODE m_ModeNext;			// モード
};
#endif