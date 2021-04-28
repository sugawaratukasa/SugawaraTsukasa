//******************************************************************************
// 2D_ポリゴン [2d_polygon.cpp]
// Author : 管原司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "manager.h"
#include "joystick.h"
#include "ui_texture.h"
#include "2d_polygon.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define ROT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		// 向き 
#define COL			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色
#define BLACK_COL	(D3DXCOLOR(0.0f,0.0f,0.0f,0.5f))	// 色
#define ADD_ALPHA	(0.03f)								// 加算
#define MIN_ALPHA	(0.1f)								// α値の最小
#define MAX_ALPHA	(1.0f)								// α値の最大
//******************************************************************************
// コンストラクタ
//******************************************************************************
C2D_Polygon::C2D_Polygon(int nPriority) : CScene2D(nPriority)
{
	m_Type	 = TYPE_NONE;
	m_bColor = false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
C2D_Polygon::~C2D_Polygon()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
C2D_Polygon * C2D_Polygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// C2D_Polygonのポインタ
	C2D_Polygon *p2D_Polygon = NULL;

	// NULLの場合
	if (p2D_Polygon == NULL)
	{
		// メモリ確保
		p2D_Polygon = new C2D_Polygon;

		// NULLでない場合
		if (p2D_Polygon != NULL)
		{
			// 情報設定
			p2D_Polygon->SetPolygon(pos, ROT, size, COL);

			// 代入
			p2D_Polygon->m_Type = type;

			switch (p2D_Polygon->m_Type)
			{
				// テクスチャなし
			case C2D_Polygon::TYPE_NONE:
				// 色設定
				p2D_Polygon->SetColor(BLACK_COL);
				break;

				// RESUME
			case C2D_Polygon::TYPE_RESUME:
				// テクスチャ受け渡し
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_RESUME));
				// 色設定
				p2D_Polygon->SetColor(COL);
				break;

				// コントローラー説明
			case C2D_Polygon::TYPE_CONTROLS:
				// テクスチャ受け渡し
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_CONTROLS));
				// 色設定
				p2D_Polygon->SetColor(COL);
				break;

				// EXIT
			case C2D_Polygon::TYPE_EXIT:
				// テクスチャ受け渡し
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_EXIT));
				// 色設定
				p2D_Polygon->SetColor(COL);
				break;

				// GAMESTART
			case C2D_Polygon::TYPE_GAMESTART:
				// テクスチャ受け渡し
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_GAMESTART));
				// 色設定
				p2D_Polygon->SetColor(COL);
				break;

				// TITLE
			case C2D_Polygon::TYPE_TITLE:
				// テクスチャ受け渡し
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_TITLE));
				// 色設定
				p2D_Polygon->SetColor(COL);
				break;

				// タイトル背景
			case C2D_Polygon::TYPE_TITLE_BG:
				// テクスチャ受け渡し
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_TITLE_BG));
				// 色設定
				p2D_Polygon->SetColor(COL);
				break;

				// PRESS_START
			case C2D_Polygon::TYPE_PRESS_START:
				// テクスチャ受け渡し
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_PRESS_START));
				// 色設定
				p2D_Polygon->SetColor(COL);
				break;

				// RESULT
			case C2D_Polygon::TYPE_RESULT:
				// テクスチャ受け渡し
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_RESULT));
				// 色設定
				p2D_Polygon->SetColor(COL);
				break;

				// MAGICUI
			case C2D_Polygon::TYPE_MAGIC_UI:
				// テクスチャ受け渡し
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_MAGIC_UI));
				// 色設定
				p2D_Polygon->SetColor(COL);
				break;
			case C2D_Polygon::TYPE_CONTROLS_BG:
				// テクスチャ受け渡し
				p2D_Polygon->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_CONTROLS_BG));
				// 色設定
				p2D_Polygon->SetColor(COL);
				break;
				// 例外
			default:
				break;
			}

			// オブジェクトタイプ設定
			p2D_Polygon->SetObjType(OBJTYPE_NOSTOP_UI);

			// 初期化
			p2D_Polygon->Init();
		}
	}
	// ポインタを返す
	return p2D_Polygon;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT C2D_Polygon::Init(void)
{
	// 初期化
	CScene2D::Init();
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void C2D_Polygon::Uninit(void)
{
	// 終了
	CScene2D::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void C2D_Polygon::Update(void)
{
	// 更新
	CScene2D::Update();

	// コントローラー取得
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	// CONTROLS_BGの場合
	if (m_Type == TYPE_CONTROLS_BG)
	{
		// NULLでない場合	
		if (g_lpDIDevice != NULL)
		{
			// B,START,Aボタンを押した場合
			if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_B) || 
				pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START))
			{
				// 更新
				pInputJoystick->Update();

				// 終了
				Uninit();
				return;
			}
		}
	}
	// PRESS_STARTの場合
	if (m_Type == TYPE_PRESS_START)
	{
		// 色取得
		D3DXCOLOR col = GetColor();

		// falseの場合
		if (m_bColor == false)
		{
			// α値減算
			col.a -= ADD_ALPHA;
			// 0.1以下の場合
			if (col.a <= MIN_ALPHA)
			{
				// 0.1fに
				col.a = MIN_ALPHA;

				// trueにする
				m_bColor = true;
			}
		}
		else
		{
			// α値加算
			col.a += ADD_ALPHA;
			// 1.0f以上の場合
			if (col.a >= MAX_ALPHA)
			{
				// 1.0fに
				col.a = MAX_ALPHA;

				// falseにする
				m_bColor = false;
			}
		}
		// 色設定
		SetColor(col);
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void C2D_Polygon::Draw(void)
{
	// 描画関数
	CScene2D::Draw();
}