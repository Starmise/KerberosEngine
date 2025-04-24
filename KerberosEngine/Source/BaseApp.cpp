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

  // Create the constant buffers
  hr = m_neverChanges.init(m_device, sizeof(CBNeverChanges));
  if (FAILED(hr))
    return hr;

  hr = m_changeOnResize.init(m_device, sizeof(CBChangeOnResize));
  if (FAILED(hr))
    return hr;

  // Initialize the view matrix
  XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
  XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  m_View = XMMatrixLookAtLH(Eye, At, Up);

  m_UI.init(m_window.m_hWnd, m_device.m_device, m_deviceContext.m_deviceContext);


  // Set model actor
  // Load Textures
  Texture banda;
  banda.init(m_device, "Textures/Koro/banda.png", ExtensionType::PNG);

  Texture color;
  color.init(m_device, "Textures/Koro/Color.png", ExtensionType::PNG);

  Texture color_ojos;
  color_ojos.init(m_device, "Textures/Koro/color_ojos.png", ExtensionType::PNG);

  Texture color_ojos_copia;
  color_ojos_copia.init(m_device, "Textures/Koro/color_ojos_copia.png", ExtensionType::PNG);

  m_default.init(m_device, "Textures/Default.png", ExtensionType::PNG);

  m_koroTextures.push_back(banda);
  m_koroTextures.push_back(color);
  m_koroTextures.push_back(color_ojos);
  m_koroTextures.push_back(color_ojos_copia);
  m_koroTextures.push_back(m_default);

  m_mloader.LoadFBXModel("Models/Koro.fbx");
  AKoro = EngineUtilities::MakeShared<Actor>(m_device);
  if (!AKoro.isNull()) {
    // Init Transform
    AKoro->getComponent<Transform>()->setTransform(EngineUtilities::Vector3(2.0f, 1.0f, 1.0f),
                                                  EngineUtilities::Vector3(XM_PI / -2.0f, 0.0f, XM_PI / 2.0f),
                                                  EngineUtilities::Vector3(1.0f, 1.0f, 1.0f));
    // Init Actor Mesh
    AKoro->setMesh(m_device, m_mloader.meshes);
    // Init Actor Textures
    AKoro->setTextures(m_koroTextures);

    std::string msg = AKoro->getName() + "Actor accessed successfully.";
    MESSAGE("Actor", "Actor", msg.c_str());
  }
  else {
    MESSAGE("Actor", "Actor", "Actor resource not found")
  }

  Texture body;
  body.init(m_device, "Textures/jonesy/M_Med_Soldier_Body_01_C.tga.png", ExtensionType::PNG);
  Texture bodyN;
  bodyN.init(m_device, "Textures/jonesy/M_Med_Soldier_Body_01_N.tga.png", ExtensionType::PNG);
  Texture head;
  head.init(m_device, "Textures/jonesy/M_Med_Soldier_Head_01_C.tga.png", ExtensionType::PNG);
  Texture headN;
  headN.init(m_device, "Textures/jonesy/M_Med_Soldier_Head_01_N.tga.png", ExtensionType::PNG);
  Texture hair;
  hair.init(m_device, "Textures/jonesy/M_SML_Survivor_Hair_02_d.tga.png", ExtensionType::PNG);

  m_jonesyTextures.push_back(body);
  m_jonesyTextures.push_back(bodyN);
  m_jonesyTextures.push_back(head);
  m_jonesyTextures.push_back(headN);
  m_jonesyTextures.push_back(hair);

  m_mloader2.LoadFBXModel("Models/Jonesy FBX Export3.fbx");
  AJones = EngineUtilities::MakeShared<Actor>(m_device);
  if (!AJones.isNull()) {
    // Init Transform
    AJones->getComponent<Transform>()->setTransform(EngineUtilities::Vector3(-3.0, -3.0f, 0.5f),
      EngineUtilities::Vector3(0.0f, 1.3f, 0.0f),
      EngineUtilities::Vector3(0.05f, 0.05f, 0.05f));
    // Init Actor Mesh
    AJones->setMesh(m_device, m_mloader2.meshes);
    // Init Actor Textures
    AJones->setTextures(m_jonesyTextures);

    std::string msg = AJones->getName() + "Actor accessed successfully.";
    MESSAGE("Actor", "Actor", msg.c_str());
  }
  else {
    MESSAGE("Actor", "Actor", "Actor resource not found")
  }

  m_mloader3.LoadOBJ_model("Models/untitled.obj");
  MESSAGE("ModelLoader", "Pistol", ("Meshes loaded: " + std::to_string(m_mloader3.meshes.size())).c_str());

  m_pistolTextures.clear();
  for (size_t i = 0; i < m_mloader3.meshes.size(); ++i) {
    Texture pistol;
    HRESULT texResult = pistol.init(m_device, "Textures/pistol/T_Pistol_HandCannon_D.png", PNG);

    if (FAILED(texResult)) {
      ERROR("Texture", "T_Pistol_HandCannon_D", "Failed to load texture for submesh.");
    }
    m_pistolTextures.push_back(pistol);
  }

  APistol = EngineUtilities::MakeShared<Actor>(m_device);
  if (!APistol.isNull()) {
    // Init Transform
    APistol->getComponent<Transform>()->setTransform(EngineUtilities::Vector3(-5.0, -1.0f, 0.5f),
      EngineUtilities::Vector3(0.0f, 1.3f, 0.0f),
      EngineUtilities::Vector3(4.5f, 4.5f, 4.5f));
    // Init Actor Mesh
    APistol->setMesh(m_device, m_mloader3.meshes);
    // Init Actor Textures
    APistol->setTextures(m_pistolTextures);

    MESSAGE("Actor", "APistol", (APistol->getName() + " - Actor accessed successfully.").c_str());
  }
  else {
    ERROR("Actor", "APistol", "Failed to create actor.");
  }

  return S_OK;
}

void
BaseApp::update() {
  // Updates the UI
  m_UI.update();

  m_UI.GUITab("ImKerberos Test");
  m_UI.GUITab("Docking Test");
 // m_UI.TransformGUI(*AKoro->getComponent<Transform>());
  m_UI.TransformGUI(*APistol->getComponent<Transform>());

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

  // Initialize the projection matrix
  float FOV = XMConvertToRadians(90.0f);
  m_Projection = XMMatrixPerspectiveFovLH(FOV, m_window.m_width / (float)m_window.m_height, 0.01f, 10000.0f);

  UpdateCamera();

  cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
  m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

  AKoro->update(0, m_deviceContext);
  AJones->update(0, m_deviceContext);
  APistol->update(0, m_deviceContext);
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
  m_shaderProgram.render(m_deviceContext);

  // Render the models
  AKoro->render(m_deviceContext);
  AJones->render(m_deviceContext);
  APistol->render(m_deviceContext);

  // Set Constant Buffers and asign Shaders
  m_neverChanges.render(m_deviceContext, 0, 1);
  m_changeOnResize.render(m_deviceContext, 1, 1);

  // Drawing
  //m_deviceContext.DrawIndexed(MC.m_index.size(), 0, 0);

  // Render the UI
  m_UI.render();

  // Present our back buffer to our front buffer
  m_swapchain.present();
}

void
BaseApp::destroy() {
  if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->ClearState();
  AKoro->destroy();

  m_changeOnResize.destroy();
  m_changesEveryFrame.destroy();
  m_neverChanges.destroy();
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

  //if (keys[87]) { // 119 minuscula (W)
  //  position.y += m_speed * deltaTime;
  //}
  //if (keys[83]) { // 115 minuscula (S)
  //  position.y -= m_speed * deltaTime;
  //}
  //if (keys[65]) { // 97 minuscula (A)
  //  position.x -= m_speed * deltaTime;
  //}
  //if (keys[68]) { // 100 minuscula (D)
  //  position.x += m_speed * deltaTime;
  //}
  //if (keys[81]) { // 113 minuscula (Q)
  //  position.z -= m_speed * deltaTime;
  //}
  //if (keys[69]) { // 101 minuscula (E)
  //  position.z += m_speed * deltaTime;
  //}

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