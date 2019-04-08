#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#define D3DFMT_SPACESHIPVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)


LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
LPDIRECT3D9   g_pD3D = NULL;   // D3D 디바이스를 생성할 D3D 객체 변수
 // 렌더링에 사용될 D3D 디바이스
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIB = NULL;


char szWinName[] = "DX9_Tutorial_02";  // 윈도우 클래스 이름
char szWinTitle[] = "DX9 Tutorial VertexBuffer";

struct SPACESHIPVERTEX
{
	D3DXVECTOR3 p;
	DWORD color;
};

struct SPACESHIPINDEX
{
	WORD _0, _1, _2;
};

struct SPACESHIPOBJECT
{
	D3DXMATRIX matLocal;
};

SPACESHIPVERTEX g_pVertices[16];
SPACESHIPINDEX g_pIndices[10];
SPACESHIPOBJECT g_pObjects[2];



struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	DWORD color;
};

struct CUBEINDEX
{
	WORD _0, _1, _2;
};

HRESULT InitD3D(HWND hwnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pd3dDevice)))
		return E_FAIL;

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return S_OK;
}

HRESULT InitVB()
{
	
	D3DXVECTOR3 p1 = D3DXVECTOR3(0.00f, 0.00f, 0.50f);
	D3DXVECTOR3 p2 = D3DXVECTOR3(0.50f, 0.00f, -0.50f);
	D3DXVECTOR3 p3 = D3DXVECTOR3(0.15f, 0.15f, -0.35f);
	D3DXVECTOR3 p4 = D3DXVECTOR3(-0.15f, 0.15f, -0.35f);
	D3DXVECTOR3 p5 = D3DXVECTOR3(0.15f, -0.15f, -0.35f);
	D3DXVECTOR3 p6 = D3DXVECTOR3(-0.15f, -0.15f, -0.35f);
	D3DXVECTOR3 p7 = D3DXVECTOR3(-0.50f, 0.00f, -0.50f);

	g_pVertices[0].p = p1; g_pVertices[0].color = 0xffebb1b;
	g_pVertices[1].p = p2; g_pVertices[1].color = 0xffebb1b;
	g_pVertices[2].p = p3; g_pVertices[2].color = 0xffebb1b;
	g_pVertices[3].p = p4; g_pVertices[3].color = 0xffebb1b;
	g_pVertices[4].p = p7; g_pVertices[4].color = 0xffebb1b;

	g_pVertices[5].p = p1; g_pVertices[5].color = 0xffebb1b;
	g_pVertices[6].p = p2; g_pVertices[6].color = 0xffebb1b;
	g_pVertices[7].p = p5; g_pVertices[7].color = 0xffebb1b;
	g_pVertices[8].p = p6; g_pVertices[8].color = 0xffebb1b;
	g_pVertices[9].p = p7; g_pVertices[9].color = 0xffebb1b;

	g_pVertices[10].p = p2; g_pVertices[10].color = 0xffebb1b;
	g_pVertices[11].p = p3; g_pVertices[11].color = 0xffebb1b;
	g_pVertices[12].p = p4; g_pVertices[12].color = 0xffebb1b;
	g_pVertices[13].p = p7; g_pVertices[13].color = 0xffebb1b;
	g_pVertices[14].p = p6; g_pVertices[14].color = 0xffebb1b;
	g_pVertices[15].p = p5; g_pVertices[15].color = 0xffebb1b;

	if (FAILED(g_pd3dDevice->CreateVertexBuffer(sizeof(g_pVertices), 0, D3DFMT_SPACESHIPVERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL)))
		return E_FAIL;

	VOID* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(g_pVertices), (void**)&pVertices, 0)))
		return E_FAIL;
	memcpy(pVertices, g_pVertices, sizeof(g_pVertices));
	g_pVB->Unlock();

	
	return S_OK;
}

HRESULT InitIB()
{
	

	g_pIndices[0]._0 = 0;	g_pIndices[0]._1 = 1;	g_pIndices[0]._2 = 2;
	g_pIndices[1]._0 = 0;	g_pIndices[1]._1 = 2;	g_pIndices[1]._2 = 3;
	g_pIndices[2]._0 = 0;	g_pIndices[2]._1 = 3;	g_pIndices[2]._2 = 4;
	g_pIndices[3]._0 = 5;	g_pIndices[3]._1 = 7;	g_pIndices[3]._2 = 6;
	g_pIndices[4]._0 = 5;	g_pIndices[4]._1 = 8;	g_pIndices[4]._2 = 7;
	g_pIndices[5]._0 = 5;	g_pIndices[5]._1 = 9;	g_pIndices[5]._2 = 8;
	g_pIndices[6]._0 = 10;	g_pIndices[6]._1 = 15;	g_pIndices[6]._2 = 11;
	g_pIndices[7]._0 = 11;	g_pIndices[7]._1 = 15;	g_pIndices[7]._2 = 12;
	g_pIndices[8]._0 = 12;	g_pIndices[8]._1 = 15;	g_pIndices[8]._2 = 14;
	g_pIndices[9]._0 = 12;	g_pIndices[9]._1 = 14;	g_pIndices[9]._2 = 13;
	if (FAILED(g_pd3dDevice->CreateIndexBuffer(sizeof(g_pIndices), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL)))
	{
		return E_FAIL;
	}
	VOID* pIndeces;
	if (FAILED(g_pIB->Lock(0, sizeof(g_pIndices), (void**)&pIndeces, 0)))
		return E_FAIL;
	memcpy(pIndeces, g_pIndices, sizeof(g_pIndices));
	g_pIB->Unlock();
	return S_OK;
}

HRESULT InitGeometry()
{
	InitVB();
	InitIB();

	D3DXMatrixIdentity(&g_pObjects[0].matLocal);
	g_pObjects[0].matLocal._41 = 0.0f;
	g_pObjects[0].matLocal._42 = 1.0f;
	g_pObjects[0].matLocal._43 = -1.0f;

	return S_OK;
}
VOID SetupRenderStates()
{
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

}
VOID SetupMatrics()
{

	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -10.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;

	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);


}
VOID SetupInputs()
{
	FLOAT fOneStep = 0.1f;

	if (GetAsyncKeyState(VK_UP))
	{
		g_pObjects[0].matLocal._43 += fOneStep;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		g_pObjects[0].matLocal._43 -= fOneStep;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		g_pObjects[0].matLocal._41 += fOneStep;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		g_pObjects[0].matLocal._41 -= fOneStep;
	}
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}
}

VOID Render()
{
	if (NULL == g_pd3dDevice)
		return;

	SetupRenderStates();
	SetupMatrics();
	SetupInputs();

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 2.0f, 0.0f, 0.0f);

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.25f, 0.25f, 0.55f), 1.0f, 0);


	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{

		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &g_pObjects[0].matLocal);
	

		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matTrans));

		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(SPACESHIPVERTEX));
		g_pd3dDevice->SetFVF(D3DFMT_SPACESHIPVERTEX);
		g_pd3dDevice->SetIndices(g_pIB);
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 10);

	

		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

VOID Cleanup()
{

	if (g_pIB != NULL)
		g_pIB->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();

	if (g_pVB != NULL)
		g_pVB->Release();



}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:    // 프로그램 종료
		Cleanup();
		PostQuitMessage(WM_QUIT);
		return 0;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}


INT WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, INT nWinMode)
{
	HWND hwnd;

	/* STEP 1 : 윈도우 클래스 정의------------------------------*/

	WNDCLASS wcl;
	wcl.hInstance = hThisInst;  // 인스턴스에 대한 핸들 
	wcl.lpszClassName = szWinName; // 윈도우 클래스 이름 
	wcl.lpfnWndProc = WndProc;  // 윈도우 콜백 함수 
	wcl.style = 0;     // 기본 스타일 
	wcl.hIcon = NULL;    // 표준 아이콘(스타일) 사용 
	wcl.hCursor = NULL;    // 표준 커서(스타일) 사용 
	wcl.lpszMenuName = NULL;  // 메뉴 사용하지 않음 
	wcl.cbClsExtra = 0;    // 추가 정보는 사용하지 않음 
	wcl.cbWndExtra = 0;    // 추가 정보는 사용하지 않음 
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 윈도우 배경을 하얀색으로 함

	/* STEP 2 : 윈도우 클래스 등록------------------------------*/

	if (!RegisterClass(&wcl))
		return 0;

	/* STEP 3 : 윈도우 생성 ------------------------------------*/
	hwnd = CreateWindow(
		szWinName,  // 윈도우 클래스 이름
		"Tutorial 02",  // 윈도우 타이틀
		WS_SYSMENU,  // 윈도우 스타일 - normal
		CW_USEDEFAULT, // X 좌표 윈도우가 결정
		CW_USEDEFAULT, // Y 좌표 윈도우가 결정
		600,   // 윈도우 넓이
		600,   // 윈도우 높이
		HWND_DESKTOP, // 부모 윈도우 없음
		NULL,   // 메뉴 없음
		hThisInst,  // 이 프로그램에 대한 인스턴스 핸들
		NULL   // 추가적인 매개 변수 없음 
	);

	if (SUCCEEDED(InitD3D(hwnd)))
	{
		if (SUCCEEDED(InitGeometry()))
		{
			/* STEP 4 : 윈도우 시현 ------------------------------------*/
			ShowWindow(hwnd, SW_SHOWDEFAULT);
			UpdateWindow(hwnd);

			/* STEP 5 : 메세지 루프 생성 -------------------------------*/
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));

			while (WM_QUIT != msg.message)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg); // 키보드 입력 허용
					DispatchMessage(&msg); // 윈도우로 제어권 반환
				}
				else
				{
					Render(); //처리할 메세지가 없으면 Render 함수 호출   
				}
			}
		}
	}
	UnregisterClass(szWinName, wcl.hInstance);
	return 0;
}