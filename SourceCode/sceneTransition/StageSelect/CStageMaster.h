#pragma once
#ifndef _CSTAGE_MASTER_H_
#define _CSTAGE_MASTER_H_

#include "main.h"
#include "CTitleTraBotton.h"
#include "CFontUIScale.h"
#include "CScoreScale.h"
#include "CFontUI.h"

#define STAGE_MAX (24)

class CStageMaster
{
public:
	static void Init(void);
	static void Update(void);
	static void Uninit(void);

	static void CreateStageSelectBar(void);
private:
	static int HitCheckMouseAndTitleObj(void);  //マウスとタイトルオブジェの当り判定(オブジェクトのシーン遷移タイプを返す)
	static void TraBottonScaleUp(int nStageNum);
	static void TraBottonScaleDown(int nStageNum);
	static void TraBottonScaleDownNotHit(int nStageNum);
	static void Transition(int nStageNum);
	static void DeleteAllStageSelectObj(void);
	static void RightClickReturnTitle(void);
	static void ClickBarTopAndBottom(void);

	//ステージ選択バーの動作関数
	static void ScrollBarLeftClick(void);
	static void ScrollBarMouseWheel(void);
	static void SetSelectBarPos(void);

	static D3DXVECTOR3   m_ScrollBarPos;
	static float         m_ScrollBarHeight;
	static D3DXVECTOR3   m_SelectBarPos;
	static float         m_SelectBarHeight;
	static D3DXVECTOR3   m_ScrollBarPosNow;

	static CTitleTraBotton* m_StageTraBotton[STAGE_MAX];
	static CFontUIScale* m_Rank[STAGE_MAX];
	static CFontUIScale* m_StageFont[STAGE_MAX];
	static CScoreScale* m_StageNumber[STAGE_MAX];
	static CFontUIScale* m_ClearFont[STAGE_MAX];
	static CFontUI* m_BarTop;
	static CFontUI* m_BarBottom;
};

#endif