//******************************************************************************
// ボタン[button.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "../3D/3DPolygon/scene3d.h"
#include "../3D/Model/model.h"
#include "3d_obj.h"
#include "../3D/Model/player.h"
#include "collision.h"
#include "../3D/Model/Block/block.h"
#include "sound.h"
#include "button.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MOVE		(D3DXVECTOR3(0.0f,2.0f,0.0f))	// 移動量
#define SIZE_DEVIDE	(3.0f)							// サイズをわる量
//******************************************************************************
//静的メンバ変数
//******************************************************************************

//******************************************************************************
// コンストラクタ
//******************************************************************************
CButton::CButton(int nPriority) : C3D_Obj(nPriority)
{
	m_SavePos	= INIT_D3DXVECTOR3;
	m_bPush		= false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CButton::~CButton()
{

}
//******************************************************************************
// 生成関数
//******************************************************************************
CButton * CButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// CButtonのポインタ
	CButton *pButton = NULL;

	// NULLの場合
	if (pButton == NULL)
	{
		// メモリ確保
		pButton = new CButton;

		// NULLでない場合
		if (pButton != NULL)
		{
			// 情報設定
			pButton->SetModel(pos, rot, size, C3D_Obj::TYPE_BUTTON);

			// 位置保存
			pButton->m_SavePos = pos;

			// オブジェクトタイプ設定
			pButton->SetObjType(OBJTYPE_BUTTON);

			// 初期化
			pButton->Init();
		}
	}
	// ポインタを返す
	return pButton;
}
//******************************************************************************
// 初期化処理
//******************************************************************************
HRESULT CButton::Init(void)
{
	// 初期化
	C3D_Obj::Init();

	return S_OK;
}
//******************************************************************************
// 終了処理
//******************************************************************************
void CButton::Uninit(void)
{
	// 終了
	C3D_Obj::Uninit();
}
//******************************************************************************
// 更新処理
//******************************************************************************
void CButton::Update(void)
{
	// 更新
	C3D_Obj::Update();

	// trueの場合
	if (m_bPush == true) 
	{
		// 移動処理
		UnderMove();
	}
	// falseの場合
	if (m_bPush == false)
	{
		// 移動処理
		UpMove();
	}

	// 当たり判定
	Collision();
}

//******************************************************************************
// 描画処理
//******************************************************************************
void CButton::Draw(void)
{
	// 描画
	C3D_Obj::Draw();
}
//******************************************************************************
// 当たり判定
//******************************************************************************
void CButton::Collision(void)
{
	// サウンド取得
	CSound *pSound = CManager::GetSound();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// シーンのポインタ
	CScene *pScene = NULL;

	// ブロックとの当たり判定
	do
	{
		// リスト構造の先頭取得
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE Objtype = pScene->GetObjType();

			// オブジェクトタイプがブロックの場合
			if (Objtype == OBJTYPE_BLOCK)
			{
				// 位置取得
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// サイズ取得
				D3DXVECTOR3 BlockSize = ((CBlock*)pScene)->GetSize();

				// 当たり判定
				if (CCollision::RectangleCollision(pos, size, BlockPos, BlockSize) == true)
				{
					// falseの場合
					if (m_bPush == false)
					{
						// 押した音再生
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);

						// trueに
						m_bPush = true;
					}
				}
				else
				{
					if (m_bPush == true)
					{
						// 押した音再生
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);

						// falseに
						m_bPush = false;
					}
				}
			}
		}
		// NULLになるまで
	} while (pScene != NULL);
}
//******************************************************************************
// 上移動処理
//******************************************************************************
void CButton::UpMove(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// ボタンを下がりきったら
	if (pos.y <= m_SavePos.y - size.y / SIZE_DEVIDE)
	{
		// 移動
		pos.y += MOVE.y;
	}

	// 位置設定
	SetPos(pos);
}
//******************************************************************************
// 下移動処理
//******************************************************************************
void CButton::UnderMove(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// ボタンを下がりきったら
	if (pos.y >= m_SavePos.y - size.y / SIZE_DEVIDE)
	{
		// 移動
		pos.y += -MOVE.y;
	}

	// 位置設定
	SetPos(pos);
}