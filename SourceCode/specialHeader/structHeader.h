#pragma once
#ifndef _STRUCT_HEADER01_H_
#define _STRUCT_HEADER01_H_

#include <d3dx9.h>

//-----------------------------------------------------------------------------------------
//�\���̐錾
//-----------------------------------------------------------------------------------------
//���_�\����(���̃t�@�[�}�b�g�̌^�ɍ��킹�邱��)
typedef struct
{
	D3DXVECTOR3 pos;                         //
	float rhw;								 //���W�ϊ��ςݒ��_�t���O(�K��1.0f)
	D3DCOLOR color;							 //���_�J���[
	D3DXVECTOR2 tex;                         //�e�N�X�`�����W(UV or ST)
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;                         //
	D3DXVECTOR3 normal;                      //�x�N�g���̕���
	D3DCOLOR color;							 //
	D3DXVECTOR2 tex;                         //�e�N�X�`�����W(UV or ST)
}VERTEX_3D;

//�}�g���N�X�z��
typedef struct
{
	D3DXVECTOR3 pos;   //���f���ړ�(���W)
	D3DXVECTOR3 rot;   //���f����]
	D3DXVECTOR3 scl;   //���f���g�嗦
}WORLD_MATRIX;

//�J�����̃X�e�[�^�X
typedef struct
{
	D3DXVECTOR3 pos;      //���f���ړ�(���W)
	D3DXVECTOR3 lookat;   //���f����]
	D3DXVECTOR3 up;       //���f���g�嗦
}CAMERA_PARA;

typedef struct
{
	int r;
	int g;
	int b;
	int a;
}RGBA;


typedef struct
{
	int r;
	int g;
	int b;
}RGB;
#endif