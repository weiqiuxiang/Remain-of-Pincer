#pragma once
#ifndef _CPLAYER_SELECTER_EF_H_
#define _CPLAYER_SELECTER_EF_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CPlayerSelecterEF : public CScene2D
{
public:
	CPlayerSelecterEF();
	CPlayerSelecterEF(int nPriority = 3);
	~CPlayerSelecterEF();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayerSelecterEF *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha, const RGB& rgb, bool bAlphaBlend , const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	static int GetPriority(void) { return s_nPriority; }

	//�Z�b�^�[
	void SetAlphaBlend(bool AlphaBlend) { m_bAlphaBlend = AlphaBlend; }
	void SetScale(float fScale) { m_Scale = max(0.1f, fScale); }
private:
	bool m_bAlphaBlend;
	static int s_nPriority;
	D3DXVECTOR3 m_OriginSize;                     //���̃T�C�Y
	float m_Scale;
};

#endif