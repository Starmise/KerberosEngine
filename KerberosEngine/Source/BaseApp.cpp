#include "BaseApp.h"

XMFLOAT4                            m_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);

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

  hr = m_textureRV.init(m_device, "seafloor.dds", DDS);
  if (FAILED(hr))
    return hr;

  // Create the sample state
  hr = m_samplerState.init(m_device);
  if (FAILED(hr))
    return hr;

  // Initialize the world matrices
  scale.x = 1.0f;
  scale.y = 1.0f;
  scale.z = 1.0f;

  m_World = XMMatrixIdentity();

  // Initialize the view matrix
  XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
  XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  m_View = XMMatrixLookAtLH(Eye, At, Up);

  m_UI.init(m_window.m_hWnd, m_device.m_device, m_deviceContext.m_deviceContext);

  return S_OK;
}

void
BaseApp::update() {
  // Updates the UI
  m_UI.update();

  m_UI.GUITab("ImKerberos Test");
  m_UI.GUITab("Docking Test");
  m_UI.TransformGUI(*this);

  // Update our time
  static float t = 0.0f;
  if (m_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE)
  {
    t += (float)XM_PI * 0.0125f;
  }
  else {
    static DWORD dwTimeStart = 0;
    DWORD dwTimeCur = GetTickCount();
    if (dwTimeStart == 0)
      dwTimeStart = dwTimeCur;
    t = (dwTimeCur - dwTimeStart) / 1000.0f;
  }

  inputActionMap(t);

  rotation.y = t;
  rotation.x = t;
  rotation.z = t;

  // Update the rotation and color of the object
  XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);
  XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
  XMMATRIX traslationMatrix = XMMatrixTranslation(position.x, position.y, position.z);

  // Compose the final matrix in the orden: scale -> rotation -> scale
  m_World = scaleMatrix * rotationMatrix * traslationMatrix;

  // Update variables that change once per frame
  cb.mWorld = XMMatrixTranspose(m_World);

  m_vMeshColor = XMFLOAT4(
    // Modify the color
    m_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f,
    m_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f,
    m_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f,
    1.0f
  );

  // Update constant buffers
  cb.vMeshColor = m_vMeshColor;
  m_changesEveryFrame.update(m_deviceContext, 0, nullptr, &cb, 0, 0);

  // Initialize the projection matrix
  float FOV = XMConvertToRadians(90.0f);
  //m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, m_window.m_width / (float)m_window.m_height, 0.01f, 100.0f);
  m_Projection = XMMatrixPerspectiveFovLH(FOV, m_window.m_width / (float)m_window.m_height, 0.01f, 10000.0f);

  UpdateCamera();

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
  m_samplerState.render(m_deviceContext, 0, 1);

  // Drawing
  m_deviceContext.DrawIndexed(MC.m_index.size(), 0, 0);

  // Render the UI
  m_UI.render();

  // Present our back buffer to our front buffer
  m_swapchain.present();
}

void
BaseApp::destroy() {
  if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->ClearState();
  
  m_samplerState.destroy();
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
  m_UI.destroy();
}

HRESULT
BaseApp::ResizeWindow(HWND hWnd, LPARAM lParam)
{
  // Validar que Swapchain exista
  if (m_swapchain.g_pSwapChain) {
    // Destruir los recursos anteriores del RTV, DS, DSV
    m_renderTargetView.destroy();
    m_depthStencil.destroy();
    m_depthStencilView.destroy();
    m_backBuffer.destroy();

    // Redimensionar los datos del ancho y alto de la ventana
    m_window.m_width = LOWORD(lParam);
    m_window.m_height = HIWORD(lParam);

    // Redimensionar el buffer del swapchain
    HRESULT hr = m_swapchain.g_pSwapChain->ResizeBuffers(0,
      m_window.m_width,
      m_window.m_height,
      DXGI_FORMAT_R8G8B8A8_UNORM,
      0);
    // Validación del HRESULT
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "SwapChain", "Failed to resize buffers");
      return hr;
    }

    // Recrear el backBuffer
    hr = m_swapchain.g_pSwapChain->GetBuffer(0,
      __uuidof(ID3D11Texture2D),
      reinterpret_cast<void**>(&m_backBuffer.m_texture));
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "ResizeWindow", "Failed to recreate back buffer");
      return hr;
    }

    // Recrear el render target view
    hr = m_renderTargetView.init(m_device,
      m_backBuffer,
      DXGI_FORMAT_R8G8B8A8_UNORM);
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "Render Target View", "Failed to create Render Target View");
      return hr;
    }

    // Recrear el depth stencil
    hr = m_depthStencil.init(m_device,
      m_window.m_width,
      m_window.m_height,
      DXGI_FORMAT_D24_UNORM_S8_UINT,
      D3D11_BIND_DEPTH_STENCIL,
      4,
      0);
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "Depth Stencil", "Failed to create Depth Stencil");
      return hr;
    }

    // Recrear el depth stencil view
    hr = m_depthStencilView.init(m_device,
      m_depthStencil,
      DXGI_FORMAT_D24_UNORM_S8_UINT);
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "Depth Stencil View", "Failed to create new Depth Stencil View");
      return hr;
    }

    // Actualizar el viewport
    m_viewport.init(m_window);

    // Actualizar la proyección
    m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, m_window.m_width / (float)m_window.m_height, 0.01f, 100.0f);
    cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
    m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
  }
}

void
BaseApp::inputActionMap(float deltaTime) {
  float m_speed = 0.001f;
  float moveSpeedCamera = 0.01f;

  if (keys[87]) { // 119 minuscula (W)
    position.y += m_speed * deltaTime;
  }
  if (keys[83]) { // 115 minuscula (S)
    position.y -= m_speed * deltaTime;
  }
  if (keys[65]) { // 97 minuscula (A)
    position.x -= m_speed * deltaTime;
  }
  if (keys[68]) { // 100 minuscula (D)
    position.x += m_speed * deltaTime;
  }
  if (keys[81]) { // 113 minuscula (Q)
    position.z -= m_speed * deltaTime;
  }
  if (keys[69]) { // 101 minuscula (E)
    position.z += m_speed * deltaTime;
  }

  XMVECTOR pos = XMLoadFloat3(&m_camera.position);
  XMVECTOR forward = XMLoadFloat3(&m_camera.forward);
  XMVECTOR right = XMLoadFloat3(&m_camera.right);

  if (keys['I']) pos += forward * moveSpeedCamera;
  if (keys['K']) pos -= forward * moveSpeedCamera;
  if (keys['J']) pos -= right * moveSpeedCamera;
  if (keys['L']) pos += right * moveSpeedCamera;

  XMStoreFloat3(&m_camera.position, pos);
}

void
BaseApp::UpdateCamera() {
  // Convertir la dirección a vectores normalizados
  XMVECTOR pos = XMLoadFloat3(&m_camera.position);
  XMVECTOR dir = XMLoadFloat3(&m_camera.forward);
  XMVECTOR up = XMLoadFloat3(&m_camera.up);

  // Calcular la nueva vista
  m_View = XMMatrixLookAtLH(pos, pos + dir, up);

  // Transponer y actualizar el buffer de la vista
  cbNeverChanges.mView = XMMatrixTranspose(m_View);
  m_neverChanges.update(m_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
}

void 
BaseApp::RotateCamera(int mouseX, int mouseY) {
  float offsetX = (mouseX - lastX) * sensitivity;
  float offsetY = (mouseY - lastY) * sensitivity;
  lastX = mouseX;
  lastY = mouseY;

  m_camera.yaw += offsetX;
  m_camera.pitch += offsetY;

  // Limitar la inclinación de la cámara
  if (m_camera.pitch > 1.5f) m_camera.pitch = 1.5f;
  if (m_camera.pitch < -1.5f) m_camera.pitch = -1.5f;

  // Recalcular la dirección hacia adelante
  XMVECTOR forward = XMVectorSet(
    cosf(m_camera.yaw) * cosf(m_camera.pitch),
    sinf(m_camera.pitch),
    sinf(m_camera.yaw) * cosf(m_camera.pitch),
    0.0f
  );

  XMVECTOR right = XMVector3Cross(forward, XMLoadFloat3(&m_camera.up));

  XMStoreFloat3(&m_camera.forward, XMVector3Normalize(forward));
  XMStoreFloat3(&m_camera.right, XMVector3Normalize(right));
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