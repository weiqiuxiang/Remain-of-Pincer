#include "scene.h"
#include "scene2D.h"
#include "renderer.h"

//グローバル変数
CScene *CScene::m_apScene[PRIORITY_MAX_NUM][SCENE_MAX_NUM] = {};
int CScene::m_nNumScene = 0;

CScene::CScene()
{
	//static変数の初期化
	for (int nCntP = 0; nCntP < PRIORITY_MAX_NUM; nCntP++)
	{
		for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
		{
			if (m_apScene[nCntP][nCnt] == NULL)
			{
				m_apScene[nCntP][nCnt] = this;
				m_nID = nCnt;
				m_nPriority = nCntP;
				m_nNumScene++;
				break;
			}
		}
	}
}

CScene::CScene(int nPriority)
{
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		if (m_apScene[nPriority][nCnt] == NULL)
		{
			m_apScene[nPriority][nCnt] = this;
			m_nID = nCnt;
			m_nPriority = nPriority;
			m_nNumScene++;
			break;
		}
	}
}

CScene::~CScene()
{

}

//Init関数ダミー
HRESULT CScene::Init(void)
{
	return S_OK;
}

//すべて生成されたインスタンスの更新処理
void CScene::UpdateAll(void)
{
	//更新処理
	for (int nCntP = 0; nCntP < PRIORITY_MAX_NUM; nCntP++)
	{
		for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
		{
			if (m_apScene[nCntP][nCnt] != NULL)
			{
				m_apScene[nCntP][nCnt]->Update();
			}
		}
	}
}

//すべて生成されたインスタンスの描画処理
void CScene::DrawAll(void)
{
	//描画処理
	for (int nCntP = 0; nCntP < PRIORITY_MAX_NUM; nCntP++)
	{
		for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
		{
			if (m_apScene[nCntP][nCnt] != NULL)
			{
				m_apScene[nCntP][nCnt]->Draw();
			}
		}
	}
}

//すべて生成されたインスタンスの解放処理
void CScene::ReleaseAll(void)
{
	for (int nCntP = 0; nCntP < PRIORITY_MAX_NUM; nCntP++)
	{
		for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
		{
			if (m_apScene[nCntP][nCnt] != NULL)
			{
				m_apScene[nCntP][nCnt]->Release();
			}
		}
	}
}

//自分自身(CScene)を解放する
void CScene::Release(void)
{
 	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int workID = m_nID;         //m_IDはdeleteの後はなくなるから,m_IDの値を保存する
		int workPriority = m_nPriority;
		delete m_apScene[m_nPriority][m_nID];    //占有するメモリの解放
		m_apScene[workPriority][workID] = NULL;    //NULLにする
		m_nNumScene--;               //総数1減らす
	}
}

//シーンオブジェのポイントを返す
CScene *CScene::GetScene(int nIdxScene,int nPriority)
{
	return m_apScene[nPriority][nIdxScene];
}

//オブジェタイプをセット
void CScene::SetObjType(OBJTYPE objType)
{
	m_Objtype = objType;
}

//オブジェタイプをゲット
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_Objtype;
}

//オブジェクト総数を返す
int CScene::GetNumScene(void)
{
	return m_nNumScene;
}