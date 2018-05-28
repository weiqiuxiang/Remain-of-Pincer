#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "CGameStage.h"
#include "scene.h"
#include "CBackground.h"
#include "CFloor.h"
#include "CBall.h"
#include "CSpring.h"
#include "CResultScore.h"

int CGameStage::m_nStageNumber = 1;
char CGameStage::m_aStageData[VERTICAL_BLOCK_MAX][HORIZON_BLOCK_MAX + 1];
CSpring *CGameStage::m_Spring = NULL;

void CGameStage::LoadStageData(const char *FilePass)
{
	CScene::ReleaseAll();
	CBackground::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), BACKGROUND_TEXTURENAME);

	memset(m_aStageData, 'X', sizeof(m_aStageData));
	
	FILE *pFile = NULL;
	pFile = fopen(FilePass, "r");                                 //ranking.txtファイルにアクセス

	if(pFile == NULL)
	{
		MessageBox(NULL, "ステージファイル存在しない,読み込みできませんでした", "エラー", MB_OK | MB_ICONHAND);
		fclose(pFile);
		return;
	}

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
				CFloor::Create(D3DXVECTOR3(j*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, i*FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, 0.0f), D3DXVECTOR3(FLOOR_BLOCK_SIZE, FLOOR_BLOCK_SIZE, 0.0f),CFloor::TYPE_NORMAL, FLOOR_NORMAL_TEX);
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
				if (bDirection == false)
				{
					m_Spring->SetUV(D3DXVECTOR2(0.0f, 0.0f));
					m_Spring->SetUVWH(D3DXVECTOR2(1.0f, 1.0f));
				}
				else
				{
					m_Spring->SetUV(D3DXVECTOR2(1.0f, 0.0f));
					m_Spring->SetUVWH(D3DXVECTOR2(-1.0f, 1.0f));
				}
				m_Spring->Update();             //設定を反映する
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

void CGameStage::StageSelect(int StageNumber)
{
	switch (StageNumber)
	{
	case 1:
		CResultScore::SetClearPair(2);
		LoadStageData(STAGE01_DATA);
		break;
	case 2:
		CResultScore::SetClearPair(3);
		LoadStageData(STAGE02_DATA);
		break;
	case 3:
		CResultScore::SetClearPair(4);
		LoadStageData(STAGE03_DATA);
		break;
	case 4:
		CResultScore::SetClearPair(8);
		LoadStageData(STAGE04_DATA);
		break;
	case 5:
		CResultScore::SetClearPair(10);
		LoadStageData(STAGE05_DATA);
		break;
	case 6:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE06_DATA);
		break;
	case 7:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE07_DATA);
		break;
	case 8:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE08_DATA);
		break;
	case 9:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE09_DATA);
		break;
	case 10:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE10_DATA);
		break;
	case 11:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE11_DATA);
		break;
	case 12:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE12_DATA);
		break;
	case 13:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE13_DATA);
		break;
	case 14:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE14_DATA);
		break;
	case 15:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE15_DATA);
		break;
	case 16:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE16_DATA);
		break;
	case 17:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE17_DATA);
		break;
	case 18:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE18_DATA);
		break;
	case 19:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE19_DATA);
		break;
	case 20:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE20_DATA);
		break;
	case 21:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE21_DATA);
		break;
	case 22:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE22_DATA);
		break;
	case 23:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE23_DATA);
		break;
	case 24:
		CResultScore::SetClearPair(14);
		LoadStageData(STAGE24_DATA);
		break;
		
	default:
		CResultScore::SetClearPair(2);
		LoadStageData(STAGE01_DATA);
		break;
	}
}