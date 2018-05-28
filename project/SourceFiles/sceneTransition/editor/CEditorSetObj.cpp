#define _CRT_SECURE_NO_WARNINGS
#include "CEditorSetObj.h"
#include "SceneTransition.h"
#include "CFloor.h"
#include "CBall.h"
#include "CEditorFloor.h"
#include "CEditorBall.h"
#include "CBackground.h"
#include "CEditorSpring.h"
#include "CEditorEraser.h"
#include "CSpring.h"
#include "hitCheck.h"
#include <stdio.h>

CEditorSetObj::CREATE_OBJ_TYPE CEditorSetObj::m_CreatType = CEditorSetObj::TYPE_FLOOR;
char CEditorSetObj::m_aStageData[VERTICAL_BLOCK_MAX][HORIZON_BLOCK_MAX + 1];
CEditorSetObj::STEP CEditorSetObj::m_Step = CEditorSetObj::STEP_MAIN;
CSpring *CEditorSetObj::m_Spring = NULL;
D3DXVECTOR2 CEditorSetObj::m_SpringPos = D3DXVECTOR2(0,0);

void CEditorSetObj::Init(void)
{
	memset(m_aStageData, 'X', sizeof(m_aStageData));
	for(int j = 0;j < VERTICAL_BLOCK_MAX;j++)
	{
		m_aStageData[j][HORIZON_BLOCK_MAX] = '\n';
	}

	CEditorFloor::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), FLOOR_NORMAL_TEX);
	m_Step = STEP_MAIN;
	m_Spring = NULL;
	m_SpringPos = D3DXVECTOR2(0, 0);
}

void CEditorSetObj::Update(void)
{
	switch (m_Step)
	{
	case STEP_MAIN:
		ChangeCreateObjType();
		LockEditorObjInMouse();
		CreateObj();
		SaveStageData();
		LoadDataFromFile();
		break;
	case STEP_CREATE_SPRING:
		CreateSpringAndAdjustDir();
		break;
	default:
		ChangeCreateObjType();
		LockEditorObjInMouse();
		CreateObj();
		SaveStageData();
		LoadDataFromFile();
		break;
	}
}

void CEditorSetObj::ChangeCreateObjType(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();
	if (CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_1))
	{
		DeleteEditorObj();
		CEditorFloor::Create(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), FLOOR_NORMAL_TEX);
		m_CreatType = TYPE_FLOOR;
	}

	if (CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_2))
	{
		DeleteEditorObj();
		CEditorFloor* pEditorFloor = CEditorFloor::Create(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), FLOOR_BREAK_TEX);
		pEditorFloor->SetUV(D3DXVECTOR2(0.0f,0.0f));
		pEditorFloor->SetUVWH(D3DXVECTOR2(0.25f, 1.0f));
		m_CreatType = TYPE_FLOOR_BREAK;
	}

	if (CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_3))
	{
		DeleteEditorObj();
		CEditorBall::Create(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), BALL_TEX);
		m_CreatType = TYPE_BALL;
	}

	if (CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_4))
	{
		DeleteEditorObj();
		CEditorSpring::Create(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f), D3DXVECTOR3(30.0f*3, 30.0f*2, 0.0f), SPRING_TEX);
		m_CreatType = TYPE_SPRING;
	}

	if (CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_5))
	{
		DeleteEditorObj();
		CEditorEraser::Create(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), ERASER_TEX);
		m_CreatType = TYPE_ERASER;
	}
}

void CEditorSetObj::CreateObj(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();
		switch (m_CreatType)
		{
		case TYPE_FLOOR:
		{
			if (CSceneTransition::GetInputMouse()->GetMousePress(MOUSE_LEFT))
			{
				int PosX = MousePos.x / FLOOR_BLOCK_SIZE;
				int PosY = MousePos.y / FLOOR_BLOCK_SIZE;
				if (m_aStageData[PosY][PosX] != 'X') break;   //ここも埋まってある
				CFloor::Create(D3DXVECTOR3(PosX*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, PosY*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, 0.0f), D3DXVECTOR3(FLOOR_BLOCK_SIZE, FLOOR_BLOCK_SIZE, 0.0f), CFloor::TYPE_NORMAL, FLOOR_NORMAL_TEX);
				m_aStageData[PosY][PosX] = 'F';
			}
			break;
		}

		case TYPE_FLOOR_BREAK:
		{
			if (CSceneTransition::GetInputMouse()->GetMousePress(MOUSE_LEFT))
			{
				int PosX = MousePos.x / FLOOR_BLOCK_SIZE;
				int PosY = MousePos.y / FLOOR_BLOCK_SIZE;
				if (m_aStageData[PosY][PosX] != 'X') break;   //ここも埋まってある
				CFloor::Create(D3DXVECTOR3(PosX*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, PosY*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, 0.0f), D3DXVECTOR3(FLOOR_BLOCK_SIZE, FLOOR_BLOCK_SIZE, 0.0f), CFloor::TYPE_BREAK, FLOOR_BREAK_TEX);
				m_aStageData[PosY][PosX] = 'C';
			}
			break;
		}

		case TYPE_BALL:
		{
			if (CSceneTransition::GetInputMouse()->GetMousePress(MOUSE_LEFT))
			{
				int PosX = MousePos.x / FLOOR_BLOCK_SIZE;
				int PosY = MousePos.y / FLOOR_BLOCK_SIZE;
				if (m_aStageData[PosY][PosX] != 'X') break;   //ここも埋まってある
				CBall::Create(D3DXVECTOR3(PosX*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, PosY*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, 0.0f), D3DXVECTOR3(30.0f, 45.0f, 0.0f), BALL_TEX);
				m_aStageData[PosY][PosX] = 'B';
			}
			break;
		}

		case TYPE_SPRING:
		{
			if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
			{
				int PosX = MousePos.x / FLOOR_BLOCK_SIZE;
				int PosY = MousePos.y / FLOOR_BLOCK_SIZE;
				if (CanSpringSet(PosY, PosX) == false) break;
				m_Spring = CSpring::Create(D3DXVECTOR3((PosX + 1)*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, PosY*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE * 2, 0.0f), D3DXVECTOR3(30.0f * 3, 30.0f * 2, 0.0f), 0.05, false, SPRING_TEX);
				m_SpringPos = D3DXVECTOR2(PosX, PosY);
				m_Step = STEP_CREATE_SPRING;                    //ばねを作るステップに行く
			}
			break;
		}
			
		case TYPE_ERASER:
		{
			if (CSceneTransition::GetInputMouse()->GetMousePress(MOUSE_LEFT))
			{
				DeleteObjFloor();
				DeleteObjBall();
				DeleteObjSpring();
			}
			break;
		}
	}
}

bool CEditorSetObj::CanSpringSet(int Y, int X)
{
	//画面外に配置しようとしているかどうか
	bool OverRange = ((X + 2) > HORIZON_BLOCK_MAX) || ( (Y+1) > VERTICAL_BLOCK_MAX-1);
	if (OverRange) return false;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(m_aStageData[Y + i][X + j] != 'X') return false;
		}
	}

	return true;
}

void CEditorSetObj::DeleteObjFloor(void)
{
	//マウスデータ取得
	D3DXVECTOR3 MousePos = GetMousePosInWindow();
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;

		nPriority = CFloor::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		bool ObjIsFloor = pScene->GetObjType() == CScene::OBJTYPE_FLOOR;
		
		if (ObjIsFloor)
		{
			//マウス座標とプレーヤー生成アイコンの当り判定
			D3DXVECTOR3 ObjPos = pScene->GetPos();
			D3DXVECTOR3 ObjSize = pScene->GetSize();

			bool MouseHit = CHitCheck::HitPointRect(MousePos, ObjPos, ObjSize);

			//判定成立
			if (MouseHit)
			{
				int PosX = ObjPos.x / FLOOR_BLOCK_SIZE;
				int PosY = ObjPos.y / FLOOR_BLOCK_SIZE;
				m_aStageData[PosY][PosX] = 'X';
				CFloor *pFloor = dynamic_cast <CFloor *> (pScene);
				if (pFloor == NULL) return;
				pFloor->Uninit();
			}
		}
	}
}

void CEditorSetObj::DeleteObjBall(void)
{
	//マウスデータ取得
	D3DXVECTOR3 MousePos = GetMousePosInWindow();
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;

		nPriority = CBall::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		bool ObjIsBall = pScene->GetObjType() == CScene::OBJTYPE_BALL;

		if (ObjIsBall)
		{
			//マウス座標とプレーヤー生成アイコンの当り判定
			D3DXVECTOR3 ObjPos = pScene->GetPos();
			D3DXVECTOR3 ObjSize = pScene->GetSize();

			bool MouseHit = CHitCheck::HitPointRect(MousePos, ObjPos, ObjSize);

			if (MouseHit)
			{
				int PosX = ObjPos.x / FLOOR_BLOCK_SIZE;
				int PosY = ObjPos.y / FLOOR_BLOCK_SIZE;
				m_aStageData[PosY][PosX] = 'X';
				CBall *pBall = dynamic_cast <CBall *> (pScene);
				if (pBall == NULL) return;
				pBall->Uninit();
			}
		}
	}
}

void CEditorSetObj::DeleteObjSpring(void)
{
	//マウスデータ取得
	D3DXVECTOR3 MousePos = GetMousePosInWindow();
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;

		nPriority = CSpring::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		bool ObjIsSpring = pScene->GetObjType() == CScene::OBJTYPE_SPRING;

		if (ObjIsSpring)
		{
			//マウス座標とプレーヤー生成アイコンの当り判定
			D3DXVECTOR3 ObjPos = pScene->GetPos();
			D3DXVECTOR3 ObjSize = pScene->GetSize();

			bool MouseHit = CHitCheck::HitPointRect(MousePos, ObjPos, ObjSize);

			if (MouseHit)
			{
				int PosX = ObjPos.x / FLOOR_BLOCK_SIZE;
				int PosY = ObjPos.y / FLOOR_BLOCK_SIZE;
				if (m_aStageData[PosY][PosX] != 'X')
				{
					switch(m_aStageData[PosY][PosX])
					{
					case 'S':
						PosX = PosX;
						break;
					case 'L':
						PosX = PosX - 1;
						break;
					case 'R':
						PosX = PosX - 1;
						break;
					case '1':
						PosX = PosX - 2;
						break;
					case '2':
						PosY = PosY - 1;
						break;
					case '3':
						PosX = PosX - 1;
						PosY = PosY - 1;
						break;
					case '4':
						PosX = PosX - 2;
						PosY = PosY - 1;
						break;
					}
					for(int i = 0; i < 2;i++)
					{
						for(int j = 0; j < 3; j++)
						{
							m_aStageData[PosY + i][PosX + j] = 'X';
						}
					}
				}
				CSpring *pSpring = dynamic_cast <CSpring *> (pScene);
				if (pSpring == NULL) return;
				pSpring->Uninit();
			}
		}
	}
}

void CEditorSetObj::SaveStageData(void)
{
	if (CSceneTransition::GetInputKeyboard()->GetKeyPress(DIK_LCONTROL) == false) return;
	if (CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_S))
	{
		FILE *pFile;
		pFile = fopen("data/STAGEDATA/EditData.txt", "w");

		for (int i = 0; i < VERTICAL_BLOCK_MAX; i++)
		{
			for (int j = 0; j < (HORIZON_BLOCK_MAX + 1); j++)
			{
				fwrite(&m_aStageData[i][j],sizeof(char) ,1,pFile);
			}
		}

		fclose(pFile);
	}
}

void CEditorSetObj::LockEditorObjInMouse(void)
{
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		nPriority = CEditorFloor::GetPriority();
		pScene = CScene::GetScene(nCnt,nPriority);
		if (pScene == NULL) continue;
		bool IsFloor = pScene->GetObjType() == CScene::OBJTYPE_EDITOR_FLOOR;

		nPriority = CEditorBall::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		bool IsBall = pScene->GetObjType() == CScene::OBJTYPE_EDITOR_BALL;

		nPriority = CEditorEraser::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		bool IsEraser = pScene->GetObjType() == CScene::OBJTYPE_EDITOR_ERASER;

		nPriority = CEditorSpring::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		bool IsSpring = pScene->GetObjType() == CScene::OBJTYPE_EDITOR_SPRING;

		if(IsFloor || IsBall || IsEraser)
		{
			D3DXVECTOR3 MousePos = GetMousePosInWindow();
			int PosX = MousePos.x / FLOOR_BLOCK_SIZE;
			int PosY = MousePos.y / FLOOR_BLOCK_SIZE;
			float fSetX = PosX*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE;
			float fSetY = PosY*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE;
			if(IsEraser == true) pScene->SetPos(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f));
			else pScene->SetPos(D3DXVECTOR3(fSetX, fSetY, 0.0f));
		}
		if(IsSpring)
		{
			D3DXVECTOR3 MousePos = GetMousePosInWindow();
			int PosX = MousePos.x / FLOOR_BLOCK_SIZE;
			int PosY = MousePos.y / FLOOR_BLOCK_SIZE;
			float fSetX = PosX*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE + 30.0f;
			float fSetY = PosY*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE + 15.0f;
			pScene->SetPos(D3DXVECTOR3(fSetX, fSetY, 0.0f));
		}
	}
}

void CEditorSetObj::DeleteEditorObj(void)
{
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;

		//エディターオブジェは床か?
		nPriority = CEditorFloor::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		bool IsFloor = false;
		if (pScene != NULL) {
			IsFloor = pScene->GetObjType() == CScene::OBJTYPE_EDITOR_FLOOR;
		}
		if (IsFloor == true)
		{
			CEditorFloor *pEditorFloor = dynamic_cast <CEditorFloor *> (pScene);
			if (pEditorFloor == NULL) return;
			pEditorFloor->Uninit();
		}

		//エディターオブジェはボールか?
		nPriority = CEditorBall::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		bool IsBall = false;
		if (pScene != NULL) {
			IsBall = pScene->GetObjType() == CScene::OBJTYPE_EDITOR_BALL;
		}
		if (IsBall == true)
		{
			CEditorBall *pEditorBall = dynamic_cast <CEditorBall *> (pScene);
			if (pEditorBall == NULL) return;
			pEditorBall->Uninit();
		}

		//エディターオブジェは消しゴムか?
		nPriority = CEditorEraser::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		bool IsEraser = false;
		if (pScene != NULL) {
			IsEraser = pScene->GetObjType() == CScene::OBJTYPE_EDITOR_ERASER;
		}
		if (IsEraser == true)
		{
			CEditorEraser *pEditorEraser = dynamic_cast <CEditorEraser *> (pScene);
			if (pEditorEraser == NULL) return;
			pEditorEraser->Uninit();
		}

		nPriority = CEditorSpring::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		bool IsSpring = false;
		if (pScene != NULL) {
			IsSpring = pScene->GetObjType() == CScene::OBJTYPE_EDITOR_SPRING;
		}
		if (IsSpring == true)
		{
			CEditorSpring *pEditorSpring = dynamic_cast <CEditorSpring *> (pScene);
			if (pEditorSpring == NULL) return;
			pEditorSpring->Uninit();
		}
	}
}

void CEditorSetObj::LoadDataFromFile(void)
{
	if (CSceneTransition::GetInputKeyboard()->GetKeyPress(DIK_LCONTROL) == false) return;
	if (CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_L))
	{
		CScene::ReleaseAll();
		CBackground::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), BACKGROUND_TEXTURENAME);
		CEditorFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), FLOOR_NORMAL_TEX);

		memset(m_aStageData, 'X', sizeof(m_aStageData));

		FILE *pFile;
		pFile = fopen("data/STAGEDATA/EditDataLoad.txt", "r");                                 //ranking.txtファイルにアクセス

		for (int i = 0; i < VERTICAL_BLOCK_MAX; i++)
		{
			for (int j = 0; j < (HORIZON_BLOCK_MAX + 1); j++)
			{
				fread(&m_aStageData[i][j], sizeof(char), 1, pFile);
				if (m_aStageData[i][j] == '\n')
				{
					break;
				}
			}
		}

		for (int i = 0; i < VERTICAL_BLOCK_MAX; i++)
		{
			for (int j = 0; j < (HORIZON_BLOCK_MAX + 1); j++)
			{
				bool bEndLoop = false;
				switch (m_aStageData[i][j])
				{
				case 'F':
					CFloor::Create(D3DXVECTOR3(j*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, i*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, 0.0f), D3DXVECTOR3(FLOOR_BLOCK_SIZE, FLOOR_BLOCK_SIZE, 0.0f), CFloor::TYPE_NORMAL, FLOOR_NORMAL_TEX);
					break;
				case 'C':
					CFloor::Create(D3DXVECTOR3(j*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, i*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, 0.0f), D3DXVECTOR3(FLOOR_BLOCK_SIZE, FLOOR_BLOCK_SIZE, 0.0f), CFloor::TYPE_BREAK, FLOOR_BREAK_TEX);
					break;
				case 'B':
					CBall::Create(D3DXVECTOR3(j*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, i*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, 0.0f), D3DXVECTOR3(30.0f, 45.0f, 0.0f), BALL_TEX);
					break;
				case 'S':
				{
					bool bDirection;
					if (m_aStageData[i][j + 1] == 'L') bDirection = false;
					else bDirection = true;
					m_Spring = CSpring::Create(D3DXVECTOR3((j + 1)*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, i*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE * 2, 0.0f), D3DXVECTOR3(30.0f * 3, 30.0f * 2, 0.0f), 0.05, bDirection, SPRING_TEX);
					//描画方向調整
					if(bDirection == false)
					{
						m_Spring->SetUV(D3DXVECTOR2(0.0f, 0.0f));
						m_Spring->SetUVWH(D3DXVECTOR2(1.0f, 1.0f));
					}
					else
					{
						m_Spring->SetUV(D3DXVECTOR2(1.0f, 0.0f));
						m_Spring->SetUVWH(D3DXVECTOR2(-1.0f, 1.0f));
					}
					m_Spring = NULL;
					break;
				}
				case '\n':
					bEndLoop = true;
					break;
				default:
					continue;
					break;
				}
				if (bEndLoop == true) break;
			}
		}

		fclose(pFile);
	}
}

void CEditorSetObj::CreateSpringAndAdjustDir(void)
{
	if (NULL == m_Spring)
	{
		m_Step = STEP_MAIN;
		return;
	}

	D3DXVECTOR3 MousePos = GetMousePosInWindow();
	D3DXVECTOR3 SpringPos = m_Spring->GetPos();
	int PosX = (int)m_SpringPos.x;
	int PosY = (int)m_SpringPos.y;

	if (MousePos.x < SpringPos.x)
	{
		m_Spring->SetUV(D3DXVECTOR2(0.0f, 0.0f));
		m_Spring->SetUVWH(D3DXVECTOR2(1.0f, 1.0f));
		if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
		{
			m_Spring->SetFixDirection(false);
			m_Spring = NULL;
			m_Step = STEP_MAIN;
			
			m_aStageData[PosY][PosX] = 'S';
			m_aStageData[PosY][PosX+1] = 'L';
			m_aStageData[PosY][PosX+2] = '1';
			m_aStageData[PosY+1][PosX] = '2';
			m_aStageData[PosY+1][PosX+1] = '3';
			m_aStageData[PosY+1][PosX+2] = '4';
		}
	}

	else
	{
		m_Spring->SetUV(D3DXVECTOR2(1.0f, 0.0f));
		m_Spring->SetUVWH(D3DXVECTOR2(-1.0f, 1.0f));
		if (CSceneTransition::GetInputMouse()->GetMousePress(MOUSE_LEFT))
		{
			m_Spring->SetFixDirection(true);
			m_Spring = NULL;
			m_Step = STEP_MAIN;

			m_aStageData[PosY][PosX] = 'S';
			m_aStageData[PosY][PosX + 1] = 'R';
			m_aStageData[PosY][PosX + 2] = '1';
			m_aStageData[PosY + 1][PosX] = '2';
			m_aStageData[PosY + 1][PosX + 1] = '3';
			m_aStageData[PosY + 1][PosX + 2] = '4';
		}
	}

}