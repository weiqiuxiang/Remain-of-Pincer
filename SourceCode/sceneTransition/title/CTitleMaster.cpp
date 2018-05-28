#include "CTitleMaster.h"
#include "hitCheck.h"
#include "SceneTransition.h"
#include "CGameStage.h"
#include "CFontUI.h"
#include "CScrollBar.h"
#include "sound.h"
#include "CTitle.h"
#include <time.h>

#define SCALE_VALUE (1.2)
#define TIME_SCALE (30)
#define STAGE_NUM (6)

#define SOUND_VOLUME_ADD (0.005f)

// �ÓI�����o�ϐ�
CLetter* CTitleMaster::m_Letter[12] = {};
CPillar* CTitleMaster::m_PillarL = NULL;
CPillar* CTitleMaster::m_PillarR = NULL;
CParticle* CTitleMaster::m_ParticleL = NULL;
CParticle* CTitleMaster::m_ParticleR = NULL;
bool CTitleMaster::m_bPlayHasamiSoundOneTime = false;

CTitleMaster::TITLESTEP CTitleMaster::m_step = CTitleMaster::TITLESTEP_1;
float CTitleMaster::m_bottom = 0;
int CTitleMaster::m_timer = 0;

HWND CTitleMaster::m_hWnd;

void CTitleMaster::Init(void)
{
	srand((unsigned)time(0));	// �����ݒ�

	m_step = TITLESTEP_1;
	m_bottom = 460.0f;
	m_bPlayHasamiSoundOneTime = false;
}

void CTitleMaster::Update(void)
{
	AnimeTitle();

	CTitleTraBotton *pTitleTra = HitCheckMouseAndTitleObj();     //�}�E�X�ƃ^�C�g���I�u�W�F�N�g�̓��蔻��
	TraBottonScaleUp(pTitleTra);                                 //���蔻�肪�������^�C�g���I�u�W�F�N�g�̃X�P�[���A�b�v
	TraBottonScaleDownNotHit(pTitleTra);                         //���蔻�肪�Ȃ��^�C�g���I�u�W�F�̃X�P�[������
	Transition(pTitleTra);                                       //�}�E�X�̍��N���b�N����
}

void CTitleMaster::AnimeTitle(void)
{
	switch (m_step)
	{
	case TITLESTEP_1: // �ҋ@
		if (m_timer > 160)
		{
			for (int i = 0; i < NUM_MAX_LETTER; i++)
			{
				if (NULL == m_Letter[i]) continue;

				m_Letter[i]->SetVelocity(D3DXVECTOR3(0.0f, rand() % 4 + 2.0f, 0.0f));
				m_Letter[i]->SetDeltaRot((1 - rand() % 3) * 0.1f);
				m_Letter[i]->SetEndPos(D3DXVECTOR3(m_Letter[i]->GetPos().x, m_Letter[i]->GetBottom() - m_Letter[i]->GetSize().y * 0.5f, 0.0f));
				m_Letter[i]->SetFall(false);
				m_Letter[i]->SetPushedL(false);
				m_Letter[i]->SetPushedR(false);
			}
			m_step = TITLESTEP_2;
			m_timer = 0;
		}
		m_timer++;
		break;

	case TITLESTEP_2: // �����̗���
		for (int i = 0; i < NUM_MAX_LETTER; i++)
		{
			if (NULL == m_Letter[i]) continue;

			m_Letter[i]->AddVelocity(D3DXVECTOR3(0.0f, 0.8f, 0.0f));
			m_Letter[i]->AddPos(m_Letter[i]->GetVelocity());
			m_Letter[i]->AddRot(m_Letter[i]->GetDeltaRot());
			if (m_Letter[i]->GetPos().y > m_Letter[i]->GetEndPos().y)
			{
				m_Letter[i]->SetPos(m_Letter[i]->GetEndPos());
				m_Letter[i]->SetRot(m_Letter[i]->GetEndRot());
			}
		}

		if (m_timer > 80)
		{
			m_step = TITLESTEP_3;
			m_timer = 0;

			m_PillarL->SetEndPos(D3DXVECTOR3(0.0f + TITLE_RELETIVE_X, 20.0f + TITLE_RELETIVE_Y, 0.0f));
			m_PillarR->SetEndPos(D3DXVECTOR3(600.0f + TITLE_RELETIVE_X, 20.0f + TITLE_RELETIVE_Y, 0.0f));
			m_PillarL->SetVelocity((m_PillarL->GetEndPos() - m_PillarL->GetPos()) * 0.05f);
			m_PillarR->SetVelocity((m_PillarR->GetEndPos() - m_PillarR->GetPos()) * 0.05f);

			for (int i = 0; i < NUM_MAX_LETTER; i++)
			{
				m_Letter[i]->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		m_timer++;
		break;

	case TITLESTEP_3:  // ������Ɉړ�
		if (NULL == m_PillarL) break;

		m_PillarL->AddPos(m_PillarL->GetVelocity());
		if (m_PillarL->GetPos().y < m_PillarL->GetEndPos().y)
		{
			m_PillarL->SetPos(m_PillarL->GetEndPos());
		}

		if (NULL == m_PillarR) break;
		m_PillarR->AddPos(m_PillarR->GetVelocity());
		if (m_PillarR->GetPos().y < m_PillarR->GetEndPos().y)
		{
			m_PillarR->SetPos(m_PillarR->GetEndPos());
		}

		if (m_timer > 80)
		{
			m_PillarL->SetEndPos(D3DXVECTOR3(m_PillarL->GetPos().x, m_bottom - m_PillarL->GetSize().y * 0.5f, 0.0f));
			m_PillarR->SetEndPos(D3DXVECTOR3(m_PillarR->GetPos().x, m_bottom - m_PillarR->GetSize().y * 0.5f, 0.0f));
			m_PillarL->SetVelocity(D3DXVECTOR3(0.0f, 8.0f, 0.0f));
			m_PillarR->SetVelocity(D3DXVECTOR3(0.0f, 8.0f, 0.0f));
			m_step = TITLESTEP_4;
			m_timer = 0;
		}
		m_timer++;

		break;

	case TITLESTEP_4: // ��������
		if (NULL == m_PillarL) break;

		m_PillarL->AddPos(m_PillarL->GetVelocity());
		if (m_PillarL->GetPos().y > m_PillarL->GetEndPos().y)
		{
			m_PillarL->SetPos(m_PillarL->GetEndPos());
		}

		if (NULL == m_PillarR) break;

		m_PillarR->AddPos(m_PillarR->GetVelocity());
		if (m_PillarR->GetPos().y > m_PillarR->GetEndPos().y)
		{
			m_PillarR->SetPos(m_PillarR->GetEndPos());

			// �p�[�e�B�N���̍쐬
			if (NULL == m_ParticleL)
			{
				m_ParticleL = CParticle::Create(m_PillarL->GetPos().x, m_PillarL->GetPos().y + m_PillarL->GetSize().y * 0.5f, 0.000, 0.000, 65.900, 65.900, 65.900, 0.009, 0.009, 0.009, 2.800, 2.800, 2.800, -0.008, -0.008, -0.008, 9, 46.000, 0.000, 0.000, 0.61, 0.46, 0.34, 0.38, 0.000, -6.400, 0.000, 5.000, 5.000, 5.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 199.000, 0.000, 0.00, 0.00, 0.00, 0.00, 0, -1, RESULT_PARTICLE_01);
				m_timer = 0;
				PlaySound(SE_HASAMU);              //������	
			}

			if (NULL == m_ParticleR)
			{
				m_ParticleR = CParticle::Create(m_PillarR->GetPos().x, m_PillarR->GetPos().y + m_PillarR->GetSize().y * 0.5f, 0.000, 0.000, 65.900, 65.900, 65.900, 0.009, 0.009, 0.009, 2.800, 2.800, 2.800, -0.008, -0.008, -0.008, 9, 46.000, 0.000, 0.000, 0.61, 0.46, 0.34, 0.38, 0.000, -6.400, 0.000, 5.000, 5.000, 5.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 199.000, 0.000, 0.00, 0.00, 0.00, 0.00, 0, -1, RESULT_PARTICLE_01);
				m_timer = 0;
			}
		}

		if (NULL != m_ParticleL && m_timer > 2)
		{
			m_ParticleL->SetStop(true);
			m_ParticleR->SetStop(true);
		}

		if (m_timer > 80)
		{
			m_PillarL->SetVelocity(D3DXVECTOR3(8.0f, 0.0f, 0.0f));
			m_PillarR->SetVelocity(D3DXVECTOR3(-8.0f, 0.0f, 0.0f));
			m_step = TITLESTEP_5;
			m_timer = 0;

			m_ParticleL = CParticle::Create(m_PillarL->GetPos().x, m_PillarL->GetPos().y, 0.000,
				0.000, 65.900, 65.900, 65.900,
				0.000, 0.000, 0.000,
				3.100, 3.100, 3.100,
				0.042, 0.042, 0.042,
				5, 60.000, 0.000, 0.000,
				0.61, 0.46, 0.00, 0.17, 0.000, -6.400, 0.000, 5.000, 5.000, 5.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 199.000, 0.000, 0.00, 0.00, 0.00, 0.00, 0, -1, PARTICLE_EF02_TEX);

			m_ParticleR = CParticle::Create(m_PillarR->GetPos().x, m_PillarR->GetPos().y, 0.000,
				0.000, 65.900, 65.900, 65.900,
				0.000, 0.000, 0.000,
				3.100, 3.100, 3.100,
				0.042, 0.042, 0.042,
				5, 60.000, 0.000, 0.000,
				0.61, 0.46, 0.00, 0.17, 0.000, -6.400, 0.000, 5.000, 5.000, 5.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 199.000, 0.000, 0.00, 0.00, 0.00, 0.00, 0, -1, PARTICLE_EF02_TEX);
		}
		m_timer++;

		break;

	case TITLESTEP_5: // ��������������
					  // �p�[�e�B�N���̈ړ�
		m_ParticleL->SetPosX(m_PillarL->GetPos().x);
		m_ParticleL->SetPosY(m_PillarL->GetPos().y + m_PillarL->GetSize().y * 0.5f);
		m_ParticleR->SetPosX(m_PillarR->GetPos().x);
		m_ParticleR->SetPosY(m_PillarR->GetPos().y + m_PillarR->GetSize().y * 0.5f);

		HitPillarAndLetter();
		if (NULL == m_PillarL || NULL == m_PillarR) break;

		m_PillarL->AddPos(m_PillarL->GetVelocity());
		m_PillarR->AddPos(m_PillarR->GetVelocity());
		for (int i = 0; i < NUM_MAX_LETTER; i++)
		{
			if (NULL == m_Letter[i]) continue;

			m_Letter[i]->AddPos(m_Letter[i]->GetVelocity());
		}

		if (m_timer > 120)
		{
			// ��ʊO�ŕ�������ׂȂ�������
			m_PillarL->SetEndPos(D3DXVECTOR3(m_PillarL->GetStartPos().x, m_PillarL->GetStartPos().y + 1000.0f, 0.0f));
			m_PillarR->SetEndPos(D3DXVECTOR3(m_PillarR->GetStartPos().x, m_PillarR->GetStartPos().y + 1000.0f, 0.0f));
			m_PillarL->SetVelocity(D3DXVECTOR3(0.0f, 8.0f, 0.0f));
			m_PillarR->SetVelocity(D3DXVECTOR3(0.0f, 8.0f, 0.0f));

			for (int i = 0; i < NUM_MAX_LETTER; i++)
			{
				if (NULL == m_Letter[i]) continue;

				m_Letter[i]->SetEndPos(D3DXVECTOR3(m_Letter[i]->GetStartPos().x, m_Letter[i]->GetStartPos().y + 1000.0f, 0.0f));
			}

			// �p�[�e�B�N��������
			if (NULL != m_ParticleL)
			{
				m_ParticleL->Uninit();
				m_ParticleL = NULL;
			}

			if (NULL != m_ParticleR)
			{
				m_ParticleR->Uninit();
				m_ParticleR = NULL;
			}

			m_step = TITLESTEP_6;
			m_timer = 0;
		}
		m_timer++;

		break;

	case TITLESTEP_6: // ��������
		if (NULL == m_PillarL || NULL == m_PillarR) break;

		m_PillarL->AddVelocity(D3DXVECTOR3(0.0f, 0.6f, 0.0f));
		m_PillarR->AddVelocity(D3DXVECTOR3(0.0f, 0.6f, 0.0f));
		m_PillarL->AddPos(m_PillarL->GetVelocity());
		m_PillarR->AddPos(m_PillarR->GetVelocity());

		if (m_timer > 120)
		{
			// ��������ׂȂ����A�ړ��x�N�g���A�ړ���ݒ�
			m_PillarL->SetPos(m_PillarL->GetEndPos());
			m_PillarR->SetPos(m_PillarR->GetEndPos());
			m_PillarL->SetVelocity(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
			m_PillarR->SetVelocity(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
			m_PillarL->SetEndPos(m_PillarL->GetStartPos());
			m_PillarR->SetEndPos(m_PillarR->GetStartPos());

			for (int i = 0; i < NUM_MAX_LETTER; i++)
			{
				if (NULL == m_Letter[i]) continue;

				m_Letter[i]->SetPos(m_Letter[i]->GetEndPos());
				m_Letter[i]->SetVelocity(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
				m_Letter[i]->SetEndPos(m_Letter[i]->GetStartPos());
				m_Letter[i]->SetRot(0.0f);
			}

			m_step = TITLESTEP_7;
			m_timer = 0;
		}

		m_timer++;

		break;

	case TITLESTEP_7: // ����������オ��
		if (NULL == m_PillarL || NULL == m_PillarR) break;

		m_PillarL->AddPos(m_PillarL->GetVelocity());
		m_PillarR->AddPos(m_PillarR->GetVelocity());

		// �ړ�����
		if (m_PillarL->GetPos().y < m_PillarL->GetEndPos().y)
		{
			m_PillarL->SetPos(m_PillarL->GetEndPos());
		}

		if (m_PillarR->GetPos().y < m_PillarR->GetEndPos().y)
		{
			m_PillarR->SetPos(m_PillarR->GetEndPos());
		}

		for (int i = 0; i < NUM_MAX_LETTER; i++)
		{
			if (NULL == m_Letter[i]) continue;

			m_Letter[i]->AddPos(m_Letter[i]->GetVelocity());

			// �ړ�����
			if (m_Letter[i]->GetPos().y < m_Letter[i]->GetEndPos().y)
			{
				m_Letter[i]->SetPos(m_Letter[i]->GetEndPos());
			}
		}

		if (m_timer > 240)
		{
			m_step = TITLESTEP_1;
			m_bPlayHasamiSoundOneTime = false;
			m_timer = 0;
		}

		m_timer++;

		break;
	}
}

void CTitleMaster::HitPillarAndLetter(void)
{
	int nHitNum = 0;
	for (int i = 0; i < NUM_MAX_LETTER; i++)
	{
		// ��������
		if (m_Letter[i]->GetFall())
		{
			m_Letter[i]->AddVelocity(D3DXVECTOR3(0.0f, 0.6f, 0.0f));
			nHitNum++;
		}
		else
		{
			// �����牟�����
			if (m_Letter[i]->GetPos().x - m_Letter[i]->GetSize().x * 0.5f < m_PillarL->GetPos().x + m_PillarL->GetSize().x * 0.5f)
			{
				m_Letter[i]->SetPos(D3DXVECTOR3(m_PillarL->GetPos().x + m_Letter[i]->GetSize().x * 0.5f, m_Letter[i]->GetPos().y, 0.0f));
				m_Letter[i]->SetPushedL(true);
			}

			// �E���牟�����
			if (m_Letter[i]->GetPos().x + m_Letter[i]->GetSize().x * 0.5f > m_PillarR->GetPos().x - m_PillarR->GetSize().x * 0.5f)
			{
				m_Letter[i]->SetPos(D3DXVECTOR3(m_PillarR->GetPos().x - m_Letter[i]->GetSize().x * 0.5f, m_Letter[i]->GetPos().y, 0.0f));
				m_Letter[i]->SetPushedR(true);
			}

			// ���E���牟�����
			if (m_Letter[i]->GetPushedL() && m_Letter[i]->GetPushedR())
			{
				m_Letter[i]->SetVelocity(D3DXVECTOR3(0.0f, -8.0f, 0.0f));
				m_Letter[i]->SetFall(true);
			}
		}
	}
	if (nHitNum == NUM_MAX_LETTER && m_bPlayHasamiSoundOneTime == false)
	{
		PlaySound(SE_HASAMU);
		m_bPlayHasamiSoundOneTime = true;
	}

	// �����Ԃ�������
	if (m_PillarL->GetPos().x + m_PillarL->GetSize().x * 0.5f > m_PillarR->GetPos().x - m_PillarR->GetSize().x * 0.5f)
	{
		m_PillarL->SetPos(D3DXVECTOR3(m_PillarR->GetPos().x - m_PillarR->GetSize().x * 0.7f, m_PillarR->GetPos().y, 0.0f));
		m_PillarL->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_PillarR->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_ParticleL->SetStop(true);
		m_ParticleR->SetStop(true);
	}
}

CTitleTraBotton *CTitleMaster::HitCheckMouseAndTitleObj(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	int Priority = CTitleTraBotton::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, Priority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_TITLE_TRA_OBJ)
		{
			//NULL�m�F
			CTitleTraBotton *pTitleTraBotton = dynamic_cast <CTitleTraBotton *> (pScene);
			if (pTitleTraBotton == NULL) continue;

			bool hitCheck = CHitCheck::HitPointRect(MousePos, pTitleTraBotton->GetPos(), pTitleTraBotton->GetSize());
			if (hitCheck) return pTitleTraBotton;
			else continue;
		}
	}

	return NULL;
}

void CTitleMaster::TraBottonScaleUp(CTitleTraBotton* pTitleTraBotton)
{
	if (pTitleTraBotton == NULL) return;

	D3DXVECTOR3 size = pTitleTraBotton->GetSize();
	D3DXVECTOR3 sizeOrigin = pTitleTraBotton->GetOriginSize();

	if (size.x < SCALE_VALUE * sizeOrigin.x)
	{
		float fScalePercent = size.x / (SCALE_VALUE * sizeOrigin.x); //���ݔ{��

		fScalePercent += 1.0f / TIME_SCALE;

		if(fScalePercent > 1 )
		{
			pTitleTraBotton->SetSize(SCALE_VALUE * sizeOrigin);
		}

		else
		{
			pTitleTraBotton->SetSize(fScalePercent*SCALE_VALUE * sizeOrigin);
		}
	}

	else
	{
		pTitleTraBotton->SetSize(SCALE_VALUE * sizeOrigin);
	}
}

void CTitleMaster::TraBottonScaleDown(CTitleTraBotton* pTitleTraBotton)
{
	if (pTitleTraBotton == NULL) return;

	D3DXVECTOR3 size = pTitleTraBotton->GetSize();
	D3DXVECTOR3 sizeOrigin = pTitleTraBotton->GetOriginSize();

	if (size.x > sizeOrigin.x)
	{
		float fScalePercent = size.x / (SCALE_VALUE * sizeOrigin.x); //���ݔ{��

		fScalePercent -= 1.0f / TIME_SCALE;

		if (fScalePercent < 0)
		{
			pTitleTraBotton->SetSize(sizeOrigin);
		}

		else
		{
			pTitleTraBotton->SetSize(fScalePercent*SCALE_VALUE * sizeOrigin);
		}
	}
}

void CTitleMaster::TraBottonScaleDownNotHit(CTitleTraBotton* pTitleTraBotton)
{
	int Priority = CTitleTraBotton::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, Priority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_TITLE_TRA_OBJ)
		{
			//NULL�m�F
			CTitleTraBotton *pTitleTra = dynamic_cast <CTitleTraBotton *> (pScene);
			if (pTitleTra == NULL) continue;
			if (pTitleTra == pTitleTraBotton) continue;
			
			TraBottonScaleDown(pTitleTra);
		}
	}
}

void CTitleMaster::Transition(CTitleTraBotton* pTitleTraBotton)
{
	if (pTitleTraBotton == NULL) return;
	CTitleTraBotton::TRA_TYPE TraType = pTitleTraBotton->GetTraType();

	if(CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
	{
		switch (TraType)
		{
		case CTitleTraBotton::TYPE_STARTGAME:
			CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_STAGE_SELECT);
			break;
		case CTitleTraBotton::TYPE_TUTORIAL:
			CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_TUTORIAL);
			CSceneTransition::GetTutorialMaster()->Init();
			break;
		case CTitleTraBotton::TYPE_EXIT:
			DestroyWindow(m_hWnd);
			break;
		}
	}
}

void CTitleMaster::CreateStartExit(void)
{
	CTitleTraBotton::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.7,0.0f), D3DXVECTOR3(297.0f, 93.0f, 0.0f),CTitleTraBotton::TYPE_STARTGAME, START_TEX);
	CTitleTraBotton::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.8, 0.0f), D3DXVECTOR3(423.0f, 79.0f, 0.0f), CTitleTraBotton::TYPE_TUTORIAL, TUTORIAL_FONT_TEX);
	CTitleTraBotton::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.9, 0.0f), D3DXVECTOR3(193.0f, 71.0f, 0.0f), CTitleTraBotton::TYPE_EXIT, EXIT_TEX);
}

void CTitleMaster::DeleteAllTitleObj(void)
{
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;

		nPriority = CTitleTraBotton::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_TITLE_TRA_OBJ)
		{
			//NULL�m�F
			CTitleTraBotton *pTitleTra = dynamic_cast <CTitleTraBotton *> (pScene);
			if (pTitleTra == NULL) continue;
			pTitleTra->Uninit();
		}

		nPriority = CFontUI::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_TUTORIAL_UI)
		{
			CFontUI *pTuUI= dynamic_cast <CFontUI *> (pScene);
			if (pTuUI == NULL) continue;
			pTuUI->Uninit();
		}

		nPriority = CScrollBar::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_SCROLL_BAR)
		{
			CScrollBar *pScrollBar = dynamic_cast <CScrollBar *> (pScene);
			if (pScrollBar == NULL) continue;
			pScrollBar->Uninit();
		}
	}
}

void CTitleMaster::FadeInTitleBgm(void)
{
	float BgmValueNow;
	GetSoundVolume(TITLE_BGM, &BgmValueNow);
	BgmValueNow += SOUND_VOLUME_ADD;
	BgmValueNow = min(0.2f, BgmValueNow);             //�ő�l����
	SetSoundVolume(TITLE_BGM, BgmValueNow);           //BGM�Z�b�g
}