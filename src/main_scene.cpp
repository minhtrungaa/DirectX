#include <stdio.h>

#include "d3d_app.h"
#include "stdafx.h"
#include "main_scene.h"

// global
//ID3D11VertexShader *pVS;    // the vertex shader
//ID3D11PixelShader *pPS;     // the pixel shader
//
//ID3D10Blob *VS, *PS;

void MainScene::Init()
{
	printf("MAIN SCENE INIT\n");
	//D3DX11CompileFromFile("shader.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
	//D3DX11CompileFromFile("shader.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

	//// encapsulate both shaders into shader objects
	//D3DApplication::m_pDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	//D3DApplication::m_pDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	//// set the shader objects
	//D3DApplication::m_pDevContext->VSSetShader(pVS, 0, 0);
	//D3DApplication::m_pDevContext->PSSetShader(pPS, 0, 0);
}

void MainScene::Update(unsigned __int32 dt)
{
	
}

void MainScene::Render()
{
}
