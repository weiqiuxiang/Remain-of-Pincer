#pragma once
#ifndef _CPLAYER_ARROW_H_
#define _CPLAYER_ARROW_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CPlayerArrow : public CScene2D
{
public:
	CPlayerArrow();
	CPlayerArrow(int nPriority = 3);
	~CPlayerArrow();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayerArrow *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�

	//�Q�b�^�[
	bool GetMouseLock(void) { return m_bMouseLock; }
	static int GetPriority(void) { return s_nPriority; }

	//�Z�b�^�[
	void SetMouseLock(bool MouseLock) { m_bMouseLock = MouseLock; }
private:
	bool m_bMouseLock;
	static int s_nPriority;
};

#endif