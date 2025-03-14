#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Swapchain.h"
#include "Texture.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "MeshComponent.h"
#include "Buffer.h"

class
  BaseApp {
public:
  /**
   * @brief Default constructor and destructor
   */
  BaseApp() = default;
  ~BaseApp() = default;

  /**
   * @brief Initializes the application by setting up the necessary resources.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT
    init();

  /**
   * @brief  Updates the application logic for each frame.
   */
  void
    update();

  /**
   * @brief Renders the elements on the window.
   */
  void
    render();

  /**
   * @brief Releases resources and elements before exiting to free memory.
   */
  void
    destroy();

  /**
   * @brief
   */
  HRESULT 
  ResizeWindow(HWND hWnd, LPARAM lParam);

  /**
  * @brief
  */
  void
  inputActionMap(float deltaTime);

  /**
  * @brief
  */
  void
  UpdateCamera();

  /**
   * @brief Runs the application from the main entry point.
   * @param hInstance Handle to the instance of the program.
   * @param hPrevInstance Handle to the previous instance.
   * @param lpCmdLine Command-line as a string.
   * @param nCmdShow Indicate how the window should be displayed.
   * @param wndproc Pointer to the window function for handling messages.
   */
  int
  run(HINSTANCE hInstance,
      HINSTANCE hPrevInstance,
      LPWSTR lpCmdLine,
      int nCmdShow,
      WNDPROC wndproc);

  LRESULT CALLBACK
  WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
  Window                              m_window;
  Device                              m_device;
  DeviceContext                       m_deviceContext;
  SwapChain                           m_swapchain;
  Texture                             m_backBuffer;
  Texture                             m_depthStencil;
  RenderTargetView                    m_renderTargetView;
  DepthStencilView                    m_depthStencilView;
  Viewport                            m_viewport;
  ShaderProgram                       m_shaderProgram;
  Buffer                              m_vertexBuffer;
  Buffer                              m_indexBuffer;
  Buffer                              m_neverChanges;
  Buffer                              m_changeOnResize;
  Buffer                              m_changesEveryFrame;
  Texture                             m_textureRV;

  ID3D11SamplerState* g_pSamplerLinear = NULL;
  XMMATRIX                            m_World;
  XMMATRIX                            m_View;
  XMMATRIX                            m_Projection;

  XMFLOAT3 position;
  XMFLOAT3 rotation;
  XMFLOAT3 scale;
  MeshComponent m_meshComponent;

  CBChangesEveryFrame cb;
  CBNeverChanges cbNeverChanges;
  CBChangeOnResize cbChangesOnResize;

  Camera m_camera;

public:
  bool keys[256] = { false };
  float m_speed = 0;
};