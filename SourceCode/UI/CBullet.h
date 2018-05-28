#pragma once

#ifndef _CBULLET_H_
#define _CBULLET_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CBullet:public CScene2D
{
public:
	CBullet();
	~CBullet();
	static HRESULT Load(int TexType);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 speed);          //CScene2D�̃C���X�^���X�𐶐�����֐�
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;                    //�e�̋��ʃe�N�X�`���|�C���g(�e���Ƃ�m_pTexture�ɃA�h���X�ɓn�����߂�)
	D3DXVECTOR3 m_move;                                      //�ړ���
};

#endif