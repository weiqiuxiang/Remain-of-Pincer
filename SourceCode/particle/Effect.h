#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "Scene2D.h"

class CEffect:public CScene2D
{
public:
	CEffect();
	CEffect(int nPriority = 7);
	~CEffect();

	typedef struct
	{
		D3DXVECTOR2 Pos;		// ���S���W
		float Angle;			// �Ίp���̊p�x
		float Length;			// �Ίp���̔����̒���
	}SPIN_INFO;
	static CEffect *Create(void);
	static CEffect *Create(  float x , float y , float Width , float Height , float Speed , float Rot , int Life);
	static CEffect *Create(  float x , float y , float Width , float Height , float Speed , float Rot , int Life , float r , float g , float b , float a );
	static CEffect *Create(float x, float y, float Width, float Height, float Speed_x , float Speed_y, float Rot, int Life ,
		float Gravity_x , float Gravity_y , float Registance_x , float Registance_y , float ScaleSpeed_x , float ScaleSpeed_y ,
		float r, float g, float b, float a ) ;
	void SetPos( float x , float y , float z ) ;
	void SetSpeed( float x , float y , float z ) ;
	void SetSize( float x , float y , float z ) ;
	void SetGravity( float x , float y , float z ) ;
	void SetRegistance( float x , float y , float z ) ;
	void SetScale( float x , float y , float z ) ;
	void SetScaleSpeed( float x , float y , float z ) ;

	static HRESULT Load( char File[] );
	static void UnLoad( void );
	static int GetPriority(void) { return s_nPriority; }

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
private:
	static TEX_ID m_TexID ;
	D3DXVECTOR3 Pos ;				// ���W
	D3DXVECTOR3 Speed ;				// �X�s�[�h
	D3DXVECTOR3 Size ;				// �e�̑傫��
	D3DXVECTOR3 CollisionPos ;		// �����蔻����W
	D3DXVECTOR3 Gravity ;					// �d��
	D3DXVECTOR3 Registance ;
	float Count ;					// �J�E���g
	D3DXVECTOR3 Scale ;					// �g�嗦
	D3DXVECTOR3 ScaleSpeed ;				// �g�嗦�̕ω���
	float Rot ;						// �p�x
	float RotSpeed ;				// �p�x�ω���
	float Radius ;					// �����蔻�蔼�a
	float ColorAlphaValue ;			// �F�̕ω���
	float RadiusValue ;				// ���a�ω���
	RGBA  Color ;				// �F
	SPIN_INFO Info ;				// ��]���
	float MoveRot_xy ;					// �i�ފp�x
	float MoveRot_xz ;					// �i�ފp�x
	int Life ;						// ����
//	DRAW_TYPE BlendMode ;
	float Length ;					// �J�����̂Ƌ���

	static int s_nPriority;
};

#endif