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
#include "SamplerState.h"
#include "UserInterface.h"
#include "ModelLoader.h"
#include "ECS/Actor.h"

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
   * @brief Resizes the application window and updates the correspondant rendering resources.
   * @param hWnd Handle to the application window.
   * @param lParam Contains the new width and height of the window.
   */
  HRESULT
  ResizeWindow(HWND hWnd, LPARAM lParam);

  /**
  * @brief Handles input actions and updates object movement based on the key pressed.
  * @param deltaTime Time elapsed since the last frame, used for smooth movement.
  */
  void
  inputActionMap(float deltaTime);

  /**
  * @brief  Updates the camera view matrix based on its current position and direction.
  */
  void
  UpdateCamera();

  /**
  * @brief Rotates the camera based on mouse movement. 
  * @param mouseX The current X position of the mouse.
  * @param mouseY The current Y position of the mouse.
  */
  void
  RotateCamera(int mouseX, int mouseY);

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
  Buffer                              m_neverChanges;
  Buffer                              m_changeOnResize;
  Buffer                              m_changesEveryFrame;
  UserInterface                       m_UI;

  Texture m_default;
  ModelLoader                         m_mloader;
  EngineUtilities::TSharedPointer<Actor> AKoro;
  std::vector<Texture>                m_koroTextures;

  ModelLoader                         m_mloader2;
  EngineUtilities::TSharedPointer<Actor> AMorgana;
  std::vector<Texture>                m_morganaTextures;

  ModelLoader                         m_mloader3;
  EngineUtilities::TSharedPointer<Actor> APistol;
  std::vector<Texture>                m_pistolTextures;

  ModelLoader                         m_mloader4;
  EngineUtilities::TSharedPointer<Actor> ADigimon;
  std::vector<Texture>                m_digiTextures;

  ModelLoader                         m_mloader5;
  EngineUtilities::TSharedPointer<Actor> ACerb;
  std::vector<Texture>                m_cerbTextures;

  XMMATRIX                            m_View;
  XMMATRIX                            m_Projection;

  CBNeverChanges cbNeverChanges;
  CBChangeOnResize cbChangesOnResize;

  Camera m_camera;
  std::vector<EngineUtilities::TSharedPointer<Actor>> m_actors;

public:
  bool keys[256] = { false };
  int lastX;
  int lastY;
  float sensitivity = 0.01f;
  bool mouseLeftDown = false;
};