//******************************************************************************
// ボム [bom.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BOM_H_
#define _BOM_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************

//******************************************************************************
// クラス
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
	int m_nPatternCount;	// パターンカウント
	int m_nAnimCount;		// アニメーションカウント

};
#endif