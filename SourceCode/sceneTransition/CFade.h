#pragma once
#ifndef _CFADE_H_
#define _CFADE_H_

#include "main.h"

class CFade
{
public:
	//�����o�֐�
	CFade();
	CFade(const D3DXVECTOR3 &Pos, const D3DXVECTOR3 &pSize);
	~CFade();

	//Init,Update,Draw,Uninit�֐�
	HRESULT Init(const D3DXVECTOR3 &Pos, const D3DXVECTOR3 &pSize, const char *filePass);
	void Update(void);
	void Draw(void);
	void Uninit(void);

	//�Z�b�^�[
	void SetLayerR(int Value);                     //RED���C���[�̒l�ݒ�
	void SetLayerG(int Value);                     //GREEN���C���[�̒l�ݒ�
	void SetLayerB(int Value);                     //BLUE���C���[�̒l�ݒ�
	void SetLayerA(int Value);                     //ALPHA���C���[�̒l�ݒ�
	void SetRGBA(RGBA rgba);                       //RGBA�ꊇ�ݒ�
	void ChangeAlpha(int ChangeValue);             //ALPHA���C���[�̒l�����X�ύX������
	void SetUV(const D3DXVECTOR2& UV) { m_UV = UV; }
	void SetUVWH(const D3DXVECTOR2& UVWH) { m_UVWH = UVWH; }
	void SetPosX(float PosX) { m_pos.x = PosX; }

	//�Q�b�^�[
	int GetLayerA(void) { return m_RGBA.a; }       //ALPHA���C���[�̒l�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	//���̊֐�
	void AddPosX(float Pos) { m_pos.x += Pos; }
private:
	//�����o�֐�
	void SetRenderStates(void);          //�����_�[�X�e�[�g���ݒ�
	void VertexBufferLock(void);         //���_���b�N

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DXVECTOR2             m_UV;           //UV���_
	D3DXVECTOR2             m_UVWH;         //UV�̕��ƍ���
	RGBA m_RGBA;
	TEX_ID *m_TexID;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;
};

#endif