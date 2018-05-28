#include "scene.h"
#include "scene2D.h"
#include "renderer.h"

//�O���[�o���ϐ�
CScene *CScene::m_apScene[PRIORITY_MAX_NUM][SCENE_MAX_NUM] = {};
int CScene::m_nNumScene = 0;

CScene::CScene()
{
	//static�ϐ��̏�����
	for (int nCntP = 0; nCntP < PRIORITY_MAX_NUM; nCntP++)
	{
		for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
		{
			if (m_apScene[nCntP][nCnt] == NULL)
			{
				m_apScene[nCntP][nCnt] = this;
				m_nID = nCnt;
				m_nPriority = nCntP;
				m_nNumScene++;
				break;
			}
		}
	}
}

CScene::CScene(int nPriority)
{
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		if (m_apScene[nPriority][nCnt] == NULL)
		{
			m_apScene[nPriority][nCnt] = this;
			m_nID = nCnt;
			m_nPriority = nPriority;
			m_nNumScene++;
			break;
		}
	}
}

CScene::~CScene()
{

}

//Init�֐��_�~�[
HRESULT CScene::Init(void)
{
	return S_OK;
}

//���ׂĐ������ꂽ�C���X�^���X�̍X�V����
void CScene::UpdateAll(void)
{
	//�X�V����
	for (int nCntP = 0; nCntP < PRIORITY_MAX_NUM; nCntP++)
	{
		for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
		{
			if (m_apScene[nCntP][nCnt] != NULL)
			{
				m_apScene[nCntP][nCnt]->Update();
			}
		}
	}
}

//���ׂĐ������ꂽ�C���X�^���X�̕`�揈��
void CScene::DrawAll(void)
{
	//�`�揈��
	for (int nCntP = 0; nCntP < PRIORITY_MAX_NUM; nCntP++)
	{
		for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
		{
			if (m_apScene[nCntP][nCnt] != NULL)
			{
				m_apScene[nCntP][nCnt]->Draw();
			}
		}
	}
}

//���ׂĐ������ꂽ�C���X�^���X�̉������
void CScene::ReleaseAll(void)
{
	for (int nCntP = 0; nCntP < PRIORITY_MAX_NUM; nCntP++)
	{
		for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
		{
			if (m_apScene[nCntP][nCnt] != NULL)
			{
				m_apScene[nCntP][nCnt]->Release();
			}
		}
	}
}

//�������g(CScene)���������
void CScene::Release(void)
{
 	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int workID = m_nID;         //m_ID��delete�̌�͂Ȃ��Ȃ邩��,m_ID�̒l��ۑ�����
		int workPriority = m_nPriority;
		delete m_apScene[m_nPriority][m_nID];    //��L���郁�����̉��
		m_apScene[workPriority][workID] = NULL;    //NULL�ɂ���
		m_nNumScene--;               //����1���炷
	}
}

//�V�[���I�u�W�F�̃|�C���g��Ԃ�
CScene *CScene::GetScene(int nIdxScene,int nPriority)
{
	return m_apScene[nPriority][nIdxScene];
}

//�I�u�W�F�^�C�v���Z�b�g
void CScene::SetObjType(OBJTYPE objType)
{
	m_Objtype = objType;
}

//�I�u�W�F�^�C�v���Q�b�g
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_Objtype;
}

//�I�u�W�F�N�g������Ԃ�
int CScene::GetNumScene(void)
{
	return m_nNumScene;
}