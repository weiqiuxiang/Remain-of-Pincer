#pragma once
#ifndef _CSCENE_TRA_BOTTON_H_
#define _CSCENE_TRA_BOTTON_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CSceneTraBotton : public CScene2D
{
public:
	CSceneTraBotton();
	CSceneTraBotton(int nPriority = 3);
	~CSceneTraBotton();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSceneTraBotton *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	static int GetPriority(void) { return s_nPriority; }

	//�Z�b�^�[
	void SetScale(float fScale) { m_Scale = max(0.1f, fScale); }
private:
	D3DXVECTOR3 m_OriginSize;                     //���̃T�C�Y
	float m_Scale;
	static int s_nPriority;
};

#endif