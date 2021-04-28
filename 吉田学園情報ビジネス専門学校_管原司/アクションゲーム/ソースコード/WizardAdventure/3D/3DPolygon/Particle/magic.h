//******************************************************************************
// 魔法 [magic.h]
// Author : 管原　司
//******************************************************************************
#ifndef _MAGIC_H_
#define _MAGIC_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_TEXT	(1024)
//******************************************************************************
// クラス
//******************************************************************************
class CMagic : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_FIRE_BALL,
		TYPE_ICE_BALL,
		TYPE_ENEMY_FIRE_BALL,
		TYPE_ENEMY_ICE_BALL,
		TYPE_MAX
	}TYPE;
	CMagic();
	~CMagic();
	static CMagic *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Collision(void);
	void Load(const char *cText);
	D3DXVECTOR3 m_pos;				// 位置座標
	D3DXVECTOR3 m_move;				// 移動量
	int m_nCount;					// 間隔
	int m_nCreateCount;				// 生成カウント
	int m_nLife;					// ライフ
	char m_cText[MAX_TEXT];			// テキスト
	TYPE m_Type;					// タイプ
};
#endif