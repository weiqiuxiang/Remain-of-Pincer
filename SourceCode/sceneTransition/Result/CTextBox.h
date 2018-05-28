#pragma once

#ifndef _CTEXTBOX_H_
#define _CTEXTBOX_H_

#include "main.h"
#include "scene2D.h"
#include "CNumber.h"

//�O���錾
class CScene2D;

class CTextBox : public CScene2D
{
public:
	CTextBox();
	CTextBox(int Priority);
	~CTextBox();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, int alpha);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�Z�b�^�[
	void SetPosX(float x) { m_pos.x = x; }
	void SetEndSize(D3DXVECTOR3 endSize) { m_endSize = endSize; }
	void SetDirVec(D3DXVECTOR3 dirVec) { m_dirVec = dirVec; }
	void SetDeltaSize(D3DXVECTOR3 deltaSize) {
		m_deltaSize = deltaSize;
	}
	void AddDirVec(D3DXVECTOR3 value) { m_dirVec += value; }
	void MultiDirVec(float value) { m_dirVec *= value; }

	//�Q�b�^�[
	D3DXVECTOR3 GetEndPos(void) { return m_endPos; }
	D3DXVECTOR3 GetEndSize(void) { return m_endSize; }
	D3DXVECTOR3 GetDirVec(void) { return m_dirVec; }
	D3DXVECTOR3 GetDeltaSize(void) { return m_deltaSize; }
	static int GetPriority(void) { return s_nPriority; }

	//���̊֐�
	void ChangePos(D3DXVECTOR3 value) { m_pos += value; }
	void ChangeSize(D3DXVECTOR3 value) { m_size += value; }
	static CTextBox *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, int alpha, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	
private:
	float m_posU;
	float m_posV;
	D3DXVECTOR3 m_endPos; // �ڕW���W
	D3DXVECTOR3 m_dirVec; // �ڕW���W�ւ̕����x�N�g��
	D3DXVECTOR3 m_endSize; // �ڕW�T�C�Y
	D3DXVECTOR3 m_deltaSize; // �ڕW�T�C�Y�ւ̕ω���
	CNumber *m_apNumber[1];
	static int s_nPriority;
};

#endif

