#pragma once
#ifndef _CJUDGE_H_
#define _CJUDGE_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CJudge : public CScene2D
{
public:
	CJudge();
	CJudge(int nPriority = 3);
	~CJudge();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CJudge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha ,const RGB& rgb,bool bAlphaBlend,const D3DXVECTOR2& UV, const D3DXVECTOR2& UVHW, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�

	//�Q�b�^�[
	bool GetMouseLock(void) { return m_bMouseLock; }
	static int GetPriority(void) { return s_nPriority; }

	//�Z�b�^�[
	void SetMouseLock(bool MouseLock) { m_bMouseLock = MouseLock; }
	void SetAlphaBlend(bool AlphaBlend) { m_bAlphaBlend = AlphaBlend; }

	//���̊֐�
	void AddPosY(float AddY) { m_pos.y += AddY; }
private:
	bool m_bMouseLock;
	bool m_bAlphaBlend;
	static int s_nPriority;
};

#endif