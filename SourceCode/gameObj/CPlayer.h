#pragma once

#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "main.h"
#include "scene2D.h"
#include "Particle.h"

//�O���錾
class CScene2D;

class CPlayer:public CScene2D
{
public:
	CPlayer();
	CPlayer(int nPriority = 3);
	~CPlayer();

	//Init,Uninit,Update,Draw�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�Q�b�^�[
	D3DXVECTOR3 GetSpeed(void);
	D3DXVECTOR3 GetPosOld(void);
	int GetPlayerId(void);
	bool GetMouseLock(void) { return m_MouseLock; }
	bool GetDirectionYes(void) { return m_bDirectionYes; }
	bool GetMoveDirection(void) { return m_bMoveDirection; }

	//�Z�b�^�[
	void AddMove(float SpeedX);
	void SetPosition(const D3DXVECTOR3& playerPos);
	void SetMouseLock(bool mouseLookFlag) { m_MouseLock = mouseLookFlag; }
	void SetMoveDirection(bool MoveDirection) { m_bMoveDirection = MoveDirection; }
	void SetDirectionYes(bool DirectionYes) { m_bDirectionYes = DirectionYes; }
	void AddPowerX(float AddPowerX) { m_Power.x += AddPowerX; }

	//���̊֐�
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	static int GetPriority(void) { return s_nPriority; }
	
private:
	//�����o�֐�
	bool GameNotStart(void);          //�Q�[���n�܂�O�̏���
	void HitFloorBeforeGameStart(void);
	void HitFloorNormal(void);
	void HitFloor(void);             //�n�ʂɑ΂��铖�蔻��
	void HitFloorCanNotMove(void);   //�ǂɛƂ������̑΍�
	void HitOtherPlayer(void);
	void PushOtherPlayer(int SceneID);
	void ChangeDirectionSeeOtherPlayer(void);
	void ChangeDirectionSeeOtherPlayerGameNotStart(void);
	void MouseCreatePlayerGuild(bool bHitPlayerAndFloor);
	void SetEarthquake(void);
	void PlayHitSound(void);
	void MoveParticle(void);                     //�ړ��̎��̃p�[�e�B�N��

	//�����o�ϐ�
	D3DXVECTOR3				m_posOld;		// �|���S���̌Â��ʒu
	D3DXVECTOR3				m_speed;	    // �|���S���̑��x
	D3DXVECTOR3             m_speedOld;
	D3DXVECTOR3             m_Power;
	int                     m_PlayerID;
	bool m_StandFloor;                     //�n�ʂɗ����Ă�
	bool m_StandFloorOld;                  //�Â��ʒu
	bool m_MouseLock;                      //�}�E�X�ɑI�����ꂽ���
	bool m_bMoveDirection;                 //�i�s����
	bool m_bDirectionYes;                  //�i�s�������łɌ��܂��Ă��邩�ǂ���

	//�p�[�e�B�N���֘A
	CParticle *m_Particle;
	CParticle *m_ParticleHitFloor;
	int m_HitFloorTime;
	static int s_nPriority;
};

#endif