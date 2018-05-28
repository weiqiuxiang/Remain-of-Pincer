// letter�̏���
#ifndef _CLETTER_H_
#define _CLETTER_H_

#include "main.h"
#include "scene2D.h"

#define NUM_MAX_LETTER (12)

class CLetter : public CScene
{
public:
	//CLetter();
	CLetter(int Priorit, D3DXVECTOR3 pos, D3DXVECTOR3 size);
	~CLetter();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�Z�b�^�[
	void SetPos(const D3DXVECTOR3& pos)override { m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size)override { m_size = size; }
	void SetStartPos(const D3DXVECTOR3& startPos) { m_startPos = startPos; }
	void SetEndPos(const D3DXVECTOR3& endPos) { m_endPos = endPos; }
	void SetEndRot(const float& endRot) { m_endRot = endRot; }
	void SetVelocity(const D3DXVECTOR3& velocity) { m_velocity = velocity; }
	void SetRot(const float& rot) { m_rot = rot; }
	void SetDeltaRot(const float& deltaRot) { m_deltaRot = deltaRot; }
	void SetPushedL(const bool value) { m_pushedL = value; }
	void SetPushedR(const bool value) { m_pushedR = value; }
	void SetFall(const bool value) { m_fall = value; }
	void SetBottom(const float& bottom) { m_bottom = bottom; }

	void AddPos(const D3DXVECTOR3& value) { m_pos += value; }
	void AddVelocity(const D3DXVECTOR3& value) { m_velocity += value; }
	void AddRot(const float& value) { m_rot += value; }

	void PowerReset(void) {};            //�󂯂�͂����Z�b�g
	void AddPowerX(float fPowerX) {};
	void AddPowerY(float fPowerY) {};

	//�Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }                    //�ʒu�擾
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetVelocity(void) { return m_velocity; }
	D3DXVECTOR3 GetStartPos(void) { return m_startPos; }
	D3DXVECTOR3 GetEndPos(void) { return m_endPos; }
	float GetRot(void) { return m_rot; }
	float GetEndRot(void) { return m_endRot; }
	float GetDeltaRot(void) { return m_deltaRot; }
	float GetBottom(void) { return m_bottom; }
	static int GetPriority(void) { return s_nPriority; }
	bool GetPushedL(void) { return m_pushedL; }
	bool GetPushedR(void) { return m_pushedR; }
	bool GetFall(void) { return m_fall; }

	//���̊֐�
	static CLetter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, float bottom, float rot, char* filepass);
	void BindTexture(TEX_ID TexID);                                        //�O�̃e�N�X�`����ǂݍ���
	HRESULT LoadTexture(const char* filePass);                                                //�Ή��ǂݍ��݃e�N�X�`����
	void SetVertex(void);

private:
	D3DXVECTOR3  m_pos;
	D3DXVECTOR3  m_size;
	D3DXVECTOR2  m_leftup;			// ����̒��_XY
	D3DXVECTOR2  m_rightup;			// �E��̒��_XY
	D3DXVECTOR2  m_leftdown;		// �����̒��_XY
	D3DXVECTOR2  m_rightdown;		// �E���̒��_XY	
	D3DXVECTOR2	 m_tex;
	D3DXVECTOR2  m_texsize;
	float		 m_length;			// �|���S���̑Ίp���̒���
	float		 m_angle;			// �|���S���̑Ίp���̊p�x
	float		 m_rot;             // ��]�p�i���W�A���j

	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;

	TEX_ID		m_TEX_ID;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_startPos;     // �X�^�[�g���W
	D3DXVECTOR3 m_endPos;       // �S�[�����W
	D3DXVECTOR3 m_velocity;		// ���x
	float m_endRot;             // ������̊p�x
	float m_deltaRot;			// �p�x�̕ω���
	float m_bottom;             // �f�t�H���g�̒��Y���W
	int m_nValue;
	static int s_nPriority;
	bool m_pushedL;			    // �����牟�����
	bool m_pushedR;				// �E���牟�����
	bool m_fall;                // ��������
};

#endif
