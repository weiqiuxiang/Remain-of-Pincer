#pragma once
#ifndef _CWORM_HOLE_H_
#define _CWORM_HOLE_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CWormHole : public CScene2D
{
public:
	CWormHole();
	CWormHole(int nPriority = 3);
	~CWormHole();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWormHole *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha, const RGB& rgb, bool bAlphaBlend , const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	static int GetPriority(void) { return s_nPriority; }

	//�Z�b�^�[
	void SetAlphaBlend(bool AlphaBlend) { m_bAlphaBlend = AlphaBlend; }
	void SetWarpFlag(bool WarpFlag) { m_WarpFlag = WarpFlag; }

	//�Q�b�^�[
	bool GetWarpFlag(void) { return m_WarpFlag; }
private:
	bool m_WarpFlag;
	bool m_bAlphaBlend;
	static int s_nPriority;
};

#endif