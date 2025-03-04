#include "BaseApp.h"

XMFLOAT4                            m_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);
CBChangesEveryFrame cb;
CBNeverChanges cbNeverChanges;
CBChangeOnResize cbChangesOnResize;

HRESULT
BaseApp::init() {
  HRESULT hr = S_OK;

  // Create Swapchain and BackBuffer
  hr = m_swapchain.init(m_device, m_deviceContext, m_backBuffer, m_window);
  if (FAILED(hr)) {
    return hr;
  }

  // Create a Render Target View
  hr = m_renderTargetView.init(m_device,
    m_backBuffer,
    DXGI_FORMAT_R8G8B8A8_UNORM);
  if (FAILED(hr)) {
    return hr;
  }

  // Create a Depth Stencil texture
  hr = m_depthStencil.init(m_device,
    m_window.m_width,
    m_window.m_height,
    DXGI_FORMAT_D24_UNORM_S8_UINT,
    D3D11_BIND_DEPTH_STENCIL, 4, 0);
  if (FAILED(hr)) {
    return hr;
  }

  // Create a Depth Stencil View
  hr = m_depthStencilView.init(m_device,
    m_depthStencil,
    DXGI_FORMAT_D24_UNORM_S8_UINT);
  if (FAILED(hr)) {
    return hr;
  }

  // Setup the viewport
  m_viewport.init(m_window);

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
  hr = m_shaderProgram.init(m_device, "KerberosEngine.fx", Layout);
  if (FAILED(hr)) {
    return hr;
  }

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

  // Create index buffer
  unsigned int indices[] =
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

  MeshComponent MC;
  for (SimpleVertex vertex : vertices) {
    MC.m_vertex.push_back(vertex);
  }

  for (unsigned int index : indices) {
    MC.m_index.push_back(index);
  }

  MC.m_numVertex = MC.m_vertex.size();
  MC.m_numIndex = MC.m_index.size();

  hr = m_vertexBuffer.init(m_device, MC, D3D11_BIND_VERTEX_BUFFER);
  if (FAILED(hr)) {
    return hr;
  }

  hr = m_indexBuffer.init(m_device, MC, D3D11_BIND_INDEX_BUFFER);
  if (FAILED(hr)) {
    return hr;
  }

  // Create the constant buffers

    // bd.ByteWidth = sizeof(CBChangeOnResize);
  hr = m_neverChanges.init(m_device, sizeof(CBNeverChanges));
  if (FAILED(hr))
    return hr;

  // bd.ByteWidth = sizeof(CBChangesEveryFrame);
  hr = m_changeOnResize.init(m_device, sizeof(CBChangeOnResize));
  if (FAILED(hr))
    return hr;

  // Load the Texture
  hr = m_changesEveryFrame.init(m_device, sizeof(CBChangesEveryFrame));
  if (FAILED(hr))
    return hr;

  /*hr = D3DX11CreateShaderResourceViewFromFile(m_device.m_device,
                                              "seafloor.dds",
                                              nullptr,
                                              nullptr,
                                              &m_textureRV,
                                              nullptr);*/
  hr = m_textureRV.init(m_device, "seafloor.dds", DDS);
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
  hr = m_device.CreateSamplerState(&sampDesc, &g_pSamplerLinear);
  if (FAILED(hr))
    return hr;

  // Initialize the world matrices
  m_World = XMMatrixIdentity();

  // Initialize the view matrix
  XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
  XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  m_View = XMMatrixLookAtLH(Eye, At, Up);

  return S_OK;
}

void
BaseApp::update() {
  // Update our time
  static float t = 0.0f;
  if (m_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE)
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
  m_World = XMMatrixRotationY(t);

  // Modify the color
  m_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
  m_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
  m_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

  // Update variables that change once per frame
  cb.mWorld = XMMatrixTranspose(m_World);
  cb.vMeshColor = m_vMeshColor;
  m_changesEveryFrame.update(m_deviceContext, 0, nullptr, &cb, 0, 0);

  // Initialize the projection matrix
  m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, m_window.m_width / (float)m_window.m_height, 0.01f, 100.0f);

  cbNeverChanges.mView = XMMatrixTranspose(m_View);
  m_neverChanges.update(m_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);

  cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
  m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
}

void
BaseApp::render() {
  // Clear the back buffer
  float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha

  // Set Viewport
  m_viewport.render(m_deviceContext);

  // Set Render Target View
  m_renderTargetView.render(m_deviceContext, m_depthStencilView, 1, ClearColor);

  // Set Depth Stencil View
  m_depthStencilView.render(m_deviceContext);

  // Render the cube
  // Set Buffers and Shaders for pipeline
  m_shaderProgram.render(m_deviceContext);
  m_vertexBuffer.render(m_deviceContext, 0, 1);
  m_indexBuffer.render(m_deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);
  m_deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  // Set Constant Buffers and asign Shaders
  // g_deviceContext.m_deviceContext->VSSetShader(g_pVertexShader, NULL, 0);
  m_neverChanges.render(m_deviceContext, 0, 1);
  m_changeOnResize.render(m_deviceContext, 1, 1);
  m_changesEveryFrame.render(m_deviceContext, 2, 1);

  m_changesEveryFrame.render(m_deviceContext, 2, 1, true);
  m_textureRV.render(m_deviceContext, 0, 1);
  m_deviceContext.PSSetSamplers(0, 1, &g_pSamplerLinear);

  // Drwa
  m_deviceContext.DrawIndexed(36, 0, 0);

  // Present our back buffer to our front buffer
  m_swapchain.present();
}

void
BaseApp::destroy() {
  if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->ClearState();
  if (g_pSamplerLinear) g_pSamplerLinear->Release();

  m_textureRV.destroy();
  m_changeOnResize.destroy();
  m_changesEveryFrame.destroy();
  m_neverChanges.destroy();
  m_indexBuffer.destroy();
  m_vertexBuffer.destroy();
  m_shaderProgram.destroy();
  m_depthStencil.destroy();
  m_depthStencilView.destroy();
  m_renderTargetView.destroy();
  m_swapchain.destroy();
  m_deviceContext.destroy();
  m_device.destroy();
}

int
BaseApp::run(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPWSTR lpCmdLine,
  int nCmdShow,
  WNDPROC wndproc) {

  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  if (FAILED(m_window.init(hInstance, nCmdShow, wndproc)))
    return 0;

  if (FAILED(init())) {
    destroy();
    return 0;
  }

  // Main message loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message)
  {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else {
      update();
      render();
    }
  }

  destroy();

  return (int)msg.wParam;
}

LRESULT BaseApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;

  switch (message)
  {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;

  case WM_SIZE:
    if (m_swapchain.g_pSwapChain) {
      m_window.m_width = LOWORD(lParam);
      m_window.m_height = HIWORD(lParam);

      // Libera los recursos existentes
      m_renderTargetView.destroy();
      m_depthStencilView.destroy();
      m_depthStencil.destroy();
      m_backBuffer.destroy();

      // Redimensionar el swap chain
      HRESULT hr = m_swapchain.g_pSwapChain->ResizeBuffers(0,
        m_window.m_width,
        m_window.m_height,
        DXGI_FORMAT_R8G8B8A8_UNORM,
        0);
      if (FAILED(hr)) {
        MessageBox(hWnd, "Failed to resize swap chain buffers.", "Error", MB_OK);
        PostQuitMessage(0);
      }

      // **3. RECREAR EL BACK BUFFER**
      hr = m_swapchain.g_pSwapChain->GetBuffer(0,
        __uuidof(ID3D11Texture2D),
        reinterpret_cast<void**>(&m_backBuffer.m_texture));
      if (FAILED(hr)) {
        ERROR("SwapChain", "Resize", "Failed to get new back buffer");
        return hr;
      }

      // **4. RECREAR EL RENDER TARGET VIEW**
      hr = m_renderTargetView.init(m_device,
        m_backBuffer,
        DXGI_FORMAT_R8G8B8A8_UNORM);
      if (FAILED(hr)) {
        ERROR("RenderTargetView", "Resize", "Failed to create new RenderTargetView");
        return hr;
      }

      // **5. RECREAR EL DEPTH STENCIL VIEW**
      hr = m_depthStencil.init(m_device,
        m_window.m_width,
        m_window.m_height,
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        D3D11_BIND_DEPTH_STENCIL,
        4,
        0);
      if (FAILED(hr)) {
        ERROR("DepthStencil", "Resize", "Failed to create new DepthStencil");
        return hr;
      }

      hr = m_depthStencilView.init(m_device,
        m_depthStencil,
        DXGI_FORMAT_D24_UNORM_S8_UINT);
      if (FAILED(hr)) {
        ERROR("DepthStencilView", "Resize", "Failed to create new DepthStencilView");
        return hr;
      }

      // Actualizar el viewport
      m_viewport.init(m_window);

      // Actualizar la proyección
      m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, m_window.m_width / (float)m_window.m_height, 0.01f, 100.0f);
      CBChangeOnResize cbChangesOnResize;
      cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
      m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
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
