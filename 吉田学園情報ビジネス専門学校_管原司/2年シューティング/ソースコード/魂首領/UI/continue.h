//******************************************************************************
// コンティニュー [continue.h]
// Author : 管原　司
//******************************************************************************
#ifndef _CONTINUE_H_
#define _CONTINUE_H_
//******************************************************************************
// 前方宣言
//******************************************************************************
class CNumber;
class CContinue_Polygon;
class CPress_Enter_Polygon;
//******************************************************************************
// クラス
//******************************************************************************
class CContinue : public CScene
{
public:
	CContinue(int nPriority = OBJTYPE_UI);
	~CContinue();
	static CContinue * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CNumber * m_pNumber;						// ナンバーの情報
	CContinue_Polygon *m_pContinue_Polygon;		// コンティニューポリゴンの情報
	CPress_Enter_Polygon *m_pPress_Enter;		// プレスエンターの情報
	D3DXVECTOR3 m_pos;							// 位置座標
	D3DXVECTOR3 m_size;							// サイズ
	int m_nContinueCount;						// カウント
	int m_nContinueNum;							// コンティニューナンバー
};
#endif