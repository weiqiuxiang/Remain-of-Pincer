//=============================================================================
//
// ���C������ [main.cpp]
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
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"Remain Of Pincer"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"Remain Of Pincer"	// �E�C���h�E�̃L���v�V������
#define WINDOW_FRAME_WIDTH_SIZE (7.0f)
#define WINDOW_FRAME_HEIGHT_SIZE (30.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void SaveMousePos(HWND hwnd);            //�}�E�X���W�ۑ�

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
D3DXVECTOR3 g_MousePosInWindow;

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CSceneTransition *pSceneTransition = NULL;
	//�}�l�[�W���[�̐���
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
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
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

	//����������
	pSceneTransition->Init(hInstance,hWnd,TRUE);

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	dwCurrentTime =
	dwFrameCount = 0;
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
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

				//�}�E�X�̍��W�ۑ�
				SaveMousePos(hWnd);

				CTitleMaster::GetWnd(hWnd);           //�E�B���h�E�n���h���擾

				// �X�V����
				pSceneTransition->Update();

				// �`�揈��
				pSceneTransition->Draw();

				dwFrameCount++;
			}
		}
	}

	//�I������
	if (pSceneTransition != NULL)
	{
		pSceneTransition->Uninit();
		delete pSceneTransition;
		pSceneTransition = NULL;
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
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
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			//DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
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

	int wx = windowInfo.rcWindow.left;                                               //Window����x���W
	int wy = windowInfo.rcWindow.top;												 //Window����y���W
	int ww = windowInfo.rcWindow.right - windowInfo.rcWindow.left;					 //Window��
	int wh = windowInfo.rcWindow.bottom - windowInfo.rcWindow.top;					 //Window����

	POINT lpPoint;
	BOOL CursorCheck = GetCursorPos(&lpPoint);                                     //�}�E�X���W�擾
	g_MousePosInWindow.x = lpPoint.x - wx - WINDOW_FRAME_WIDTH_SIZE;                                         //�}�E�X�̃E�B���h�Ex���W�v�Z
	g_MousePosInWindow.y = lpPoint.y - wy - WINDOW_FRAME_HEIGHT_SIZE;                                         //�}�E�X�̃E�B���h�Ey���W�v
}

D3DXVECTOR3 GetMousePosInWindow(void)
{
	return g_MousePosInWindow;
}