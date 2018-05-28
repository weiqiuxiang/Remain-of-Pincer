//=============================================================================
//
// メイン処理 [main.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "main.h"
#include "SceneTransition.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "CTitleMaster.h"
#include "resource.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"Remain Of Pincer"			// ウインドウのクラス名
#define WINDOW_NAME		"Remain Of Pincer"	// ウインドウのキャプション名
#define WINDOW_FRAME_WIDTH_SIZE (7.0f)
#define WINDOW_FRAME_HEIGHT_SIZE (30.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void SaveMousePos(HWND hwnd);            //マウス座標保存

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
D3DXVECTOR3 g_MousePosInWindow;

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CSceneTransition *pSceneTransition = NULL;
	//マネージャーの生成
	pSceneTransition = new CSceneTransition;

	RECT cr = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&cr, WS_OVERLAPPEDWINDOW ^ (WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX ), FALSE);

	RECT dr;
	GetWindowRect(GetDesktopWindow(), &dr);

	int dw = dr.right - dr.left;
	int dh = dr.bottom - dr.top;

	int ww = cr.right - cr.left;
	int wh = cr.bottom - cr.top;

	int wx = ww > dw ? 0 : (dw - ww) / 2;
	int wy = wh > dh ? 0 : (dh - wh) / 2;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1))
	};

	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE,
						wx,
						wy,
						ww,
						wh,
						NULL,
						NULL,
						hInstance,
						NULL);

	//初期化部分
	pSceneTransition->Init(hInstance,hWnd,TRUE);

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwCurrentTime =
	dwFrameCount = 0;
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();

	// ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				pSceneTransition->GetRenderer()->m_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//マウスの座標保存
				SaveMousePos(hWnd);

				CTitleMaster::GetWnd(hWnd);           //ウィンドウハンドル取得

				// 更新処理
				pSceneTransition->Update();

				// 描画処理
				pSceneTransition->Draw();

				dwFrameCount++;
			}
		}
	}

	//終了処理
	if (pSceneTransition != NULL)
	{
		pSceneTransition->Uninit();
		delete pSceneTransition;
		pSceneTransition = NULL;
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			//DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void SaveMousePos(HWND hwnd)
{
	WINDOWINFO windowInfo;
	windowInfo.cbSize = sizeof(WINDOWINFO);

	GetWindowInfo(hwnd, &windowInfo);

	int wx = windowInfo.rcWindow.left;                                               //Window左上x座標
	int wy = windowInfo.rcWindow.top;												 //Window左上y座標
	int ww = windowInfo.rcWindow.right - windowInfo.rcWindow.left;					 //Window幅
	int wh = windowInfo.rcWindow.bottom - windowInfo.rcWindow.top;					 //Window高さ

	POINT lpPoint;
	BOOL CursorCheck = GetCursorPos(&lpPoint);                                     //マウス座標取得
	g_MousePosInWindow.x = lpPoint.x - wx - WINDOW_FRAME_WIDTH_SIZE;                                         //マウスのウィンドウx座標計算
	g_MousePosInWindow.y = lpPoint.y - wy - WINDOW_FRAME_HEIGHT_SIZE;                                         //マウスのウィンドウy座標計
}

D3DXVECTOR3 GetMousePosInWindow(void)
{
	return g_MousePosInWindow;
}