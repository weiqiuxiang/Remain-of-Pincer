#pragma once
#ifndef _CPAUSE_H_
#define _CPAUSE_H_

#include "main.h"
#include "CPauseObj.h"

class CPause
{
public:
	static void Init(void);
	static void CreatePauseBar(void);
	static void DelectAllPauseObj(void);
	static void HitCheckMouseAndPauseObj(void);

	//ゲッター
	static bool GetHelpFlag(void) { return m_bHelpFlag; }
private:
	//メンバ関数
	static void HitFontResume(void);
	static void HitFontHelp(void);
	static void HitFontRetire(void);
	static void HitFontTitle(void);
	static void HitFontStageSelect(void);

	//メンバ変数
	static CPauseObj* m_MenuBar;
	static CPauseObj* m_FontResume;
	static CPauseObj* m_FontHelp;
	static CPauseObj* m_FontRitire;
	static CPauseObj* m_FontReturnTitle;
	static CPauseObj* m_FontReturnStageSelect;
	static CPauseObj* m_FontResumeEF;
	static CPauseObj* m_FontHelpEF;
	static CPauseObj* m_FontRitireEF;
	static CPauseObj* m_FontReturnTitleEF;
	static CPauseObj* m_FontReturnStageSelectEF;
	static CPauseObj* m_HelpImage;
	static bool m_bHelpFlag;
};

#endif