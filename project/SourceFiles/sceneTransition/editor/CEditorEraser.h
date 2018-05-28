#pragma once
#ifndef _CEDITOR_ERASER_H_
#define _CEDITOR_ERASER_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CEditorEraser : public CScene2D
{
public:
	CEditorEraser();
	CEditorEraser(int nPriority = 3);
	~CEditorEraser();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEditorEraser *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	static int GetPriority(void) { return s_nPriority; }
private:
	static int s_nPriority;
};

#endif