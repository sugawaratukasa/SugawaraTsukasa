//******************************************************************************
// メイン処理 [main.h]
// Author : 管原　司
//******************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION 0x800
#define _CRT_SECURE_NO_WARNINGS 
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <Windows.h>
#include <dinput.h>
#include "d3dx9.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INIT_INT			(0)														// int型初期化
#define INIT_FLOAT			(0.0f)													// float型初期化
#define INIT_D3DXVECTOR3	(D3DXVECTOR3(0.0f,0.0f,0.0f))							// D3DXVECTOR3初期化
#define INIT_COLOR			(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))						// D3DXCOLOR初期化
#define MAX_TEXT			(1024)													// テキストの最大
int GetFPS(void);
#endif