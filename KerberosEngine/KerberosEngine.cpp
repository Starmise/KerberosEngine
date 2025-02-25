#include "Prerequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Swapchain.h"
#include "Texture.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Viewport.h"
// #include "InputLayout.h"
#include "ShaderProgram.h"

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
//HINSTANCE                           g_hInst = NULL;
//HWND                                g_hWnd = NULL;
Window                              g_window;
Device                              g_device;
DeviceContext                       g_deviceContext;
SwapChain                           g_swapchain;
Texture                             g_backBuffer;
Texture                             g_depthStencil;
RenderTargetView                    g_renderTargetView;
DepthStencilView                    g_depthStencilView;
Viewport                            g_viewport;
// InputLayout                         g_inputLayout;
ShaderProgram                       g_shaderProgram;

//D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
//D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
//ID3D11Device* g_pd3dDevice = NULL;
// ID3D11DeviceContext* g_pImmediateContext = NULL;
// IDXGISwapChain* g_pSwapChain = NULL;
// ID3D11RenderTargetView* g_pRenderTargetView = NULL;
// ID3D11Texture2D* g_pDepthStencil = NULL;
// ID3D11DepthStencilView* g_pDepthStencilView = NULL;
// ID3D11VertexShader* g_pVertexShader = NULL;
// ID3D11PixelShader* g_pPixelShader = NULL;
// ID3D11InputLayout* g_pVertexLayout = NULL;
ID3D11Buffer* g_pVertexBuffer = NULL;
ID3D11Buffer* g_pIndexBuffer = NULL;
ID3D11Buffer* g_pCBNeverChanges = NULL;
ID3D11Buffer* g_pCBChangeOnResize = NULL;
ID3D11Buffer* g_pCBChangesEveryFrame = NULL;
ID3D11ShaderResourceView* g_pTextureRV = NULL;
ID3D11SamplerState* g_pSamplerLinear = NULL;
XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);

CBChangesEveryFrame cb;
CBNeverChanges cbNeverChanges;
CBChangeOnResize cbChangesOnResize;
// D3D11_VIEWPORT vp;
unsigned int stride = sizeof(SimpleVertex);
unsigned int offset = 0;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
//HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, unsigned int, WPARAM, LPARAM);
void update();
void Render();

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  if (FAILED(g_window.init(hInstance, nCmdShow, WndProc)))
    return 0;

  if (FAILED(InitDevice()))
  {
    CleanupDevice();
    return 0;
  }

  // Main message loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      update();
      Render();
    }
  }

  CleanupDevice();

  return (int)msg.wParam;
}

//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
//HRESULT
//CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut) {
//  HRESULT hr = S_OK;
//
//  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
//#if defined( DEBUG ) || defined( _DEBUG )
//  // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
//  // Setting this flag improves the shader debugging experience, but still allows 
//  // the shaders to be optimized and to run exactly the way they will run in 
//  // the release configuration of this program.
//  dwShaderFlags |= D3DCOMPILE_DEBUG;
//#endif
//
//  ID3DBlob* pErrorBlob;
//  hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
//    dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
//  if (FAILED(hr))
//  {
//    if (pErrorBlob != NULL)
//      OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
//    if (pErrorBlob) pErrorBlob->Release();
//    return hr;
//  }
//  if (pErrorBlob) pErrorBlob->Release();
//
//  return S_OK;
//}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT
InitDevice() {
  HRESULT hr = S_OK;

  // Create Swapchain and BackBuffer
  g_swapchain.init(g_device, g_deviceContext, g_backBuffer, g_window);
  if (FAILED(hr)) {
    return hr;
  }

  // Create a Render Target View
  hr = g_renderTargetView.init(g_device, 
															 g_backBuffer, 
															 DXGI_FORMAT_R8G8B8A8_UNORM);
  if (FAILED(hr)) {
    return hr;
  }  

  // Create a Depth Stencil texture
  hr = g_depthStencil.init(g_device,
                          g_window.m_width,
                          g_window.m_height,
                          DXGI_FORMAT_D24_UNORM_S8_UINT,
                          D3D11_BIND_DEPTH_STENCIL, 4, 0);
  if (FAILED(hr)) {
    return hr;
  }

  // Create a Depth Stencil View
  hr = g_depthStencilView.init(g_device,
                              g_depthStencil,
                              DXGI_FORMAT_D24_UNORM_S8_UINT);
  if (FAILED(hr)) {
    return hr;
  }
    
  // Setup the viewport
  g_viewport.init(g_window);

  //// Compile the vertex shader
  //ID3DBlob* pVSBlob = NULL;
  //hr = CompileShaderFromFile("KerberosEngine.fx", "VS", "vs_4_0", &pVSBlob);
  //if (FAILED(hr))
  //{
  //  MessageBox(NULL,
  //    "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
  //  return hr;
  //}

  //// Create the vertex shader
  //hr = g_device.CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
  //if (FAILED(hr))
  //{
  //  pVSBlob->Release();
  //  return hr;
  //}

  // Define the input layout
  std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

  D3D11_INPUT_ELEMENT_DESC position;
  position.SemanticName = "POSITION";
  position.SemanticIndex = 0;
  position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
  position.InputSlot = 0;
  position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*0*/;
  position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  position.InstanceDataStepRate = 0;
  Layout.push_back(position);

  D3D11_INPUT_ELEMENT_DESC texcoord;
  texcoord.SemanticName = "TEXCOORD";
  texcoord.SemanticIndex = 0;
  texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
  texcoord.InputSlot = 0;
  texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
  texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  texcoord.InstanceDataStepRate = 0;
  Layout.push_back(texcoord);

  // Create the Shader Program
  hr = g_shaderProgram.init(g_device, "KerberosEngine.fx", Layout);
  if (FAILED(hr)) {
    return hr;
  }
  
  //// Compile the pixel shader
  //ID3DBlob* pPSBlob = NULL;
  //hr = CompileShaderFromFile("KerberosEngine.fx", "PS", "ps_4_0", &pPSBlob);
  //if (FAILED(hr))
  //{
  //  MessageBox(NULL,
  //    "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
  //  return hr;
  //}

  //// Create the pixel shader
  //hr = g_device.CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
  //pPSBlob->Release();
  //if (FAILED(hr))
  //  return hr;

  // Create vertex buffer
  SimpleVertex vertices[] =
  {
      { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

      { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

      { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

      { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

      { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },

      { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
  };

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = sizeof(SimpleVertex) * 24;
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = 0;
  D3D11_SUBRESOURCE_DATA InitData;
  ZeroMemory(&InitData, sizeof(InitData));
  InitData.pSysMem = vertices;
  hr = g_device.CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
  if (FAILED(hr))
    return hr;

  // Create index buffer
  // Create vertex buffer
  WORD indices[] =
  {
      3,1,0,
      2,1,3,

      6,4,5,
      7,4,6,

      11,9,8,
      10,9,11,

      14,12,13,
      15,12,14,

      19,17,16,
      18,17,19,

      22,20,21,
      23,20,22
  };

  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = sizeof(WORD) * 36;
  bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
  bd.CPUAccessFlags = 0;
  InitData.pSysMem = indices;
  hr = g_device.CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
  if (FAILED(hr))
    return hr;

  // Create the constant buffers
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = sizeof(CBNeverChanges);
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = 0;
  hr = g_device.CreateBuffer(&bd, NULL, &g_pCBNeverChanges);
  if (FAILED(hr))
    return hr;

  bd.ByteWidth = sizeof(CBChangeOnResize);
  hr = g_device.CreateBuffer(&bd, NULL, &g_pCBChangeOnResize);
  if (FAILED(hr))
    return hr;

  bd.ByteWidth = sizeof(CBChangesEveryFrame);
  hr = g_device.CreateBuffer(&bd, NULL, &g_pCBChangesEveryFrame);
  if (FAILED(hr))
    return hr;

  // Load the Texture
  hr = D3DX11CreateShaderResourceViewFromFile(g_device.m_device, "seafloor.dds", NULL, NULL, &g_pTextureRV, NULL);
  if (FAILED(hr))
    return hr;

  // Create the sample state
  D3D11_SAMPLER_DESC sampDesc;
  ZeroMemory(&sampDesc, sizeof(sampDesc));
  sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sampDesc.MinLOD = 0;
  sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
  hr = g_device.CreateSamplerState(&sampDesc, &g_pSamplerLinear);
  if (FAILED(hr))
    return hr;

  // Initialize the world matrices
  g_World = XMMatrixIdentity();

  // Initialize the view matrix
  XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
  XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  g_View = XMMatrixLookAtLH(Eye, At, Up);

  return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void
CleanupDevice() {
  if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->ClearState();
  if (g_pSamplerLinear) g_pSamplerLinear->Release();
  if (g_pTextureRV) g_pTextureRV->Release();
  if (g_pCBNeverChanges) g_pCBNeverChanges->Release();
  if (g_pCBChangeOnResize) g_pCBChangeOnResize->Release();
  if (g_pCBChangesEveryFrame) g_pCBChangesEveryFrame->Release();
  if (g_pVertexBuffer) g_pVertexBuffer->Release();
  if (g_pIndexBuffer) g_pIndexBuffer->Release();
  
  g_shaderProgram.destroy();
  g_depthStencil.destroy();
  g_depthStencilView.destroy();
  g_renderTargetView.destroy();
  g_swapchain.destroy();
  g_deviceContext.destroy();
  g_device.destroy();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;

  switch (message)
  {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;

  case WM_SIZE:
    if (g_swapchain.g_pSwapChain) {
      g_window.m_width = LOWORD(lParam);
      g_window.m_height = HIWORD(lParam);

      // Libera los recursos existentes
      g_renderTargetView.destroy();
      g_depthStencilView.destroy();
      g_depthStencil.destroy();
      g_backBuffer.destroy();

      // Redimensionar el swap chain
      HRESULT hr = g_swapchain.g_pSwapChain->ResizeBuffers(0,
        g_window.m_width,
        g_window.m_height,
        DXGI_FORMAT_R8G8B8A8_UNORM,
        0);
      if (FAILED(hr)) {
        MessageBox(hWnd, "Failed to resize swap chain buffers.", "Error", MB_OK);
        PostQuitMessage(0);
      }

      // **3. RECREAR EL BACK BUFFER**
      hr = g_swapchain.g_pSwapChain->GetBuffer(0,
        __uuidof(ID3D11Texture2D),
        reinterpret_cast<void**>(&g_backBuffer.m_texture));
      if (FAILED(hr)) {
        ERROR("SwapChain", "Resize", "Failed to get new back buffer");
        return hr;
      }

      // **4. RECREAR EL RENDER TARGET VIEW**
      hr = g_renderTargetView.init(g_device,
        g_backBuffer,
        DXGI_FORMAT_R8G8B8A8_UNORM);
      if (FAILED(hr)) {
        ERROR("RenderTargetView", "Resize", "Failed to create new RenderTargetView");
        return hr;
      }

      // **5. RECREAR EL DEPTH STENCIL VIEW**
      hr = g_depthStencil.init(g_device,
        g_window.m_width,
        g_window.m_height,
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        D3D11_BIND_DEPTH_STENCIL,
        4,
        0);
      if (FAILED(hr)) {
        ERROR("DepthStencil", "Resize", "Failed to create new DepthStencil");
        return hr;
      }

      hr = g_depthStencilView.init(g_device,
        g_depthStencil,
        DXGI_FORMAT_D24_UNORM_S8_UINT);
      if (FAILED(hr)) {
        ERROR("DepthStencilView", "Resize", "Failed to create new DepthStencilView");
        return hr;
      }
      // Actualizar el viewport
      //D3D11_VIEWPORT vp;
      g_viewport.init(g_window);

      // Actualizar la proyección
      g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (float)g_window.m_height, 0.01f, 100.0f);
      CBChangeOnResize cbChangesOnResize;
      cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
      g_deviceContext.UpdateSubresource(g_pCBChangeOnResize, 0, nullptr, &cbChangesOnResize, 0, 0);
    }
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

//--------------------------------------------------------------------------------------
// Update frame-specific variables
//--------------------------------------------------------------------------------------
void 
update() {
  // Update our time
  static float t = 0.0f;
  if (g_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE)
  {
    t += (float)XM_PI * 0.0125f;
  }
  else
  {
    static DWORD dwTimeStart = 0;
    DWORD dwTimeCur = GetTickCount();
    if (dwTimeStart == 0)
      dwTimeStart = dwTimeCur;
    t = (dwTimeCur - dwTimeStart) / 1000.0f;
  }

  // Rotate cube around the origin
  g_World = XMMatrixRotationY(t);

  // Modify the color
  g_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
  g_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
  g_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;


  //
  // Update variables that change once per frame
  //
  CBChangesEveryFrame cb;
  cb.mWorld = XMMatrixTranspose(g_World);
  cb.vMeshColor = g_vMeshColor;
  g_deviceContext.m_deviceContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);


  // Initialize the projection matrix
  g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (float)g_window.m_height, 0.01f, 100.0f);

  cbNeverChanges.mView = XMMatrixTranspose(g_View);
  g_deviceContext.UpdateSubresource(g_pCBNeverChanges, 0, nullptr, &cbNeverChanges, 0, 0);

  cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
  g_deviceContext.UpdateSubresource(g_pCBChangeOnResize, 0, nullptr, &cbChangesOnResize, 0, 0);
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void
Render() {

  //
  // Clear the back buffer
  //
  float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
  
  // Set Viewport
  g_viewport.render(g_deviceContext);

  //
  // Set Render Target View
  //
  g_renderTargetView.render(g_deviceContext, g_depthStencilView, 1, ClearColor);

  //
  // Set Depth Stencil View
  //
  g_depthStencilView.render(g_deviceContext);

  //
  // Render the cube
  //
  // Set Buffers and Shaders for pipeline
  g_shaderProgram.render(g_deviceContext);
  g_deviceContext.IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
  g_deviceContext.IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
  g_deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  
  // Set Constant Buffers and asign Shaders
  // g_deviceContext.m_deviceContext->VSSetShader(g_pVertexShader, NULL, 0);
  g_deviceContext.VSSetConstantBuffers(0, 1, &g_pCBNeverChanges);
  g_deviceContext.VSSetConstantBuffers(1, 1, &g_pCBChangeOnResize);
  g_deviceContext.VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
 
  // g_deviceContext.m_deviceContext->PSSetShader(g_pPixelShader, NULL, 0);
  g_deviceContext.PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
  g_deviceContext.PSSetShaderResources(0, 1, &g_pTextureRV);
  g_deviceContext.PSSetSamplers(0, 1, &g_pSamplerLinear);
  
  // Drwa
  g_deviceContext.DrawIndexed(36, 0, 0);

  //
  // Present our back buffer to our front buffer
  //
  g_swapchain.present();
}
