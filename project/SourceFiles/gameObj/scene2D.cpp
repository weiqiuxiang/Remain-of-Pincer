#include "SceneTransition.h"
#include "scene2D.h"
#include "renderer.h"
#include "CEarthquake.h"

int CScene2D::s_nPriority = 3;

CScene2D::CScene2D() : CScene(3)
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_UV = D3DXVECTOR2(0.0f,0.0f);
	m_UVWH = D3DXVECTOR2(1.0f,1.0f);
	m_powerBetween = { 0,0 };
	m_mass = 1.0f;
	m_pVtxBuff = NULL;
	m_TEX_ID = -1;
	m_nAlpha = 255;
	m_Color = { 255, 255, 255 };
}

CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_UV = D3DXVECTOR2(0.0f, 0.0f);
	m_UVWH = D3DXVECTOR2(1.0f, 1.0f);
	m_powerBetween = { 0,0 };
	m_mass = 1.0f;
	m_pVtxBuff = NULL;
	m_TEX_ID = -1;
	m_nAlpha = 255;
	m_Color = { 255, 255, 255 };
}

CScene2D::~CScene2D()
{

}

//�|���S���`��֐�
HRESULT CScene2D::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();

	// �|���S���̈ʒu��ݒ�
	m_pos = pos;
	m_size = size;
	m_pVtxBuff = NULL;
	m_UV = D3DXVECTOR2(0.0f, 0.0f);
	m_UVWH = D3DXVECTOR2(1.0f, 1.0f);
	m_TEX_ID = -1;
	m_nAlpha = 255;
	m_Color = { 255, 255, 255 };

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	VertexLock();      //���_���b�N

	return S_OK;
}

//�|���S���̉���֐�
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	this->Release();
}

//�|���S���X�V�֐�
void CScene2D::Update(void)
{
	
}

//�`��֐�
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));                     //VRAM����GPU�Ƀf�[�^���X�g���[��

																					   // ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CTexManager::UseTex(m_TEX_ID));												 //�e�N�X�`���̐ݒ�

																					 // �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);                                  //�`��
}

//CScene2D�̃C���X�^���X�𐶐�����֐�
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D(s_nPriority);
	pScene2D->Init(pos, size); //������
	pScene2D->LoadTexture(filePass);     //�e�N�X�`���ǂݍ���
	return pScene2D;
}

void CScene2D::BindTexture(TEX_ID TexID)
{
	//��������������|�C���g
	m_TEX_ID = TexID;
}

HRESULT CScene2D::LoadTexture(const char* filePass)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();

	m_TEX_ID = CTexManager::LoadTex(filePass);

	return S_OK;
}

void CScene2D::VertexLock(void)
{
	VERTEX_2D *pVtx = NULL;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();

	D3DXVECTOR3 HalfSize = m_size * 0.5;

	// ���_����ݒ�
	/***************************���z�A�h���X���擾���o�b�t�@�����b�N����************************************/
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���[�J�����W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - HalfSize.x, m_pos.y - HalfSize.y + CEarthquake::GetChangeY(), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + HalfSize.x, m_pos.y - HalfSize.y + CEarthquake::GetChangeY(), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - HalfSize.x, m_pos.y + HalfSize.y + CEarthquake::GetChangeY(), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + HalfSize.x, m_pos.y + HalfSize.y + CEarthquake::GetChangeY(), 0.0f);

	pVtx[0].tex = D3DXVECTOR2(m_UV.x, m_UV.y);
	pVtx[1].tex = D3DXVECTOR2(m_UV.x + m_UVWH.x, m_UV.y);
	pVtx[2].tex = D3DXVECTOR2(m_UV.x, m_UV.y + m_UVWH.y);
	pVtx[3].tex = D3DXVECTOR2(m_UV.x + m_UVWH.x, m_UV.y + m_UVWH.y);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].color = D3DCOLOR_RGBA(m_Color.r, m_Color.g, m_Color.b, m_nAlpha);
	pVtx[1].color = D3DCOLOR_RGBA(m_Color.r, m_Color.g, m_Color.b, m_nAlpha);
	pVtx[2].color = D3DCOLOR_RGBA(m_Color.r, m_Color.g, m_Color.b, m_nAlpha);
	pVtx[3].color = D3DCOLOR_RGBA(m_Color.r, m_Color.g, m_Color.b, m_nAlpha);

	m_pVtxBuff->Unlock();
}

//�ʒu�擾
D3DXVECTOR3 CScene2D::GetPos(void)
{
	return m_pos;
}

D3DXVECTOR3 CScene2D::GetSize(void)
{
	return m_size;
}

void CScene2D::SetAlpha(int nValue)
{
	if (nValue > 255) { m_nAlpha = 255; return; }
	if (nValue < 0) { m_nAlpha = 0; return; }
	m_nAlpha = nValue;
}

void CScene2D::ChangeAlpha(int ChangeValue)
{
	m_nAlpha += ChangeValue;
	if (m_nAlpha > 255) {m_nAlpha = 255; return;}
	if (m_nAlpha < 0) { m_nAlpha = 0; return; }
}

void CScene2D::PowerReset(void)
{
	m_powerBetween = {0,0};
}

void CScene2D::AddPowerX(float fPowerX)
{
	if(fPowerX < 0) m_powerBetween.powerLeft = fPowerX;
	else m_powerBetween.powerRight = fPowerX;
}

void CScene2D::AddPowerY(float fPowerY)
{
	
}

void CScene2D::SetColor(const RGB &Color) {
	m_Color.r = max(0, Color.r);
	m_Color.r = min(255, m_Color.r);
	m_Color.g = max(0, Color.g);
	m_Color.g = min(255, m_Color.g);
	m_Color.b = max(0, Color.b);
	m_Color.b = min(255, m_Color.b);
}
void CScene2D::SetColor(const RGBA &Color) {
	m_Color.r = max(0, Color.r);
	m_Color.r = min(255, m_Color.r);
	m_Color.g = max(0, Color.g);
	m_Color.g = min(255, m_Color.g);
	m_Color.b = max(0, Color.b);
	m_Color.b = min(255, m_Color.b);
	m_nAlpha = max(0, Color.a);
	m_nAlpha = min(255, m_nAlpha);
}