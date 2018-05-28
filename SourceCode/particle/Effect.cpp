#include "Effect.h"
#include "Renderer.h"
#include "input.h"
#include "SceneTransition.h"
#include <math.h>

TEX_ID CEffect::m_TexID = -1 ;
int CEffect::s_nPriority = 10;

CEffect::CEffect() : CScene2D(7)
{

}

CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	
}

CEffect::~CEffect()
{

}

HRESULT CEffect::Init()
{
	CScene2D::Init( D3DXVECTOR3(Pos.x , Pos.y , Pos.z) , D3DXVECTOR3( Size.x , Size.y , Size.z ) );

	MoveRot_xz = D3DX_PI / 2 ;
	Pos.x = 0 ;
	Pos.y = 0 ;
	Pos.z = 0 ;
	Speed.x = 0 ;
	Speed.y = 0 ;
	Speed.z = 0 ;
	Scale.x = 1.0f ;
	Scale.y = 1.0f ;
	Scale.z = 1.0f ;
	MoveRot_xy = 0 ;
	MoveRot_xz = 0 ;
	Count = 0 ;
	Gravity.x = 0 ;
	Gravity.y = 0 ;
	Gravity.z = 0 ;
	return S_OK ;
}

void CEffect::Uninit()
{
	CScene2D::Uninit();
}

void CEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CSceneTransition::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		  // アルファブレンドの演算式を設定, 引き算に設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	  // 描画元（スプライト）のアルファブレンド設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		  // 描画先（背景）のアルファブレンド設定

	CScene2D::BindTexture(m_TexID);
	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}

void CEffect::Update()
{
	// 色の設定
	Color.a -= ColorAlphaValue ;
	Pos.x += cosf(MoveRot_xy ) * Speed.x + Gravity.x * Count;	// 座標の更新
	Pos.y += sinf(MoveRot_xy ) * Speed.y + Gravity.y * Count ;	// 座標の更新
//	Pos.z += cosf(MoveRot_xy ) * cosf(MoveRot_xz ) * Speed.z + Gravity.z * Count;	// 座標の更新
	Speed.x += ( 0.0f - Speed.x ) * Registance.x ;
	Speed.y += ( 0.0f - Speed.y ) * Registance.y ;
	Speed.z += ( 0.0f - Speed.z ) * Registance.z ;
	Rot += RotSpeed ;
	Count += 0.01f ;
	Scale.x += ScaleSpeed.x ;										// 拡大率の更新
	Scale.y += ScaleSpeed.y ;										// 拡大率の更新
	Scale.z += ScaleSpeed.z ;										// 拡大率の更新

	CScene2D::SetPos( D3DXVECTOR3( Pos.x , Pos.y , 0 ) );
	CScene2D::SetSize( D3DXVECTOR3( Size.x, Size.y, 0 ) );

	//ここ必須
	CScene2D::SetColor( Color );
	CScene2D::Update();
	CScene2D::VertexLock();
	Life -- ;
	if( Life < 0  )
	{
		Uninit();
	}
	/*
	for( int nCntScene = 0 ; nCntScene < MAX_SCENE ; nCntScene++ )
	{
		CScene *pScene ;
		pScene = CScene::GetScene( nCntScene );

		// NULLチェック
		if( pScene != NULL  )
		{
			CScene::OBJTYPE objType ;
			objType = pScene->GetObjType();

			// エネミー診断
			if( objType == TargetObj )
			{
				CScene::SPIN_INFO TargetInfo = pScene->GetSpin();
				CScene::SPIN_INFO EffectInfo = CScene2D::GetSpin();

				// 当たり判定
				if( (EffectInfo.Pos.x - TargetInfo.Pos.x) * (EffectInfo.Pos.x - TargetInfo.Pos.x) +
				 (EffectInfo.Pos.y - TargetInfo.Pos.y) * (EffectInfo.Pos.y - TargetInfo.Pos.y)
										<
				 (EffectInfo.Length + TargetInfo.Length) * (EffectInfo.Length + TargetInfo.Length) )
				{
					CScore *Score = CManager::GetScore();
//					CExplosion::Create( TargetInfo.Pos.x , TargetInfo.Pos.y , 200 , 200 , 0 , 0 , 20 ) ;
					if( TargetObj == OBJTYPE_ENEMY )
					{
						CEnemy *Enemy = static_cast<CEnemy*>(pScene);
						Enemy->Hit(1);
					}
					else
					{
						Score->AddScore(10);
						pScene->Uninit();
					}

					Uninit();
					return ;
				}
				/*
if( ( (EffectWater + CntEffectWater)->CollisionPos.x - ( Fire + CntFire)->Fire.Particle->Pos_x ) * ( (EffectWater + CntEffectWater)->CollisionPos.x - ( Fire + CntFire)->Fire.Particle->Pos_x )	+
( (EffectWater + CntEffectWater)->CollisionPos.y - ( Fire + CntFire)->Fire.Particle->Pos_y ) * ( (EffectWater + CntEffectWater)->CollisionPos.y - ( Fire + CntFire)->Fire.Particle->Pos_y ) <
( (EffectWater + CntEffectWater)->Radius + ( Fire + CntFire)->Fire.Particle->Size_x / 2 ) * ( (EffectWater + CntEffectWater)->Radius + (( Fire + CntFire)->Fire.Particle->Size_x / 2 ) ))

			}
		}
		
	}
	*/
}

CEffect * CEffect::Create()
{
	CEffect* pEffect ;
	pEffect = new CEffect(s_nPriority);
	pEffect->Init();
	pEffect->SetPos(pEffect->Pos.x, pEffect->Pos.y, 0);
	pEffect->SetSize(pEffect->Size.x, pEffect->Size.y, 0);
	return pEffect ;

}

CEffect * CEffect::Create( float x , float y , float Width , float Height , float Speed , float Rot , int Life )
{
	CEffect* pEffect ;
	pEffect = new CEffect(s_nPriority);
	pEffect->SetPos(x, y, 0);
	pEffect->SetSize(Width, Height, 0);
	pEffect->Init();
	pEffect->Pos.x = x ;
	pEffect->Pos.y = y ;
	pEffect->Size.x = Width ;
	pEffect->Size.y = Height ;
	pEffect->Rot = Rot ;
	pEffect->Speed.x = Speed ;
	pEffect->Speed.y = -Speed ;
	pEffect->Life = Life ;
	pEffect->Update();

	return pEffect ;
}

CEffect *CEffect::Create(  float x , float y , float Width , float Height , float Speed , float Rot , int Life , float r , float g , float b , float a )
{
	CEffect* pEffect ;
	pEffect = new CEffect(s_nPriority);
	pEffect->SetPos(x, y, 0);
	pEffect->SetSize(Width, Height, 0);
	pEffect->Init();
	pEffect->Pos.x = x ;
	pEffect->Pos.y = y ;
	pEffect->Size.x = Width ;
	pEffect->Size.y = Height ;
	pEffect->Rot = Rot ;
	pEffect->Speed.x = Speed ;
	pEffect->Speed.y = Speed ;
	pEffect->Life = Life ;
	pEffect->Color.r = r ;
	pEffect->Color.g = g ;
	pEffect->Color.b = b ;
	pEffect->Color.a = a ;
	pEffect->ColorAlphaValue = a / Life ;
	pEffect->Update();
	return pEffect ;
}



CEffect *CEffect::Create(float x, float y, float Width, float Height, float Speed_x, float Speed_y, float Rot, int Life,
	float Gravity_x, float Gravity_y, float Registance_x, float Registance_y, float ScaleSpeed_x, float ScaleSpeed_y,
	float r, float g, float b, float a)
{
	CEffect* pEffect;
	pEffect = new CEffect(s_nPriority);
	pEffect->Init();
	pEffect->SetPos(x, y, 0);
	pEffect->SetSize(Width, Height, 0);
	pEffect->Pos.x = x;
	pEffect->Pos.y = y;
	pEffect->Size.x = Width;
	pEffect->Size.y = Height;
	pEffect->MoveRot_xy = Rot;
	pEffect->Speed.x = Speed_x;
	pEffect->Speed.y = Speed_y;
	pEffect->Gravity.x = Gravity_x;
	pEffect->Gravity.y = Gravity_y;
	pEffect->Registance.x = Registance_x;
	pEffect->Registance.y = Registance_y;
	pEffect->ScaleSpeed.x = ScaleSpeed_x;
	pEffect->ScaleSpeed.y = ScaleSpeed_y;
	pEffect->Life = Life;
	pEffect->Color.r = r;
	pEffect->Color.g = g;
	pEffect->Color.b = b;
	pEffect->Color.a = a;
	pEffect->ColorAlphaValue = a / Life;
	pEffect->Update();
	return pEffect;
}
// テキスチャー読み込み
HRESULT CEffect::Load( char File[] )
{
	LPDIRECT3DDEVICE9 pDevice ;
	
	m_TexID = CTexManager::LoadTex(File);

	return E_FAIL ;
}

// テキスチャー破棄
void CEffect::UnLoad( void )
{

}

void CEffect::SetPos( float x , float y , float z )
{
	Pos.x = x ;
	Pos.y = y ;
	Pos.z = z ;
}

void CEffect::SetSpeed( float x , float y , float z )
{
	Speed.x = x ;
	Speed.y = y ;
	Speed.z = z ;
}

void CEffect::SetSize( float x , float y , float z )
{
	Size.x = x ;
	Size.y = y ;
	Size.z = z ;
}

void CEffect::SetGravity( float x , float y , float z )
{
	Gravity.x = x ;
	Gravity.y = y ;
	Gravity.z = z ;
}

void CEffect::SetRegistance( float x , float y , float z )
{
	Registance.x = x ;
	Registance.y = y ;
	Registance.z = z ;
}

void CEffect::SetScale( float x , float y , float z )
{
	Scale.x = x ;
	Scale.y = y ;
	Scale.z = z ;
}
void CEffect::SetScaleSpeed( float x , float y , float z )
{
	ScaleSpeed.x = x ;
	ScaleSpeed.y = y ;
	ScaleSpeed.z = z ;
}









