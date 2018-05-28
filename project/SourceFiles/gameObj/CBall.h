#pragma once
#ifndef _CBALL_H_
#define _CBALL_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CBall :public CScene2D
{
public:
	CBall();
	CBall(int Priority);
	~CBall();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	void HitFloor(void);
	void HitPlayer(void);
	static int GetPriority(void) { return s_nPriority; }

	//�Q�b�^�[
	bool GetDeadFlag(void) {return m_bDead;}

	D3DXVECTOR3 GetHitSize(void) { return m_HitSize; }

	//���̊֐�
	void AddPowerX(float PowerX) { m_PowerOther.x += PowerX; }
	void VertexLockRorate(float fAngle);

private:
	void BallAliveAction(void);
	void BallDeadAction(void);
	bool GameNotStart();

	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_PowerOther;              //�v���[���[�ȊO�̊O��
	D3DXVECTOR3 m_speed;
	D3DXVECTOR3 m_HitSize;
	bool m_StandFloor;                     //�n�ʂɗ����Ă�
	bool m_bDead;
	int m_nCntChangeUV;
	int m_nCntMotionChange;
	static int s_nPriority;

	float m_fAngle;
	bool m_TexChangeMove;
	bool m_bMoveDir;
};

#endif