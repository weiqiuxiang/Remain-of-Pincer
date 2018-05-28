#pragma once
#ifndef _CTITLE_TRA_BOTTON_H_
#define _CTITLE_TRA_BOTTON_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CTitleTraBotton : public CScene2D
{
public:
	typedef enum
	{
		TYPE_STARTGAME = 0,
		TYPE_TUTORIAL,
		TYPE_EXIT,
		TYPE_STAGE_NUM,
	}TRA_TYPE;

	CTitleTraBotton();
	CTitleTraBotton(int nPriority = 3);
	~CTitleTraBotton();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�Z�b�^�[
	void SetStageNum(int StageNum) {m_nStageNum = StageNum;}

	//�Q�b�^�[
	D3DXVECTOR3 GetOriginSize(void) { return m_sizeOrigin; }
	TRA_TYPE GetTraType(void) { return m_TraType; }
	static int GetPriority(void) { return s_nPriority; }
	int GetStageNum(void) { return m_nStageNum; }

	//���̊֐�
	static CTitleTraBotton *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TRA_TYPE TraType, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	static CTitleTraBotton *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nStageNum, const char* filePass);
private:
	D3DXVECTOR3 m_sizeOrigin;
	TRA_TYPE    m_TraType;
	int m_nStageNum;
	static int s_nPriority;
};

#endif