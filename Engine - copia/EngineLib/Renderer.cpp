#include "Renderer.h"
#include "pg2_vertexbuffer.h"
//==================================================================================
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") 
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 

#define _USE_MATH_DEFINES
#include <math.h>

//==================================================================================
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define TEXTUREFVF (D3DFVF_XYZ | D3DFVF_TEX1)
//---------------------------primitive assignment-------------------------------
D3DPRIMITIVETYPE _primitives[PRIMITIVE_COUNT] =
{
	{D3DPT_POINTLIST},
	{D3DPT_LINELIST},
	{D3DPT_LINESTRIP},
	{D3DPT_TRIANGLELIST},
	{D3DPT_TRIANGLESTRIP},
	{D3DPT_TRIANGLEFAN,}
};
//---------------------------Matrix Type assignment-------------------------------
D3DTRANSFORMSTATETYPE _matrixType[MATRIX_TYPE_COUNT] =
{
	{ D3DTS_VIEW },
	{ D3DTS_PROJECTION },
	{ D3DTS_WORLD }
};
//==================================================================================
Renderer::Renderer(){}
//==================================================================================
Renderer::~Renderer(){
	m_pkDevice->Release();
	m_pkDevice = NULL;

	m_pkD3D->Release();
	m_pkD3D = NULL;

	delete v_buffer;
	v_buffer = NULL;

	std::vector<Texture>::iterator iter;
	for(iter = _textureList.begin(); iter != _textureList.end(); iter++){
		(*iter)->Release();
		(*iter) = NULL;
	}

	_textureList.clear();
}
//==================================================================================
bool Renderer::init(HWND hWnd, unsigned int uiW, unsigned int uiH){
	uiWidth = uiW;
	uiHeight = uiH;
	_hwnd = hWnd;
	//------------------directX cretion-------------------------------------
	m_pkD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!m_pkD3D) return false;
	//-----------------display creation-------------------------------------
	D3DDISPLAYMODE displayMode;
	HRESULT hr;
	hr = m_pkD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

	if (hr != D3D_OK) return false;
	//------------------directX present struct------------------------------
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//------------------device creation-------------------------------------
	hr = m_pkD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pkDevice);

	if (hr != D3D_OK) return false;
	//----------------------States-----------------------------------------
	m_pkDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pkDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pkDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pkDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pkDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pkDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//-----------------viewport creation-----------------------------------
	D3DVIEWPORT9 viewport;
	m_pkDevice->GetViewport(&viewport);

	float viewportWidth = static_cast<float>(viewport.Width);
	float viewportHeight = static_cast<float>(viewport.Height);
	//----------------orthogonal projection--------------------------------
	D3DXMATRIX projectionMatrix;
	//D3DXMatrixOrthoLH(&projectionMatrix, viewportWidth, viewportHeight, 0.0f, 1000.0f);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, M_PI * 0.25, viewportWidth / viewportHeight, 1.0f, 10000.0f);
	m_pkDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
	_projectionMatrix = new D3DXMATRIX();
	_projectionMatrix = &projectionMatrix;
	//----------------vertex Buffers---------------------------------------
	v_buffer = new VertexBuffer(m_pkDevice, sizeof(Vertex), CUSTOMFVF);
	texturedVBuffer = new VertexBuffer(m_pkDevice, sizeof(TexturedVertex), TEXTUREFVF);

	return true;
}
//==================================================================================
void Renderer::beginFrame(){
	m_pkDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);
	m_pkDevice->BeginScene();
}
//==================================================================================
void Renderer::draw(Vertex* gameVertex, Primitive primitive, int vertexCount){
	v_buffer->bind();
	v_buffer->draw(gameVertex, _primitives[primitive], vertexCount);
}
//==================================================================================
void Renderer::draw(TexturedVertex* gameVertex, Primitive primitive, int vertexCount){
	texturedVBuffer->bind();
	texturedVBuffer->draw(gameVertex, _primitives[primitive], vertexCount);
}
//==================================================================================
Font& Renderer::createFont(int charSize, std::string textFont, bool italic){
	Font font;
	D3DXCreateFont(m_pkDevice, 
				   charSize, 
				   0, 
				   FW_NORMAL, 
				   1, italic, 
				   DEFAULT_CHARSET, 
				   OUT_DEFAULT_PRECIS, 
				   ANTIALIASED_QUALITY, 
				   FF_DONTCARE,
				   textFont.c_str(),
				   &font);

	return font;
}
//==================================================================================
RECT& Renderer::createRect(int x, int y, int width, int height){
	RECT rect;
	SetRect(&rect, x, y, width, height);

	return rect;
}
//==================================================================================
void Renderer::displayText(Font& font, RECT& rect, std::string text){
	font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255,255,255));
}
//==================================================================================
void Renderer::endFrame(){
	m_pkDevice->EndScene();
	m_pkDevice->Present(NULL, NULL, NULL, NULL);
}
//==================================================================================
void Renderer::setMatrix(MatrixType matrixType, const Matrix& matrix){
	m_pkDevice->SetTransform(_matrixType[matrixType], matrix);
}
//==================================================================================
const Texture Renderer::loadTexture(const std::string& textureName, D3DCOLOR ColorKey){
	Texture texture = NULL;

	D3DXCreateTextureFromFileEx(m_pkDevice,
								textureName.c_str(),
								D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
								D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
								D3DX_FILTER_NONE, D3DX_FILTER_NONE,
								ColorKey,
								NULL,
								NULL,
								&texture);

	if(texture){
		for(int i = 0; i < _textureList.size(); i++){
			if(texture == _textureList[i])
				return texture;
		}

		_textureList.push_back(texture);
		return texture;
	}

	else{
		MessageBox(_hwnd,"No Texture", "No Texture",MB_OK);
		return NoTexture;
	}
}
//==================================================================================
void Renderer::setCurrentTexture(const Texture& texture){
	m_pkDevice->SetTexture(0, texture);
}
//==================================================================================
Matrix& Renderer::getProjectionMatrix(){
	return _projectionMatrix;
}
<<<<<<< HEAD
//==================================================================================
pg2::VertexBuffer* Renderer::createVertexBuffer(size_t vertexSize, unsigned int fvf){

}

pg2::IndexBuffer* Renderer::createIndexBuffer(){

}

void Renderer::setCurrentIndexBuffer(pg2::IndexBuffer* indexBuffer){

}

void Renderer::setCurrentVertexBuffer(pg2::VertexBuffer* vertexBuffer){

}
=======
//==================================================================================
>>>>>>> origin/master
