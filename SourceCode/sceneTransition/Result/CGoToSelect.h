#pragma once
#ifndef _GOTOSELECT_BOTTON_H_
#define _GOTOSELECT_BOTTON_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CGoToSelect : public CScene2D
{
public:
	CGoToSelect();
	CGoToSelect(int Priority);
	~CGoToSelect();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int alpha);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGoToSelect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass, int alpha);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	static int GetPriority(void) { return s_nPriority; }
private:
	static int s_nPriority;
};

#endif