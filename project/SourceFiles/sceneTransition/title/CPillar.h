// CPillar�̏���
#ifndef _CPILLAR_H_
#define _CPILLAR_H_

#include "main.h"
#include "scene2D.h"
#include "CNumber.h"

//�O���錾
class CScene2D;

class CPillar : public CScene2D
{
public:

	CPillar();
	CPillar(int Priority);
	~CPillar();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�Z�b�^�[
	void SetStartPos(D3DXVECTOR3 startPos) { m_startPos = startPos; }
	void SetEndPos(D3DXVECTOR3 endPos) { m_endPos = endPos; }
	void SetVelocity(D3DXVECTOR3 velocity) { m_velocity = velocity; }

	void AddPos(D3DXVECTOR3 value) { m_pos += value; }
	void AddVelocity(D3DXVECTOR3 value) { m_velocity += value; }

	//�Q�b�^�[
	D3DXVECTOR3 GetStartPos(void) { return m_startPos; }
	D3DXVECTOR3 GetEndPos(void) { return m_endPos; }
	D3DXVECTOR3 GetVelocity(void) { return m_velocity; }
	static int GetPriority(void) { return s_nPriority; }

	//���̊֐�
	static CPillar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�

private:
	float m_posU;
	float m_posV;
	D3DXVECTOR3 m_startPos;
	D3DXVECTOR3 m_endPos; // �ڕW���W
	D3DXVECTOR3 m_velocity; // �ڕW���W�ւ̕����x�N�g��
	static int s_nPriority;
};

#endif

