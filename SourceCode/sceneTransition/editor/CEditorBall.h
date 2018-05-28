#pragma once
#ifndef _CEDITOR_BALL_H_
#define _CEDITOR_BALL_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CEditorBall : public CScene2D
{
public:
	CEditorBall();
	CEditorBall(int nPriority);
	~CEditorBall();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEditorBall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	static int GetPriority(void) { return s_nPriority; }
private:
	static int s_nPriority;
};

#endif