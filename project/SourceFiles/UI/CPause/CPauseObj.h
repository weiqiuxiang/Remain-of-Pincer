#pragma once
#ifndef _CPAUSE_OBJ_H_
#define _CPAUSE_OBJ_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CPauseObj : public CScene2D
{
public:
	CPauseObj();
	CPauseObj(int nPriority = 3);
	~CPauseObj();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPauseObj *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha,bool bAlphaBlend, RGB rgb, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�

	//�Q�b�^�[
	static int GetPriority(void) { return s_nPriority; }

	//�Z�b�^�[
	void SetAlphaBlend(bool AlphaBlend) { m_bAlphaBlend = AlphaBlend; }
private:
	bool m_bAlphaBlend;
	static int s_nPriority;
};

#endif