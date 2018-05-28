#pragma once

#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"
#include "TexManager.h"

//�O���錾
class CScene;

typedef struct
{
	float powerLeft;
	float powerRight;
}BETWEEN_POWTER;

class CScene2D : public CScene
{
public:
	CScene2D();
	CScene2D(int nPriority = 3);
	~CScene2D();

	//Init,Uninit,Update,Draw�֐�
	HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�Q�b�^�[
	D3DXVECTOR3 GetPos(void);                    //�ʒu�擾
	D3DXVECTOR3 GetSize(void);
	int GetAlpha(void) { return m_nAlpha; }

	//�Z�b�^�[
	void SetUV(const D3DXVECTOR2& UV) { m_UV = UV; }
	void SetUVWH(const D3DXVECTOR2& UVWH) { m_UVWH = UVWH; }
	void SetPos(const D3DXVECTOR3& pos) {m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size) { m_size = size; }
	void SetAlpha(int nValue);
	void SetColor(const RGB &Color);            //�F�ݒ�
	void SetColor(const RGBA &Color);           //�F�ݒ�
	void ChangePos(const D3DXVECTOR3& PosValue) { m_pos += PosValue; }
	void AddPowerX(float fPowerX);
	void AddPowerY(float fPowerY);
	void PowerReset(void);                       //�󂯂�͂����Z�b�g
	void ChangeAlpha(int ChangeValue);             //ALPHA���C���[�̒l�����X�ύX������
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	void BindTexture(TEX_ID TexID);                                        //�O�̃e�N�X�`����ǂݍ���
	HRESULT LoadTexture(const char* filePass);                                                //�Ή��ǂݍ��݃e�N�X�`����
	static int GetPriority(void) { return s_nPriority; }
private:
	TEX_ID		m_TEX_ID;		// �e�N�X�`���ւ̃|�C���^
	static int s_nPriority;
protected:
	void VertexLock(void);                  //���_���b�N

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_size;			// �|���S���̃T�C�Y
	BETWEEN_POWTER			m_powerBetween;	// �I�u�W�F���󂯂����ޗ�
	D3DXVECTOR2             m_UV;           //UV���_
	D3DXVECTOR2             m_UVWH;         //UV�̕��ƍ���
	float                   m_mass;         // ����
	int                     m_nAlpha;        //�A���t�@�l
	RGB                     m_Color;        //�F
	bool m_bLoadTexture;                    //�e�N�X�`���ǂݍ��܂ꂽ���̃t���O
};

#endif